#include"casseBriques.h"
#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <unistd.h>
void color(int t,int f)
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,f*16+t);
}
void printMap(char** map, int lenght, int height){
   system("cls");
    printf("\n");
    for (int i=0;i<lenght;i++){
        printf("\t\t\t\t\t");
        for (int j=0;j<height;j++){
            if (map[i][j]=='m') {
                color(10, 0);
                printf("%c", map[i][j]);
                continue;
            }
            color(15, 0);
            if (map[i][j]=='x') {
                color(12, 0);
                printf("%c", map[i][j]);
                continue;
            }
            color(15, 0);
            printf("%c",map[i][j]);
            color(15, 0);
        }
        printf("\n");
    }
   color(15, 0);
}
char** createMap(int lenght,int height, int nbPlayers){
    char** map=(char**)malloc(lenght * sizeof(char*));
    for (int i = 0; i < lenght; i++) {
        map[i] = (char*)malloc(height* sizeof(char));
    }
    srand(time(NULL));
    for (int i=0;i<lenght;i++)
    {
        for (int j=0;j<height;j++)
        {
            map[i][j]='?';
        }
    }
    placePlayers(nbPlayers, map,lenght,height);
    for (int i=0;i<lenght;i++)
    {
        for (int j=0;j<height;j++)
        {   if ((i==0||j==0 || i==lenght-1||j==height-1) && (map[i][j]!='p'))
            {
                map[i][j]='x';//les cotes
            }
            if (map[i][j]=='?')
            {
                int caseContent = rand()%5;
                switch (caseContent) {
                    case 0:
                        map[i][j]=' ';
                        break;
                    case 1:
                        map[i][j]='m';
                        break;
                    case 2:
                        map[i][j]='x';
                        break;
                    default:
                        map[i][j]=' ';
                }
            }
        }
    }
    return map;
}
Maps** createRandomMaps(int mode){
    int nbMaps=0;
    char s[80];
    while (nbMaps<=0)
    {
        printf("\t\t\tCombien de choix de cartes voudriez-vous?\n");
        sleep(1);
        scanf("%s", s);
        nbMaps = atoi(s);
        if (nbMaps>1)
        {
            printf("\t\t\tParfait! vous avez choisi %i cartes\n", nbMaps);
            printf("\t\t\tMaintenant, choisissez celles qui vous plaisent\n");
        }
    }
    Maps** mapsArray = (Maps **) malloc(nbMaps * sizeof(Maps*));
    for (int i = 0; i < nbMaps; i++) {
        mapsArray[i] = (Maps *) malloc(nbMaps * sizeof(Maps));
    }
    for (int i = 0; i < nbMaps; i++) {
        mapsArray[i]->lenght=(int*)malloc(sizeof (int));
        mapsArray[i]->height=(int*)malloc(sizeof (int));
        mapsArray[i]->choosen=(int*)malloc(sizeof (int));
        *(mapsArray[i]->lenght)=(rand() % 10) + 20;
        *(mapsArray[i]->height)=(rand() % 10) + 20;
        *(mapsArray[i]->choosen) = 0;
        mapsArray[i]->Map =createMap(*(mapsArray[i]->lenght), *(mapsArray[i]->height),4);
    }
    chooseMaps(mapsArray,nbMaps,mode);
    return  mapsArray;
}
Player** initPlayers(int nbPlayers){
    Player * *playersArray = (Player **) malloc(nbPlayers * sizeof(Player *));
    for (int i = 0; i < nbPlayers; i++)
    {
        playersArray[i] = createPlayer();
    }
    for (int i = 0; i < nbPlayers; i++)
    {
        *(playersArray[i]->bombsNumber)=5;
        *(playersArray[i]->bombRange)=2;
        *(playersArray[i]->lifes)=1;
        *(playersArray[i]->turn)=0;
        *(playersArray[i]->bombKick)=0;
    }
    return playersArray;
}
void chooseMaps(Maps** mapsArray,int nbMaps,int mode){
    char res;
    int choosenMaps=0;
    for (int i = 0; i < nbMaps; i++) {
        printf("\t\t\t\t\tCarte %d  \n", i);
        printMap(mapsArray[i]->Map,*(mapsArray[i]->lenght),*(mapsArray[i]->height));
        res = ' ';
        printf("\n");
        if (nbMaps > 1) {
            printf("\n\t\tVoullez vous avoir cette carte au cours du jeu ? (Y/N) \n");
            scanf("%c", &res);
            while (res != 'Y' && res != 'N') {
                printf("\n\t\tY ou N s'il vous plait :)\n");
                scanf("%c", &res);
            }
            if (res == 'Y') {
                printf("\t\tOk,vous allez avoir cette carte.\n\n\n");
                *(mapsArray[i]->choosen) = 1;
                choosenMaps++;
            }
            else {
                printf("\t\tOk, vous n'allez pas avoir cet carte.\n\n\n");

            }
            if (i == nbMaps-1 && choosenMaps == 0) {
                printf("\t\tPlus de choix,vous aurez cette carte\n");
                *(mapsArray[i]->choosen) = 1;
            }

        }
        else{
            printf(" \t\tVous allez avoir la carte ci-desssus\n");

            *(mapsArray[i]->choosen) = 1;
        }
    }
    for (int i = 0; i < nbMaps; i++)
    {
        if(*(mapsArray[i]->choosen) ==1)
        {
            printf("\t\tvous avez choisi la carte no %d \n", i);
            if (mode==2) {
                playMap(mapsArray[i]->Map, *(mapsArray[i]->lenght), *(mapsArray[i]->height), 4);
            }
            else{
                playMapComputer(mapsArray[i]->Map, *(mapsArray[i]->lenght), *(mapsArray[i]->height), 4);
            }

        }
        for (int j = 0; j < *(mapsArray[i]->lenght); j++) {
                free(mapsArray[i]->Map[j]);
            }
        free(mapsArray[i]->Map);
        free(mapsArray[i]->lenght);
        free(mapsArray[i]->height);
        free(mapsArray[i]->choosen);
        free(mapsArray[i]);
    }
    free(mapsArray);
}
Player* createPlayer(){
    Player* res = (Player*)malloc(sizeof(Player));
    res->bombRange = (int*) malloc(sizeof (int));
    res->bombsNumber = (int*) malloc(sizeof (int));
    res->lifes = (int*) malloc(sizeof (int));
    res->x = (int*) malloc(sizeof (int));
    res->y = (int*) malloc(sizeof (int));
    res->turn = (int*) malloc(sizeof (int));
    res->bombKick = (int*) malloc(sizeof (int));
    res->playerNumber =0;
    return res;
}
void placePlayers(int nbPlayers,char** map, int lenght, int height){
    for (int i=0;i<nbPlayers;i++) {
        int tmpx = (rand() % (lenght-2)+1);
        int tmpy = (rand() % (height-2)+1);
        if (map[tmpx][tmpy] != 'p')
        {
            map[tmpx][tmpy] =i+'0';
        }
        else
        {
            while (map[tmpx][tmpy] == 'p')
            {
                tmpx = rand() % (lenght - 2) + 1;
                tmpy = rand() % (height - 2) + 1;
            }
        }
    }
}
int findX(char playerNumber, char** map,  int length, int height){
    for (int i=0;i<length;i++)
    {
        for (int j=0;j<height;j++)
        {
            if (map[i][j]==playerNumber)
                return i;
        }
    }
    return 0;
}
int findY(char playerNumber, char** map,  int length, int height){
    for (int i=0;i<length;i++)
    {
        for (int j=0;j<height;j++)
        {
            if (map[i][j]==playerNumber)
                return j;
        }
    }
    return 0;
}
void exploseBomb(Player** player, int x,int y,int nbPlayers,int* alive,char** MapToPlay,int lenght,int height) {
    exploseRight(player, x, y,nbPlayers,alive,MapToPlay,height);
    exploseLeft(player, x, y,nbPlayers,alive,MapToPlay);
    exploseUp(player, x, y,nbPlayers,alive,MapToPlay,lenght);
    exploseDown(player, x, y,nbPlayers,alive,MapToPlay);
}

