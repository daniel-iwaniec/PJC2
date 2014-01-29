#include <panel.h>
#include <time.h>
#include <math.h>
#define N 8

bool isInArray(int tab[], int num_elements, int value) {
 int i;
 for (i = 0; i < num_elements; i++) {
  if (tab[i] == value) {
   return true; /* it was found */
  }
 }
 return false; /* if it was not found */
}

int main() {
 WINDOW * my_wins[N];
 PANEL * my_panels[N];
 int bubbleChain[N], bubbleChainValues[N];
 int lines = 5, q, cols = 8, koniec_programu = 0, y = 2, x = 0, h = 1, z, i, j = 0, k, l, ch, losowe[N], losoweConst[N], map[50], maxX, maxY, leftX, bci, bciTemp;
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

 start_color();
 init_pair(0, COLOR_WHITE, COLOR_BLACK);
 init_pair(1, COLOR_RED, COLOR_BLACK);
 init_pair(2, COLOR_GREEN, COLOR_BLACK);
 init_pair(3, COLOR_YELLOW, COLOR_BLACK);
 init_pair(4, COLOR_BLUE, COLOR_BLACK);
 init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
 init_pair(6, COLOR_CYAN, COLOR_BLACK);
 init_pair(7, COLOR_CYAN, COLOR_BLACK);
 init_pair(8, COLOR_CYAN, COLOR_BLACK);
 init_pair(9, COLOR_CYAN, COLOR_BLACK);
 init_pair(10, COLOR_CYAN, COLOR_BLACK);

 attron(A_BOLD);
 //printw("sortowanie metoda shella maxX: %d, maxY: %d, leftX: %d\n", maxX, maxY, leftX);
 //printw("Press F2 to exit");
 attroff(A_BOLD);

 x = leftX;
 for (i = 0; i < N; ++i) {
  losowe [i] = (rand() % 40);
  map[losowe[i]] = i;

  my_wins[i] = newwin(lines, cols, y, x);
  //wbkgdset(my_wins[i], COLOR_PAIR(i));
  werase(my_wins[i]);
  box(my_wins[i], 0, 0);
  my_panels[i] = new_panel(my_wins[i]);
  tempFloat = (double) ((double) losowe[i] / (double) 4.0);
  mvwprintw(my_wins[i], y, 2, "%.2f", tempFloat);
  x = x + cols;
 }

 update_panels();
 doupdate();

 while ((q = getch()) != KEY_F(2)) {
 }

 //SORTOWANIE- wyznaczanie h
 for (h = 1; h < N; h = 3 * h + 1);
 h /= 9;
 if (!h) h++;

 // Sortujemy
 while (h) {
  for (j = N - h - 1; j >= 0; j--) {
   for (i = 0; i < N; ++i) {
    bubbleChain[i] = -1;
   }

   z = losowe[j];
   i = j + h;
   l = -1; bci = 0;

   for (l = 0; l < N; l++) {
    losoweConst[l] = losowe[l];
   }

   while ((i < N) && (z > losowe [i])) {
    losowe[i - h] = losowe[i];

    if (!isInArray(bubbleChain, bci, i) && i >= 0 && i <= N) {
     bubbleChain[bci] = i;
     bubbleChainValues[bci] = i;
     bci++;
     //l++;
    }
    //wbkgdset(my_wins[i], COLOR_PAIR(l + 1));
    //box(my_wins[i], 0, 0);
    //wrefresh(my_wins[i]);

    if (!isInArray(bubbleChain, bci, (i-h)) && (i-h) >= 0 && (i-h) <= N) {
     bubbleChain[bci++] = i-h;
     //l++;
    }
    //wbkgdset(my_wins[i - h], COLOR_PAIR(l + 1));
    //box(my_wins[i - h], 0, 0);
    //wrefresh(my_wins[i - h]);

    i += h;
   }
   losowe[i - h] = z;
   if (bci > 0) {

    bciTemp = bubbleChain[0];
    bubbleChain[0] = bubbleChain[1];
    bubbleChain[1] = bciTemp;

    bciTemp = 0;
    while (bubbleChain[bciTemp] != -1) {
     wbkgdset(my_wins[bubbleChain[bciTemp]], COLOR_PAIR(1));
     box(my_wins[bubbleChain[bciTemp]], 0, 0);
     wrefresh(my_wins[bubbleChain[bciTemp]]);
     bciTemp++;
    }

    bciTemp = 0;
    while (bubbleChain[bciTemp+1] != -1) {
     l = bubbleChain[bciTemp];
     wbkgdset(my_wins[bubbleChain[bciTemp]], COLOR_PAIR(2));
     box(my_wins[bubbleChain[bciTemp]], 0, 0);
     wrefresh(my_wins[bubbleChain[bciTemp]]);
     l = bubbleChain[bciTemp+1];
     wbkgdset(my_wins[bubbleChain[bciTemp+1]], COLOR_PAIR(2));
     box(my_wins[bubbleChain[bciTemp+1]], 0, 0);
     wrefresh(my_wins[bubbleChain[bciTemp+1]]);

     while ((q = getch()) != KEY_F(2));

     tempFloat = (double) ((double) losoweConst[bubbleChain[bciTemp+1]] / (double) 4.0);
     mvwprintw(my_wins[bubbleChain[bciTemp]], y, 2, "%.2f", tempFloat);
     wrefresh(my_wins[bubbleChain[bciTemp]]);

     tempFloat = (double) ((double) losoweConst[bubbleChain[bciTemp]] / (double) 4.0);
     mvwprintw(my_wins[bubbleChain[bciTemp+1]], y, 2, "%.2f", tempFloat);
     wrefresh(my_wins[bubbleChain[bciTemp+1]]);

     l = losoweConst[bubbleChain[bciTemp+1]];
     losoweConst[bubbleChain[bciTemp+1]] = losoweConst[bubbleChain[bciTemp]];
     losoweConst[bubbleChain[bciTemp]] = l;

     while ((q = getch()) != KEY_F(2));

     wbkgdset(my_wins[bubbleChain[bciTemp]], COLOR_PAIR(0));
     box(my_wins[bubbleChain[bciTemp]], 0, 0);
     wrefresh(my_wins[bubbleChain[bciTemp]]);

     wbkgdset(my_wins[bubbleChain[bciTemp+1]], COLOR_PAIR(0));
     box(my_wins[bubbleChain[bciTemp+1]], 0, 0);
     wrefresh(my_wins[bubbleChain[bciTemp+1]]);
     bciTemp++;
    }

    //tutaj rysuj okienka
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
    while ((q = getch()) != KEY_F(2));
   }
  }
  h /= 3;
 }

 printw("Zakonczono");
 while ((q = getch()) != KEY_F(2));

 endwin();
 return 0;
}