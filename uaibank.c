#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 

// Variável global usada para exibir ou não mensagens de depuração
int debug = 0;

/**
 * Estrutura que representa um usuário do sistema bancário.
 * @param id    Identificador único do usuário.
 * @param nome  Nome do usuário (até 100 caracteres).
 * @param idade Idade do usuário.
 * @param saldo Saldo da conta do usuário.
 */
typedef struct {
    int id;
    char nome[101];
    int idade;
    float saldo;
} Usuarios;

/**
 * Exibe o nome "UaiBank" de forma estilizada no terminal.
 * Não recebe parâmetros nem retorna valores.
 */
void escrever_uai_bank() {
    const char *texto[]= {" ___   ___      ___      ___ _______     ___      __     __ ___   ____  ",
                            "|   | |   |    /   \\    |   |   __  \\   /   \\    |  \\   |  |   | /   /  ",                       
                            "|   | |   |   /  ^  \\   |   |  |__| /  /  ^  \\   |   \\  |  |   |/   /   ",                         
                            "|   | |   |  /  /_\\  \\  |   |   __ <  /  /_\\  \\  |    \\ |  |       <    ",                               
                            "|   |_|   | /  _____  \\ |   |  |__| \\/  _____  \\ |  |\\ \\|  |   |\\   \\   ",                      
                            "|_________|/__/     \\__\\|___|_______/__/     \\__\\|__| \\____|___| \\___\\  "};                           

    printf("\033[1;34m"); // Cor azul
    for (int i = 0; i < sizeof(texto)/sizeof(texto[0]); i++) {
        printf("%s\n", texto[i]);
        fflush(stdout);
        usleep(100000); // Pausa de 100 milissegundos
    }
    printf("\033[0m\n"); // Resetar cor
}

/**
 * Lê um número inteiro positivo digitado pelo usuário.
 * Faz validação para garantir que apenas dígitos foram inseridos.
 * @return Valor inteiro lido.
 */
int ler_inteiro() {
    int valor;
    char str[1000];
    int valido = 0;

    do {
        fgets(str, sizeof(str), stdin);
        str[strcspn(str, "\n")] = 0;

        // Verifica se contém apenas dígitos
        valido = 1;
        for (size_t i = 0; i < strlen(str); i++) {
            if (str[i] < '0' || str[i] > '9') {
                valido = 0;
                printf("Valor invalido. Digite novamente: ");
                break;
            }
        }
    } while (!valido);

    valor = atoi(str);
    return valor;
}

/**
 * Lê um número de ponto flutuante positivo digitado pelo usuário.
 * Faz validação para garantir formato correto e valor não-negativo.
 * @return Valor float lido.
 */
float ler_float() {
    char str[1000];
    int valido;
    float valor;

    do {
        fgets(str, sizeof(str), stdin);
        str[strcspn(str, "\n")] = 0;

        valido = 1;
        int ponto = 0;

        for (size_t i = 0; i < strlen(str); i++) {
            if (str[i] == '.') {
                if (ponto) {
                    valido = 0;
                    break;
                }
                ponto = 1;
            } else if (str[i] < '0' || str[i] > '9') {
                valido = 0;
                break;
            }
        }

        if (!valido || atof(str) < 0) {
            printf("Valor invalido. Digite novamente: ");
            valido = 0;
        }

    } while (!valido);

    valor = atof(str);
    return valor;
}

/**
 * Salva os dados do novo usuário no arquivo "dados.txt" e o ID em "log.txt".
 * @param usuario         Ponteiro para o vetor de usuários.
 * @param total_usuarios  Ponteiro para o total de usuários cadastrados.
 * @return 0 em caso de sucesso, 1 em caso de erro.
 */
int atualizar_arquivo(Usuarios **usuario, int *total_usuarios) {
    FILE *arquivo = fopen("dados.txt", "a");
    FILE *arquivo2 = fopen("log.txt", "a");
    if (arquivo2 == NULL) {
        printf("Erro ao abrir o arquivo de log.\n");
        return 1;
    }

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    fprintf(arquivo2, "ID: %d\n", (*usuario)[*total_usuarios].id);

    fprintf(arquivo,"%s, %d, %.2f\n",
            (*usuario)[*total_usuarios].nome,
            (*usuario)[*total_usuarios].idade,
            (*usuario)[*total_usuarios].saldo);
    fclose(arquivo);
    fclose(arquivo2);
    return 0;
}

