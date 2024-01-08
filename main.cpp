#include <graphics.h>
#include <iostream>
#include <cmath>
#include <ctime>
#include <tuple>

#define PI 3.1415
#define SIZE 500

using namespace std;

struct Point
{
  double x, y;
};

char *intToString(int number);
void drawClock();
void drawLine(Point A, Point B, int size);
void eraseLine(Point A, Point B, int size);
void drawHour(Point center, int hour);
void drawMinutes(Point center, int min);
void drawSeconds(Point center, int sec);

int main()
{

  initwindow(SIZE, SIZE, "ANALOG CLOCK");
  drawClock();

  Point center = {SIZE / 2, SIZE / 2};

  while (!kbhit())
  {

    time_t now = time(0);

    tm *ltm = localtime(&now);

    drawHour(center, ltm->tm_hour);
    drawMinutes(center, ltm->tm_min);
    drawSeconds(center, ltm->tm_sec);

    delay(1000);
  }

  closegraph();

  return 0;
}

char *intToString(int number)
{
  // Determine the length of the integer when converted to string
  int length = snprintf(NULL, 0, "%d", number);

  // Allocate memory for the string
  char *result = (char *)malloc(length + 1);

  // Convert the integer to string and store in result
  snprintf(result, length + 1, "%d", number);

  return result;
}

void drawClock()
{
  cleardevice();

  setcolor(WHITE);

  circle(SIZE / 2, SIZE / 2, 220);

  circle(SIZE / 2, SIZE / 2, 5);

  for (int i = 1; i <= 12; i++)
  {
    outtextxy(250 + 200 * sin(i * PI / 6) - 5, 250 - 200 * cos(i * PI / 6), intToString(i));
  }
}

void drawLine(Point A, Point B, int size, int color = WHITE)
{

  setcolor(color);
  setlinestyle(0, 0, size);
  line(A.x, A.y, B.x, B.y);
}
void eraseLine(Point A, Point B, int size)
{
  setcolor(BLACK);
  setlinestyle(0, 0, size);
  line(A.x, A.y, B.x, B.y);
}

void drawHour(Point center, int hour, )
{

  Point aux = {250 + 150 * sin(hour * PI / 6),
               250 - 150 * cos(hour * PI / 6)};

  drawLine(center, aux, 3);
}

void drawMinutes(Point center, int min)
{

  Point aux = {250 + 190 * sin(min * PI / 30),
               250 - 190 * cos(min * PI / 30)};

  drawLine(center, aux, 3);
}

void drawSeconds(Point center, int sec)
{

  Point aux = {250 + 150 * sin(sec * PI / 30),
               250 - 150 * cos(sec * PI / 30)};

  drawLine(center, aux, 3);
}
