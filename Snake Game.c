#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<time.h>
#include<unistd.h>
#include<windows.h>



int c[300][2], tamanho=1, pontuacao=0, record=0, cx=3, cy=3;
int comida[2];

char nome_record[100];


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
    
    comida[0] = (rand() % 49+3);
    comida[1] = (rand() % 18+4);

    gotoxy(comida[0],comida[1]);
    printf("%c",42);

}


void ReiniciarVariaveis() {

     tamanho=1;
     pontuacao=0;
     cx=3;
     cy=3;

}


int main(){

    char resposta = 's';

    while (resposta == 's' || resposta == 'S') {

        system("cls");

        ReiniciarVariaveis();

        int i, gameover=0;
        int velocidade=150;
        int comandos;

        c[0][0]=cx;
        c[0][1]=cy;

        for(i=1; i<=51; i++){
            gotoxy(i,2);
            printf("%c",219);
        }

        for(i=2; i<=21; i++){
            gotoxy(51,i);
            printf("%c",219);
        }

        for(i=51; i>0; i--){
            gotoxy(i,22);
            printf("%c",219);
        }

        for(i=21; i>1; i--){
            gotoxy(1,i);
            printf("%c",219);
        }


        RandomComida();
        Desenhar();
        comandos='d';
        while(gameover==0){
            gotoxy(21,0);
            printf("SNAKE GAME");

            gotoxy(54,3);
            printf("Pontos: %d\t",pontuacao);

            gotoxy(21,24);
            printf("Record: %d", record);

            if (record>0) {
                gotoxy(54,0);
                printf("MAIOR PONTUACAO = %s", nome_record);
            }

            c[0][0]=cx;
            c[0][1]=cy;
            if(kbhit())
                comandos=getch();

            if(comandos=='w' || comandos=='W' || comandos==72){
                cy--;

                if(cy==2) {
                    gameover=1;
                    break;
                }
            }
            if(comandos=='a' || comandos=='A' || comandos==75){
                cx--;

                if(cx==1) {
                    gameover=1;
                    break;
                }
            }
            if(comandos=='s' || comandos=='S' || comandos==80){
                cy++;

                if(cy==22) {
                    gameover=1;
                    break;
                }
            }
            if(comandos=='d' || comandos=='D' || comandos==77){
                cx++;

                if(cx>=51) {
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

        if (pontuacao>record) {
            printf("NOVO RECORD!\n\nEscreva seu nome: ",pontuacao);
            fflush(stdin);
            fgets(nome_record, 100, stdin);

            record=pontuacao;

            system("cls");
        }

        if (pontuacao<10) {
            printf("PONTUACAO = %d \n\n",pontuacao);
            printf ("Boa tentativa!\n\n");
        }

        else if (pontuacao<20) {
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

    }

    return 0;
}