/**
 * Cria um novo usuário, faz validações, armazena em memória e salva no arquivo.
 * @param usuario     Ponteiro para o vetor de usuários.
 * @param id_global   Ponteiro para o ID global (incrementado a cada novo usuário).
 * @param total_usuarios Ponteiro para o total de usuários cadastrados.
 * @return 0 em caso de sucesso, 1 em caso de erro.
 */
int novo_usuario(Usuarios **usuario, int *id_global, int *total_usuarios) {
    char nome[101];
    int idade;
    float saldo;
    const char* caracteres_permitidos = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ";
    int flag = 0;

    do {
        printf("Digite o nome: ");
        scanf(" %[^\n]", nome);
        getchar(); // Limpa o buffer

        //Elimina espaços extras no início e no final do nome

        if (nome[strlen(nome) - 1] == ' ') {
            for (int i = (strlen(nome) - 1); nome[i] == ' '; i--) {
            nome[i] = "";
            }
        }

        if (nome[0] == ' ') {
            for (int i = 0; nome[i] == ' '; i++) {
                nome[i] = "";
            }
        }

        // Elimina espaços extras no meio do nome
        for (int i = 0; i < strlen(nome) - 1; i++) {
            if (nome[i] == ' ' && nome[i + 1] == ' ') {
                for (int j = i + 1; j < strlen(nome); j++) {
                    nome[j] = nome[j + 1];
                }
                i--;
            }
        }

        for (int i = 0; i < strlen(nome); ++i) {
            if (strchr(caracteres_permitidos, nome[i]) == NULL) {
                printf("Caracter Invalido! Utilize apenas letras\n");
                flag = 0;
                break;
            }
            else {
                flag = 1;
            }
        }

        


    } while (!flag);
    
    

    printf("Digite a idade: ");
    idade = ler_inteiro();

    printf("Digite o saldo: ");
    saldo = ler_float();

    *usuario = realloc(*usuario, (*total_usuarios + 1) * sizeof(Usuarios));
    if (*usuario == NULL) {
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }

    (*id_global)++;
    (*usuario)[*total_usuarios].id = *id_global;
    strcpy((*usuario)[*total_usuarios].nome, nome);
    (*usuario)[*total_usuarios].idade = idade;
    (*usuario)[*total_usuarios].saldo = saldo;

    printf("Usuario cadastrado com sucesso.\n");

    if (atualizar_arquivo(usuario, total_usuarios) != 0) {
        printf("Erro ao atualizar o arquivo.\n");
        return 1;
    }

    (*total_usuarios)++;
    return 0;
}

/**
 * Lê os dados dos arquivos "dados.txt" e "log.txt" para preencher os usuários na memória.
 * Atualiza o id_global e o total de usuários.
 * @param usuario         Ponteiro para o vetor de usuários.
 * @param id_global       Ponteiro para o ID global.
 * @param total_usuarios  Ponteiro para o total de usuários.
 * @return 0 em caso de sucesso, 1 em caso de erro.
 */
int ler_arquivo(Usuarios **usuario, int *id_global, int *total_usuarios) {
    *id_global = 0;
    *total_usuarios = 0;

    FILE *arquivo = fopen("dados.txt", "r");
    FILE *arquivo2 = fopen("log.txt", "r");

    if (arquivo != NULL && arquivo2 != NULL) {
        char linha[256];
        while (fgets(linha, sizeof(linha), arquivo) != NULL) {
            *usuario = realloc(*usuario, (*total_usuarios + 1) * sizeof(Usuarios));
            if (*usuario == NULL) {
                printf("Erro ao alocar memoria.\n");
                fclose(arquivo);
                return 1;
            }

            sscanf(linha, "%100[^,], %d, %f",
                   
                   (*usuario)[*total_usuarios].nome,
                   &(*usuario)[*total_usuarios].idade,
                   &(*usuario)[*total_usuarios].saldo);
            
            fgets(linha, sizeof(linha), arquivo2);
            sscanf(linha, "ID: %d", &(*usuario)[*total_usuarios].id);

            if ((*usuario)[*total_usuarios].id > *id_global)
                *id_global = (*usuario)[*total_usuarios].id;

            (*total_usuarios)++;
        }
        fclose(arquivo);
        fclose(arquivo2);
    }
    return 0;
}

