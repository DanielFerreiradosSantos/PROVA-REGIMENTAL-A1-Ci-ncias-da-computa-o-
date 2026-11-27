Sistema de Operações Matriciais em C

Sobre o projeto

Este projeto foi desenvolvido como uma atividade de programação em linguagem C, utilizando como base os conteúdos estudados durante o segundo semestre de Ciência da Computação.

A proposta é trabalhar com matrizes e realizar diferentes operações matemáticas, utilizando também outros recursos da linguagem que foram estudados durante a disciplina.

Procurei organizar o código de uma maneira simples e funcional, separando as tarefas em funções e utilizando variáveis com nomes curtos e objetivos.

Funcionalidades

O programa permite:

Cadastrar de 2 até 5 matrizes.

Definir a quantidade de linhas e colunas de cada matriz.

Informar individualmente os valores de cada elemento.

Realizar adição de matrizes.

Realizar subtração de matrizes.

Realizar multiplicação de matrizes.

Realizar divisão matricial por meio da matriz inversa.

Verificar condições necessárias para cada operação.

Consultar o histórico das operações realizadas.

Organizar o histórico utilizando Bubble Sort ou Quick Sort.

Salvar o histórico em um arquivo de texto.

Conteúdos utilizados

Durante o desenvolvimento, foram aplicados diferentes assuntos estudados ao longo do semestre:

Variáveis e tipos de dados.

Entrada e saída de informações.

Operadores matemáticos e relacionais.

Estruturas condicionais (if, else e switch).

Estruturas de repetição (for, while e do-while).

Vetores e matrizes.

Funções.

Estruturas (struct).

Ponteiros.

Manipulação de arquivos.

Bubble Sort.

Quick Sort.

Recursividade.

O programa foi dividido em funções para que cada parte tenha uma responsabilidade específica.

Algumas funções ficam responsáveis pela leitura e exibição das matrizes, enquanto outras realizam os cálculos matemáticos.

Também foram criadas funções para registrar as operações, mostrar o histórico, organizar os registros e salvar as informações em um arquivo.

Dessa maneira, a função principal (main) fica responsável por controlar o funcionamento do programa e apresentar o menu de opções.

Como funciona a divisão matricial?

A divisão entre matrizes não funciona da mesma maneira que a divisão entre números comuns.

Neste programa, ela é realizada utilizando a matriz inversa, seguindo a expressão:

A / B = A × B⁻¹

Para isso, a matriz divisora precisa ser quadrada e possuir uma inversa. Caso essas condições não sejam atendidas, o programa informa que a operação não pode ser realizada.

Como executar

É necessário ter um compilador C instalado, como o GCC.
Com o arquivo SISTEMA DE CALCULADORA DE MATRIZES.c aberto na pasta do projeto, execute no terminal:

gcc main.c -o matrizes.exe -lm

Depois, execute o programa no Windows:

.\matrizes.exe

Arquivos

SISTEMA DE CALCULADORA DE MATRIZES.c: contém o código-fonte completo do programa.

historico.txt: arquivo criado pelo próprio programa para armazenar o histórico das operações.

Considerações finais

Este projeto reúne diferentes conteúdos que estudei durante o semestre em uma única aplicação.

Além de trabalhar com operações matriciais, foi uma oportunidade de praticar a organização do código, a criação de funções, o uso de estruturas de dados e a aplicação de algoritmos de ordenação.

A proposta também me ajudou a visualizar como diferentes recursos da linguagem C podem trabalhar juntos para resolver um problema.

Linguagem utilizada: C
Compilador: GCC
Ambiente de desenvolvimento: Dev c++
