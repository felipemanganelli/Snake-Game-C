#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<time.h>
#include <unistd.h>
#include<windows.h>



int c[300][2], tamanho=1, pontuacao=0, cx=2, cy=2;
int comida[2];


void gotoxy(int x, int y){
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x,y});
}


void Desenhar(){

    int i;

    for(i=0; i<tamanho; i++){
        gotoxy(c[i][0],c[i][1]);
        printf("%c",'o');
    }
}


void Movimento(){

    int i;

    gotoxy(c[tamanho][0],c[tamanho][1]);
    printf(" ");

    for(i=tamanho; i>=0; i--){
        c[i+1][0] = c[i][0];
        c[i+1][1] = c[i][1];
    }
}


int EncostarCorpo(){

    int i, retorno=0;

    for(i=1; i<tamanho; i++){
        if(cx==c[i][0] && cy==c[i][1]){
            retorno=1; }
    }

    return retorno;
}


void RandomComida(){

    gotoxy(comida[0],comida[1]);
    printf(" ");
    srand(time(NULL));
    comida[0] = (rand() % 48) +1;
    comida[1] = (rand() % 18) +1;
    gotoxy(comida[0],comida[1]);
    printf("%c",42);

}


void ReiniciarVariaveis() {

     tamanho=1;
     pontuacao=0;
     cx=2;
     cy=2;

}


int main(int argc, char **argv){

    char resposta = 's';


    while (resposta == 's' || resposta == 'S') {

        system("cls");

        ReiniciarVariaveis();

        int i, gameover=0;
        int velocidade=150;
        int comandos;

        c[0][0]=cx;
        c[0][1]=cy;

        for(i=0; i<50; i++){
            gotoxy(i,0);
            printf("%c",219);
        }

        for(i=0; i<20; i++){
            gotoxy(50,i);
            printf("%c",219);
        }

        for(i=50; i>=0; i--){
            gotoxy(i,20);
            printf("%c",219);
        }

        for(i=20; i>0; i--){
            gotoxy(0,i);
            printf("%c",219);
        }


        RandomComida();
        Desenhar();
        comandos='d';
        while(gameover==0){
            gotoxy(52,2);
            printf("Pontos: %d\t",pontuacao);
            gotoxy(52,4);

            c[0][0]=cx;
            c[0][1]=cy;
            if(kbhit())
                comandos=getch();

            if(comandos=='w' || comandos=='W' || comandos==72){

                cy--;

                if(cy==0) {
                    gameover=1;
                    break;
                }
            }
            if(comandos=='a' || comandos=='A' || comandos==75){

                cx--;

                if(cx==0) {
                    gameover=1;
                    break;
                }
            }
            if(comandos=='s' || comandos=='S' || comandos==80){

                cy++;

                if(cy==20) {
                    gameover=1;
                    break;
                }
            }
            if(comandos=='d' || comandos=='D' || comandos==77){

                cx++;

                if(cx>=50) {
                    gameover=1;
                    break;
                }
            }

            if(cx==comida[0] && cy==comida[1]){
                tamanho++;
                pontuacao++;
                if(velocidade>60) velocidade-=10;
                RandomComida();
            }
            gameover=EncostarCorpo();
            Movimento();
            Desenhar();
            gotoxy(50,20);
            Sleep(velocidade);
        }



        system("cls");

        if (pontuacao<10) {
            printf("PONTUACAO = %d \n\n",pontuacao);
            printf ("Boa tentativa!\n\n");
        }

        else if (pontuacao<15) {
            printf("PONTUACAO = %d\n\n",pontuacao);
            printf("Meus parabens! Voce e muito bom!\n\n");
        }

        else {
            printf("PONTUACAO = %d \n\n",pontuacao);
            printf ("Caramba! Voce e o mestre da cobra! \nConseguiu ser o melhor!\n\n");
        }



        do {

            printf("Deseja jogar novamente? (S/N): ");
            scanf(" %c", &resposta);

        } while (resposta != 's' && resposta != 'S' && resposta != 'n' && resposta != 'N');

        if (resposta == 's' || resposta == 'S') {

            char *args[] = {argv[0], NULL};
            execvp(args[0], args);

        }
    }

    return 0;
}