void playMap(char** MapToPlay,int lenght, int height, int nbPlayers) {
    int command;
    Player **playersArray = initPlayers(nbPlayers);
    printf("\t\t\t\t\tlongueur = %d \n\t\t\t\t\thauteur = %d\n\t\t\t\t\tnombre de bombes = 5\n", lenght,height);
    printMap(MapToPlay, lenght, height);
    for (int i = 0; i < nbPlayers; i++) {
        playersArray[i]->playerNumber = i + '0';
    }
    for (int i = 0; i < nbPlayers; i++) {
        *(playersArray[i]->x) = findX(playersArray[i]->playerNumber, MapToPlay, lenght, height);
        *(playersArray[i]->y) = findY(playersArray[i]->playerNumber, MapToPlay, lenght, height);
    }
    int* i= malloc(sizeof(int));
    *i=0;
    int begin ;
    int end ;
    int *alivePlayers = malloc(sizeof(int));
    *alivePlayers = nbPlayers;
    *(playersArray[0]->turn) = 1;
    while (1) {
        if (*alivePlayers < 2) {
            printf("\t\t\tle joueur %d gagne \n", *i);
            break;
        }
        if (*(playersArray[*i]->turn) == 1 && *(playersArray[*i]->lifes) != 0) {
            begin = 0;
            end = 2 ;
            while(begin < end)
            {
                 printf("\t\t\tle joueur %d a le tour\n", *i);
                printf("\t\t\tle portee bombes=  %d \n", *(playersArray[*i])->bombRange);
                printf("\t\t\tnombre de vies=  %d \n", *(playersArray[*i])->lifes);
                printf("\t\t\tbomb kick=  %d \n\n\n", *(playersArray[*i])->bombKick);
                command = getch();
                readCommand(MapToPlay, lenght, height, nbPlayers, playersArray, alivePlayers, command, *i);
                begin++;
            }
            passTurn(playersArray, i);
        }
    }

    for (int j = 0; j < nbPlayers; j++)
    {
        free(playersArray[j]->bombRange);
        free(playersArray[j]->bombsNumber);
        free(playersArray[j]->lifes);
        free(playersArray[j]->x);
        free(playersArray[j]->y);
        free(playersArray[j]->turn);
        free(playersArray[j]->bombKick);
        free(playersArray[j]);
    }
    free(playersArray);
    free(alivePlayers);
    free(i);

}

