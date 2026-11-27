
#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAX_MAT 5
#define MAX_DIM 5
#define MAX_HIST 100
#define EPS 0.000000001

// Cada matriz possui dimensoes e seus elementos.
typedef struct {
    int lin;
    int col;
    double val[MAX_DIM][MAX_DIM];
} Matriz;

// Cada registro guarda uma operacao realizada.
typedef struct {
    char op[20];
    int lin;
    int col;
    double soma;
} Hist;

// Prototipos das funcoes.
void lerMatrizes(Matriz mx_mat[], int qtd);
void mostrarMatriz(Matriz mx);
Matriz somar(Matriz a, Matriz b);
Matriz subtrair(Matriz a, Matriz b);
Matriz multiplicar(Matriz a, Matriz b);
int inverter(Matriz a, Matriz *inv);
int dividir(Matriz a, Matriz b, Matriz *res);
double somarElementos(Matriz mx);

void registrar(Hist hist[], int *qtd_hist,
               char op[], Matriz res);

void mostrarHistorico(Hist hist[], int qtd_hist);
void bubble(Hist hist[], int qtd_hist);
void quick(Hist hist[], int inicio, int fim);
int particionar(Hist hist[], int inicio, int fim);
void salvarArquivo(Hist hist[], int qtd_hist);


// Recebe os dados de todas as matrizes.
void lerMatrizes(Matriz mx_mat[], int qtd) {
    int i, j, k;

    for (i = 0; i < qtd; i++) {
        printf("\nMATRIZ %d\n", i + 1);

        do {
            printf("Linhas: ");
            scanf("%d", &mx_mat[i].lin);

            printf("Colunas: ");
            scanf("%d", &mx_mat[i].col);

            if (mx_mat[i].lin < 1 || mx_mat[i].lin > MAX_DIM ||
                mx_mat[i].col < 1 || mx_mat[i].col > MAX_DIM) {
                printf("Dimensoes invalidas. Use valores de 1 a %d.\n",
                       MAX_DIM);
            }

        } while (mx_mat[i].lin < 1 || mx_mat[i].lin > MAX_DIM ||
                 mx_mat[i].col < 1 || mx_mat[i].col > MAX_DIM);

        for (j = 0; j < mx_mat[i].lin; j++) {
            for (k = 0; k < mx_mat[i].col; k++) {
                printf("Elemento [%d][%d]: ", j, k);
                scanf("%lf", &mx_mat[i].val[j][k]);
            }
        }
    }
}


// Exibe uma matriz organizada em linhas e colunas.
void mostrarMatriz(Matriz mx) {
    int i, j;

    for (i = 0; i < mx.lin; i++) {
        for (j = 0; j < mx.col; j++) {
            printf("%10.2lf", mx.val[i][j]);
        }
        printf("\n");
    }
}


// Realiza a adicao de duas matrizes.
Matriz somar(Matriz a, Matriz b) {
    Matriz res;
    int i, j;

    res.lin = a.lin;
    res.col = a.col;

    for (i = 0; i < a.lin; i++) {
        for (j = 0; j < a.col; j++) {
            res.val[i][j] = a.val[i][j] + b.val[i][j];
        }
    }

    return res;
}


// Realiza a subtracao de duas matrizes.
Matriz subtrair(Matriz a, Matriz b) {
    Matriz res;
    int i, j;

    res.lin = a.lin;
    res.col = a.col;

    for (i = 0; i < a.lin; i++) {
        for (j = 0; j < a.col; j++) {
            res.val[i][j] = a.val[i][j] - b.val[i][j];
        }
    }

    return res;
}


// Multiplica duas matrizes.
Matriz multiplicar(Matriz a, Matriz b) {
    Matriz res;
    int i, j, k;

    res.lin = a.lin;
    res.col = b.col;

    for (i = 0; i < res.lin; i++) {
        for (j = 0; j < res.col; j++) {
            res.val[i][j] = 0;

            for (k = 0; k < a.col; k++) {
                res.val[i][j] += a.val[i][k] * b.val[k][j];
            }
        }
    }

    return res;
}


