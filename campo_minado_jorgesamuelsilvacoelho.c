// Importação das bibliotecas que serão utilizadas no programa.

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Declaração da struct coordenada, utilizada para armazenar o local onde as bombas são posicionadas.

typedef struct coordenada {
  int x;
  int y;
} Coordenada;

// Declaração da struct campo, utilizada para armazenar cada elemento da matriz que representa o campo minado, podendo ser usada para verificar se há bomba no elemento, quantas bombas estão próximas e se o elemento está visível para o usuário ou não.

typedef struct campo {
  int quantBombas;
  bool ehVisivel;
} Campo;

// Declaração das funções que serão utilizadas no programa.

int escaneiaDificuldade();

int retornaTamanhoCampo();

int verificaCoordenada(int tamanho, int x, int y);

int retornaQuantBombas(int tamanho);

void defineLocaldasBombas(Coordenada vetor[], int quantBombas, int tamanho);

void adicionaValoresMatriz(Campo **matriz, int tamanho);

void posicionaBombas(Coordenada *vetor, int quantBombas, int tamanho, Campo **matriz);

void imprimeMatriz(Campo **matriz, int tamanho);

void tornaCamposVisiveis(Campo **matriz, int tamanho);

int verificaValidadeCoordenada(Coordenada vetor[], int tamanho, Coordenada nova);

void verificaMatriz(Campo ** matriz, int tamanho);

void verificaVetor(Coordenada vetor[], int tamanho);

int main(void) {

  int tamanhoMat = retornaTamanhoCampo();

  Campo **matriz = (Campo **)malloc(tamanhoMat * sizeof(Campo *));

  for (int i = 0; i < tamanhoMat; i++) {
    matriz[i] = (Campo *)malloc(tamanhoMat * sizeof(Campo));
  }

  int quantBombas = retornaQuantBombas(tamanhoMat);

  int quantCamposSemBomba = tamanhoMat * tamanhoMat - quantBombas; // Quantidade de campos que não possuem bombas.

  // O vetorBombas foi criado como forma de armazenar as coordenadas das bombas, que posteriormente precisam ser adicionadas à matriz.

  Coordenada *vetorBombas = (Coordenada *)malloc(quantBombas * sizeof(Coordenada));

  verificaVetor(vetorBombas, quantBombas); // Verifica se há espaço para o vetorBombas.

  verificaMatriz(matriz, tamanhoMat); // Verifica se há espaço para a matriz.

  defineLocaldasBombas(vetorBombas, quantBombas, tamanhoMat);

  // Função criada para igualar os elementos da matriz ao padrão de 0.
  
  adicionaValoresMatriz(matriz, tamanhoMat);

  // Função criada para posicionar as bombas na matriz de acordo com as coordenadas armazenadas no vetorBombas.

  posicionaBombas(vetorBombas, quantBombas, tamanhoMat, matriz);

  imprimeMatriz(matriz, tamanhoMat);

  // Estrutura de repetição utilizada para pedir coordenadas para o usuário enquanto ainda houverem campos sem bomba que ainda não foram revelados. 
  
  while (quantCamposSemBomba > 0) {
    printf("\n");
    printf("Digite as coordenadas do campo que deseja verificar, escreva no formato ""x,y""\n");
    printf("\n");
    int x, y, resultado;
    bool gameOver = 0;

    /* 
    Lógica criada para verificar se a coordenada que o usuário escolheu está dentro dos limites da matriz.
    A primeira coisa a se fazer é verificar se a coordenada que o usuário escolheu está dentro dos limites da matriz que representa o campo minado. Sendo assim, a função verificaCoordenada() é chamada para fazer essa verificação.
    
    Caso a coordenada esteja dentro dos limites da matriz, há 3 casos:
    1. Se o elemento da matriz na coordenada que o usuário escolheu já estiver vísivel, imprime "Você já abriu esse campo".
    2. Se o elemento da matriz na coordenada que o usuário escolheu não estiver vísivel e não houver bomba na coordenada escolhida, imprime "Ufa, sem bombas por aqui!".
    3. Se o elemento da matriz na coordenada que o usuário escolheu não estiver vísivel e houver bomba na coordenada escolhida, imprime "game over".

    Caso a coordenada não esteja demtro dos limites da matriz, imprime "Coordenada inválida!".

    O do while foi utilziado para tratamento de exceções que dependem do input do usuário.
    */
    
    do {
      resultado = scanf("%d,%d", &x, &y);

      int coordenadaX = x - 1;
      int coordenadaY = y - 1;

      if (resultado == 2) {
        if (verificaCoordenada(tamanhoMat, coordenadaX, coordenadaY)) {
          if (matriz[coordenadaX][coordenadaY].ehVisivel) {
            printf("\n");
            printf("Você já abriu esse campo!\n");
            printf("\n");
          } else {
            if (matriz[coordenadaX][coordenadaY].quantBombas != -1) {
              matriz[coordenadaX][coordenadaY].ehVisivel = 1;
              printf("\n");
              printf("Ufa, sem bombas por aqui!\n");
              printf("\n");
              imprimeMatriz(matriz, tamanhoMat);
              printf("\n");
              printf("Digite mais coordenadas, no formato ""x,y"", para continuar\n");
              printf("\n");
              quantCamposSemBomba--;
            } else {
              printf("\n");
              printf("game over\n");
              printf("\n");
              tornaCamposVisiveis(matriz, tamanhoMat);
              imprimeMatriz(matriz, tamanhoMat);
              gameOver = 1;
              break;
            }
          }
        } else {
          printf("\n");
          printf("Coordenada inválida!\n");  
          printf("\n");
        }
      } else {
        printf("\n");
        printf("A coordenada que você inseriu é inválida! Digite no formato: ""numero,numero""\n");
        printf("\n");

        while (getchar() != '\n'); // Limpa o buffer de entrada, caso o usuário insira um input inválido.
      }

      if (quantCamposSemBomba == 0) {
        break;
      }

    } while (1);

    if(gameOver) {
      break;
    }
  }

  // Se o usuário sair do loop e a quantidade de campos sem bomba for igual a zero, quer dizer que ele ganhou o jogo. Logo, imprime "parabens, voce eh fera".
  
  if(quantCamposSemBomba == 0) {
    printf("parabens, voce eh fera\n");
    tornaCamposVisiveis(matriz, tamanhoMat);
    imprimeMatriz(matriz, tamanhoMat);
  }

  // Liberação da memória alocada para o vetor e a matriz alocada dinamicamente.

  free(vetorBombas);

  for(int i = 0; i < tamanhoMat; i++) {
    free(matriz[i]);
  }

  free(matriz);
}