void passTurn(Player **playersArray, int * i){
    for (int j = 1; j < 4; j++) {
        if (*(playersArray[(*i + j) % 4]->lifes) > 0) {
            *(playersArray[(*i + j) % 4]->turn) = 1;
            *(playersArray[(*i) % 4]->turn) = 0;
            *i = (*i + j) % (4);
            printf("\t\t\tpassTurn : le joueur %d a le tour\n", *i);
            break;
        }
    }
}
void giveGift(Player* player){
    int gift = rand()%11;
    switch (gift) {
        case 0: //Bomb Up
            *(player->bombsNumber)=*(player->bombsNumber)+1;
            printf("\t\t\tbomb up\n");
            break;
        case 1: //Bomb Down
            *(player->bombsNumber)=*(player->bombsNumber)-1;
            printf("\t\t\tbomb down\n");
            break;
        case 2: //flamme Jaune
            *(player->bombRange)=*(player->bombRange)+1;
            printf("\t\t\tflamme jaune\n");
            break;
        case 3: //Flamme bleue
            *(player->bombsNumber)=*(player->bombsNumber)-1;
            printf("\t\t\tflamme bleue\n");
            break;
        case 4: //Bomb Down
            *(player->bombsNumber)=*(player->bombsNumber)-1;
            printf("\t\t\tbomb down\n");
            break;
        case 5: //range max RARE!!!!!!
            *(player->bombRange)=*(player->bombRange)+10;
            printf("\t\t\t Bravo! portee maximale!\n");
            break;
        case 6://Bomb kick
            printf("\t\t\t Bombes comme un ballon\n");
            *(player->bombKick)=1;
            break;
        case 7://Vie
            printf("\t\t\t Une autre vie\n");
            *(player->lifes)=*(player->lifes)+1;
            break;
        default:
            printf(" Pas de Cadeau cette fois\n");
            break;
    }
}
void bombKick(Player **player,  int x, int y,int nbPlayers,int* alive,char** MapToPlay){
    int i;
    int j;
    int range =10;
    for (i = 1; i<=range; i++) {
        if (y - 1 > 0) {
            if (MapToPlay[x][y - i] == 'x')
                break;
            if (MapToPlay[x][y - i] == 'm') {
                MapToPlay[x][y - i] = ' ';
                break;
            }
            for (j = 0; j <= nbPlayers; j++) {
                if (MapToPlay[x][y - i] == j + '0') {
                    *(player[j]->lifes) =*(player[j]->lifes)-1;
                    if (*(player[j]->lifes) == 0) {
                        printf("\t\t\tun joueur en moins!\n");
                        *alive = *alive - 1;
                    }
                    MapToPlay[x][y - i] = ' ';
                    break;
                }
            }
        }
    }
}
void readCommand(char** MapToPlay, int lenght,int height,int nbPlayers,Player **playersArray,int * alivePlayers,int command, int i ){
    switch (command) {
        case 72 :
            moveUp(playersArray[i]->playerNumber, (playersArray[i]->x),
                   *(playersArray[i]->y), MapToPlay, lenght);
            printf("\t\t\thaut\n");
            printMap(MapToPlay, lenght, height);
            break;
        case 80 :
            printf("\t\t\tbas\n");
            moveDown(playersArray[i]->playerNumber, playersArray[i]->x,
                     *(playersArray[i])->y, MapToPlay, lenght);
            printMap(MapToPlay, lenght, height);
            break;
        case 77 :
            printf("\t\t\tdroite\n");
            moveRight(playersArray[i]->playerNumber, *(playersArray[i]->x),
                      playersArray[i]->y, MapToPlay, height);
            printMap(MapToPlay, lenght, height);
            break;
        case 75 :
            printf("\t\t\tgauche\n");
            moveLeft(playersArray[i]->playerNumber, *(playersArray[i]->x),
                     playersArray[i]->y, MapToPlay, height);
            printMap(MapToPlay, lenght, height);
            break;
        case 13 :
            printf("\t\t\tBoooommm!\n");
            printMap(MapToPlay, lenght, height);
            if(*(playersArray[i]->bombKick)==1){
                bombKick(playersArray, *(playersArray[i]->x), *(playersArray[i]->y),
                         nbPlayers, alivePlayers, MapToPlay);
                printMap(MapToPlay, lenght, height);
            }
            else {
                exploseBomb(playersArray, *(playersArray[i]->x), *(playersArray[i]->y),
                            nbPlayers, alivePlayers, MapToPlay, lenght, height);
                printMap(MapToPlay, lenght, height);
            }
            break;
        default:
            printf("Commande lue non valide!\n");
            break;
    }

}
void moveUp(char playerNumber,int* x, int y,char** MapToPlay,int lenght){
    if (*x<lenght && MapToPlay[*x-1][y]==' ' ) {
        MapToPlay[*x][y] = ' ';
        MapToPlay[*x-1][y] = playerNumber;
        *x = *x - 1;
    }
    else {
        printf("\t\t\tmouvement impossible!\n");
    }
}
void moveDown(char playerNumber,int* x, int y,char** MapToPlay, int lenght){
    if (*x<lenght && MapToPlay[*x+1][y]==' ' ) {
        MapToPlay[*x][y] = ' ';
        MapToPlay[*x+1][y] = playerNumber;
        *x = *x + 1;
    }
    else {
        printf("\t\t\tmouvement impossible!\n");
    }
}
void moveRight(char playerNumber, int x,int* y,char** MapToPlay, int height){
    if (x<height && MapToPlay[x][*y+1]==' ' ) {
        MapToPlay[x][*y] = ' ';
        MapToPlay[x][*y+1] = playerNumber;
        *y = *y + 1;
    }
    else {
        printf("\t\t\tmouvement impossible!\n");
    }
}
void moveLeft(char playerNumber, int x,int* y,char** MapToPlay, int height){
    if (x<height && MapToPlay[x][*y-1]==' ' ) {
        MapToPlay[x][*y] = ' ';
        MapToPlay[x][*y-1] = playerNumber;
        *y = *y - 1;
    }
    else {
        printf("\t\t\tmouvement impossible!\n");
    }
}
void exploseRight(Player** player,  int x, int y,int nbPlayers,int* alive,char** MapToPlay, int height) {
    int i;
    int j;
    for (i = 1; i <= *(player[i]->bombRange); i++) {
        if (y + i < height) {
            if (MapToPlay[x][y + i] == 'x')
                break;
            if (MapToPlay[x][y + i] == 'm') {
                MapToPlay[x][y + i] = ' ';
                giveGift(player[i]);
                break;
            }
            for (j = 0; j <= nbPlayers; j++) {
                if (MapToPlay[x][y + i] == j + '0') {
                    *(player[j]->lifes) =*(player[j]->lifes)-1 ;
                    if (*(player[j]->lifes) == 0) {
                        printf("\t\t\tun joueur en moins!\n");
                        *alive = *alive - 1;
                    }
                    MapToPlay[x][y + i] = ' ';
                    break;
                }
            }
        }
    }
}
void exploseLeft(Player** player,int x, int y,int nbPlayers,int* alive,char** MapToPlay ){
    int i;
    int j;
    for (i = 1; i<=*(player[i]->bombRange); i++) {
        if (y - 1 > 0) {
            if (MapToPlay[x][y - i] == 'x')
                break;
            if (MapToPlay[x][y - i] == 'm') {
                MapToPlay[x][y - i] = ' ';
                giveGift(player[i]);
                break;
            }
            for (j = 0; j <= nbPlayers; j++) {
                if (MapToPlay[x][y - i] == j + '0') {
                    *(player[j]->lifes) =*(player[j]->lifes)-1;
                    if (*(player[j]->lifes) == 0) {
                        printf("\t\t\tun joueur en moins!\n");
                        *alive = *alive - 1;
                    }
                    MapToPlay[x][y - i] = ' ';
                    break;
                }

            }
        }
    }
}
void exploseUp(Player** player,  int x, int y,int nbPlayers,int* alive,char** MapToPlay, int lenght){
    int i ;
    int j ;
    for (i = 1; i<=*(player[i]->bombRange); i++) {
        if (x + i < lenght) {
            if (MapToPlay[x + i][y] == 'x')
                break;
            if (MapToPlay[x + i][y] == 'm') {
                MapToPlay[x + i][y] = ' ';
                giveGift(player[i]);
                break;
            }
            for (j = 0; j <= nbPlayers; j++) {
                if (MapToPlay[x + i][y] == j +'0') {
                    *(player[j]->lifes) =*(player[j]->lifes)-1;
                    if (*(player[j]->lifes) == 0){
                        printf("\t\t\tun joueur en moins!\n");
                        *alive = *alive - 1;
                    }
                    MapToPlay[x + i][y] = ' ';
                    break;
                }

            }
        }
    }
}
void exploseDown(Player** player, int x, int y,int nbPlayers,int* alive,char** MapToPlay){
    int i;
    int j ;
    for(i = 1; i<=*(player[i]->bombRange); i++) {
        if (x - i > 0) {
            if (MapToPlay[x - i][y] == 'x')
                break;
            if (MapToPlay[x - i][y] == 'm') {
                MapToPlay[x - i][y] = ' ';
                giveGift(player[i]);
                break;
            }
            for (j = 0; j <= nbPlayers; j++) {
                if (MapToPlay[x - i][y] == j + '0') {
                    *(player[j]->lifes) =*(player[j]->lifes)-1;
                    if (*(player[j]->lifes) == 0) {
                        printf("\t\t\tun joueur en moins!\n");
                        *alive = *alive - 1;
                    }
                    MapToPlay[x - i][y] = ' ';
                    break;
                }
            }
        }
    }
}
char scanLeft(int x, int y,char** MapToPlay ) {
    int j;
    if (y - 1 >= 0) {
        for (j = 0; j < 4; j++) {
            if (MapToPlay[x][y - 1] == j + '0') {
                return 'p';
            }
            return MapToPlay[x][y - 1];
        }
    }
    return 'x';
}
char scanRight(int x, int y,char** MapToPlay, int height ) {
    int j;
    if (y + 1 <= height) {
        for (j = 0; j < 4; j++) {
            if (MapToPlay[x][y + 1] == j + '0') {
                return 'p';
            }
        }
        return MapToPlay[x][y + 1];
    }
    return 'x';
}
char scanUp(int x, int y,char** MapToPlay ) {
    int j;
    if (x -1 >=0) {
        for (j = 0; j<4; j++) {
            if (MapToPlay[x-1][y] == j + '0') {
                return 'p';
            }
        }
        return MapToPlay[x -1][y];
    }
    return 'x';
}
char scanDown(int x, int y,char** MapToPlay, int lenght ) {
    int j;
    if (x + 1 <= lenght) {
        for (j = 0; j < 4; j++) {
            if (MapToPlay[x + 1][y] == j + '0') {
                return 'p';
            }
        }
        return MapToPlay[x + 1][y];
    }
    return 'x';
}
void playMapComputer(char** MapToPlay,int lenght, int height, int nbPlayers) {
    int command;
    Player **playersArray = initPlayers(nbPlayers);
    printf("\t\t\t\t\tlongueur = %d \n\t\t\t\t\thauteur = %d\n\t\t\t\t\tnombre de bombes = 5\n", lenght,height);
    printMap(MapToPlay, lenght, height);
    for (int i = 0; i < nbPlayers; i++) {
        playersArray[i]->playerNumber = i + '0';
    }
    for (int i = 0; i < nbPlayers; i++) {
        *(playersArray[i]->x) = findX(playersArray[i]->playerNumber, MapToPlay, lenght, height);
        *(playersArray[i]->y) = findY(playersArray[i]->playerNumber, MapToPlay, lenght, height);
    }
    int* i= malloc(sizeof(int));
    *i=0;
    int  begin ;
    int end ;
    int *alivePlayers = malloc(sizeof(int));
    *alivePlayers = nbPlayers;
    *(playersArray[0]->turn) = 1;
    while (1) {
        if (*alivePlayers < 2) {
            printf("\t\t\tle joueur %d gagne \n", *i);
            break;
        }
        if (*(playersArray[*i]->turn) == 1 && *(playersArray[*i]->lifes) != 0) {
            begin = 0;
            end = 1;
            while(begin <end) {
                printf("\t\t\tle joueur %d a le tour\n", *i);
                printf("\t\t\tle portee bombes=  %d \n", *(playersArray[*i])->bombRange);
                printf("\t\t\tnombre de vies=  %d \n", *(playersArray[*i])->lifes);
                printf("\t\t\tbomb kick=  %d \n\n\n", *(playersArray[*i])->bombKick);
                if(*i==0) {
                    command = getch();
                    readCommand(MapToPlay, lenght, height, nbPlayers, playersArray, alivePlayers, command, *i);
                }
                else {
                    command = generateCommande(MapToPlay, lenght, height, playersArray, *i);
                    printf("commande = %d", command);
                    readCommand(MapToPlay, lenght, height, nbPlayers, playersArray, alivePlayers, command, *i);
                }
                begin++;
            }
            passTurn(playersArray, i);
        }
    }

    for (int j = 0; j < nbPlayers; j++)
    {
        free(playersArray[j]->bombRange);
        free(playersArray[j]->bombsNumber);
        free(playersArray[j]->lifes);
        free(playersArray[j]->x);
        free(playersArray[j]->y);
        free(playersArray[j]->turn);
        free(playersArray[j]->bombKick);
        free(playersArray[j]);
    }
    free(playersArray);
    free(alivePlayers);
    free(i);

}
void choose_mode(){
    int res;
    char s[80];
    do
    {
        printf("\n");
        printf("\t\t\tCASSE BRIQUES ESGI 2022-2023 :\n");
        printf("\n");
        printf("\t\t\tveuillez choisir le mode de jeu :\n");
        printf("\t\t\t1 : Demarrer \n");
        printf("\t\t\t2 : Demarrer le serveur \n");
        printf("\t\t\t3 : Rejoindre le serveur \n\t\t\t\t");
        scanf("%s", s);
        res = atoi(s);
        createRandomMaps(res);
    }
    while(res != 1);
}
int generateCommande(char** MapToPlay, int lenght,int height ,Player **playersArray ,int i) {
    int resLeft;
    int resRight;
    int resUp;
    int resDown;
    int resFinal[4];
    int decision;
    char left=scanLeft(*(playersArray[i]->x), *(playersArray[i]->y), MapToPlay);
    char up = scanUp(*(playersArray[i]->x), *(playersArray[i]->y), MapToPlay);
    char down = scanDown(*(playersArray[i]->x), *(playersArray[i]->y), MapToPlay, lenght);
    char right = scanRight(*(playersArray[i]->x), *(playersArray[i]->y), MapToPlay, height);
    printf("left = %c\n",left);
    printf("right = %c\n",right);
    printf("up = %c\n",up);
    printf("down = %c\n",down);
    switch (left) {
        case 'p' :case 'm':
            resLeft = 13;
            printf("scan left = un mur ou un joueur\n");
            break;
        case ' ':
            resLeft = 75;
            break;
        default:
            resLeft = 1000;
    }
    resFinal[0]=resLeft;
    switch (right) {
        case 'p' :case 'm':
            resRight = 13;
            printf("scanRight = un mur ou un joueur\n");
            break;
        case ' ':
            resRight = 77;
            break;
        default:
            resRight = 1000;
    }
    resFinal[1]=resRight;
    switch (up) {
        case 'p' :case 'm':
            resUp = 13;
            printf("scanUp = un mur ou un joueur\n");
            break;
        case ' ':
            resUp = 72;
            break;
        default:
            resUp = 1000;
    }
    resFinal[2]=resUp;
    switch (down) {
        case 'p' :case 'm':
            resDown = 13;
            printf("scanDown = un mur ou un joueur\n");
            break;
        case ' ':
            resDown = 88;
            break;
        default:
            resDown = 1000;
    }
    resFinal[3]=resDown;
    sort(resFinal,4);
    decision=resFinal[0];
    switch (decision) {
        case 13:
            printf("decision = boom\n");
            break;
        case 77:
            printf("decision = move right\n");
            break;
        case 72:
            printf("decion = move up\n");
            break;
        case 88:
            printf("decion = move down\n");
            break;
        case 75:
            printf("decion = move left\n");
            break;
        default:
            printf("Decision : Erreur\n");
    }
    return decision;
}
void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
void sort(int array[], int n){
    int i, j, min_element;
    for (i = 0; i < n-1; i++)
    {
        min_element = i;
        for (j = i+1; j < n; j++)
            if (array[j] < array[min_element])
                min_element = j;
        swap(&array[min_element], &array[i]);
    }
}