// Calcula a inversa usando escalonamento.
int inverter(Matriz a, Matriz *inv) {
    double arm[MAX_DIM][MAX_DIM * 2];
    double aux, piv;
    int i, j, k, maior;
    int n;

    // A matriz precisa ser quadrada.
    if (a.lin != a.col) {
        return 0;
    }

    n = a.lin;

    // Monta a matriz aumentada [A | identidade].
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            arm[i][j] = a.val[i][j];
            arm[i][j + n] = (i == j) ? 1 : 0;
        }
    }

    for (i = 0; i < n; i++) {

        // Procura o maior pivo da coluna.
        maior = i;

        for (k = i + 1; k < n; k++) {
            if (fabs(arm[k][i]) > fabs(arm[maior][i])) {
                maior = k;
            }
        }

        // Troca as linhas quando necessario.
        if (maior != i) {
            for (j = 0; j < 2 * n; j++) {
                aux = arm[i][j];
                arm[i][j] = arm[maior][j];
                arm[maior][j] = aux;
            }
        }

        piv = arm[i][i];

        // Pivo muito proximo de zero: matriz sem inversa.
        if (fabs(piv) < EPS) {
            return 0;
        }

        // Divide a linha pelo pivo.
        for (j = 0; j < 2 * n; j++) {
            arm[i][j] /= piv;
        }

        // Zera os outros elementos da coluna.
        for (k = 0; k < n; k++) {
            if (k != i) {
                aux = arm[k][i];

                for (j = 0; j < 2 * n; j++) {
                    arm[k][j] -= aux * arm[i][j];
                }
            }
        }
    }

    // Copia o lado direito para a matriz inversa.
    inv->lin = n;
    inv->col = n;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            inv->val[i][j] = arm[i][j + n];
        }
    }

    return 1;
}


// Divide A por B usando A * inversa(B).
int dividir(Matriz a, Matriz b, Matriz *res) {
    Matriz inv;

    if (b.lin != b.col) {
        printf("A matriz divisora precisa ser quadrada.\n");
        return 0;
    }

    if (!inverter(b, &inv)) {
        printf("A matriz divisora nao possui inversa.\n");
        return 0;
    }

    if (a.col != inv.lin) {
        printf("Dimensoes incompativeis para a divisao.\n");
        return 0;
    }

    *res = multiplicar(a, inv);

    return 1;
}


// Soma todos os elementos de uma matriz.
double somarElementos(Matriz mx) {
    double total = 0;
    int i, j;

    for (i = 0; i < mx.lin; i++) {
        for (j = 0; j < mx.col; j++) {
            total += mx.val[i][j];
        }
    }

    return total;
}


// Registra uma operacao no vetor de historico.
void registrar(Hist hist[], int *qtd_hist,
               char op[], Matriz res) {

    if (*qtd_hist >= MAX_HIST) {
        printf("Historico cheio.\n");
        return;
    }

    strcpy(hist[*qtd_hist].op, op);
    hist[*qtd_hist].lin = res.lin;
    hist[*qtd_hist].col = res.col;
    hist[*qtd_hist].soma = somarElementos(res);

    (*qtd_hist)++;
}


// Mostra os registros realizados.
void mostrarHistorico(Hist hist[], int qtd_hist) {
    int i;

    if (qtd_hist == 0) {
        printf("\nNenhuma operacao registrada.\n");
        return;
    }

    printf("\n--- HISTORICO ---\n");

    for (i = 0; i < qtd_hist; i++) {
        printf("%d - %s | %dx%d | Soma: %.2lf\n",
               i + 1,
               hist[i].op,
               hist[i].lin,
               hist[i].col,
               hist[i].soma);
    }
}


// Ordenacao Bubble Sort: compara registros vizinhos.
void bubble(Hist hist[], int qtd_hist) {
    int i, j;
    Hist aux;

    for (i = 0; i < qtd_hist - 1; i++) {
        for (j = 0; j < qtd_hist - 1 - i; j++) {

            if (hist[j].soma > hist[j + 1].soma) {
                aux = hist[j];
                hist[j] = hist[j + 1];
                hist[j + 1] = aux;
            }
        }
    }
}


// Separa os registros em torno de um pivo.
int particionar(Hist hist[], int inicio, int fim) {
    double piv = hist[fim].soma;
    int i = inicio - 1;
    int j;
    Hist aux;

    for (j = inicio; j < fim; j++) {
        if (hist[j].soma <= piv) {
            i++;

            aux = hist[i];
            hist[i] = hist[j];
            hist[j] = aux;
        }
    }

    aux = hist[i + 1];
    hist[i + 1] = hist[fim];
    hist[fim] = aux;

    return i + 1;
}


// Quick Sort: organiza o historico de forma recursiva.
void quick(Hist hist[], int inicio, int fim) {
    int p;

    if (inicio < fim) {
        p = particionar(hist, inicio, fim);

        quick(hist, inicio, p - 1);
        quick(hist, p + 1, fim);
    }
}


