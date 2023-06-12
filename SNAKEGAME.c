#include <stdio.h>
#include <windows.h> //----PARA A FUNÇÃO SET CONSOLE POSITION
#include <stdlib.h>
#include <conio.h> //PARA FUNÇÃO GETCH E KBHIT
#include <time.h>


//------PRONTO
//--O JOGO COMECA EM UMA POSIÇÃO ALEATORIA //----PRONTO
//----A COBRA SE MOVIMENTA W,D,S,A --- PRONTO
//---A CADA 10 MOVI, 2 COMIDAS
//---A CADA 10 MOVI, 2 OBSTACULOS
//---A COBRINHA NÃO PODE CHOCAR CONSIGO MESMA ---PRONTO
//-- SE A COBRINHA COMER UM ALIMENTO, CRESCE UMA CELULA E MARCA 10 PONTOS ---- PRONTO
//--- O JOGO TERMINA QUANDO A COBRA MORRE ---- PRONTO
//--- O JOGO ARMAZENA O RECORDE
//---AO MORRER O JOGO INFORMA SE O RECORDE FOI QUEBRADO OU NAO


typedef struct{
    char nome[15];
    int recorde;

}Jogador;

void coordXY(int x, int y){

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){x,y});
}

void zerar(int tam1, int tam2, int cenario[tam1][tam2]){ //PARA ZERAR O CENARIO COM APENAS ESPAÇOS

    for(int i = 0; i < tam1; i++){
        for(int j = 0; j < tam2; j++){
            cenario[i][j] = 32;

        }
    }
}

void preencher(){ //-PREENCHIMENTO DO CENARIO

    for(int i = 0; i < 50; i++){//--LINHA DE CIMA
        coordXY(i,0);
        printf("%c", 178);

    }

    for(int i = 50; i >=0; i--){//---LINHA DE BAIXO
        coordXY(i,20);
        printf("%c", 178);

    }

    for(int i = 0; i < 20; i++){//---LINHA DA DIREITA
        coordXY(50,i);
        printf("%c", 178);

    }

    for(int i = 20; i > 0; i--){//----LINHA DA ESQUERDA
        coordXY(0,i);
        printf("%c", 178);

    }
}

void desenha(int tam, int tamCobra, int cenario[tam][tam]){//----DESENHA A COBRA NO CENARIO
    int i;
    for(i = 0; i < tamCobra; i++){
        coordXY(cenario[i][0], cenario[i][1]);
        printf("%c", 219);
    }
}


void posAtualiza(int tam1, int tam2, int cenario[tam1][tam2], int tamCobra){ //---ATUALIZA A POSIÇÃO DA COBRA

    coordXY(cenario[tamCobra][0], cenario[tamCobra][1]);
    printf(" ");

    for(int i = tamCobra; i >=0; i--){
        cenario[i+1][0] = cenario[i][0];
        cenario[i+1][1] = cenario[i][1];

    }
}

int corpoCobra(int tam1,int tam2, int cenario[tam1][tam2], int tamCobra, int cx, int cy){ //----VERIFICA SE O CORPO DA COBRA ENCONTOU NELA MESMA

    int retorno = 0;

    for(int i = 1; i < tamCobra; i++){
        if(cx == cenario[i][0] && cy == cenario[i][1]){
            retorno = 1;
        }
    }

    return retorno;
}

void geraComida(int comida[4]){//----GERAÇÃO DE COMIDA

        coordXY(comida[0], comida[1]);
        printf(" ");
        comida[0] = (rand()%48) + 1;
        comida[1] = (rand()%18) + 1;

        coordXY(comida[2], comida[3]);
        printf(" ");
        comida[2] = (rand()%48) + 1;
        comida[3] = (rand()%18) + 1;


        if(comida[0] != '+' && comida[1] != '+'){
            coordXY(comida[0], comida[1]);
            printf("%c", 43);
        }
        else{
            comida[0] = (rand()%48) + 1;
            comida[1] = (rand()%18) + 1;
        }
        if(comida[2] != '+' && comida[3] != '+'){
            coordXY(comida[2], comida[3]);
            printf("%c", 43);
        }
        else{
            comida[2] = (rand()%48) + 1;
            comida[3] = (rand()%18) + 1;
        }


}



void geraObsta(int obsta[4]){//---GERAÇÃO DE OBSTACULOS
        coordXY(obsta[0], obsta[1]);
        obsta[0] = (rand()%48) + 1;
        obsta[1] = (rand()%18) + 1;


        coordXY(obsta[2], obsta[3]);
        obsta[2] = (rand()%48) + 1;
        obsta[3] = (rand()%18) + 1;
        //coordXY(obsta[2], obsta[3]);
        printf("%c", 79);

        if(obsta[0] != 'O' && obsta[1] != 'O'){
            coordXY(obsta[0], obsta[1]);
            printf("%c", 79);
        }
        else{
            obsta[0] = (rand()%48) + 1;
            obsta[1] = (rand()%18) + 1;
        }

        if(obsta[2] != 'O' && obsta[3] != 'O'){
            coordXY(obsta[2], obsta[3]);
            printf("%c", 79);
        }

        else{
            obsta[2] = (rand()%48) + 1;
            obsta[3] = (rand()%18) + 1;
        }


}

void pergunta(Jogador nickname[20], int pontos, int* j){

    for(*j = 0; *j < 2; *j++){
        printf("Bem vindo ao Jogo da Cobrinha, digite um nick para comecar: ");
        scanf("%s", nickname[*j].nome);
        nickname[*j].recorde = pontos;
    }


}

