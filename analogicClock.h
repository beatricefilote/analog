#ifndef ANALOGIC_H
#define ANALOGIC_H

#include <graphics.h>

struct Point
{
  double x, y;
};

char *intToString(int number);
void drawClock();
void drawLine(Point A, Point B, int size, int color = WHITE);
void eraseLine(Point A, Point B, int size);
void drawHour(Point center, int hour);
void drawMinutes(Point center, int min);
void drawSeconds(Point center, int sec);

#endif // !ANALOGIC_H