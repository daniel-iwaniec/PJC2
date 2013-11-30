#include <curses.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define N 10
#define MENU_POZ 3

const char *menu_poz[]={"Pozycja1", "Pozycja2", "Koniec"};
int i;
WINDOW *okno1, *okno2[N], *menu;


void odswiez_ekran() {
	wnoutrefresh(okno1);wnoutrefresh(menu);
	doupdate();
}
int main() {


int wybrane_menu = 0,koniec_programu=0, znak, n;
int lines = 5,q, cols = 5, y = 10, x = 10,h=1,z, i,j=0,ch, losowe[N];
srand(time(0));
initscr();
noecho();
start_color();
init_pair(1, COLOR_RED, COLOR_BLUE); 
init_pair(2, COLOR_YELLOW, COLOR_GREEN); 
init_pair(3, COLOR_BLUE, COLOR_GREEN);


okno1 = newwin(30, 80, 2, 0);
box(okno1, 0, 0);
wattrset(okno1, A_BOLD);
wbkgdset(okno1, COLOR_PAIR(2));
werase(okno1);
mvwprintw(okno1, 1, 1, "%s", "Zasady dzialania programu: ");
mvwprintw(okno1, 2, 1, "%s", "Opcja menu \"1\" liczby do sortowania");
mvwprintw(okno1, 3, 1, "%s", "Opcja menu \"2\" liczby po sortowaniu");
mvwprintw(okno1, 4, 1, "%s", "Opcja menu \"Koniec\" konczy program");

menu = newwin(2, 80, 0, 0);
box(menu, 0, 0);
wbkgdset(menu, COLOR_PAIR(1));
werase(menu);




keypad(menu, 1);
odswiez_ekran();

while (!koniec_programu) {

        
for (n=0; n<MENU_POZ; n++)
{
if(wybrane_menu==n)
wattrset(menu, A_REVERSE);



else	wattrset(menu, A_NORMAL);
mvwprintw(menu, 0, n*16, "%s", menu_poz[n]);
		}
		znak = wgetch(menu);	// Oczekiwanie na klawisz


if((znak == KEY_LEFT) && (wybrane_menu>0))
			wybrane_menu--;
		if((znak == KEY_RIGHT) && (wybrane_menu<MENU_POZ-1))
			wybrane_menu++;
		if(znak == '\n') {
			mvwprintw(okno1, 5, 1, "Wybrano nr %d", wybrane_menu+1);

for(i = 0; i < N; ++i){

	losowe [i] = ((rand() % 50) + 0);
	okno2[i] = newwin(lines, cols, y, x);

	wbkgdset(okno2[i], COLOR_PAIR(3));
	werase(okno2[i]);

	mvwprintw(okno2[i],10, 0,"%d", losowe [i]);
	
	x=x+5;
}

for(i = 0; i < N; ++i)
	box(okno2[i], 0, 0);










			if(wybrane_menu == 2)	koniec_programu=1;
		}
		


odswiez_ekran();



}
endwin(); 

return(0);
}

