Sistema de Gerenciamento de Senhas de Atendimento Clínico

 Sobre o projeto

Este projeto foi desenvolvido como uma atividade de programação em linguagem C, utilizando como base os conteúdos estudados durante o segundo semestre de Ciência da Computação.

A proposta é criar um sistema simples para organizar senhas de atendimento de uma clínica, considerando diferentes categorias de prioridade.

O programa permite cadastrar pacientes, analisar suas informações, gerar senhas automaticamente e controlar a ordem de atendimento.

Procurei organizar o código de maneira simples e lógica, separando as funcionalidades em funções e utilizando estruturas que foram estudadas durante a disciplina.

 Funcionalidades

O sistema permite:

- Cadastrar pacientes.
- Informar gênero e idade.
- Registrar condições como gestação, lactação, necessidade especial e obesidade.
- Classificar automaticamente cada paciente.
- Gerar senhas sequenciais independentes para cada categoria.
- Consultar a próxima senha.
- Chamar o próximo paciente.
- Identificar o atendimento em andamento.
- Finalizar atendimentos.
- Visualizar um painel com as filas e suas quantidades.

 Categorias de atendimento

O programa trabalha com três categorias:

| Código | Categoria | Condição |
|---|---|---|
| N001 | Normal | Pacientes sem prioridade cadastrada |
| P001 | Preferencial | Pacientes que atendem às condições preferenciais da atividade |
| U001 | Urgente | Pacientes com idade superior a 80 anos |

A prioridade de chamada segue esta ordem:

1. Urgente.
2. Preferencial.
3. Normal.

Cada categoria possui sua própria numeração, mantendo a sequência de emissão das senhas.

 Conteúdos utilizados

Durante o desenvolvimento, foram aplicados diferentes conteúdos estudados no semestre:

- Variáveis e tipos de dados.
- Entrada e saída de informações.
- Operadores relacionais e lógicos.
- Estruturas condicionais (if, else e switch).
- Estruturas de repetição (for e do-while).
- Vetores.
- Estruturas (struct).
- Funções.
- Ponteiros.
- Manipulação de caracteres e textos.

 Organização do código

O programa foi dividido em funções para separar as responsabilidades.

Existem funções para cadastrar pacientes, classificar as informações, gerar senhas, adicionar e retirar pacientes das filas, consultar a próxima chamada e apresentar o painel de atendimento.

Também foram utilizadas estruturas para armazenar os dados dos pacientes e organizar as três categorias de atendimento.

A função principal (main) fica responsável por apresentar o menu e controlar as operações disponíveis.

 Funcionamento das filas

O sistema utiliza três filas independentes:

- Fila normal.
- Fila preferencial.
- Fila urgente.

A chamada respeita a prioridade entre as categorias. Dentro de cada fila, os pacientes são atendidos na mesma ordem em que receberam suas senhas.

Esse funcionamento segue o conceito FIFO (*First In, First Out*), no qual o primeiro elemento que entra é o primeiro a sair.

 Como executar

É necessário ter um compilador C instalado, como o GCC.

Com o arquivo SISTEMA DE GERENCIAMENTO DE SENHAS.c na pasta do projeto, execute no terminal:

bash
gcc "SISTEMA DE GERENCIAMENTO DE SENHAS.c" -o senhas.exe


Depois, execute no Windows:

bash
.\senhas.exe


 Arquivos

SISTEMA DE GERENCIAMENTO DE SENHAS.c: contém o código-fonte completo do programa.
README.md: apresenta informações sobre o projeto, suas funcionalidades e instruções de execução.

 Considerações finais

Este projeto foi uma oportunidade de trabalhar com estruturas de dados e organização de informações utilizando a linguagem C.

Além de praticar funções, vetores, estruturas e ponteiros, também pude aplicar a lógica de filas e prioridades em uma situação simulada.

A proposta foi reunir diferentes conteúdos estudados durante o semestre em um programa funcional, mantendo uma organização simples e facilitando o entendimento de cada parte do código.

Linguagem utilizada: C  
Compilador: GCC  
Ambiente de desenvolvimento:Visual Studio Code
