/* >>> QUESTÃO 1 <<<

    Aluna: Júlia Gabriella Ferreira Siqueira
    Matrícula: 241036142

    Disciplina: Matemática Discreta 2
    Professora: Cristiane
    Data: 18/10/2025
    UNB 25/2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <ctype.h>  

// Função de Multiplicação Modular
long long multiplicacao_modular(long long a, long long b, long long mod) {
    long long res = 0;
    a %= mod;
    while (b > 0) {
        if (b % 2 == 1) { // Se b é ímpar
            res = (res + a) % mod;
        }
        a = (a * 2) % mod; // Dobra 'a'
        b /= 2;           // Divide 'b' por 2
    }
    return res;
}

// declara funções
long long mdc(long long a, long long b, int imp);
long long pollard_rho(long long N);
long long inverso_modular(long long E, long long z);
long long exp_modular(long long base, long long exp, long long n, long long z);
int primo(long long n);

// ETAPA 1: FATORAÇÃO
// Algoritmo de Euclides para o MDC.
// O parâmetro 'imp' controla se os passos devem ser impressos.
long long mdc(long long a, long long b, int imp) {
    long long a_inicial = a;
    long long b_inicial = b;
    if (imp) printf("\t-> Calculando MDC(%lld, %lld) com Algoritmo de Euclides:\n", a, b);

    while (b != 0) {
        long long resto = a % b;
        if (imp) printf("\t\t- Passo: %lld mod %lld = %lld\n", a, b, resto);
        a = b;
        b = resto;
    }
    if (imp) printf("\t-> MDC(%lld, %lld) = %lld\n", a_inicial, b_inicial, a);
    return a;
}

// Função de iteração para o Pollard's Rho: g(x) = (x^2 + 1) mod N
long long g(long long x, long long N) {
    long long produto = multiplicacao_modular(x, x, N);
    return (produto + 1) % N;
}

// Método Rho de Pollard para encontrar um fator não trivial.
long long pollard_rho(long long N) {
    printf("\n--- Iniciando Metodo Rho de Pollard para N = %lld ---\n", N);
    
    // Inicial x0 = 2, conforme o enunciado.
    long long x = 2;
    long long y = 2;
    long long d = 1;
    int iter = 0;

    while (d == 1) {
        iter++;
        printf("Iteracao %d:\n", iter);
        
        // x avança um passo: x = g(x)
        x = g(x, N);
        printf("\t- x = g(%lld) = %lld\n", x, x); 
        
        // y avança dois passos: y = g(g(y))
        y = g(g(y, N), N);
        printf("\t- y = g(g(%lld)) = %lld\n", y, y);
        
        long long diff = llabs(x - y); 
        printf("\t- Calculando |x - y| = |%lld - %lld| = %lld\n", x, y, diff);
        
        // Calcula o MDC
        d = mdc(diff, N, 1);
        
        if (d == N) {
            printf("\tFalha: Fator encontrado e igual a N. Tente outro numero.\n");
            return -1; // Sinaliza falha
        }
    }
    
    printf("--- Fator nao trivial de %lld encontrado: %lld ---\n", N, d);
    return d;
}

// ETAPA 2: GERAÇÃO DE CHAVES

// Algoritmo Estendido de Euclides para encontrar o inverso modular D.
long long inverso_modular(long long E, long long z) {
    long long m0 = z, t, q;
    long long x0 = 0, x1 = 1;

    printf("\n--- Calculando Inverso Modular D de E=%lld (mod z=%lld) ---\n", E, z);

    if (z == 1) return 0;
    int iter = 0;
    while (E > 1) {
        iter++;
        q = E / z;
        t = z;
        z = E % z, E = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
        printf("Iteracao %d: q=%lld, D parcial=%lld\n", iter, q, x0);
    }
    
    // Garante que o resultado seja positivo
    if (x1 < 0) x1 += m0;

    printf("--- Inverso Modular D encontrado: %lld ---\n", x1);
    return x1;
}

// ETAPA 3: CRIPTOGRAFIA 

// Função auxiliar para verificar se um número é primo.
int primo(long long n) {
    if (n <= 1) return 0;
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

// Exponenciação modular com seleção de teorema para otimização.
long long exp_modular(long long base, long long exp, long long n, long long z) {
    printf("\nCalculando (%lld ^ %lld) mod %lld...\n", base, exp, n);
    
    long long exp_reduzido = exp;

    // Lógica de seleção de teorema, conforme a questão
    if (primo(n)) {
        printf("\t- Metodo: Pequeno Teorema de Fermat (n eh primo).\n");
        exp_reduzido = exp % (n - 1);
        if (exp_reduzido == 0) exp_reduzido = n - 1; 
        printf("\t- Expoente reduzido: %lld mod %lld = %lld\n", exp, n - 1, exp_reduzido);
    } else if (mdc(base, n, 0) == 1) {
        printf("\t- Metodo: Teorema de Euler (mdc(base, n) = 1).\n");
        exp_reduzido = exp % z;
        if (exp_reduzido == 0) exp_reduzido = z;
        printf("\t- Expoente reduzido: %lld mod %lld = %lld\n", exp, z, exp_reduzido);
    } else {
        printf("\t- Metodo: Divisao Euclidiana (caso geral).\n");
        exp_reduzido = exp;
        printf("\t- Nenhuma otimizacao por teorema aplicada.\n");
    }

    // Algoritmo de exponenciação por quadratura (binária)
    long long resultado = 1;
    base %= n;
    printf("\t- Iniciando exponenciacao por quadratura com expoente %lld...\n", exp_reduzido);
    while (exp_reduzido > 0) {
        long long resultado_anterior = resultado;
    
        // Se o expoente for ímpar, multiplica a base no resultado
        if (exp_reduzido % 2 == 1) {
            resultado = multiplicacao_modular(resultado, base, n);
            printf("\t\t- Expoente impar. Multiplica: (%lld * %lld) mod %lld = %lld\n", resultado_anterior, base, n, resultado);
        }
        long long base_anterior = base;
        // Eleva a base ao quadrado e divide o expoente por 2
        base = multiplicacao_modular(base, base, n);
        exp_reduzido /= 2;
        printf("\t\t- Quadrado da base: (%lld^2) mod %lld = %lld. Novo expoente: %lld\n", base_anterior, n, base, exp_reduzido);
    }
    
    printf("\t- Resultado do calculo: %lld\n", resultado);
    return resultado;
}

// MAIN
int main() {
    printf("=== IMPLEMENTACAO DO SISTEMA RSA COMPLETO ===\n\n");
    
    // FATORAÇÃO
    printf("--- ETAPA 1: OBTENCAO DOS PRIMOS p E q ---\n");
    printf("Instrucao: Forneca dois numeros compostos (3 ou 4 digitos) que sejam produto de dois primos distintos.\n");
    
    long long N1, N2, p, q;
    
    // Validação forçada para N1
    do {
        printf("Digite o primeiro numero composto (N1) [100 a 9999]: ");
        scanf("%lld", &N1);
        if (N1 < 100 || N1 > 9999) {
            printf("Erro: O valor de N1 deve ter 3 ou 4 digitos. Tente novamente.\n");
        }
    } while (N1 < 100 || N1 > 9999);
    p = pollard_rho(N1);

    // Verificação da fatoração de N1
    if (p != -1) {
        long long cofator_p = N1 / p;
        if (!primo(p) || !primo(cofator_p) || p == cofator_p) {
            printf("\nErro de validacao: N1=%lld nao e um produto de dois primos distintos (fatores: %lld, %lld).\n", N1, p, cofator_p);
            return 1;
        }
    } else { return 1; }

    // Validação forçada para N2
    do {
        printf("Digite o segundo numero composto (N2) [100 a 9999]: ");
        scanf("%lld", &N2);
        if (N2 < 100 || N2 > 9999) {
            printf("Erro: O valor de N2 deve ter 3 ou 4 digitos. Tente novamente.\n");
        }
    } while (N2 < 100 || N2 > 9999);
    q = pollard_rho(N2);

    // Verificação da fatoração de N2
    if (q != -1) {
        long long cofator_q = N2 / q;
        if (!primo(q) || !primo(cofator_q) || q == cofator_q) {
            printf("\nErro de validacao: N2=%lld nao e um produto de dois primos distintos (fatores: %lld, %lld).\n", N2, q, cofator_q);
            return 1;
        }
    } else { return 1; }

    if (p == -1 || q == -1 || p == q) {
        printf("\nErro na fatoracao ou p=q. Encerrando.\n");
        return 1;
    }
    printf("\nPrimos obtidos: p = %lld, q = %lld\n", p, q);

    // GERAÇÃO DAS CHAVES 
    printf("\n--- ETAPA 2: GERACAO DAS CHAVES RSA ---\n");
    long long n = p * q;
    long long z = (p - 1) * (q - 1);
    
    printf("Calculo do modulo: n = p * q = %lld * %lld = %lld\n", p, q, n);
    printf("Calculo do Totiente de Euler: z(n) = (p-1)*(q-1) = %lld * %lld = %lld\n", p - 1, q - 1, z);
    
    // Escolha de E
    long long E = 2;
    printf("\nBuscando o menor expoente publico E > 1 tal que mdc(E, %lld) = 1...\n", z);
    while (mdc(E, z, 1) != 1) {
        E++;
    }
    printf("Expoente publico E encontrado: %lld\n", E);
    
    // Cálculo de D
    long long D = inverso_modular(E, z);

    printf("\nCHAVES GERADAS:\n");
    printf("Chave Publica: (n, E) = (%lld, %lld)\n", n, E);
    printf("Chave Privada: (n, D) = (%lld, %lld)\n", n, D);

    // CRIPTOGRAFIA E DESCRIPTOGRAFIA
    printf("\n--- ETAPA 3: CODIFICACAO E DECODIFICACAO ---\n");
    char mensagem_original[256];
    char mensagem_limpa[256];
    printf("Digite a mensagem a ser criptografada (A-Z, espacos): ");
    scanf(" %[^\n]s", mensagem_original);

    // Limpa a mensagem (converte para maiúsculas) para simplificar
    int j = 0;
    for (int i = 0; mensagem_original[i] != '\0'; i++) {
        if (isalpha(mensagem_original[i]) || mensagem_original[i] == ' ') {
            mensagem_limpa[j++] = toupper(mensagem_original[i]);
        }
    }
    mensagem_limpa[j] = '\0';
    
    printf("Mensagem original (processada): %s\n", mensagem_limpa);
    
    int len = strlen(mensagem_limpa);
    long long blocos_numericos[len];
    long long blocos_cifrados[len];
    char mensagem_decifrada[len + 1];

    // Criptografia
    printf("\n--- Criptografando a mensagem ---\n");
    for (int i = 0; i < len; i++) {
        long long M = (mensagem_limpa[i] == ' ') ? 0 : mensagem_limpa[i] - 'A' + 11;
        blocos_numericos[i] = M;
        printf("\nCaractere '%c' -> Bloco M = %lld\n", mensagem_limpa[i], M);
        blocos_cifrados[i] = exp_modular(M, E, n, z);
        printf("Bloco Cifrado C = %lld\n", blocos_cifrados[i]);
    }

    // Descriptografia
    printf("\n--- Descriptografando a mensagem ---\n");
    for (int i = 0; i < len; i++) {
        long long C = blocos_cifrados[i];
        printf("\nBloco Cifrado C = %lld\n", C);
        long long M_decifrado = exp_modular(C, D, n, z);
        printf("Bloco Decifrado M = %lld\n", M_decifrado);
        mensagem_decifrada[i] = (M_decifrado == 0) ? ' ' : (char)(M_decifrado - 11 + 'A');
        printf("Caractere decifrado: '%c'\n", mensagem_decifrada[i]);
    }
    mensagem_decifrada[len] = '\0';

    // CONFIRMAÇÃO FINAL
    printf("\n--- RESULTADO FINAL ---\n");
    printf("Mensagem Original:   %s\n", mensagem_limpa);
    printf("Mensagem Decifrada:  %s\n", mensagem_decifrada);
    
    if (strcmp(mensagem_limpa, mensagem_decifrada) == 0) {
        printf("\nConfirmacao: SUCESSO! A mensagem decifrada eh identica a original.\n");
    } else {
        printf("\nConfirmacao: FALHA! A mensagem decifrada eh diferente da original.\n");
    }

    return 0;
}
