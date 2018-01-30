//Aluno: Luis Roberto Costa Dias
//Matricula: 21783
//Turma: ECO2011
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SEQUENCIA 4
#define MAX_AUX 6
#define MAX_CARTA 13
#define MAX_COLUNA 11
#define MAX_MONTE 24

typedef enum{false, true} bool;

typedef struct no{
    int valor;
    int naipe;
    struct no * prox;
} noCarta;

noCarta * monte = NULL;

int quantMonte;

noCarta * pilhaJogo[MAX_COLUNA];

int linhaEscondida[MAX_COLUNA];

void criarMonte(){
    int i, j;
    noCarta * atual;
    quantMonte = MAX_SEQUENCIA * MAX_CARTA;
    for(j=1; j<=MAX_CARTA; j++){
    for(i=3; i<= MAX_AUX; i++){
            if((i==3)&&(j==1)){
                monte = (noCarta *)malloc(sizeof(noCarta));
                atual = monte;
            }else{
                atual->prox = (noCarta *)malloc(sizeof(noCarta));
                atual = atual->prox;
            }
            atual->naipe = i;
            atual->valor = j;
            atual->prox = NULL;
        
    }
}
}

noCarta * removeMonte(int posicao){
    int i;
    noCarta *ant=NULL;
    noCarta *atual=monte;
    if(posicao >= quantMonte){
        return NULL;
    }else{
        quantMonte--;
        for(i=0; i<posicao; i++){
            ant=atual;
            atual=atual->prox;
        }
            if(atual==monte){
            monte = atual->prox;
        }else{
            ant->prox=atual->prox;
        }
        return atual;
    }
}

void embaralharMonte(){
    int sorteio;
    noCarta* atual;
    noCarta* prim = NULL;
    srand(time(NULL));
    while( quantMonte > 0){
        sorteio = rand() % quantMonte;
        atual = removeMonte(sorteio);
        atual->prox = prim;
        prim = atual;
    }
    monte = prim;
    quantMonte = MAX_SEQUENCIA * MAX_CARTA;
}

void imprimirMonte(){
    int i=0;
	int colunaPilha=0;
	int linhaPilha=0;
    noCarta * atual = monte;
    printf("      Monte    \n\n");
    // imprimir monte
     switch (atual->valor) {
    case 1:  printf(" [A][%c]", atual->naipe); break;
    case 11: printf(" [J][%c]", atual->naipe); break;
    case 12: printf(" [Q][%c]", atual->naipe); break;
    case 13: printf(" [K][%c]", atual->naipe); break;
    default:     printf("[%02d][%c] ", atual->valor, atual->naipe);
    }
    printf("     ");
        atual = atual->prox;
        i++;
        if((i % MAX_COLUNA) == 0){
            printf("\n");
					    linhaPilha++;
		}//endif
    printf("\n\n");
}//imprimirMonte
void criarPilhaJogo(){
    int linhaPilha, sorteio,aux;
    int colunaPilha = 0;
    noCarta* atual;
     for(linhaPilha=0;linhaPilha<MAX_COLUNA;linhaPilha++){
        linhaEscondida[linhaPilha] = 0;
    }
    linhaPilha=1;
    colunaPilha=0;
    while( quantMonte > MAX_MONTE){
        for(aux=0;aux<linhaPilha;aux++){
        sorteio = rand() % quantMonte;
        atual = removeMonte(sorteio);
        atual->prox = pilhaJogo[colunaPilha];
        pilhaJogo[colunaPilha] = atual;
        linhaEscondida[colunaPilha] ++;
        }
        colunaPilha++;
        linhaPilha++;
    }
        for(linhaPilha=0;linhaPilha<MAX_COLUNA;linhaPilha++){
        linhaEscondida[linhaPilha] -= 2;
    }
}

