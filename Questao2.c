/* >>> QUESTÃO 2 <<<

    Aluna: Júlia Gabriella Ferreira Siqueira
    Matrícula: 241036142

    Disciplina: Matemática Discreta 2
    Professora: Cristiane
    Data: 18/10/2025
    UNB 25/2
*/

#include <stdio.h>

// --- FUNÇÕES DE CÁLCULO ---

// Função para calcular o Máximo Divisor Comum (MDC) entre dois números com o Algoritmo de Euclides.
int calcular_mdc(int a, int b) {
    int ai = a;
    int bi = b;

    printf("\t\t-> Calculando MDC(%d, %d) com Algoritmo de Euclides:\n", a, b);

    // Ele repete a divisão até que o resto seja zero.
    while (b != 0) {
        int resto = a % b;
        //Impressão do passo atual do algoritmo.
        printf("\t\t\t- Passo: %d mod %d = %d\n", a, b, resto);
        a = b;
        b = resto;
    }
    // O último valor de 'a' é o MDC.
    // Impressão do resultado do cálculo do MDC.
    printf("\t\t-> MDC(%d, %d) = %d\n", ai, bi, a);
    return a;
}

// Função para calcular o Mínimo Múltiplo Comum (MMC) entre dois números. Fórmula usada: MMC(a, b) = (a * b) / MDC(a, b).
int calcular_mmc(int a, int b) {
    printf("\t- Aplicando a formula: MMC(a, b) = (a * b) / MDC(a, b)\n");
    
    // Cálculo do produto.
    long long produto = (long long)a * b;
    printf("\t\t- Produto: %d * %d = %lld\n", a, b, produto);
    
    // É feito a chamada da função MDC para obter o divisor.
    int mdc = calcular_mdc(a, b);
    
    int mmc = produto / mdc;
    //Cálculo da divisão final.
    printf("\t\t- Divisao: %lld / %d = %d\n", produto, mdc, mmc);
    
    return mmc;
}


int main() {
    int chaves;           // Variável do número de chaves.
    int ciclos[10];       // Array para guardar os ciclos de cada chave. 
    int mmc_resultado;    // Variável para guardar o resultado final do MMC.

    // Validação de entradas
    do {
        printf("\nDigite o numero de chaves (entre 1 e 10): ");
        scanf("%d", &chaves);
        if (chaves < 1 || chaves > 10) {
            printf("Erro: O valor deve estar entre 1 e 10. Tente novamente.\n");
        }
    } while (chaves < 1 || chaves > 10);

    printf("\nAgora, digite os %d ciclos (cada um entre 2 e 20):\n", chaves);
    for (int i = 0; i < chaves; i++) {
        do {
            printf("Ciclo da chave %d: ", i + 1);
            scanf("%d", &ciclos[i]);
            if (ciclos[i] < 2 || ciclos[i] > 20) {
                printf("Erro: O ciclo deve estar entre 2 e 20. Tente novamente.\n");
            }
        } while (ciclos[i] < 2 || ciclos[i] > 20);
    }
    
    /*
    === JUSTIFICATIVA DO METODO ==
    O problema exige o primeiro ano em que todas as chaves se alinham, isso corresponde ao menor numero 
    que é múltiplo de todos os ciclos. Esse numero é o Mínimo Múltiplo Comum (MMC), que será calculado iterativamente
    */

    printf("\n\n=== PASSO A PASSO DO CALCULO ===\n\n");

    // O mmc inicial é o ciclo da primeira chave.
    mmc_resultado = ciclos[0];
    printf("Passo 1: O MMC parcial inicial e o Primeiro ciclo: %d\n", mmc_resultado);
    
    // Calcula o MMC do resultado atual com o próximo ciclo da lista.
    for (int i = 1; i < chaves; i++) {
        printf("\nPasso %d: Calculando o MMC entre o Resultado parcial (%d) e o Proximo ciclo (%d)\n", i + 1, mmc_resultado, ciclos[i]);
        
        // Atualiza novo valor de 'mmc_resultado'
        // A chamada a 'calcular_mmc' agora irá imprimir todo o detalhamento do cálculo.
        mmc_resultado = calcular_mmc(mmc_resultado, ciclos[i]);
        
        printf("\t-->NOVO MMC PARCIAL: %d\n", mmc_resultado);

       
    }
    
    //Verificação para confirmar o resultado.
    if (mmc_resultado <= 50) {
        printf("\n\n=== VERIFICACAO DO RESULTADO ===\n\n");
        printf("Confirmando que o resultado %d eh um multiplo de todos os ciclos:\n", mmc_resultado);
        for (int i = 0; i < chaves; i++) {
            printf(" -> %d e multiplo de %d? (%d %% %d = %d) -> SIM\n", mmc_resultado, ciclos[i], mmc_resultado, ciclos[i], mmc_resultado % ciclos[i]);
        }
    }
    
    printf("\n\n=== CONCLUSAO ===\n\n");
    
    if (mmc_resultado <= 50) {
        printf("O primeiro ano X > 0 em que todas as chaves podem ser utilizadas e: %d\n", mmc_resultado);
    } else {
        printf("Nao foi possivel encontrar um ano sincronizado dentro do limite de 50 anos.\n");
    }

    return 0;
}