/**
 * Busca um usuário pelo ID e exibe suas informações.
 * @param usuario         Ponteiro para o vetor de usuários.
 * @param id_busca        ID a ser buscado.
 * @param total_usuarios  Ponteiro para o total de usuários.
 * @return 0 se encontrado, 1 se não encontrado.
 */
int buscar_id(Usuarios **usuario, int id_busca, int *total_usuarios) {
    for (int i = 0; i < *total_usuarios; i++) {
        if ((*usuario)[i].id == id_busca) {
            printf("ID: %d | Nome: %s | Idade: %d | Saldo: %.2f\n",
                   (*usuario)[i].id,
                   (*usuario)[i].nome,
                   (*usuario)[i].idade,
                   (*usuario)[i].saldo);
            return 0;
        }
    }
    return 1;
}

/**
 * Remove um usuário com base no ID, realoca o vetor e reescreve o arquivo.
 * @param usuario         Ponteiro para o vetor de usuários.
 * @param id_busca        ID do usuário a ser removido.
 * @param total_usuarios  Ponteiro para o total de usuários.
 * @return 1 se encontrado e removido, 0 se não encontrado.
 */
int deletar_usuario(Usuarios **usuario, int id_busca, int *total_usuarios) {
    int encontrado = 0;
    for (int i = 0; i < *total_usuarios; i++) {
        if ((*usuario)[i].id == id_busca) {
            encontrado = 1;
            for (int j = i; j < *total_usuarios - 1; j++) {
                (*usuario)[j] = (*usuario)[j + 1];
            }
            (*total_usuarios)--;
            *usuario = realloc(*usuario, (*total_usuarios) * sizeof(Usuarios));
            if (*total_usuarios > 0 && *usuario == NULL) {
                printf("Erro ao realocar memoria.\n");
                return 1;
            }
            if (reescrever_arquivo(usuario, total_usuarios) != 0) {
                return 1;
            }
            break;
        }
    }
    return encontrado;
}

/**
 * Reescreve todo o arquivo "dados.txt" e "log.txt" com os dados atualizados dos usuários.
 * @param usuario         Ponteiro para o vetor de usuários.
 * @param total_usuarios  Ponteiro para o total de usuários.
 * @return 0 em caso de sucesso, 1 em caso de erro.
 */
int reescrever_arquivo(Usuarios **usuario, int *total_usuarios) {
    FILE *arquivo = fopen("dados.txt", "w");
    FILE *arquivo2 = fopen("log.txt", "w");

    if (arquivo2 == NULL) {
        printf("Erro ao abrir o arquivo de log.\n");
        return 1;
    }

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    for (int i = 0; i < *total_usuarios; i++) {
        fprintf(arquivo, "%s, %d, %.2f\n",
                
                (*usuario)[i].nome,
                (*usuario)[i].idade,
                (*usuario)[i].saldo);
        fprintf(arquivo2, "ID: %d \n", (*usuario)[i].id);
    }


    fclose(arquivo);
    fclose(arquivo2);
    return 0;
}

/**
 * Encontra o índice de um usuário no vetor com base no ID.
 * @param usuario         Vetor de usuários.
 * @param total_usuarios  Total de usuários.
 * @param id_procurado    ID a ser procurado.
 * @return Índice do usuário se encontrado, -1 caso contrário.
 */
int encontrar_indice_por_id(Usuarios *usuario, int total_usuarios, int id_procurado) {
    for (int i = 0; i < total_usuarios; i++) {
        if (usuario[i].id == id_procurado)
            return i;
    }
    return -1;
}

/**
 * Realiza transferência de saldo entre dois usuários.
 * @param usuario         Ponteiro para o vetor de usuários.
 * @param total_usuarios  Total de usuários.
 * @param id_origem       ID do usuário de origem.
 * @param id_destino      ID do usuário de destino.
 * @param valor           Valor a ser transferido.
 * @return 0 em caso de sucesso, 1 em caso de erro.
 */