void imprimirPilhaJogo(){
    int colunaPilha = 0;
    int linhaPilha = 0;
    noCarta * atual[MAX_COLUNA];
    int pilhaImpressa = 0;
    printf("     |                      JOGO                             |           CEU                 |\n\n");
    printf("     ");
    for(colunaPilha=0; colunaPilha<MAX_COLUNA; colunaPilha++){
if(colunaPilha==7){
printf("| \3(7) ");}
if(colunaPilha==8){
printf("| \4(8) ");}
if(colunaPilha==9){
printf("| \5(9) ");}
if(colunaPilha==10){
printf("| \6(10) ");}
if((colunaPilha>=0)&&(colunaPilha<7)){
printf("|  %2d   ", colunaPilha);}

        atual[colunaPilha] = pilhaJogo[colunaPilha];
    }
    printf("\n");
        while (pilhaImpressa < MAX_COLUNA){
        pilhaImpressa = 0;
        printf(" %2d  ", linhaPilha);

        for(colunaPilha=0; colunaPilha<MAX_COLUNA; colunaPilha++){
            if(atual[colunaPilha] == NULL){
                printf("        ");
                pilhaImpressa++;
            }else{

                if(linhaPilha <= linhaEscondida[colunaPilha]){
                    printf("[??][??]");
                }else{
    switch (atual[colunaPilha]->valor) {
    case 1:  printf("  [A][%c] ", atual[colunaPilha]->naipe); break;
    case 11: printf("  [J][%c] ", atual[colunaPilha]->naipe); break;
    case 12: printf("  [Q][%c] ", atual[colunaPilha]->naipe); break;
    case 13: printf("  [K][%c] ", atual[colunaPilha]->naipe); break;
    default: printf(" [%02d][%c] ", atual[colunaPilha]->valor,atual[colunaPilha]->naipe);
    }
                }
                atual[colunaPilha] = atual[colunaPilha]->prox;
            }
        }
        linhaPilha++;
        printf("\n");
    }
}

void distribuirMontePilhaJogo(){
    int colunaPilha;
    noCarta* atual, * cartaMonte;
    for(colunaPilha=0; colunaPilha < MAX_COLUNA; colunaPilha++){
        if(quantMonte > 0){
            cartaMonte = removeMonte(0);
            cartaMonte->prox = NULL;
            atual = pilhaJogo[colunaPilha];
            if(atual == NULL){
                pilhaJogo[colunaPilha] = cartaMonte;
            }else{
                while (atual->prox != NULL){
                    atual = atual->prox;
                }
                atual->prox = cartaMonte;
            }
        }
    }
}

void moverMontePilhaJogo(int movec){
    int colunaPilha;
    noCarta* atual, * cartaMonte;
        if(quantMonte > 0){
            cartaMonte = removeMonte(0);
            cartaMonte->prox = NULL;
            atual = pilhaJogo[movec];
            if(atual == NULL){
                  pilhaJogo[movec] = cartaMonte;
            }else{
                  while (atual->prox != NULL){
                  atual = atual->prox;
                }
                 atual->prox = cartaMonte;
            }
            }
}

bool moveCartasPilhaJogo(int colunaRemove, int linhaRemove, int colunaInsere){
    noCarta  * antRem, * atualRem, * atualIns;
    int pos = 0;
    if ((colunaRemove<0) && (colunaRemove<MAX_COLUNA) &&
        (colunaInsere<0) && (colunaInsere<MAX_COLUNA)){
        printf("limites inválidos\n");
        return false;
    }else{
        antRem = NULL;
        atualRem = pilhaJogo[colunaRemove];
        while ((pos < linhaRemove) && (atualRem != NULL)){
            pos ++;
            antRem = atualRem;
            atualRem = atualRem->prox;
        }
        atualIns = pilhaJogo[colunaInsere];    
        if(atualIns != NULL){
            while (atualIns->prox != NULL){
                pos ++;
                atualIns = atualIns->prox;
            }
            if((colunaInsere!=7)&&(colunaInsere!=8)&&(colunaInsere!=9)&&(colunaInsere!=10)){
            if((atualIns->valor-1) != atualRem->valor){
                printf("Operacao Invalida: A carta nao eh menor(!)\n");
                return false;
            }
            if((atualIns->naipe)==(atualRem->naipe)){
                printf("Operacao Invalida: O naipe das cartas eh igual\n");
                return false;
            }
        }
        }
        if((colunaInsere==7)&&(atualIns==NULL)){
        if((atualRem->valor)!=1){
            return false;
        }
        }
        if((colunaInsere==8)&&(atualIns==NULL)){
        if((atualRem->valor)!=1){
            return false;
        }
        }
        if((colunaInsere==9)&&(atualIns==NULL)){
        if((atualRem->valor)!=1){
            return false;
        }
        }
        if((colunaInsere==10)&&(atualIns==NULL)){
        if((atualRem->valor)!=1){
            return false;
        }
        }
        if((colunaInsere==7)&&(atualIns!=NULL)){
        if((atualIns->naipe)!=(atualRem->naipe)){
                printf("Os Naipes nao iguais. Nao pode guardar\n");
                return false;
            }
          if((atualIns->valor+1) != atualRem->valor){

return false;}
        }
        if((colunaInsere==8)&&(atualIns!=NULL)){
           if((atualIns->naipe)!=(atualRem->naipe)){
                printf("Os Naipes nao iguais. Nao pode guardar\n");
                return false;
            }
          if((atualIns->valor+1) != atualRem->valor){

return false;}
        }
             if((colunaInsere==8)&&(atualIns!=NULL)){
           if((atualIns->naipe)!=(atualRem->naipe)){
                printf("Os Naipes nao iguais. Nao pode guardar\n");
                return false;
            }
          if((atualIns->valor+1) != atualRem->valor){

return false;}
        }
             if((colunaInsere==10)&&(atualIns!=NULL)){
           if((atualIns->naipe)!=(atualRem->naipe)){
                printf("Os Naipes nao iguais. Nao pode guardar\n");
                return false;
            }
          if((atualIns->valor+1) != atualRem->valor){

return false;}
        }
         if(atualIns==NULL){
            pilhaJogo[colunaInsere]=atualRem;
        }
        if(antRem == NULL){
            pilhaJogo[colunaRemove] = NULL;
        }else{
            antRem->prox = NULL;
        }
        if(atualIns!=NULL){
        atualIns->prox = atualRem;}
        if( (linhaEscondida[colunaRemove] > -1) && ((linhaEscondida[colunaRemove]+1)==linhaRemove)){
            linhaEscondida[colunaRemove] --;
        }
        return true;}
    }

