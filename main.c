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
#define N 8

bool isInArray(int array[], int n, int value) {
 int i;
 for (i = 0; i < n; i++) {
  if (array[i] == value) return true;
 }
 return false;
}

int main() {
 int key;

 char header[] = "SORTOWANIE SHELL'A";
 WINDOW * my_wins[N];
 PANEL * my_panels[N];
 int lines = 5, cols = 8, x, maxX, maxY, leftX, leftXString;

 int bubbleChain[N], losowe[N], losoweConst[N];
 int collectionCount = 0, switchCount = 0;
 int h = 1, z, i, j = 0, k, l, bci, bciTemp;

 double tempFloat;

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

 mvprintw(lines + 2 + 1, leftX + 1, "Ilosc podzbiorow: %d", collectionCount);
 mvprintw(lines + 2 + 2, leftX + 1, "Ilosc zamian: %d", switchCount);
 while ((key = getch()) != KEY_F(2));

 endwin();
 return 0;
}
