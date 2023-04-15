#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>


// Gerando o Xadrez e a Vetor para os Dados Anteriores
int** gerarXadrez(int n){
  int** Xadrez = (int **)malloc(n * sizeof(int*));
  
  for (int i=0; i < n; i++){
    Xadrez[i] = (int*) malloc(n * sizeof(int));
    for(int j=0; j < n; j++){
      Xadrez[i][j] = 0;
    }
  }
  
  return Xadrez;
}

int * gerarSolucao(int n){
  int *solucao = (int*)malloc(n*sizeof(int));
  for(int i=0; i < n; i++){
    solucao[i] = -1;
  }
  return solucao;
}

// --=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=


/* Funções Auxiliares que ajudam a verificar se a posição
indicada na matriz vai ser possivel...
*/
int Horizontal(int **matriz, int posicaoLinha, int posicaoColuna, int n){
  for(int i=0; i < n; i++){
    if(i != posicaoColuna){
      if(matriz[posicaoLinha][i] != 0){
        return 0;
      }
    }
  }
  return 1;
}

int Vertical(int **matriz, int posicaoColuna, int posicaoLinha, int n){
  for(int i=0; i < n; i++){
    if(i != posicaoLinha){
      if(matriz[i][posicaoColuna] != 0){
        return 0;
      }
    }
  }
  return 1;
}

int DiagonalPrimaria(int **matriz, int posicaolinha, int posicaoColuna){
  int i = posicaolinha-1;
  int j = posicaoColuna-1;
  for(int k=0; i >= 0 && j >= 0; k--){
    if(matriz[i][j] != 0){
      return 0;
    }
    i--;
    j--;
  }
  return 1;
}

int DiagonalSecudanria(int **matriz, int posicaolinha, int posicaoColuna){
  int i = posicaolinha-1;
  int j = posicaoColuna+1;
  for(int k=0; i >= 0 && j <= 3; k--){
    if(matriz[i][j] != 0){
      return 0;
    }
    i--;
    j++;
  }
  return 1;
}

int TemNaHorizontal(int **matriz, int n){
  for(int i=0; i < n; i++ ){
    if(matriz[0][i] != 0){
      return 1;
    }
  }
  return 0;
}
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


// Função verificam a posição se é uma promessa
int Promessa(int **matriz, int PosLinha, int PosColuna, int n){
  if(Horizontal(matriz, PosLinha, PosColuna, n) && Vertical(matriz, PosColuna, PosLinha, n) && DiagonalPrimaria(matriz, PosLinha, PosColuna) && DiagonalSecudanria(matriz, PosLinha, PosColuna)){
      return 1;
    }
  return 0;
}
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


// Funções Auxiliares para adicionar ou remover na matriz e no vetor
int* AddDado(int *ListaDado, int linha, int dado){
  ListaDado[linha] = dado;
  return ListaDado;
}

int** AddMatriz(int **matriz, int linha, int coluna){
  matriz[linha][coluna] = 1;
  return matriz;
}

int** RemoverMatriz(int **matriz, int linha, int coluna){
  matriz[linha][coluna] = 0;
  return matriz;
}
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

void printfMatriz(int **matriz, int tamanho){
  printf("Matriz gerada:\n");
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

void liberarMatriz(int **matriz, int tamanho){
  for (int i = 0; i < tamanho; i++) {
        free(matriz[i]);
    }
    free(matriz);
}


// Função do BackTracking
int** BackTracking(int **matriz, int linha, int* DadoAnterior, int Booleano, int n){
  if(linha == n){
    return matriz;
  }else{
    for(int i=0; i < n; i++){
      if( !Booleano){
        if(Promessa(matriz, linha, i, n)){
        return BackTracking(AddMatriz(matriz, linha, i), linha+1, AddDado(DadoAnterior, linha, i), 0, n);}
      }else{
        if(i > DadoAnterior[linha] && DadoAnterior[linha] < n-1){
          if(Promessa(matriz, linha, i, n)){
        return BackTracking(AddMatriz(matriz, linha, i), linha+1, AddDado(DadoAnterior, linha, i), 0, n);}  
        }else{
          if(i == n-1 && linha == 0 ){
            return matriz;
          }
        }
      }
    }
  if(linha != n){
   return BackTracking(RemoverMatriz(matriz, linha-1, DadoAnterior[linha-1]), linha-1, DadoAnterior, 1, n);}
 }
}

void N_Rainha(int **matriz, int linha, int *DadoAnterior, int Booleano, int ordem){
  int **xadrez = BackTracking(matriz, linha, DadoAnterior, Booleano, ordem);
  if(TemNaHorizontal(xadrez, ordem)){
    printfMatriz(xadrez, ordem);
    liberarMatriz(xadrez, ordem);
  }else{
    printf("Não tem solucao");
    liberarMatriz(xadrez, ordem);
  }
  
}




int main(void) {
  int n;
  printf("Qual numero?");
  scanf("%i", &n);
  int* DadoAnterior = gerarSolucao(n);
  int **xadrez = gerarXadrez(n);
  N_Rainha(xadrez, 0, DadoAnterior, 0, n);

  return 0;
}