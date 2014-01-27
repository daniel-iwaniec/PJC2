#include <panel.h>
#include <time.h>
#include <math.h>
#define N 8

int main() {
 WINDOW * my_wins[N];
 PANEL * my_panels[N];
 int lines = 5, q, cols = 8, koniec_programu = 0, y = 2, x = 0, h = 1, z, i, j = 0, k, l, ch, losowe[N], map[50], maxX, maxY, leftX;
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
   z = losowe[j];
   i = j + h; l = 0;
   while ((i < N) && (z > losowe [i])) {
    losowe[i - h] = losowe[i];

    wbkgdset(my_wins[i], COLOR_PAIR(l+1));
    box(my_wins[i], 0, 0);
    wrefresh(my_wins[i]);

    wbkgdset(my_wins[i-h], COLOR_PAIR(l+1));
    box(my_wins[i-h], 0, 0);
    wrefresh(my_wins[i-h]);

    i += h; l++;
   }
   losowe[i - h] = z;
   if (l > 0) {
   while ((q = getch()) != KEY_F(2)) {
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
   while ((q = getch()) != KEY_F(2)) {
  }}
  }
  h /= 3;
 }

 //napisz ze koniec

 endwin();
 return 0;
}