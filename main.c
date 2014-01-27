#include <panel.h>
#include <time.h>
#include <math.h>
#define N 20

int main() {
 WINDOW * my_wins[N];
 PANEL * my_panels[N];
 int lines = 5, q, cols = 8, koniec_programu = 0, y = 2, x = 0, h = 1, z, i, j = 0, ch, losowe[N], map[50], maxX, maxY, leftX;
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
 init_pair(0, COLOR_YELLOW, COLOR_BLUE);
 init_pair(1, COLOR_RED, COLOR_GREEN);
 init_pair(2, COLOR_GREEN, COLOR_YELLOW);
 init_pair(3, COLOR_RED, COLOR_WHITE);
 init_pair(4, COLOR_WHITE, COLOR_YELLOW);
 init_pair(5, COLOR_BLUE, COLOR_GREEN);
 init_pair(6, COLOR_RED, COLOR_BLUE);
 init_pair(7, COLOR_BLUE, COLOR_GREEN);
 init_pair(8, COLOR_RED, COLOR_GREEN);
 init_pair(9, COLOR_WHITE, COLOR_GREEN);

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
   i = j + h;
   while ((i < N) && (z > losowe [i])) {
    losowe[i - h] = losowe [i];
    i += h;
   }
   losowe[i - h] = z;
   //tutaj rysuj okienka
   x = leftX;
   for (i = 0; i < N; ++i) {
    my_wins[i] = newwin(lines, cols, y, x);
    wbkgdset(my_wins[i], COLOR_PAIR(3));
    werase(my_wins[i]);
    box(my_wins[i], 0, 0);
    my_panels[i] = new_panel(my_wins[i]);
    tempFloat = (double) ((double) losowe[i] / (double) 4.0);
    mvwprintw(my_wins[i], 2, 2, "%.2f", tempFloat);
    x = x + cols;
   }
  }
  h /= 3;



  update_panels();
  doupdate();

  while ((q = getch()) != KEY_F(2)) {
  }

 }

 // Wy�wietlamy wynik sortowania
 x = leftX;
 for (i = 0; i < N; ++i) {
  my_wins[i] = newwin(lines, cols, y, x);
  //wbkgdset(my_wins[i], COLOR_PAIR(map[losowe[i]]));
  werase(my_wins[i]);
  tempFloat = (double) ((double) losowe[i] / (double) 4.0);
  mvwprintw(my_wins[i], y, 2, "%.2f", tempFloat);
  x = x + cols;
 }


 for (i = 0; i < N; ++i)
  box(my_wins[i], 0, 0);
 /* Attach a panel to each window */
 for (i = 0; i < N; ++i) {
  my_panels[i] = new_panel(my_wins[i]);

 }

 update_panels();
 doupdate();


 while ((q = getch()) != KEY_F(2)) {



  koniec_programu = 1;

  update_panels();
  doupdate();
 }
 endwin();
 return 0;
}