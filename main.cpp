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
void drawMinutes(Point center, int hour);
void drawSeconds(Point center, int hour);

int main()
{

  initwindow(SIZE, SIZE, "ANALOG CLOCK");

  while (!kbhit())

  {

    drawClock();

    Point center = {SIZE / 2, SIZE / 2};
    Point current, current2;

    time_t now = time(0);

    tm *ltm = localtime(&now);

    system("cls");

    cout << ltm->tm_hour << " " << ltm->tm_min;

    drawHour(center, ltm->tm_hour);
    int raza1 = 150, raza2 = 200;

    float unghi1, unghi2;

    for (unghi1 = 0; unghi1 <= 2 * PI; unghi1 += 2 * PI / 60) // minutar
    {
      current.x = center.x + raza1 * cos(unghi1 - PI / 2);
      current.y = center.y + raza1 * sin(unghi1 - PI / 2);

      drawLine(center, current, 3);

      for (unghi2 = 0; unghi2 <= 2 * PI; unghi2 += 2 * PI / 60) // secundar
      {
        current2.x = center.x + raza2 * cos(unghi2 - PI / 2);
        current2.y = center.y + raza2 * sin(unghi2 - PI / 2);

        drawLine(center, current2, 1);

        delay(1000); // puneti 1000 ca sa fie o secunda

        eraseLine(center, current2, 1);
      }
      eraseLine(center, current, 3);
    }

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

void drawLine(Point A, Point B, int size)
{
  setcolor(WHITE);
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
               250 - 100 * cos(hour * PI / 6)};

  drawLine(center, aux, 3);
}

void drawMinutes(Point center, int hour)
{

  Point aux = {250 + 190 * sin(hour * PI / 30),
               250 - 190 * cos(hour * PI / 30)};

  drawLine(center, aux, 3);
}

void drawSeconds(Point center, int hour)
{

  Point aux = {250 + 150 * sin(hour * PI / 30),
               250 - 150 * cos(hour * PI / 30)};

  drawLine(center, aux, 3);
}