void criarGuardar(){
    int linhaGuardar, sorteio,aux;
    int colunaGuardar = 7;
    noCarta* atual;
    for(linhaGuardar=7;linhaGuardar<13;linhaGuardar++){
        linhaEscondida[linhaGuardar] = 0;
    }
    linhaGuardar=1;
   colunaGuardar=7;
    while( quantMonte > MAX_MONTE){
        for(aux=0;aux<linhaGuardar;aux++){

        pilhaJogo[colunaGuardar] = NULL;
        }
        colunaGuardar++;
        linhaGuardar++;
    }
}


void imprimirGuardar(){
    int colunaGuardar = 0;
    int linhaGuardar = 0;
    noCarta * atual[13];
    int pilhaImpressa = 0;
    printf("                           Guardar                                \n");
    printf("     ");
    //inicializando atual com o inicio de cada pilhaJogo
    for(colunaGuardar=7; colunaGuardar<13; colunaGuardar++){
        printf("   %2d    ", colunaGuardar);

        atual[colunaGuardar] = pilhaJogo[colunaGuardar];
    }//endfor
    printf("\n");
    // imprimir as pilhas
    while (pilhaImpressa < 13){
        pilhaImpressa = 0;
        printf(" %2d  ", linhaGuardar);

        for(colunaGuardar=7; colunaGuardar<13; colunaGuardar++){
            if(atual[colunaGuardar] == NULL){
                printf("         ");
                pilhaImpressa++;
            }else{

                if(linhaGuardar<= linhaEscondida[colunaGuardar]){
                    printf("[??][??] ");

                }else{

                    printf("[%2d][%c] ", atual[colunaGuardar]->valor, (atual[colunaGuardar]->naipe+1));
                }//endif
                atual[colunaGuardar] = atual[colunaGuardar]->prox;
            }//endif
        }//endfor
        //incrementando a linha da pilhaJogo
        linhaGuardar++;
        printf("\n");
    }//endwhile
}//imprimirPilhaJogo

int main(int argc, char * argv[]){
    char opcao;
    int colRem, linRem, colIns,columover, score=0;
    criarMonte();
    embaralharMonte();
    criarPilhaJogo();

    while ( true ){
        system("cls");
        imprimirPilhaJogo();
        imprimirMonte();
        printf("O ceu e para onde deve-se mover as cartas para   \n");
        printf("formar-se os naipes completos.\n");
        printf("Score: %d\n", score);
        printf("Selecione uma opcao:\n");
        printf("0-Sair\n");
        printf("1-Mover Carta do 'Jogo'\n");
        printf("2-Mover Carta do 'Monte'\n");
        opcao = getchar();
        switch(opcao){
            case '0':
                return 0;
                break;
            case '1':
                printf("remover |coluna,linha|\n:");
                scanf("%d,%d", &colRem, &linRem);
                printf("Inserir carta(s) na coluna:\n");
                scanf("%d", &colIns);
                if(moveCartasPilhaJogo(colRem, linRem, colIns) == false){
                    printf("Movimento Invalido\n");
                    getchar();
                }//endif
                score++;
                break;

                case '2':
                printf("Digite para qual coluna deseja mover a carta do monte\n");
                scanf("%d",&columover);
                (moverMontePilhaJogo(columover));
                    getchar();
                                    score++;
                  break;
        }
        //switch
    }//while
    getchar();
    return 0;
}//main
