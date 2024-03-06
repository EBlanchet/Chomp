/* Author : Elise Blanchet */
/* Creation : 25/02/2022 */
/* Modification : 04/03/2022 */

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>

#define NB_LIGNES 8
#define NB_COLONNES 16

typedef struct tablette{ 
    int chocolat[NB_LIGNES][NB_COLONNES];
}Tablette;

typedef enum{
    JOUEUR_1,
    JOUEUR_2
}Joueur;

typedef struct position{
    Tablette tab;
    Joueur j;
}Position;

typedef struct coup{
    int x;
    int y;
}Coup;

Joueur adversaire(Joueur joueur){
    return 1 - joueur;
}

Tablette creer_tablette(){
    Tablette tablette;
    int i, j;
    if (tablette.chocolat == NULL){
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < NB_LIGNES; i++) {
        if (tablette.chocolat[i] == NULL){
            exit(EXIT_FAILURE);
        }
        for (j = 0; j < NB_COLONNES; j++){
            tablette.chocolat[i][j] = 1;
        }
    }
    return tablette;
    
}

void manger(Tablette *tab, int x, int y){
    for (; x < NB_LIGNES; x++){
        // free(tab->chocolat[x]); autre méthode ?
        for (; y < NB_COLONNES; y++){
            // free(tab->chocolat[y]); autre méthode ?
            if (tab->chocolat[x][y] == 1){
                tab->chocolat[x][y] = 0;
            }
        }
    }
}

int est_legal(Position pos, Coup coup){
    if (coup.x >= NB_COLONNES || coup.y >= NB_LIGNES || pos.tab.chocolat[coup.y][coup.x] == 0){
        return 0;
    }
    return 1;
}

int est_jeu_termine(Position pos, Joueur *joueur_gagnant){
    if(pos.tab.chocolat[0][0] == 0){
        *joueur_gagnant = pos.j;
        return 1;
    }
    return 0;
}

void jouer_coup(Position *pos, Coup coup){
    manger(&(pos->tab), coup.y, coup.x);
    pos->j = adversaire(pos->j);
}

void afficher_position(Position pos){
    int x, y;
    for (y = 0; y < NB_LIGNES; y++){
        for (x = 0; x < NB_COLONNES; x++){
            if (pos.tab.chocolat[y][x] == 0){
                continue;
            }
            else if (pos.tab.chocolat[y][x] == 1){
                int ligne, colonne;
                ligne = y*4;
                colonne = x*6;
                for(; ligne <= (y*4) + 4; ligne++){
                    for(; colonne <= (x*6) + 6; colonne++){
                        move(ligne, colonne);
                        if ((ligne == 0) || (ligne == ((y*4) + 4))){
                            printw("-");
                        }
                        else if ((colonne == 0) || (colonne == ((x*6) + 6))){
                            printw("|");
                        }
                    }
                }
                refresh();
            }
        }
    }
    mvprintw(2, 3, "*");
    refresh();
}

Coup lire_coup(Position pos){
    Coup tmp;
    int touche;
    MEVENT event;

    while (touche != KEY_MOUSE || getmouse(&event) != OK){
        touche = getch();
    }
    if (event.x > 6){
        tmp.x = event.x / 6;
    }
    else{
        tmp.x = 0;
    }
    if (event.y > 4){
        tmp.y = event.y / 4;
    }
    else{
        tmp.y = 0;
    }
    return tmp;
}


int main(){
    Tablette tablette;
    Joueur joueur, gagnant;
    Position position;
    Coup coup;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
    curs_set(FALSE);

    tablette = creer_tablette();
    joueur = JOUEUR_1;
    position.tab = tablette;
    position.j = joueur;

    afficher_position(position);

    while(1){
        clear();
        afficher_position(position);

        if (position.j == JOUEUR_1){
            mvprintw(LINES-1, 0, "Joueur 1 à votre tour");
        }
        else{
            mvprintw(LINES-1, 0, "Joueur 2 à votre tour");
        }

        while (est_legal(position, coup) == 0){
            coup = lire_coup(position);
            mvprintw(LINES-1, (COLS-1) / 2, "Coup invalide");
        }

        jouer_coup(&position, coup);
        refresh();

        if (est_jeu_termine(position, &gagnant) == 1){
            clear();
            mvprintw((LINES-1) / 2, (COLS-1) / 2, "%d à gagné", gagnant);
            refresh();
            sleep(2);
            endwin();
            return 0;
        }
        else{
            continue;
        }
    }  
}
