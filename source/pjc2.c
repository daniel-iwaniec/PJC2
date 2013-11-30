#include <panel.h>
#include <time.h>
#define N 10

int main() {
 WINDOW * my_wins[N];
 PANEL * my_panels[N];
 srand(time(0));
 int lines = 5, q, cols = 5, koniec_programu = 0, y = 2, x = 2, h = 1, z, i, j = 0, ch, losowe[N], map[50];
 float tempFloat;

 initscr();
 cbreak();
 noecho();
 curs_set(1);
 keypad(stdscr, TRUE);

 start_color();
 init_pair(1, COLOR_YELLOW, COLOR_BLACK);
 init_pair(2, COLOR_RED, COLOR_GREEN);
 init_pair(3, COLOR_GREEN, COLOR_BLACK);
 init_pair(4, COLOR_RED, COLOR_WHITE);
 init_pair(5, COLOR_WHITE, COLOR_YELLOW);
 init_pair(6, COLOR_BLACK, COLOR_GREEN);
 init_pair(7, COLOR_RED, COLOR_BLUE);
 init_pair(8, COLOR_BLUE, COLOR_GREEN);
 init_pair(9, COLOR_RED, COLOR_GREEN);
 init_pair(10, COLOR_WHITE, COLOR_GREEN);

 attron(A_BOLD);
 printw("sortowanie metoda shella. nacisnij 1 !!!");
 printw("Press F1 to exit");
 attroff(A_BOLD);

 for (i = 0; i < N; ++i) {

  losowe [i] = ((rand() % 50) + 0);
  map[losowe[i]] = i;
  my_wins[i] = newwin(lines, cols, y, x);

  wbkgdset(my_wins[i], COLOR_PAIR(i));
  werase(my_wins[i]);

  //tempFloat = losowe[i]/4;
  mvwprintw(my_wins[i], y, 2, "%d", losowe[i]);

  x = x + 5;
 }

 for (i = 0; i < N; ++i)
  box(my_wins[i], 0, 0);

 /* Attach a panel to each window */
 for (i = 0; i < N; ++i)
  my_panels[i] = new_panel(my_wins[i]);
 update_panels();
 doupdate();
 // Wyznaczamy wartość początkowego przesunięcia

 for (h = 1; h < N; h = 3 * h + 1);
 h /= 9;
 if (!h) h++; // istotne dla małych N, dla większych można pominąć!

 // Sortujemy

 /*while (h) {
  for (j = N - h - 1; j >= 0; j--) {
   z = losowe[j];
   i = j + h;
   while ((i < N) && (z > losowe [i])) {
    losowe[i - h] = losowe [i];
    i += h;
   }
   losowe[i - h] = z;
  }
  h /= 3;

 }*/
 // Wyświetlamy wynik sortowania


 x = 2;
 for (i = 0; i < N; ++i) {

  my_wins[i] = newwin(lines, cols, y + 5, x);

  wbkgdset(my_wins[i], COLOR_PAIR(map[losowe[i]]));
  werase(my_wins[i]);
  tempFloat = (float)((float)losowe[i] / (float)4.0);
  mvwprintw(my_wins[i], y, 2, "%f", tempFloat);
  x = x + 5;



 }


 for (i = 0; i < N; ++i)

  box(my_wins[i], 0, 0);
 /* Attach a panel to each window */
 for (i = 0; i < N; ++i) {
  my_panels[i] = new_panel(my_wins[i]);

 }

 update_panels();
 doupdate();


 while (!koniec_programu) {


  if (wgetch(my_wins[0]) == '1') {
   top_panel(my_panels[0]);
  }
  if (wgetch(my_wins[1]) == '2') {
   top_panel(my_panels[1]);
  }
  if (wgetch(my_wins[2]) == '3') {
   top_panel(my_panels[2]);
  }
  if (wgetch(my_wins[3]) == '4') {
   top_panel(my_panels[3]);
  }
  if (wgetch(my_wins[4]) == '5') {
   top_panel(my_panels[4]);
  }
  if (wgetch(my_wins[5]) == '6') {
   top_panel(my_panels[5]);
  }
  if (wgetch(my_wins[6]) == '7') {
   top_panel(my_panels[6]);
  }
  if (wgetch(my_wins[7]) == '8') {
   top_panel(my_panels[7]);
  }
  if (wgetch(my_wins[8]) == '9') {
   top_panel(my_panels[8]);
  }

  koniec_programu = 1;
  update_panels();




  doupdate();
 }
 endwin();
 return 0;
}

