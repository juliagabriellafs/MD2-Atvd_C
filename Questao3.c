/* >>> QUESTÃO 3 <<<

    Aluna: Júlia Gabriella Ferreira Siqueira
    Matrícula: 241036142

    Disciplina: Matemática Discreta 2
    Professora: Cristiane
    Data: 18/10/2025
    UNB 25/2
*/


#include <stdio.h>


// Função para calcular potência com inteiros
long long calcular_potencia_int(int base, int exp) {
    long long resultado = 1;
    for (int i = 0; i < exp; i++) {
        resultado = resultado * base;
    }
    return resultado;
}

int main() {
    
    int N_entrada;
    int N;
    int fatores_primos[10];
    int expoentes[10];
    int num_fatores = 0; // Contador de quantos fatores primos distintos encontramos

    //LEITURA E VALIDAÇÃO DA ENTRADA 
    printf("Digite um numero inteiro (entre 1 e 105): ");
    scanf("%d", &N_entrada);

    // Validação, conforme o enunciado [1 <= N <= 105]
    if (N_entrada < 1 || N_entrada > 105) {
        printf("Erro: O valor de N deve estar entre 1 e 105.\n");
        return 1; // Retorna 1 para indicar um erro
    }

    // Tratamento especial para o caso N = 1
    if (N_entrada == 1) {
        printf("\nO numero 1 nao possui fatores primos.\n");
        printf("Por definicao, tau(1) = 1 e sigma(1) = 1.\n");
        printf("\nResultado Final:\n");
        printf("Razao de Eficiencia(1) = sigma(1) / tau(1) = 1 / 1 = 1.00\n");
        return 0;
    }

    N = N_entrada; // Copia do valor original

    // FATORAÇÃO PRIMA (TRIAL DIVISION)
    printf("\n=== PASSO 1: Fatoracao Prima de %d ===\n", N_entrada); // Mudei N para N_entrada para mostrar o valor original
    
    // O algoritmo testa divisores a partir de 2
    for (int divisor = 2; N > 1; divisor++) {
        // Se o divisor divide N
        if (N % divisor == 0) {
            // Guarda divisor como um fator primo
            fatores_primos[num_fatores] = divisor;
            expoentes[num_fatores] = 0; // Inicializa o expoente
            
            // Conta quantas vezes divide N.
            while (N % divisor == 0) {
                expoentes[num_fatores]++;
                N = N / divisor;
            }
            // Incrementa contador de fatores distintos
            num_fatores++;
        }
    }

    // Impressão da fatoração encontrada
    printf("Decomposicao: %d = ", N_entrada);
    for (int i = 0; i < num_fatores; i++) {
        printf("%d^%d", fatores_primos[i], expoentes[i]);
        if (i < num_fatores - 1) {
            printf(" * ");
        }
    }
    printf("\n");


    // CÁLCULO DE tau(N)
    printf("\n=== PASSO 2: Calculo de tau(N) (Numero de Divisores) ===\n");
    //Justificativa: A formula e tau(N) = (e1 + 1) * (e2 + 1) * ...\n")
    
    int tau_N = 1;
    printf("Calculo: tau(%d) = ", N_entrada);
    for (int i = 0; i < num_fatores; i++) {
        tau_N = tau_N * (expoentes[i] + 1);
        printf("(%d + 1)", expoentes[i]);
        if (i < num_fatores - 1) {
            printf(" * ");
        }
    }
    printf(" = %d\n", tau_N);


    // CÁLCULO DE sigma(N) 
    printf("\n=== PASSO 3: Calculo de sigma(N) (Soma dos Divisores) ===\n");
    //Justificativa: A formula e sigma(N) = [(p1^(e1+1) - 1)/(p1-1)] * [(p2^(e2+1) - 1)/(p2-1)] * ...\n")

    long long sigma_N = 1;
    printf("Calculo: sigma(%d) = ", N_entrada);
    for (int i = 0; i < num_fatores; i++) {
        int p = fatores_primos[i];
        int e = expoentes[i];
        
        // Calcular a potência
        // *** CORREÇÃO APLICADA AQUI ***
        long long potencia = calcular_potencia_int(p, e + 1);
        long long termo = (potencia - 1) / (p - 1);
        sigma_N = sigma_N * termo;

        printf("[(%d^%d - 1)/(%d-1)]", p, e + 1, p);
        if (i < num_fatores - 1) {
            printf(" * ");
        }
    }
    printf(" = %lld\n", sigma_N);


    // CÁLCULO E EXIBIÇÃO DA RAZÃO DE EFICIÊNCIA 
    printf("\n=== PASSO 4: Calculo da Razao de Eficiencia ===\n");
    
    // Convertendo para double antes da divisão para não perder a parte decimal
    double razao = (double)sigma_N / (double)tau_N;
    
    printf("Resultado Final:\n");
    printf("Razao de Eficiencia(%d) = sigma(%d) / tau(%d) = %lld / %d = %.2f\n", N_entrada, N_entrada, N_entrada, sigma_N, tau_N, razao);

    return 0;
}