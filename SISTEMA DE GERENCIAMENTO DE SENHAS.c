
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_PAC 100

// Dados de cada paciente.
typedef struct {
    char gen;
    int idade;
    int gest;
    int lact;
    int nec;
    int obes;
    int cat;
    char senha[10];
} Paciente;

// Cada fila armazena os pacientes de uma categoria.
typedef struct {
    Paciente pac[MAX_PAC];
    int qtd;
} Fila;


// Prototipos das funcoes.
int lerResposta(char pergunta[]);
void cadastrar(Fila *normal, Fila *pref, Fila *urg,
               int *numN, int *numP, int *numU);

int classificar(Paciente pac);
void gerarSenha(Paciente *pac, int *numN,
                int *numP, int *numU);

void adicionar(Fila *fila, Paciente pac);
Paciente retirar(Fila *fila);
Paciente *proxima(Fila *normal, Fila *pref, Fila *urg);

void consultar(Fila *normal, Fila *pref, Fila *urg);
void chamar(Fila *normal, Fila *pref, Fila *urg,
            Paciente *atual, int *em_atend);

void finalizar(Paciente *atual, int *em_atend);

void mostrarFila(Fila fila, char nome[]);
void painel(Fila *normal, Fila *pref, Fila *urg,
            Paciente atual, int em_atend);


// Leitura de respostas simples: 1 para sim e 0 para nao.
int lerResposta(char pergunta[]) {
    int resp;

    do {
        printf("%s (1-Sim / 0-Nao): ", pergunta);
        scanf("%d", &resp);

        if (resp != 0 && resp != 1) {
            printf("Resposta invalida.\n");
        }

    } while (resp != 0 && resp != 1);

    return resp;
}


// Classifica o paciente conforme as regras da atividade.
int classificar(Paciente pac) {

    // Urgencia tem prioridade sobre as outras categorias.
    if (pac.idade > 80) {
        return 2;
    }

    // Verifica as condicoes de atendimento preferencial.
    if (pac.gest == 1 || pac.lact == 1 ||
        pac.nec == 1 || pac.obes == 1) {
        return 1;
    }

    if (pac.gen == 'F' && pac.idade >= 60) {
        return 1;
    }

    if (pac.gen == 'M' && pac.idade >= 65) {
        return 1;
    }

    return 0;
}


// Gera uma senha independente para cada categoria.
void gerarSenha(Paciente *pac, int *numN,
                int *numP, int *numU) {

    if (pac->cat == 2) {
        (*numU)++;
        sprintf(pac->senha, "U%03d", *numU);
    }
    else if (pac->cat == 1) {
        (*numP)++;
        sprintf(pac->senha, "P%03d", *numP);
    }
    else {
        (*numN)++;
        sprintf(pac->senha, "N%03d", *numN);
    }
}


// Adiciona um paciente ao final da fila.
void adicionar(Fila *fila, Paciente pac) {

    if (fila->qtd < MAX_PAC) {
        fila->pac[fila->qtd] = pac;
        fila->qtd++;
    }
}


// Retira o primeiro paciente da fila.
Paciente retirar(Fila *fila) {
    Paciente pac;
    int i;

    pac = fila->pac[0];

    // Desloca os outros pacientes uma posicao.
    for (i = 0; i < fila->qtd - 1; i++) {
        fila->pac[i] = fila->pac[i + 1];
    }

    fila->qtd--;

    return pac;
}


// Encontra a proxima senha seguindo a ordem de prioridade.
Paciente *proxima(Fila *normal, Fila *pref, Fila *urg) {

    if (urg->qtd > 0) {
        return &urg->pac[0];
    }

    if (pref->qtd > 0) {
        return &pref->pac[0];
    }

    if (normal->qtd > 0) {
        return &normal->pac[0];
    }

    return NULL;
}


// Cadastra um paciente e encaminha para sua fila.
void cadastrar(Fila *normal, Fila *pref, Fila *urg,
               int *numN, int *numP, int *numU) {

    Paciente pac;

    printf("\n=== CADASTRO DE PACIENTE ===\n");

    printf("Genero (M/F/O): ");
    scanf(" %c", &pac.gen);

    pac.gen = toupper(pac.gen);

    while (pac.gen != 'M' && pac.gen != 'F' &&
           pac.gen != 'O') {
        printf("Genero invalido. Informe M, F ou O: ");
        scanf(" %c", &pac.gen);
        pac.gen = toupper(pac.gen);
    }

    printf("Idade: ");
    scanf("%d", &pac.idade);

    while (pac.idade < 0) {
        printf("Idade invalida. Informe novamente: ");
        scanf("%d", &pac.idade);
    }

    pac.gest = 0;
    pac.lact = 0;

    // Perguntas especificas para pacientes do genero feminino.
    if (pac.gen == 'F') {
        pac.gest = lerResposta("A paciente esta gestante?");
        pac.lact = lerResposta("A paciente esta lactante?");
    }

    pac.nec = lerResposta("Possui necessidade especial?");
    pac.obes = lerResposta("Possui condicao de obesidade?");

    // Define a categoria automaticamente.
    pac.cat = classificar(pac);

    // Gera a senha de acordo com a categoria.
    gerarSenha(&pac, numN, numP, numU);

    // Encaminha para a fila correspondente.
    if (pac.cat == 2) {

        if (urg->qtd >= MAX_PAC) {
            printf("Fila urgente cheia.\n");
            return;
        }

        adicionar(urg, pac);
        printf("\nCategoria: URGENTE\n");
    }
    else if (pac.cat == 1) {

        if (pref->qtd >= MAX_PAC) {
            printf("Fila preferencial cheia.\n");
            return;
        }

        adicionar(pref, pac);
        printf("\nCategoria: PREFERENCIAL\n");
    }
    else {

        if (normal->qtd >= MAX_PAC) {
            printf("Fila normal cheia.\n");
            return;
        }

        adicionar(normal, pac);
        printf("\nCategoria: NORMAL\n");
    }

    printf("Senha gerada: %s\n", pac.senha);
}