void reinicia(int tamCobra, int cx, int cy, int pontos, int tecla, int comida[4], int obsta[100], int cenario[50][25], int* i){

    zerar(50,25,cenario);
    preencher();
    geraComida(comida);
    geraObsta(obsta);
    tamCobra = 1;
    tecla = 'f';
    cx = (rand()%48) + 1;
    cy = (rand()%18) + 1;

}


int main(){


    srand(time(NULL));
    //---CENARIO
    int cenario[50][25];

    //---COBRA
    int tamCobra = 1;//---TAMANHO DA COBRA
    int cx = rand()%49;//---POSIÇÃO X INICIAL(LINHA)
    int cy = rand()%19;//---POSIÇÃO Y INICIAL (COLUNA)

    //---VARIAVEIS
    int gameover = 0;
    char tecla;
    int pontos = 0;
    char perguntaSN = 's';
    //---COMIDA
    int comida[4];//--VETOR DA COMIDA


    //---OBSTACULOS
    int obsta[4]; //VETOR DO OBSTACULO



    Jogador nickname[20];
    int i;
    int a;
    int j;

    pergunta(nickname, pontos, &j);
    system("cls");


    //--CHAMADAS DAS FUNÇÕES
    preencher();
    zerar(50,25, cenario);
    desenha(1,tamCobra, cenario);
    //geraComida(comida);
    //geraObsta(obsta);


    //-------

    int mod = 0;

    //-------

    do{

        preencher();

        //---POSIÇÃO DE ONDE VAI FICAR AS INFORMAÇÕES DOS PONTOS
        coordXY(52,2);
        printf("Pontos: %d", pontos);

        cenario[0][0] = cx;
        cenario[0][1] = cy;

        //---PEGA A TECLA PRECIONADA
        if(kbhit()){
            tecla = getch();
        }


        //---MOVIMENTAÇÃO
        if(tecla == 'w'){
            cy--;
            if(cy == 0){
                system("cls");
                printf("Deseja continuar? S/N");
                scanf("%c", &perguntaSN);
                getchar();
                printf("%c", pergunta);

                if(perguntaSN == 's'){
                    i++;
                    printf("Bem vindo ao Jogo da Cobrinha, digite um nick para comecar: ");
                    scanf("%s", nickname[i].nome);
                    nickname[i].recorde = pontos;
                    system("cls");
                    reinicia(tamCobra,cx,cy,pontos,'s',comida,obsta, cenario, &i);
                }
                else{
                    break;
                }

            }
        }
        if(tecla == 'd'){
            cx++;
            if(cx >= 50){
                system("cls");
                printf("Deseja continuar? S/N");
                scanf("%c", &perguntaSN);
                getchar();
                printf("%c", pergunta);


                if(perguntaSN == 's'){
                    i++;
                    printf("Bem vindo ao Jogo da Cobrinha, digite um nick para comecar: ");
                    scanf("%s", nickname[i].nome);
                    nickname[i].recorde = pontos;
                    system("cls");
                    reinicia(tamCobra,cx,cy,pontos,'s',comida,obsta,cenario, &i);
                }
                else{
                    break;
                }


            }
        }
        if(tecla == 's'){
            cy++;
            if(cy == 20){

                system("cls");
                printf("Deseja continuar? S/N");
                scanf("%c", &pergunta);
                getchar();
                printf("%c", pergunta);

                if(perguntaSN == 's'){
                    i++;
                    printf("Bem vindo ao Jogo da Cobrinha, digite um nick para comecar: ");
                    scanf("%s", nickname[i].nome);
                    nickname[i].recorde = pontos;
                    system("cls");
                    reinicia(tamCobra,cx,cy,pontos,'s',comida,obsta,cenario, &i);
                }
                else{
                    break;
                }
            }
        }
        if(tecla == 'a'){
            cx--;
            if(cx == 0){

                system("cls");
                printf("Deseja continuar? S/N");
                scanf("%c", &pergunta);
                getchar();


                if(perguntaSN == 's'){
                    i++;
                    printf("Bem vindo ao Jogo da Cobrinha, digite um nick para comecar: ");
                    scanf("%s", nickname[i].nome);
                    nickname[i].recorde = pontos;
                    system("cls");
                    reinicia(tamCobra,cx,cy,pontos,'s',comida,obsta, cenario, &i);
                }
                else{
                    break;
                }

            }
        }


        //-----VERIFICAO DA COMIDA
        if(cx == comida[0] && cy == comida[1]){
            pontos += 10;
            tamCobra++;
        }

        if(cx == comida[2] && cy == comida[3]){
            pontos += 10;
            tamCobra++;
        }



        //-----VERIFICAO DOS OBSTACULOS
        if(cx == obsta[0] && cy == obsta[1]){
            system("cls");
            printf("GAMEOVER! O jogador %s fez %d pontos\n\n", nickname[0].nome, pontos);
            system("pause");
        }

       if(cx == obsta[2] && cy == obsta[3]){
            system("cls");
            printf("GAMEOVER! O jogador %s fez %d pontos\n\n", nickname[0].nome, pontos);
            system("pause");
        }


        gameover = corpoCobra(50,25, cenario,tamCobra, cx,cy);
        posAtualiza(50,25, cenario,tamCobra);
        desenha(1,tamCobra,cenario);
        coordXY(50,20);
        mod++;

        if(mod%10 == 0){
            geraComida(comida);
            geraObsta(obsta);

        }

        //--TAXA DE ATUALIZAÇÃO
        Sleep(200);

    }while(perguntaSN == 's');


    system("cls");
    printf("GAMEOVER! O jogador %s fez %d pontos\n\n", nickname[0].nome, pontos);
    system("pause");



    return 0;
}
