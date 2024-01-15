#include <iostream>
#include <chrono>
#include <ctime>
#include <cstring>
#include <conio.h> // Pentru getch()
#include <graphics.h>
#include <cmath>
#define PI 3.1415
#define SIZE 500

using namespace std;
using namespace chrono;

struct Alarm
{
  char an[256], luna[256], zi[256], ora[256], minut[256], secunda[256];
};
struct Point
{
  double x, y; // voi avea nevoie pt a trasa liniile la ceasul analogic
};
int charToInt(char s[]) // converteste un sir la un nr
{
  int x = 0;
  unsigned int lg = strlen(s);
  for (unsigned int i = 0; i < lg; i++)
    x = x * 10 + (int)(s[i] - '0');
  return x;
}
/*
char *intToString(int number) //converteste un nr la un sir//
{

    int length = snprintf(NULL, 0, "%d", number);
    char *result = (char *)malloc(length + 1);
    snprintf(result, length + 1, "%d", number);
    return result;
}
*/
void afisareWakeUp(int x, int y)
{
  setcolor(RED);
  settextstyle(EUROPEAN_FONT, 0, 4);
  outtextxy(x, y, "WAKE UP!!");
  setcolor(WHITE);
}

void AfisareCeasDigital(const Alarm &alarm, char alarma[], int i, int &ore, int &minute)
{

  /*
  int w = GetSystemMetrics(SM_CXSCREEN);
  int h = GetSystemMetrics(SM_CYSCREEN);
  */
  initwindow(1000, 500, "Ceas digital");
  settextstyle(EUROPEAN_FONT, 0, 5);

  do
  {
    cleardevice();
    auto now = system_clock::to_time_t(system_clock::now()) + ore * 3600 * (-1) + minute * 60 * (-1);
    settextstyle(EUROPEAN_FONT, 0, 6);
    outtextxy(10, 50, ctime(&now));

    if (i != 0)
    {

      strcpy(alarma, alarm.luna);
      strcat(alarma, " ");
      strcat(alarma, alarm.zi);
      strcat(alarma, " ");
      strcat(alarma, alarm.ora);
      strcat(alarma, ":");
      strcat(alarma, alarm.minut);
      strcat(alarma, ":");
      strcat(alarma, alarm.secunda);
      strcat(alarma, " ");
      strcat(alarma, alarm.an);

      settextstyle(EUROPEAN_FONT, 0, 4);

      outtextxy(10, 200, "Alarm set for: ");
      outtextxy(250, 200, alarma);
      if ((strncmp(ctime(&now) + 4, alarm.luna, 3) == 0) && (strncmp(ctime(&now) + 8, alarm.zi, 2) == 0) && (strncmp(ctime(&now) + 11, alarm.ora, 2) == 0) && (strncmp(ctime(&now) + 14, alarm.minut, 2) == 0) && (strncmp(ctime(&now) + 20, alarm.an, 4) == 0))

      {

        afisareWakeUp(10, 300);

        Beep(333, 333);
      }
    }

    delay(1000);
  } while (!kbhit());

  getch();
  closegraph();
}
bool doar_cifre(char s[])
{
  int j;
  for (j = 0; j < strlen(s); j++)
  {
    if (isdigit(s[j]) == false)
      return false;
  }
  return true;
}
bool verificare_an(char s[])
{
  int aux;
  aux = charToInt(s);
  if (aux >= 2024 && aux <= 2025)
    return true;
  else
    return false;
}
bool verificare_luna(char luna[])
{
  int aux;
  aux = charToInt(luna);
  if (aux >= 1 && aux <= 12)
  {

    if (aux == 1)
      strcpy(luna, "Jan");
    if (aux == 2)
      strcpy(luna, "Feb");
    if (aux == 3)
      strcpy(luna, "Mar");
    if (aux == 4)
      strcpy(luna, "Apr");
    if (aux == 5)
      strcpy(luna, "May");
    if (aux == 6)
      strcpy(luna, "Jun");
    if (aux == 7)
      strcpy(luna, "Jul");
    if (aux == 8)
      strcpy(luna, "Aug");
    if (aux == 9)
      strcpy(luna, "Sep");
    if (aux == 10)
      strcpy(luna, "Oct");
    if (aux == 11)
      strcpy(luna, "Nov");
    if (aux == 12)
      strcpy(luna, "Dec");
    return true;
  }
  return false;
}
bool verificare_zi(char an[], char luna[], char zi[])
{
  int auxa;
  int auxl;
  int auxz;
  auxa = charToInt(an);
  auxl = charToInt(luna);
  auxz = charToInt(zi);
  if (auxl == 1 || auxl == 3 || auxl == 5 || auxl == 7 || auxl == 8 || auxl == 10 || auxl == 12)
  {
    if (auxz >= 1 && auxz <= 31)
      return true;
    return false;
  }
  else if (auxl == 4 || auxl == 6 || auxl == 9 || auxl == 11)
  {
    if (auxz >= 1 && auxz <= 30)
      return true;
    else
      return false;
  }
  else if (auxl == 2)
  {
    if (auxa % 4 == 0 && auxa % 400 == 0)
    {
      if (auxz >= 1 && auxz <= 29)
        return true;
      return false;
    }
    else if (auxz >= 1 && auxz <= 28)
      return true;
    return false;
  }
}
bool verificare_ora(char ora[])
{
  int aux;
  aux = charToInt(ora);
  if (aux >= 0 && aux <= 23)
    return true;
  else
    return false;
}
bool verificare_minut(char minut[])
{
  int aux;
  aux = charToInt(minut);
  if (aux >= 0 && aux <= 59)
    return true;
  return false;
}
void AdaugareAlarme(Alarm v[], int &i)
{
  i++;
  cout << "Introduceti anul: ";
  cin.getline(v[i].an, 256);
  while (v[i].an[0] == NULL)
  {
    cin.getline(v[i].an, 256);
  }
  while ((verificare_an(v[i].an)) == false || (doar_cifre(v[i].an)) == false)
  {
    cout << "Date nevalide!"
         << " "
         << "Introduceti din nou anul: ";
    cin.getline(v[i].an, 256);
  }

  cout << "Introduceti luna: ";
  cin.getline(v[i].luna, 256);
  while (v[i].luna[0] == NULL)
  {
    cin.getline(v[i].luna, 256);
  }
  while ((doar_cifre(v[i].luna)) == false || (verificare_luna(v[i].luna)) == false)
  {
    cout << "Date nevalide!"
         << " "
         << "Introduceti din nou luna: ";
    cin.getline(v[i].luna, 256);
  }
  cout << "Introduceti ziua: ";
  cin.getline(v[i].zi, 256);
  while (v[i].zi[0] == NULL)
  {
    cin.getline(v[i].zi, 256);
  }
  while ((verificare_zi(v[i].an, v[i].luna, v[i].zi)) == false || (doar_cifre(v[i].zi)) == false)
  {
    cout << "Date nevalide!"
         << " "
         << "Introduceti din nou ziua: ";
    cin.getline(v[i].zi, 256);
  }

  cout << "Introduceti ora: ";
  cin.getline(v[i].ora, 256);
  while (v[i].ora[0] == NULL)
  {
    cin.getline(v[i].ora, 256);
  }
  while ((verificare_ora(v[i].ora)) == false || (doar_cifre(v[i].ora)) == false)
  {
    cout << "Date nevalide!"
         << " "
         << "Introduceti din nou ora: ";
    cin.getline(v[i].ora, 256);
  }

  cout << "Introduceti minutul: ";
  cin.getline(v[i].minut, 256);
  while (v[i].minut[0] == NULL)
  {
    cin.getline(v[i].minut, 256);
  }
  while ((verificare_minut(v[i].minut)) == false || (doar_cifre(v[i].minut)) == false)
  {
    cout << "Date nevalide!"
         << " "
         << "Introduceti din nou minutul: ";
    cin.getline(v[i].minut, 256);
  }

  v[i].secunda[0] = '0';
  v[i].secunda[1] = '0';
  v[i].secunda[2] = NULL;
  cout << "Alarm " << i << " set." << endl;
}
void drawClock()
{
  cleardevice();

  setcolor(WHITE);

  circle(SIZE / 2, SIZE / 2, 220); // cadran ceas

  circle(SIZE / 2, SIZE / 2, 5); // mijloc

  outtextxy(250 + 200 * sin(1 * PI / 6) - 5, 250 - 200 * cos(1 * PI / 6), "1");
  outtextxy(250 + 200 * sin(2 * PI / 6) - 5, 250 - 200 * cos(2 * PI / 6), "2");
  outtextxy(250 + 200 * sin(3 * PI / 6) - 5, 250 - 200 * cos(3 * PI / 6), "3");
  outtextxy(250 + 200 * sin(4 * PI / 6) - 5, 250 - 200 * cos(4 * PI / 6), "4");
  outtextxy(250 + 200 * sin(5 * PI / 6) - 5, 250 - 200 * cos(5 * PI / 6), "5");
  outtextxy(250 + 200 * sin(6 * PI / 6) - 5, 250 - 200 * cos(6 * PI / 6), "6");
  outtextxy(250 + 200 * sin(7 * PI / 6) - 5, 250 - 200 * cos(7 * PI / 6), "7");
  outtextxy(250 + 200 * sin(8 * PI / 6) - 5, 250 - 200 * cos(8 * PI / 6), "8");
  outtextxy(250 + 200 * sin(9 * PI / 6) - 10, 250 - 200 * cos(9 * PI / 6), "9");
  outtextxy(250 + 200 * sin(10 * PI / 6) - 10, 250 - 200 * cos(10 * PI / 6), "10");
  outtextxy(250 + 200 * sin(11 * PI / 6) - 10, 250 - 200 * cos(11 * PI / 6), "11");
  outtextxy(250 + 200 * sin(12 * PI / 6) - 5, 250 - 200 * cos(12 * PI / 6), "12");
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

void drawHour(Point center, int hour) // 12 ore=> unghi de 30 grade intre ele => 12*30=2pi =>pi/6 pt fiecare ora
{

  Point aux = {250 + 130 * sin(hour * PI / 6),
               250 - 130 * cos(hour * PI / 6)};

  drawLine(center, aux, 3, RED);
}

void drawMinutes(Point center, int min) // 360/60min=>6 grade de fiec=>pi/30
{

  Point aux = {250 + 150 * sin(min * PI / 30),
               250 - 150 * cos(min * PI / 30)};

  drawLine(center, aux, 3, WHITE);
}

void drawSeconds(Point center, int sec) // la fel ca la min, dar am alte coordonate x, y (din cauza razelor=sec e cel mai lung)
{

  Point aux = {250 + 180 * sin(sec * PI / 30), 250 - 180 * cos(sec * PI / 30)};

  drawLine(center, aux, 3, GREEN);
}
void AfisareCeasAnalolgic(const Alarm &alarm, char alarma[], int i, int &ore, int &minute)
{
  initwindow(1000, 1000, "clock");

  Point center = {SIZE / 2, SIZE / 2}; // coordonate centru ceas

  while (!kbhit())
  {
    drawClock();

    time_t now = time(0);

    tm *ltm = localtime(&now);

    drawHour(center, ltm->tm_hour);
    drawMinutes(center, ltm->tm_min);
    drawSeconds(center, ltm->tm_sec);

    if (i != 0)
    {

      strcpy(alarma, alarm.luna);
      strcat(alarma, " ");
      strcat(alarma, alarm.zi);
      strcat(alarma, " ");
      strcat(alarma, alarm.ora);
      strcat(alarma, ":");
      strcat(alarma, alarm.minut);
      strcat(alarma, ":");
      strcat(alarma, alarm.secunda);
      strcat(alarma, " ");
      strcat(alarma, alarm.an);

      settextstyle(EUROPEAN_FONT, 0, 4);

      outtextxy(10, 500, "Alarm set for: ");
      outtextxy(250, 500, alarma);
      if ((strncmp(ctime(&now) + 4, alarm.luna, 3) == 0) && (strncmp(ctime(&now) + 8, alarm.zi, 2) == 0) && (strncmp(ctime(&now) + 11, alarm.ora, 2) == 0) && (strncmp(ctime(&now) + 14, alarm.minut, 2) == 0) && (strncmp(ctime(&now) + 20, alarm.an, 4) == 0))

      {

        afisareWakeUp(10, 600);

        Beep(333, 333);
      }
    }

    delay(1000);
    cleardevice();
  }

  closegraph();
}
void SchimbareOra(int &ore, int &minute)
{
  int o, m;
  cout << "Introduceti noua ora:";
  cin >> o;
  cout << endl;
  cout << "Introduceti noul minut:";
  cin >> m;
  time_t now = time(0);
  tm *ltm = localtime(&now);
  ore = ltm->tm_hour - o;
  minute = ltm->tm_min - m;
}

char meniu()
{
  char tasta;
  cout << "Operatii cu ceasul\n";
  cout << "c=afisare ceas digital |p=afisare ceas analogic| a=adaugare alarma| o=schimbare ora | t=timer" << endl;
  cout << "Comanda dvs:";
  cin >> tasta;
  return tasta;
}
void timer();

int main()
{

  Alarm v[101];

  char comanda;

  char alarma[50];

  int i = 0, ore = 0, minute = 0;

  do

  {

    comanda = meniu();
    switch (comanda)
    {
    case 'c':
      if (i == -1)
        cout << "Nu exista alarma setata." << endl;
      AfisareCeasDigital(v[i], alarma, i, ore, minute);
      break;
    case 'p':
      if (i == -1)
        cout << "Nu exista alarma setata." << endl;
      AfisareCeasAnalolgic(v[i], alarma, i, ore, minute);
      break;
    case 'a':
      if (i < 100)
        AdaugareAlarme(v, i);
      else
        cout << "Numarul maxim de alarme a fost atins." << endl;
      break;
    case 'o':
      SchimbareOra(ore, minute);
      break;
    case 't':
      timer();
      break;
    }
  } while (comanda != 's');

  return 0;
}

struct Time
{
  int hours;
  int minutes;
  int seconds;
};

void addSecond(Time &time)
{
  if (time.seconds == 59)
  {
    time.seconds = 0;
    time.minutes++;
  }
  else
  {
    time.seconds++;
  }
  if (time.minutes == 59)
  {
    time.minutes = 0;
    time.hours++;
  }
}

char *intToChar(int t)
{

  char *res = "";
  if (t < 10)
  {
    strcpy(res, "0");
    char digit = char('0' + t);
    strcmp(res, &digit);
  }

  return res;
}

char *formatTime(Time t)
{
  char *time = "";
  strcpy(time, intToChar(t.hours));
  strcat(time, ":");

  strcpy(time, intToChar(t.hours));
  strcat(time, ":");
  strcpy(time, intToChar(t.hours));
  return time;
}

void timer()
{
  Time currentTime = {0, 0, 0};

  initwindow(1000, 500, "Cronometru");
  settextstyle(EUROPEAN_FONT, 0, 5);

  while (kbhit)
  {
    cleardevice();

    // outtextxy(10, 50, formatTime(currentTime));
    cout << formatTime(currentTime) << endl;
    addSecond(currentTime);
    cout << currentTime.hours << ' ' << currentTime.minutes << ' ' << currentTime.seconds << endl;
    delay(1000);
  }
}
