
#include <graphics.h>
#include <iostream>
#include <cmath>
#include <ctime>
#include<conio.h>
#include<dos.h>

#define PI 3.1415
#define SIZE 800
union REGS in, out;

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
int initmouse(); void showmouseptr(); void getmousepos(int *button, int *x, int *y);

    using namespace std;
option options[] = {
      {"DIGITAL CLOCK", 0},
      {"ANALOG CLOCK", 1},
      {"ALARM", 2},
      {"TIMER", 3},
  };

int main()
{
  int status, button, x, y;


  initwindow(SIZE, SIZE, "clock");
  status = initmouse();
  showmouseptr();

  while (!kbhit())
  {
    getmousepos(&button, &x, &y);
    if (button == 1)
    {
      cout << x << ' ' << y << endl;
    }
    showOptions();
    getmouseclick(WM_LBUTTONDOWN, x, y);
    cout << x << ' ' << y;
  }

 // closegraph();

  return 0;
}

void drawOptionCard(option menuOption, int id)
{

  Point start = {0, 0};
  Point end = {0, 0};

  if (id == 0)
  {
    start = {0, 0};
    end = {SIZE / 2, SIZE / 2};
  }
  if (id == 1)
  {
    start = {0, SIZE / 2 + 1};
    end = {SIZE / 2, SIZE};
  }
  if (id == 2)
  {
    start = {SIZE / 2 + 1, 0};
    end = {SIZE, SIZE / 2};
  }
  if (id == 3)
  {
    start = {SIZE / 2 + 1, SIZE / 2 + 1};
    end = {SIZE, SIZE};
  }

  setcolor(WHITE);
  rectangle(start.x, start.y, end.x, end.y);
  outtextxy((start.x + end.x) / 2, (start.y + end.y) / 2, menuOption.label);
}

void showOptions()
{

  for (int i = 0; i < 4; i++)
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

int initmouse()
{

  in.x.ax = 0;
  int86(0X33, &i, &o);
  return (out.x.ax);
}

void showmouseptr()
{
  in.x.ax = 1;
  int86(0X33, &i, &o);
}

void getmousepos(int *button, int *x, int *y)
{
  in.x.ax = 3;
  int86(0X33, &i, &o);

  *button = out.x.bx;
  *x = out.x.cx;
  *y = out.x.dx;
}
