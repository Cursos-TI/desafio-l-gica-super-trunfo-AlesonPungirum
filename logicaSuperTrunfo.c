#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Estrutura para armazenar os dados de uma carta (cidade)
typedef struct {
    char estado[3];          // Estado (ex: SP, RJ)
    char codigo[4];          // Código da carta (ex: A01)
    char nome[50];           // Nome da cidade (ex: Ladainha, Teofilo Otoni)
    long long populacao;     // População
    double area;             // Área em km²
    double pib;              // PIB em bilhões
    int pontos_turisticos;   // Número de pontos turísticos
} Carta;

// Função para cadastrar uma carta
void cadastrarCarta(Carta *c, int numeroCarta) {
    printf("Cadastro da Carta %d:\n", numeroCarta);
    
    printf("Digite o estado (ex: SP): ");
    scanf("%2s", c->estado);
    
    printf("Digite o código da carta (ex: A01): ");
    scanf("%3s", c->codigo);
    
    printf("Digite o nome da cidade: ");
    scanf(" %[^\n]", c->nome);
    
    printf("Digite a população: ");
    scanf("%lld", &c->populacao);
    
    printf("Digite a área (em km²): ");
    scanf("%lf", &c->area);
    
    printf("Digite o PIB (em bilhões): ");
    scanf("%lf", &c->pib);
    
    printf("Digite o número de pontos turísticos: ");
    scanf("%d", &c->pontos_turisticos);
    
    printf("\n");
}

// Função para exibir os dados de uma carta
void exibirCarta(const Carta *c, int numeroCarta) {
    printf("Carta %d:\n", numeroCarta);
    printf("Estado: %s\n", c->estado);
    printf("Código: %s\n", c->codigo);
    printf("Nome: %s\n", c->nome);
    printf("População: %lld\n", c->populacao);
    printf("Área: %.2lf km²\n", c->area);
    printf("PIB: %.2lf bilhões\n", c->pib);
    printf("Pontos Turísticos: %d\n", c->pontos_turisticos);
    double densidade = (double)c->populacao / c->area;
    printf("Densidade Populacional: %.2lf hab/km²\n", densidade);
    printf("\n");
}

// Função para comparar duas cartas com base em um atributo específico
// Retorna 1 se carta1 vence, 2 se carta2 vence, 0 se empate
int compararCartas(const Carta *c1, const Carta *c2, int atributo) {
    double valor1, valor2;
    int maiorVence = 1;  // Por padrão, maior valor vence
    
    switch (atributo) {
        case 1:  // População
            valor1 = c1->populacao;
            valor2 = c2->populacao;
            break;
        case 2:  // Área
            valor1 = c1->area;
            valor2 = c2->area;
            break;
        case 3:  // PIB
            valor1 = c1->pib;
            valor2 = c2->pib;
            break;
        case 4:  // Pontos Turísticos
            valor1 = c1->pontos_turisticos;
            valor2 = c2->pontos_turisticos;
            break;
        case 5:  // Densidade Populacional (menor vence)
            valor1 = (double)c1->populacao / c1->area;
            valor2 = (double)c2->populacao / c2->area;
            maiorVence = 0;
            break;
        default:
            return -1;  // Atributo inválido
    }
    
    if (valor1 > valor2) {
        return maiorVence ? 1 : 2;
    } else if (valor1 < valor2) {
        return maiorVence ? 2 : 1;
    } else {
        return 0;  // Empate
    }
}

// Função para obter o nome do atributo
const char* getNomeAtributo(int atributo) {
    switch (atributo) {
        case 1: return "População";
        case 2: return "Área";
        case 3: return "PIB";
        case 4: return "Pontos Turísticos";
        case 5: return "Densidade Populacional";
        default: return "Desconhecido";
    }
}

// Função para menu interativo (Nível Aventureiro)
int menuAtributo() {
    int escolha;
    printf("Escolha o atributo para comparação:\n");
    printf("1 - População\n");
    printf("2 - Área\n");
    printf("3 - PIB\n");
    printf("4 - Pontos Turísticos\n");
    printf("5 - Densidade Populacional (menor vence)\n");
    printf("Digite sua escolha: ");
    scanf("%d", &escolha);
    return escolha;
}

