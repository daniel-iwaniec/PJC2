#include <stdio.h>        //mozna pominac gdy uzywamy curses
#include <stdlib.h>       //malloc mozna pominac gdy uzywamy curses
#include <string.h>       //strcat
#include <curses.h>

int main(int argc, char *argv[]){
char plik1[100] = {}, plik2[100] = {};
char *tablica1, *tablica2;                          //tablice dynamiczne do przechowywania danych z plikow
int licznik1 = 0, licznik2 = 0;                         //liczniki ilosci znakow w plikach
int szer;                                   //szerokosc okien - ramka
int y = 1;                                  //aktualny wiersz, w ktorym wyswietla znak
int x = 1;                                  //aktualna kolumna, w ktorej wyswietla znak
char zp1, zp2;
int ch;

WINDOW *okno1, *okno2;

FILE *f1, *f2;                                  //wskazniki na pliki

//if (argc != 3){
//    printf("Cos sie pojebalo, sprobuj %s nazwa1 nazwa2", argv[0]);      //sprawdza czy podano argumenty w wierszu polecen
//    exit(1);
//}
//strcat(plik1, "./"); strcat(plik2, "./");

if (((f1 = fopen(strcat(plik1, "test.txt"), "r")) == NULL) || (f2 = fopen(strcat(plik2, "test2.txt"), "r")) == NULL){
    //sprawdza, czy moze otworzyc pliki, nie chce mi sie tego rozbijac na 2 osobne bledy wiec jest razem, strcat laczy ./ z nazwa pliku
    printf("Blad otwarcia ktoregos pliku");
    exit(1);
}

while((zp1 = fgetc(f1)) != EOF) licznik1++;                 //ustalamy ilosc znakow, do zaalokowania pamieci
while((zp2 = fgetc(f2)) != EOF) licznik2++;                 // ^
//printf("licznik1 %d \tlicznik2 %d", licznik1, licznik2);
licznik1 += 1; licznik2 += 1;
//while((ch = getchar()) != 27) continue;

tablica1 = (char *) malloc (licznik1 * sizeof (char));              //rozmiar rablic dopasowany do ilosci znakow w pliku
tablica2 = (char *) malloc (licznik2 * sizeof (char));              //^

if (tablica1 == NULL || tablica2 == NULL) { puts("Cos nie pyklo"); exit(EXIT_FAILURE); } //sprawdza, czy faktycznie cos zostalo przydzielone tablicom, NULL znaczy, ze malloc nie zadzialal

licznik1 = 0; licznik2 = 0;                         //zeruje liczniki, przydadza sie w nastepnej linijce
zp1 = 0; zp2 = 0;

fclose(f1);
fclose(f2);

if (((f1 = fopen(plik1, "r")) == NULL) || (f2 = fopen(plik2, "r")) == NULL){
    //sprawdza, czy moze otworzyc pliki, nie chce mi sie tego rozbijac na 2 osobne bledy wiec jest razem, strcat laczy ./ z nazwa pliku
    printf("Blad otwarcia ktoregos pliku");
    exit(1);
}

while(zp1 = getc(f1) != EOF) { tablica1[licznik1] = zp1; licznik1++; }  //wypelniam tablice znakami z pliku
while(zp2 = getc(f2) != EOF) { tablica2[licznik2] = zp2; licznik2++; }  //^

ch = 0;
licznik1 = 0;
//while(tablica1[licznik1] != EOF) { putc(tablica1[licznik1], stdout); licznik1++; }
//while((ch = getchar()) != 27) continue;


fclose(f1); fclose(f2);                             //znaki sa juz w tablicy wiec pliki mozna zamknac, mozna bezposrednio z plikow kopiowac na ekran
                                        //ale z tablicami mozna sobie dziubac w ciagu niezaleznym od plikow, jesli polecenie tego wymaga



initscr();                                  //inicjalizuje ekran curses
curs_set(0);                                    //"usuwa" kursor
cbreak(); noecho();                             //znaki sa od razu pobierane, program nie czeka na EOF przy czytaniu ciagu


okno1 = newwin(LINES, (COLS / 2), 0, 0);                    //tworzy okna o rozmiarach na pol ekranu standardowego, nie uwzglednia reszty z dzielenia wiec moze sie troche rozjechac
okno2 = newwin(LINES, (COLS / 2), 0, (COLS / 2));               //^

szer = (COLS / 2) - 2;                              //obliczenie szerokosci okien -(minus) ramka

box(okno1, 0, 0); box(okno2, 0, 0);                     //ramka z kresek
wnoutrefresh(okno1); wnoutrefresh(okno2); refresh();                //odswiezanie okien, bez tego nic sie nie pokaze

licznik1 = 0; licznik2 = 0;                         //znowu uzywam licznikow, zeby nie robic bilion zmiennych

while (tablica1[licznik1] != EOF && tablica2[licznik2] != EOF){         //dziala do momentu, gdy jeden z plikow osiagnie EOF

    if (x == szer) { x = 1; y += 1; }                   //jezeli linia dojdzie do konca okna, przenosi do nowego wiersza

    if (tablica1[licznik1] == tablica2[licznik2]){              //jezeli znaki w obu tablicach sa takie same, to drukuje je w negatywie
        mvwprintw(okno1, y, x, "%c", tablica1[licznik1] | A_REVERSE);
        mvwprintw(okno2, y, x, "%c", tablica2[licznik2] | A_REVERSE);
    }

    if (tablica1[licznik1] != tablica2[licznik2]){              //jezeli znaki nie sa takie same, drukuje je normalnie
        mvwprintw(okno1, y, x, "%c", tablica1[licznik1]);
        mvwprintw(okno2, y, x, "%c", tablica2[licznik2]);
    }
    wnoutrefresh(okno1); wnoutrefresh(okno2); refresh();            //odswiezanie okien, bez tego nic sie nie pokaze

    x++; licznik1++; licznik2++;                        //zmienia pozycje kursora o 1(x), zeby ciag mogl sie wyswietlic, inkrementuje liczniki
}

if (tablica1[licznik1] != EOF && tablica2[licznik2] == EOF){            //jesli tablica1 jest dluzsza niz tablica2 to trzeba dalej z niej wypisywac, nie?
    if (x == szer) { x = 1; y += 1; }
    mvwprintw(okno1, y, x, "%c", tablica1[licznik1]);

    wnoutrefresh(okno1); wnoutrefresh(okno2); refresh();            //odswiezanie okien, bez tego nic sie nie pokaze
    x++; licznik1++;
}

if (tablica1[licznik1] == EOF && tablica2[licznik2] != EOF){            //jesli tablica2 jest dluzsza niz tablica1 to trzeba dalej z niej wypisywac, nie?
    if (x == szer) { x = 1; y += 1; }
    mvwprintw(okno2, y, x, "%c", tablica2[licznik2]);

    wnoutrefresh(okno1); wnoutrefresh(okno2); refresh();            //odswiezanie okien, bez tego nic sie nie pokaze
    x++; licznik2++;
}

getch();                                    //bez tego program sie wykona, a my nic nie zobaczymy :(
delwin(okno1); delwin(okno2);                           //po zakonczeniu dzialania powinno sie usuwac okna
endwin();                                   //konczy dzialanie curses
free(tablica1); free(tablica2);                         //zwalnia pamiec przechowywana przez tablice
return 0;
}