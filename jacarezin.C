#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int lerInteiro(const char *msg) {
    int valor;
    printf("%s", msg);
    scanf("%d", &valor);
    return valor;
}

int apostaValida(int aposta, int saldo) {
    if (aposta <= 0 || aposta > saldo) {
        printf("Aposta invalida!\n");
        return 0;
    }
    return 1;
}

// ===== BONUS =====
void bonus(int *saldo) {
    int ganho = rand() % 50 + 10;
    *saldo += ganho;
    printf("\n[BONUS] Voce recebeu %d moedas!\n", ganho);
}

// ===== JOGOS =====
void jogarRoleta(int *saldo) {
    int aposta = lerInteiro("\nValor da aposta (0 = ALL IN): ");
    
    if (aposta == 0) aposta = *saldo;

    if (!apostaValida(aposta, *saldo)) return;

    int escolha = lerInteiro("Numero (0-9): ");
    int sorte = rand() % 10;

    printf("Numero sorteado: %d\n", sorte);

    if (escolha == sorte) {
        printf("ACERTOU EM CHEIO!\n");
        *saldo += aposta * 3;
    } else {
        printf("Errou...\n");
        *saldo -= aposta;
    }
}

void jogarSlot(int *saldo) {
    char *simbolos[] = {"@", "#", "$"};

    int aposta = lerInteiro("\nValor da aposta: ");
    if (!apostaValida(aposta, *saldo)) return;

    int a = rand() % 3;
    int b = rand() % 3;
    int c = rand() % 3;

    printf("\n[ %s | %s | %s ]\n", simbolos[a], simbolos[b], simbolos[c]);

    if (a == b && b == c) {
        printf("JACKPOT ABSURDO!!!\n");
        *saldo += aposta * 5;
    }
    else if (a == b || b == c || a == c) {
        printf("Quase! Recuperou aposta\n");
    }
    else {
        printf("Perdeu tudo!\n");
        *saldo -= aposta;
    }
}

void menu() {
    printf("\n==== MENU ====\n");
    printf("1 - Roleta\n");
    printf("2 - Caca-Niquel\n");
    printf("3 - Bonus\n");
    printf("4 - Ver status\n");
    printf("5 - Sair\n");
}

int main() {
    srand(time(NULL));

    int saldo = 100;
    int opcao;
    int nivel = 1;
    int ganhos = 0;

    printf("==== JACAREZINHO DA SORTE ====\n");

    while (saldo > 0) {
        printf("\nSaldo: %d | Nivel: %d\n", saldo, nivel);
        menu();

        opcao = lerInteiro("> ");

        switch (opcao) {
            case 1:
                jogarRoleta(&saldo);
                break;

            case 2:
                jogarSlot(&saldo);
                break;

            case 3:
                bonus(&saldo);
                break;

            case 4:
                printf("\n=== STATUS ===\n");
                printf("Saldo: %d\nNivel: %d\n", saldo, nivel);
                break;

            case 5:
                printf("\nSaiu com %d moedas!\n", saldo);
                return 0;

            default:
                printf("Opcao invalida!\n");
        }

        // evolução
        if (saldo > ganhos + 200) {
            nivel++;
            ganhos = saldo;
            printf("\nLEVEL UP! Agora nivel %d\n", nivel);
        }

        // vitória
        if (saldo >= 1000) {
            printf("\nVOCE VIROU O DONO DO CASSINO!\n");
            return 0;
        }
    }

    printf("\nVoce quebrou! GAME OVER\n");
    return 0;
}