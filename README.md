# Campo Minado - Projeto Prático de Algoritmos e Estruturas de Dados I

O presente trabalho foi proposto como primeira forma avaliativa da disciplina Algoritmos e Estruturas de Dados I, disciplina essencial para o desenvolvimento da criatividade e do pensamento lógico, apresentando as principais estruturas de dados presentes na linguagem C.

## 💣 Começando

O jogo consiste em escolher células dentro de um tabuleiro, evitando que as células escolhidas contenham bombas. Caso o jogador consiga revelar todas as células que não possuem bombas, ele vence!

Nesse trabalho, o usuário pode escolher entre as seguintes dificuldades: Fácil, Médio e Difícil. De acordo com elas, o tabuleiro irá ter um tamanho e uma quantidade de bombas diferente. 

Segue imagem para ilustrar como é construído o tabuleiro

![1](https://github.com/user-attachments/assets/2f91832f-9384-4227-9c66-593212eb08cb)

As representações são meramente ilustrativas pois, para esse projeto, foi necessário que nas dificuldades fácil, médio e difiícil houvessem tabuleiros de ordem 10, 20 e 30 respectivamente. Cujas quantidades de bombas também aumentavam conforme o tamanho do tabuleiro, sendo 3,6 e 9 as quantidades de bombas presentes nos tabuleiros.


Importante lembrar que ao escolher uma célula que não possui bomba, o jogo alerta ao usuário a quantidade de bombas adjacentes aquela célula. Esse ponto é de suma importância para elaborar uma estratégia de jogo!

## 🚀 Como executar o projeto

Antes de começar, certifique-se de ter o compilador GCC instalado. Se você ainda não o tiver, siga as instruções abaixo para instalá-lo:

```bash

# •	Windows: Execute no terminal
$ wsl --install
$ sudo apt update
$ sudo apt install gcc

# •	Linux (Ubuntu/Debian): Execute no terminal
$ sudo apt update
$ sudo apt install gcc

# •	MacOS: Utilize o Homebrew
$ brew install gcc

```

Executando o projeto

```bash

$ gcc -o campo_minado campo_minado_jorgesamuelsilvacoelho.c
$ ./campo_minado

```



## 🛠️ Construído com

Mencione as ferramentas que você usou para criar seu projeto

* [C]([http://www.dropwizard.io/1.0.2/docs/](https://devdocs.io/c/)) - Linguagem de programação utilizada
* [Visual Studio Code]([https://maven.apache.org/](https://code.visualstudio.com/)) - IDE utilizada

## ✒️ Autores

Mencione todos aqueles que ajudaram a levantar o projeto desde o seu início

* **Desenvolvedor** - *Codificação do trabalho* - [Samuel Coelho](https://github.com/samuelcoelhoam)

Agradecimentos especiais ao ICOMP pelo suporte e pela base acadêmica fornecida ao longo da discipina de Algoritmos e Estruturas de Dados I, presente no curso Engenharia de Software, contribuindo diretamente para o desenvolvimento deste projeto.