// Grava o historico em um arquivo texto.
void salvarArquivo(Hist hist[], int qtd_hist) {
    FILE *arq;
    int i;

    arq = fopen("historico.txt", "w");

    if (arq == NULL) {
        printf("Nao foi possivel criar o arquivo.\n");
        return;
    }

    fprintf(arq, "HISTORICO DE OPERACOES MATRICIAIS\n\n");

    for (i = 0; i < qtd_hist; i++) {
        fprintf(arq, "%d - %s | %dx%d | Soma: %.2lf\n",
                i + 1,
                hist[i].op,
                hist[i].lin,
                hist[i].col,
                hist[i].soma);
    }

    fclose(arq);

    printf("Historico salvo em historico.txt.\n");
}


// Funcao principal: controla o programa.
int main() {
    Matriz mx_mat[MAX_MAT];
    Matriz res;

    Hist hist[MAX_HIST];

    int qtd, qtd_hist = 0;
    int op, i, valido;

    char nome_op[20];

    printf("=== SISTEMA DE OPERACOES MATRICIAIS ===\n");

    // Quantidade de matrizes.
    do {
        printf("\nQuantas matrizes deseja cadastrar? ");
        scanf("%d", &qtd);

        if (qtd < 2 || qtd > MAX_MAT) {
            printf("Informe de 2 a %d matrizes.\n", MAX_MAT);
        }

    } while (qtd < 2 || qtd > MAX_MAT);

    lerMatrizes(mx_mat, qtd);

    // Menu principal.
    do {
        printf("\n========== MENU ==========\n");
        printf("1 - Adicao\n");
        printf("2 - Subtracao\n");
        printf("3 - Multiplicacao\n");
        printf("4 - Divisao\n");
        printf("5 - Mostrar historico\n");
        printf("6 - Ordenar com Bubble Sort\n");
        printf("7 - Ordenar com Quick Sort\n");
        printf("0 - Salvar e sair\n");
        printf("Escolha: ");
        scanf("%d", &op);

        valido = 1;
        res = mx_mat[0];

        switch (op) {

            case 1:
                strcpy(nome_op, "Adicao");

                for (i = 1; i < qtd; i++) {
                    if (res.lin != mx_mat[i].lin ||
                        res.col != mx_mat[i].col) {
                        printf("Dimensoes diferentes. Operacao invalida.\n");
                        valido = 0;
                        break;
                    }

                    res = somar(res, mx_mat[i]);
                }
                break;

            case 2:
                strcpy(nome_op, "Subtracao");

                for (i = 1; i < qtd; i++) {
                    if (res.lin != mx_mat[i].lin ||
                        res.col != mx_mat[i].col) {
                        printf("Dimensoes diferentes. Operacao invalida.\n");
                        valido = 0;
                        break;
                    }

                    res = subtrair(res, mx_mat[i]);
                }
                break;

            case 3:
                strcpy(nome_op, "Multiplicacao");

                for (i = 1; i < qtd; i++) {
                    if (res.col != mx_mat[i].lin) {
                        printf("Dimensoes incompativeis.\n");
                        valido = 0;
                        break;
                    }

                    res = multiplicar(res, mx_mat[i]);
                }
                break;

            case 4:
                strcpy(nome_op, "Divisao");

                for (i = 1; i < qtd; i++) {
                    if (!dividir(res, mx_mat[i], &res)) {
                        valido = 0;
                        break;
                    }
                }
                break;

            case 5:
                mostrarHistorico(hist, qtd_hist);
                break;

            case 6:
                bubble(hist, qtd_hist);
                printf("Historico organizado pelo Bubble Sort.\n");
                mostrarHistorico(hist, qtd_hist);
                break;

            case 7:
                quick(hist, 0, qtd_hist - 1);
                printf("Historico organizado pelo Quick Sort.\n");
                mostrarHistorico(hist, qtd_hist);
                break;

            case 0:
                salvarArquivo(hist, qtd_hist);
                printf("Programa encerrado.\n");
                break;

            default:
                printf("Opcao invalida.\n");
                valido = 0;
        }

        // Exibe e registra o resultado das operacoes.
        if (op >= 1 && op <= 4 && valido) {
            printf("\nResultado da %s:\n", nome_op);
            mostrarMatriz(res);

            registrar(hist, &qtd_hist, nome_op, res);
        }

    } while (op != 0);

    return 0;
}