// Consulta qual sera a proxima senha.
void consultar(Fila *normal, Fila *pref, Fila *urg) {
    Paciente *pac;

    pac = proxima(normal, pref, urg);

    printf("\n=== PROXIMA SENHA ===\n");

    if (pac == NULL) {
        printf("Nao existem pacientes aguardando.\n");
        return;
    }

    printf("Senha: %s\n", pac->senha);

    if (pac->cat == 2) {
        printf("Categoria: URGENTE\n");
    }
    else if (pac->cat == 1) {
        printf("Categoria: PREFERENCIAL\n");
    }
    else {
        printf("Categoria: NORMAL\n");
    }
}


// Chama o proximo paciente da fila.
void chamar(Fila *normal, Fila *pref, Fila *urg,
            Paciente *atual, int *em_atend) {

    Paciente *pac;

    if (*em_atend == 1) {
        printf("\nFinalize o atendimento atual antes de chamar outro.\n");
        return;
    }

    pac = proxima(normal, pref, urg);

    if (pac == NULL) {
        printf("\nNao existem pacientes na fila.\n");
        return;
    }

    // Retira o paciente da fila correspondente.
    if (pac->cat == 2) {
        *atual = retirar(urg);
    }
    else if (pac->cat == 1) {
        *atual = retirar(pref);
    }
    else {
        *atual = retirar(normal);
    }

    *em_atend = 1;

    printf("\n=== CHAMADA REALIZADA ===\n");
    printf("Senha chamada: %s\n", atual->senha);
}


// Finaliza o atendimento atual.
void finalizar(Paciente *atual, int *em_atend) {

    if (*em_atend == 0) {
        printf("\nNao existe atendimento em andamento.\n");
        return;
    }

    printf("\nAtendimento da senha %s finalizado.\n",
           atual->senha);

    *em_atend = 0;
}


// Mostra os pacientes de uma fila.
void mostrarFila(Fila fila, char nome[]) {
    int i;

    printf("\n%s: %d paciente(s)\n", nome, fila.qtd);

    if (fila.qtd == 0) {
        printf("Nenhuma senha aguardando.\n");
    }

    for (i = 0; i < fila.qtd && i < 3; i++) {
        printf("%d - %s\n", i + 1, fila.pac[i].senha);
    }

    if (fila.qtd > 3) {
        printf("... e mais %d paciente(s).\n", fila.qtd - 3);
    }
}


// Painel geral de atendimento.
void painel(Fila *normal, Fila *pref, Fila *urg,
            Paciente atual, int em_atend) {

    printf("\n========== PAINEL DE ATENDIMENTO ==========\n");

    if (em_atend == 1) {
        printf("SENHA EM ATENDIMENTO: %s\n", atual.senha);
    }
    else {
        printf("SENHA EM ATENDIMENTO: Nenhuma\n");
    }

    printf("\n--- PROXIMAS SENHAS ---\n");

    mostrarFila(*urg, "URGENTES");
    mostrarFila(*pref, "PREFERENCIAIS");
    mostrarFila(*normal, "NORMAIS");

    printf("\n--- TOTAL DE PACIENTES EM ESPERA ---\n");

    printf("Urgentes: %d\n", urg->qtd);
    printf("Preferenciais: %d\n", pref->qtd);
    printf("Normais: %d\n", normal->qtd);

    printf("Total: %d\n",
           urg->qtd + pref->qtd + normal->qtd);

    printf("===========================================\n");
}


// Funcao principal: controla o menu e as operacoes.
int main() {

    Fila normal = {{{0}}, 0};
    Fila pref = {{{0}}, 0};
    Fila urg = {{{0}}, 0};

    Paciente atual;

    int numN = 0;
    int numP = 0;
    int numU = 0;

    int op;
    int em_atend = 0;

    do {
        printf("\n========== SISTEMA DE ATENDIMENTO ==========\n");
        printf("1 - Cadastrar paciente\n");
        printf("2 - Consultar proxima senha\n");
        printf("3 - Chamar paciente\n");
        printf("4 - Finalizar atendimento\n");
        printf("5 - Mostrar painel\n");
        printf("0 - Encerrar sistema\n");
        printf("Escolha: ");
        scanf("%d", &op);

        switch (op) {

            case 1:
                cadastrar(&normal, &pref, &urg,
                          &numN, &numP, &numU);
                break;

            case 2:
                consultar(&normal, &pref, &urg);
                break;

            case 3:
                chamar(&normal, &pref, &urg,
                       &atual, &em_atend);
                break;

            case 4:
                finalizar(&atual, &em_atend);
                break;

            case 5:
                painel(&normal, &pref, &urg,
                       atual, em_atend);
                break;

            case 0:
                printf("\nSistema encerrado.\n");
                break;

            default:
                printf("\nOpcao invalida.\n");
        }

    } while (op != 0);

    return 0;
}
