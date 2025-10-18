/* 
    >>> QUESTÃO 4 <<<

    Aluna: Júlia Gabriella Ferreira Siqueira
    Matrícula: 241036142

    Disciplina: Matemática Discreta 2
    Professora: Cristiane
    Data: 18/10/2025
    UNB 25/2
*/

#include <stdio.h>

#ifdef WIN32
#include <windows.h>
#endif

//CÓDIGO PREENCHIDO FORNECIDO NA QUESTÃO
int mdcComPassos (int a, int b) {

    int resto;
    while (b != 0) { //LINHA 10 - PREENCHIDA - Justificativa: O Algoritmo de Euclides continua enquanto o divisor 'b' não for zero. A condição de parada é b == 0.
        resto = a % b;
        printf("Algoritmo de Euclides: %d mod %d = %d\n", a, b, resto);

        a = b;
        b = resto; //LINHA 14 PREENCHIDA - Justificativa: No Algoritmo de Euclides, o divisor da próxima iteração ('b') é o resto da iteração atual ('resto').
    }
    return a;
}

int inversoModular(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;
    int A = a, B = m;

    mdcComPassos(a,m); //LINHA 23 - PREENCHIDA - Justificativa: Chamada para exibir os passos do MDC, conforme a exigência do exercício de mostrar todos os cálculos.

    while (m != 0) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;

        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)

        x1 += m0; // LINHA 36 - PREENCHIDA - Justificativa: Converte um resultado de inverso negativo para seu equivalente positivo no corpo modular, somando o módulo 'm0'.

    printf("\nSubstituindo, temos que o inverso de %d em mod %d é %d.\n\n", A, B, x1);
    return x1;
}

int powMod(int base, int exp, int mod) {
    long long res = 1;
    long long b = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) //LINHA 45 - PREENCHIDA - Justificativa: Na exponenciação binária, se o expoente é ímpar, a base atual é multiplicada no resultado acumulado.
            res = (res * b) % mod;

        b = (b * b) % mod;
        exp >>= 1;
    }
    return (int)res;
}

int main() {
#ifdef WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    int H, G, Zn, x, n1;

    printf("Insira H: ");
    scanf("%d", &H);

    printf("Insira G: ");
    scanf("%d", &G);

    printf("Insira Zn: ");
    scanf("%d", &Zn);

    printf("Insira x: ");
    scanf("%d", &x);

    printf("Insira n1: ");
    scanf("%d", &n1);

    printf("\n");

    int inverso = inversoModular(G, Zn); //LINHA 72 - PREENCHIDA - Justificativa: Para realizar a divisão modular (H / G), é preciso primeiro calcular o inverso modular de G.
    int a = (H * inverso) % Zn;

    printf("Fazendo a multiplicação modular: %d * %d mod %d = %d\n", H, inverso, Zn, a);

    int resultado = powMod(a, x, n1); //LINHA 78 - PREENCHIDA - Justificativa: Chama a função de exponenciação modular para calcular a^x mod n1, a etapa final da congruência.

    printf("\n%d é o inverso de %d\n", inverso, G);
    printf("Valor final da congruência: %d\n", resultado);
    return 0;

    /*
    PERGUNTA 1 - Q4:
        Qual seria a saída com os valores: H: 7, G: 3, Zn: 11,  x: 10, n1: 13

        Insira H: 7
        Insira G: 3
        Insira Zn: 11
        Insira x: 10
        Insira n1: 13


            >RESPOSTA<

        Algoritmo de Euclides: 3 mod 11 = 3
        Algoritmo de Euclides: 11 mod 3 = 2
        Algoritmo de Euclides: 3 mod 2 = 1
        Algoritmo de Euclides: 2 mod 1 = 0

        Substituindo, temos que o inverso de 3 em mod 11 é 4.

        Fazendo a multiplicação modular: 7 * 4 mod 11 = 6

        4 é o inverso de 3
        Valor final da congruência: 4
     
    PERGUNTA 2 - Q4

         (V) O algoritmo de Euclides estendido é utilizado para calcular o inverso modular de um número.

                Justificativa: A alternativa é verdadeira pois no próprio código é possível identificar a implementação do
                algoritmo de Euclides estendido na função inversoModular. Por meio dos coeficientes de bezout x0/x1 atualizadas a 
                cada passo do laço, e retorna x1 como inverso, se condição de primos suprida.


        2.(F) Se mdc(G, Zn) ≠ 1, o programa ainda consegue encontrar o inverso de G em Zn.

                Justificativa: O inverso modular de G em Zn só existe se G e Zn forem primos entre si, todavia a implementação do código
                em si não possui uma verificação para essa condição, o programa espera que seja inserido de fato primos entre si, 

        3.(V) A operação (H * inverso) % Zn representa a divisão modular de H por G.

                Justificativa: Verdadeiro pois a divisão modula de H por G será equivalente a multiplicar H pelo inverso modular de G
                logo [int a = (H * inverso) % Zn] ==  [H*G^(-1)mod Zn]

        4.(V) Se n1 for primo, o código aplica o Pequeno Teorema de Fermat para simplificar o cálculo de
            a^x mod n1.

                Justificativa: O Pequeno Teorema de Fermat permite otimizar a exponenciação, pois se o módulo n1 é primo, o expoente x pode ser reduzido para x mod (n1-1),
                simplificando drasticamente o cálculo.

        5.(F) A função powMod implementa o cálculo de potência modular utilizando multiplicações diretas
            sem otimização.

                Justificativa: A função utiliza o algoritmo de exponenciação binária para exatamente otimizar o cálculo. Em vez de realizar n multiplicações,
                este método reduz o número de operações para uma ordem logarítmica. Isso é enquanto o expoente for maior que zero, a base é elevada ao quadrado 
                e o expoente é dividido por dois a cada passo (usando um deslocamento de bits exp >>= 1). Se o expoente for ímpar em uma determinada etapa, 
                o resultado acumulado é multiplicado pela base.

        6.(V) Quando o resultado do inverso é negativo, o código ajusta o valor somando o módulo m0.

                Justificativa: Ao final do algoritmo, uma verificação condicional (if x1 < 0) é realizada. Se o resultado x1 for negativo, o módulo original 
                m0 é adicionado a ele. Garantindo que o inverso modular retornado seja um valor positivo dentro do intervalo [0, m-1].

        7.(V) O cálculo de fi(n1) (função totiente de Euler) é utilizado apenas quando n1 não é primo.

                Justificativa: O Teorema de Euler generaliza o Pequeno Teorema de Fermat para módulos compostos. Quando lidamos com um módulo 
                que não é primo, usamos o Teorema de Euler para simplificar cálculos. Com um módulo n não primo, o Teorema de Euler mostra que os resultados das potências se repetem em ciclos.
                Por isso, em vez de usar um expoente enorme, usamos um equivalente menor para chegar ao mesmo resultado mais rápido.
        
     */

}