// Função para comparação aninhada de múltiplos atributos (Nível Aventureiro/Mestre)
// Aqui, se empate no primeiro, compara o segundo
int compararMultiplos(const Carta *c1, const Carta *c2, int attr1, int attr2) {
    int res1 = compararCartas(c1, c2, attr1);
    if (res1 != 0) {
        return res1;
    } else {
        // Empate no primeiro, compara o segundo
        return compararCartas(c1, c2, attr2);
    }
}

// Função para menu dinâmico de dois atributos (Nível Mestre)
void menuDoisAtributos(int *attr1, int *attr2) {
    printf("Escolha o PRIMEIRO atributo para comparação:\n");
    *attr1 = menuAtributo();
    printf("\nEscolha o SEGUNDO atributo (para desempate):\n");
    *attr2 = menuAtributo();
    // Validação simples para evitar mesmo atributo
    while (*attr1 == *attr2) {
        printf("Atributos iguais! Escolha um segundo atributo diferente:\n");
        *attr2 = menuAtributo();
    }
}

int main() {
    Carta carta1, carta2;
    int opcaoNivel;
    
    printf("Bem-vindo ao Super Trunfo - Países!\n");
    printf("Escolha o nível:\n");
    printf("1 - Novato\n");
    printf("2 - Aventureiro\n");
    printf("3 - Mestre\n");
    printf("Digite sua escolha: ");
    scanf("%d", &opcaoNivel);
    
    // Cadastro das cartas (comum a todos os níveis)
    cadastrarCarta(&carta1, 1);
    cadastrarCarta(&carta2, 2);
    
    // Exibição das cartas (comum)
    exibirCarta(&carta1, 1);
    exibirCarta(&carta2, 2);
    
    int atributo1, atributo2;
    int resultado;
    const char *nomeAttr1, *nomeAttr2;
    
    switch (opcaoNivel) {
        case 1:  // Nível Novato
            // Atributo fixo
            atributo1 = 1;  // População como exemplo
            resultado = compararCartas(&carta1, &carta2, atributo1);
            nomeAttr1 = getNomeAtributo(atributo1);
            printf("Comparação baseada em: %s\n", nomeAttr1);
            if (resultado == 1) {
                printf("A carta vencedora é a Carta 1 (%s)!\n", carta1.nome);
            } else if (resultado == 2) {
                printf("A carta vencedora é a Carta 2 (%s)!\n", carta2.nome);
            } else {
                printf("Empate entre as cartas!\n");
            }
            break;
        
        case 2:  // Nível Aventureiro
            // Menu interativo para um atributo
            atributo1 = menuAtributo();
            while (atributo1 < 1 || atributo1 > 5) {
                printf("Escolha inválida! Tente novamente.\n");
                atributo1 = menuAtributo();
            }
            resultado = compararCartas(&carta1, &carta2, atributo1);
            nomeAttr1 = getNomeAtributo(atributo1);
            printf("Comparação baseada em: %s\n", nomeAttr1);
            if (resultado == 1) {
                printf("A carta vencedora é a Carta 1 (%s)!\n", carta1.nome);
            } else if (resultado == 2) {
                printf("A carta vencedora é a Carta 2 (%s)!\n", carta2.nome);
            } else {
                printf("Empate entre as cartas!\n");
            }
            break;
        
        case 3:  // Nível Mestre
            // Menu dinâmico para dois atributos
            menuDoisAtributos(&atributo1, &atributo2);
            // Comparação aninhada com desempate
            resultado = compararMultiplos(&carta1, &carta2, atributo1, atributo2);
            nomeAttr1 = getNomeAtributo(atributo1);
            nomeAttr2 = getNomeAtributo(atributo2);
            printf("Comparação baseada em: %s (e %s em caso de empate)\n", nomeAttr1, nomeAttr2);
            // Uso de operador ternário para exibir vencedor
            char *vencedor = (resultado == 1) ? carta1.nome : 
                             (resultado == 2) ? carta2.nome : 
                             "Nenhuma (empate mesmo com desempate)";
            printf("A carta vencedora é: %s!\n", vencedor);
            // Detalhes adicionais
            int resPrimario = compararCartas(&carta1, &carta2, atributo1);
            if (resPrimario != 0) {
                printf("Decidido no primeiro atributo.\n");
            } else if (resultado != 0) {
                printf("Empate no primeiro; decidido no segundo atributo.\n");
            } else {
                printf("Empate nos dois atributos.\n");
            }
            break;
        
        default:
            printf("Nível inválido! Encerrando.\n");
            return 1;
    }
    
    return 0;
}