// Função criada para retornar a dificuldade do jogo, escolhida pelo usuário. Há tratamento de exceções para quando o usuário digita qualquer valor que não seja, 1, 2 ou 3.

int escaneiaDificuldade() {
  int dificuldade, resultado;
  printf("Selecione uma das seguintes dificuldades:\n");
  printf("\u20221- Fácil\n\u20222- Médio\n\u20223- Difícil\n");
  
  do {
    resultado = scanf("%d", &dificuldade);

    if (resultado == 1 && (dificuldade == 1 || dificuldade == 2 || dificuldade == 3)) {
      break;
    } else {
      printf("Essa dificuldade não está entre as dificuldades oferecidas! "
        "Escolha entre uma das seguintes opções:\n");
      printf("\u20221- Fácil\n\u20222- Médio\n\u20223- Difícil\n");
      
      while (getchar() != '\n'); // Limpa o buffer de entrada, caso o usuário insira um input inválido.
    }

  } while (1);

  return dificuldade;
}

// Verifica se há espaço para a matriz

void verificaMatriz(Campo ** matriz, int tamanho) {
  if (matriz == NULL) {
    printf("Memória insuficiente");
    exit(1);
  }

  for(int i = 0; i < tamanho; i++){
    if(matriz[i] == NULL) {
      printf("Memória insuficiente");
      exit(1);
    }
  }
}

// Verifica se há espaço para o vetor

void verificaVetor(Coordenada vetor[], int tamanho) {
  if (vetor == NULL) {
    printf("Memória insuficiente");
    exit(1);
  }
}

// Função que recebe a coordenada escolhida pelo usuário e verifica se ela está dentro dos limites da matriz, que varia de acordo com o tamanho dela, parâmetro também recebido pela função.

int verificaCoordenada(int tamanho, int x, int y) {
  if (x < 0 || x >= tamanho || y < 0 || y >= tamanho) {
    return 0;
  }
  return 1;
}

// Função criada para retorna o tamanho do campo minado, de acordo com a dificuldade escolhida pelo usuário, essa função chama a escaneiaDificuldade() pois o tamanho do campo minado depende da dificuldade escolhida.

int retornaTamanhoCampo() {
  int retorno;

  int dificuldade = escaneiaDificuldade();

  if (dificuldade == 1) {
    retorno = 10;
  } else if (dificuldade == 2) {
    retorno = 20;
  } else {
    retorno = 30;
  }

  return retorno;
}

// Função criada, para retornar a quantidade de bombas que serão posicionadas no campo minado, de acordo com o tamanho da matriz, que é passado como parâmetro para a função.

int retornaQuantBombas(int tamanho) {
  int retorno;

  if (tamanho == 10) {
    retorno = 3;
  } else if (tamanho == 20) {
    retorno = 6;
  } else {
    retorno = 9;
  }

  return retorno;
}