int realizar_transferencia(Usuarios **usuario, int total_usuarios, int id_origem, int id_destino, float valor) {
    int i_origem = -1, i_destino = -1;
    for (int i = 0; i < total_usuarios; i++) {
        if ((*usuario)[i].id == id_origem) i_origem = i;
        if ((*usuario)[i].id == id_destino) i_destino = i;
    }

    if (i_origem == -1 || i_destino == -1) {
        printf("ID(s) invalido(s).\n");
        return 1;
    }

    if ((*usuario)[i_origem].saldo < valor) {
        printf("Saldo insuficiente.\n");
        return 1;
    }

    (*usuario)[i_origem].saldo -= valor;
    (*usuario)[i_destino].saldo += valor;
    if (reescrever_arquivo(usuario, &total_usuarios) != 0) {
        return 1;
    }
    return 0;
}

/**
 * Função principal do programa.
 * Apresenta o menu, controla as operações e gerencia o ciclo de vida do sistema bancário.
 * @return 0 ao finalizar o programa.
 */
int main() {
    Usuarios *usuario = NULL;
    int id_global = 0;
    int total_usuarios = 0;

    ler_arquivo(&usuario, &id_global, &total_usuarios);

    int var_loop = 1;

    escrever_uai_bank();

    while (var_loop) {
        printf("\n======== UaiBank ========\n");
        printf("1 - Inserir usuario\n");
        printf("2 - Inserir varios usuarios\n");
        printf("3 - Buscar usuario por ID\n");
        printf("4 - Realizar transferencia\n");
        printf("5 - Remover usuario por ID\n");
        printf("6 - Listar usuarios\n");
        printf("7 - Limpar Tela\n");
        printf("0 - Sair\n");
        printf("=========================\n");
        printf("Escolha uma opcao: ");

        int opcao;
        opcao = ler_inteiro();

        switch (opcao) {
            case 1:
                novo_usuario(&usuario, &id_global, &total_usuarios);
                break;
            case 2: {
                int num_usuarios;
                printf("Quantos usuarios deseja inserir? ");
                num_usuarios = ler_inteiro();
                for (int i = 0; i < num_usuarios; i++) 
                {
                    printf("\nInserindo usuario %d de %d\n", i + 1, num_usuarios);
                    novo_usuario(&usuario, &id_global, &total_usuarios);
                }
                break;
            }
            
            case 3: {
                int id_busca;
                printf("Digite o ID do usuario: ");
                id_busca = ler_inteiro();
                buscar_id(&usuario, id_busca, &total_usuarios);
                break;
            }
            
            case 4: 
                printf("ID do usuario de origem: ");
                int id_origem = ler_inteiro();
                printf("ID do usuario de destino: ");
                int id_destino = ler_inteiro();
                printf("Valor da transferencia: ");
                float valor_transferencia = ler_float();

                if (realizar_transferencia(&usuario, total_usuarios, id_origem, id_destino, valor_transferencia) != 0) 
                {
                    printf("Erro na transferencia.\n");
                } 
                else 
                {
                    printf("Transferencia realizada com sucesso.\n");
                }
                break;
        
            case 5: 
                printf("Digite o ID do usuario a remover: ");
                int id_remover = ler_inteiro();
                if (deletar_usuario(&usuario, id_remover, &total_usuarios) != 0) 
                {
                    printf("Usuario removido com sucesso.\n");
                } 
                else 
                {
                    printf("ID nao encontrado.\n");
                }
                break;
            
            case 6:
                for (int i = 0; i < total_usuarios; i++) 
                {
                    printf("ID: %d | Nome: %s | Idade: %d | Saldo: %.2f\n",
                           usuario[i].id,
                           usuario[i].nome,
                           usuario[i].idade,
                           usuario[i].saldo);
                }
                break;
            
            case 7: 
                system("cls");
                escrever_uai_bank();
                break;

            case 0:
                var_loop = 0;
                break;
            default:
                printf("Opcao invalida.\n");
        }
    }

    free(usuario);
    return 0;
}
