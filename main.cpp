
#include <graphics.h>
#include <iostream>
#include <cmath>
#include <ctime>

#define PI 3.1415
#define SIZE 500

struct Point
{
  double x, y;
};

struct option
{
  char *label = "";
  int id;
};

char *intToString(int number);
void drawClock();
void drawLine(Point A, Point B, int size, int color = WHITE);
void eraseLine(Point A, Point B, int size);
void drawHour(Point center, int hour);
void drawMinutes(Point center, int min);
void drawSeconds(Point center, int sec);
void analogicClock();
void showOptions();
void drawOptionCard(option menuOption, int id);

using namespace std;

int main()
{

  initwindow(SIZE, SIZE, "clock");

  while (!kbhit())
  {

    showOptions();
  }

  closegraph();

  return 0;
}

void drawOptionCard(option menuOption, int id)
{

  Point start = {SIZE / 2 * (id % 2),
                 SIZE / 2 * (id % 2)};

  Point end = {SIZE / 2 * (id % 2 + 1),
               SIZE / 2 * (id % 2 + 1)};

  outtextxy((start.x + end.x) / 2, (start.y + end.y) / 2, menuOption.label);
}

void showOptions()
{

  option options[] = {
      {"DIGITAL CLOCK", 0},
      {"ANALOG CLOCK", 1},
      {"ALARM", 2},
      {"TIMER", 3},
  };

  for (int i= 0; i < 4; i++)
  {
    drawOptionCard(options[i], i);
  }
}

void analogicClock()
{
  Point center = {SIZE / 2, SIZE / 2};

  while (!kbhit())
  {
    drawClock();

    time_t now = time(0);

    tm *ltm = localtime(&now);

    drawHour(center, ltm->tm_hour);
    drawMinutes(center, ltm->tm_min);
    drawSeconds(center, ltm->tm_sec);

    delay(1000);
    cleardevice();
  }
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

void drawLine(Point A, Point B, int size, int color)
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

void drawHour(Point center, int hour)
{

  Point aux = {250 + 150 * sin(hour * PI / 6),
               250 - 150 * cos(hour * PI / 6)};

  drawLine(center, aux, 3, RED);
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