// Função que percorre o vetor que armazena as coordenadas em que ficarão as bombas, e gera números aleatórios no intervalo de 0 a tamanho da matriz - 1 para serem as coordenadas das bombas.

void defineLocaldasBombas(Coordenada vetor[], int quantBombas, int tamanho) {
  int x, y, quantCoordenadas;
  quantCoordenadas = 0;
  srand(time(NULL));

  while (quantCoordenadas < quantBombas) {
    Coordenada novaCoordenada;
    novaCoordenada.x = rand() % tamanho;
    novaCoordenada.y = rand() % tamanho;

    if(!verificaValidadeCoordenada(vetor, tamanho, novaCoordenada)) {
      vetor[quantCoordenadas].x = novaCoordenada.x;
      vetor[quantCoordenadas].y = novaCoordenada.y;
      quantCoordenadas ++;
    }
  }
}

// Função para verificar se a coordenada gerada aleatoriamente para conter uma bomba já existe no vetor de coordenadas das bombas. Caso a coordenada já exista, gera novamente outra coordenada.

int verificaValidadeCoordenada(Coordenada vetor[], int tamanho, Coordenada nova) {
    for (int i = 0; i < tamanho; i++) {
        if (vetor[i].x == nova.x && vetor[i].y == nova.y) {
            return 1; 
        }
    }
    return 0;
}

// Função criada para preencher a matriz com o seu padrão de quantidade de bombas = 0 e visibilidade = 0.

void adicionaValoresMatriz(Campo **matriz, int tamanho) {
  for (int i = 0; i < tamanho; i++) {
    for (int j = 0; j < tamanho; j++) {
      matriz[i][j].quantBombas = 0;
      matriz[i][j].ehVisivel = 0;
    }
  }
}

// Função criada para mudar a visibilidade de todos os campos da matrizes para 1, tornando os campos visíveis.

void tornaCamposVisiveis(Campo **matriz, int tamanho) {
  for (int i = 0; i < tamanho; i++) {
    for (int j = 0; j < tamanho; j++) {
      matriz[i][j].ehVisivel = 1;
    }
  }
}

/*
  Função criada para posicionar as bombas na matriz, de acordo com as coordenadas presentes no vetor que armazena as coordenadas das bombas.
  O padrão estabelecido para as bombas é -1, que representa que há bomba naquela coordenada.
*/
  
void posicionaBombas(Coordenada *vetor, int quantBombas, int tamanho, Campo **matriz) {
  for (int i = 0; i < quantBombas; i++) {
    int x = vetor[i].x;
    int y = vetor[i].y;

    matriz[x][y].quantBombas = -1;

    // Por se tratar de um jogo de campo minado, é necessário que as coordenadas adjacentes à bomba alertem ao usuário quantas bombas estão próximas, assim sendo, é necessário criar uma estrutura de repetição para percorrer as coordenadas adjacentes à bomba e adicionar 1 à quantidade de bombas presentes nas coordenadas adjacentes àquela coordenada.
    
    for (int i = x - 1; i <= x + 1; i++) {
      for (int j = y - 1; j <= y + 1; j++) {

        // É necessário verificar se as coordenadas adjacentes à bomba estão dentro dos limites da matriz e também se não são a própria coordenada da bomba. A quantidade de bombas adjacentes só aumenta caso esses critérios sejam atendidos.
        
        if (i != x || j != y) {
          if (i >= 0 && i < tamanho && j >= 0 && j < tamanho) {
            if (matriz[i][j].quantBombas != -1) {
              matriz[i][j].quantBombas += 1;
            }
          }
        }
      }
    }
  }
}

void imprimeMatriz(Campo **matriz, int tamanho) {

  // Exibe espaçamentos e números das colunas da matriz.
  printf("    ");
  for(int i = 0; i < tamanho; i++) {
    if(i < 8) {
      printf(" %d ", i + 1);
    } else {
      printf(" %d", i + 1);
    }
  }
  printf("\n");
  printf("\n");

  // Exibe espaçamentos e números das linhas da matriz.
  
  for (int i = 0; i < tamanho; i++) {
    printf("%d", i + 1);
    if(i < 9) {
      printf("   ");
    } else {
      printf("  ");
    }

    // Percorre os elementos da matriz e verifica se cada elemento é visível para o usuário ou não, imprimindo a quantidade de bombas na coordenada caso seja visível ou "x" caso não seja.
    
    for (int j = 0; j < tamanho; j++) {
      if (matriz[i][j].ehVisivel) {
        if(matriz[i][j].quantBombas == -1) {
          printf("%d ", matriz[i][j].quantBombas);
        } else {
          printf(" %d ", matriz[i][j].quantBombas);
        }
      } else {
        printf(" x ");
      }
    }
    printf("\n");
  }
}
