#include "analogicClock.h"
#include <graphics.h>
#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

int main()
{

  int gd = DETECT, gm;

  initWindow(SIZE, SIZE, "clock");

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

  closegraph();

  return 0;
}
