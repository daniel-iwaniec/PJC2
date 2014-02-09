/*
Programowanie w języku C 2 - Projekt
Sortowanie metodą Shell'a
* Daniel Iwaniec
* Artur Kałuża
*/

#include <panel.h>
#include <time.h>
#include <math.h>
#include <string.h>

bool isInArray(int array[], int n, int value) {
 int i;
 for (i = 0; i < n; i++) {
  if (array[i] == value) return true;
 }
 return false;
}

int main() {
 int N; char inputN[2];
 int lines = 5, cols = 8, x, maxX, maxY, leftX;
 int leftXString, leftXStringCollection, leftXStringSwitch;

 char option1[] = "Podaj ilosc liczb do posortowania: ";

 srand(time(0));
 initscr();
 keypad(stdscr, TRUE);
 getmaxyx(stdscr, maxY, maxX);

 leftX = maxX - cols * N;
 leftX = round((float) leftX / 2);

 leftXString = maxX - strlen(option1);
 leftXString = round((float) leftXString / 2);

 mvprintw(0, leftXString, option1);
 scanw("%d", &N);

 clear();
 cbreak();
 noecho();
 curs_set(0);

 int key;

 char header[] = "SORTOWANIE SHELL'A";
 char collectionStat[] = "Ilosc podzbiorow: ";
 char switchStat[] = "Ilosc zamian: ";

 WINDOW * my_wins[N];
 PANEL * my_panels[N];


 int bubbleChain[N], losowe[N], losoweConst[N];
 int collectionCount = 0, switchCount = 0;
 int h = 1, z, i, j = 0, k, l, bci, bciTemp;

 bool saveStats = true;
 char filename[] = "./statystyki.txt";
 FILE *plik;

 double tempFloat;

 plik = fopen(filename, "w+");

 srand(time(0));
 initscr();
 cbreak();
 noecho();
 curs_set(0);
 keypad(stdscr, TRUE);
 getmaxyx(stdscr, maxY, maxX);

 leftX = maxX - cols * N;
 leftX = round((float) leftX / 2);

 leftXString = maxX - strlen(header);
 leftXString = round((float) leftXString / 2);

 start_color();
 init_pair(0, COLOR_WHITE, COLOR_BLACK);
 init_pair(1, COLOR_RED, COLOR_BLACK);
 init_pair(2, COLOR_GREEN, COLOR_BLACK);

 attron(A_BOLD);
 mvprintw(0, leftXString, header);
 attroff(A_BOLD);

 x = leftX;
 for (i = 0; i < N; ++i) {
  losowe [i] = (rand() % 40);

  my_wins[i] = newwin(lines, cols, 2, x);
  wbkgdset(my_wins[i], COLOR_PAIR(0));
  werase(my_wins[i]);
  box(my_wins[i], 0, 0);
  my_panels[i] = new_panel(my_wins[i]);
  tempFloat = (double) ((double) losowe[i] / (double) 4.0);
  mvwprintw(my_wins[i], 2, 2, "%.2f", tempFloat);

  x = x + cols;
 }

 update_panels();
 doupdate();

 while ((key = getch()) != KEY_F(2));

 for (h = 1; h < N; h = 3 * h + 1);
 h /= 9;
 if (!h) h++;


 while (h) {
  for (j = N - h - 1; j >= 0; j--) {
   bci = 0;
   for (i = 0; i < N; i++) {
    bubbleChain[i] = -1;
   }

   for (l = 0; l < N; l++) {
    losoweConst[l] = losowe[l];
   }

   z = losowe[j];
   i = j + h;

   while ((i < N) && (z > losowe [i])) {
    losowe[i - h] = losowe[i];

    if (!isInArray(bubbleChain, bci, i) && i >= 0 && i <= N) {
     bubbleChain[bci++] = i;
    }

    if (!isInArray(bubbleChain, bci, (i - h)) && (i - h) >= 0 && (i - h) <= N) {
     bubbleChain[bci++] = i - h;
    }

    i += h;
   }
   losowe[i - h] = z;

   if (bci > 0) {
    collectionCount++;

    bciTemp = bubbleChain[0];
    bubbleChain[0] = bubbleChain[1];
    bubbleChain[1] = bciTemp;

    bciTemp = 0;
    while (bubbleChain[bciTemp] != -1 && bciTemp >= 0 && bciTemp < N) {
     wbkgdset(my_wins[bubbleChain[bciTemp]], COLOR_PAIR(1));
     box(my_wins[bubbleChain[bciTemp]], 0, 0);
     wrefresh(my_wins[bubbleChain[bciTemp]]);
     bciTemp++;
    }

    bciTemp = 0;
    while (bubbleChain[bciTemp + 1] != -1 && bciTemp >= 0 && bciTemp < (N - 1)) {
     switchCount++;

     wbkgdset(my_wins[bubbleChain[bciTemp]], COLOR_PAIR(2));
     box(my_wins[bubbleChain[bciTemp]], 0, 0);
     wrefresh(my_wins[bubbleChain[bciTemp]]);

     wbkgdset(my_wins[bubbleChain[bciTemp + 1]], COLOR_PAIR(2));
     box(my_wins[bubbleChain[bciTemp + 1]], 0, 0);
     wrefresh(my_wins[bubbleChain[bciTemp + 1]]);

     while ((key = getch()) != KEY_F(2));

     tempFloat = (double) ((double) losoweConst[bubbleChain[bciTemp + 1]] / (double) 4.0);
     mvwprintw(my_wins[bubbleChain[bciTemp]], 2, 2, "%.2f", tempFloat);
     wrefresh(my_wins[bubbleChain[bciTemp]]);

     tempFloat = (double) ((double) losoweConst[bubbleChain[bciTemp]] / (double) 4.0);
     mvwprintw(my_wins[bubbleChain[bciTemp + 1]], 2, 2, "%.2f", tempFloat);
     wrefresh(my_wins[bubbleChain[bciTemp + 1]]);

     l = losoweConst[bubbleChain[bciTemp + 1]];
     losoweConst[bubbleChain[bciTemp + 1]] = losoweConst[bubbleChain[bciTemp]];
     losoweConst[bubbleChain[bciTemp]] = l;

     while ((key = getch()) != KEY_F(2));

     wbkgdset(my_wins[bubbleChain[bciTemp]], COLOR_PAIR(0));
     box(my_wins[bubbleChain[bciTemp]], 0, 0);
     wrefresh(my_wins[bubbleChain[bciTemp]]);

     wbkgdset(my_wins[bubbleChain[bciTemp + 1]], COLOR_PAIR(0));
     box(my_wins[bubbleChain[bciTemp + 1]], 0, 0);
     wrefresh(my_wins[bubbleChain[bciTemp + 1]]);

     bciTemp++;
    }

    x = leftX;
    for (k = 0; k < N; ++k) {
     wbkgdset(my_wins[k], COLOR_PAIR(0));
     werase(my_wins[k]);
     box(my_wins[k], 0, 0);
     tempFloat = (double) ((double) losowe[k] / (double) 4.0);
     mvwprintw(my_wins[k], 2, 2, "%.2f", tempFloat);
     wrefresh(my_wins[k]);
     x = x + cols;
    }
    while ((key = getch()) != KEY_F(2));
   }
  }
  h /= 3;
 }

 strcat(collectionStat, "%d");
 sprintf(collectionStat, collectionStat, collectionCount);
 leftXStringCollection = maxX - strlen(collectionStat);
 leftXStringCollection = round((float) leftXStringCollection / 2);
 mvprintw(lines + 3, leftXStringCollection, collectionStat);

 strcat(switchStat, "%d");
 sprintf(switchStat, switchStat, switchCount);
 leftXStringSwitch = maxX - strlen(switchStat);
 leftXStringSwitch = round((float) leftXStringSwitch / 2);
 mvprintw(lines + 4, leftXStringSwitch, switchStat);

 while ((key = getch()) != KEY_F(2));

 endwin();

 fprintf(plik, "Statystki\r\n");
 fprintf(plik, "Ilosc podzbiorow: %d\r\n", collectionStat);
 fprintf(plik, "Ilosc zamian: %d\r\n", switchStat);

 return 0;
}