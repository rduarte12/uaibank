#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Variável global usada para exibir ou não mensagens de depuração
int debug = 0;

// Estrutura que representa um usuário do sistema bancário
typedef struct {
    int id;
    char nome[101];
    int idade;
    float saldo;
} Usuarios;

// Função para ler e validar um número inteiro positivo digitado pelo usuário
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

// Função para ler e validar um número de ponto flutuante positivo digitado pelo usuário
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

// Salva os dados do novo usuário no arquivo
int atualizar_arquivo(Usuarios **usuario, int *total_usuarios) {
    FILE *arquivo = fopen("dados.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    fprintf(arquivo, "%d, %s, %d, %.2f\n",
            (*usuario)[*total_usuarios].id,
            (*usuario)[*total_usuarios].nome,
            (*usuario)[*total_usuarios].idade,
            (*usuario)[*total_usuarios].saldo);
    fclose(arquivo);
    return 0;
}

// Cria um novo usuário e armazena em memória e no arquivo
int novo_usuario(Usuarios **usuario, int *id_global, int *total_usuarios) {
    char nome[101];
    int idade;
    float saldo;

    printf("Digite o nome: ");
    scanf(" %[^\n]", nome);
    getchar(); // Limpa o buffer

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

// Lê os dados do arquivo para preencher os usuários na memória
int ler_arquivo(Usuarios **usuario, int *id_global, int *total_usuarios) {
    *id_global = 0;
    *total_usuarios = 0;

    FILE *arquivo = fopen("dados.txt", "r");
    if (arquivo != NULL) {
        char linha[256];
        while (fgets(linha, sizeof(linha), arquivo) != NULL) {
            *usuario = realloc(*usuario, (*total_usuarios + 1) * sizeof(Usuarios));
            if (*usuario == NULL) {
                printf("Erro ao alocar memoria.\n");
                fclose(arquivo);
                return 1;
            }

            sscanf(linha, "%d, %100[^,], %d, %f",
                   &(*usuario)[*total_usuarios].id,
                   (*usuario)[*total_usuarios].nome,
                   &(*usuario)[*total_usuarios].idade,
                   &(*usuario)[*total_usuarios].saldo);

            if ((*usuario)[*total_usuarios].id > *id_global)
                *id_global = (*usuario)[*total_usuarios].id;

            (*total_usuarios)++;
        }
        fclose(arquivo);
    }
    return 0;
}

// Busca um usuário pelo ID
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

// Remove um usuário com base no ID
int deletar_usuario(Usuarios **usuario, int *id_global, int id_busca, int *total_usuarios) {
    ler_arquivo(usuario, id_global, total_usuarios);
    int encontrado = 0;
    for (int i = 0; i < *total_usuarios; i++) {
        if ((*usuario)[i].id == id_busca) {
            encontrado = 1;
            for (int j = i; j < *total_usuarios - 1; j++) {
                (*usuario)[j] = (*usuario)[j + 1];
            }
            (*total_usuarios)--;
            break;
        }
    }
    return encontrado;
}

// Reescreve todo o arquivo com os dados atualizados
int reescrever_arquivo(Usuarios **usuario, int *total_usuarios) {
    FILE *arquivo = fopen("dados.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    for (int i = 0; i < *total_usuarios; i++) {
        fprintf(arquivo, "%d, %s, %d, %.2f\n",
                (*usuario)[i].id,
                (*usuario)[i].nome,
                (*usuario)[i].idade,
                (*usuario)[i].saldo);
    }

    fclose(arquivo);
    return 0;
}

// Encontra o índice no vetor com base no ID
int encontrar_indice_por_id(Usuarios *usuario, int total_usuarios, int id_procurado) {
    for (int i = 0; i < total_usuarios; i++) {
        if (usuario[i].id == id_procurado)
            return i;
    }
    return -1;
}

// Função principal: apresenta menu e controla as operações
int main() {
    Usuarios *usuario = NULL;
    int id_global = 0;
    int total_usuarios = 0;

    ler_arquivo(&usuario, &id_global, &total_usuarios);

    int var_loop = 1;

    while (var_loop) {
        printf("\n======== UaiBank ========\n");
        printf("1 - Inserir usuario\n");
        printf("2 - Inserir varios usuarios\n");
        printf("3 - Buscar usuario por ID\n");
        printf("4 - Realizar transferencia\n");
        printf("5 - Remover usuario por ID\n");
        printf("6 - Listar usuarios\n");
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
                for (int i = 0; i < num_usuarios; i++) {
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
            case 4: {
                int id_origem, id_destino;
                float valor_transferencia;

                printf("ID do usuario de origem: ");
                id_origem = ler_inteiro();

                printf("ID do usuario de destino: ");
                id_destino = ler_inteiro();

                printf("Valor da transferencia: ");
                valor_transferencia = ler_float();

                int i_origem = encontrar_indice_por_id(usuario, total_usuarios, id_origem);
                int i_destino = encontrar_indice_por_id(usuario, total_usuarios, id_destino);

                if (i_origem == -1 || i_destino == -1) {
                    printf("ID(s) invalido(s).\n");
                    break;
                }

                if (usuario[i_origem].saldo < valor_transferencia) {
                    printf("Saldo insuficiente.\n");
                } else {
                    usuario[i_origem].saldo -= valor_transferencia;
                    usuario[i_destino].saldo += valor_transferencia;
                    reescrever_arquivo(&usuario, &total_usuarios);
                    printf("Transferencia realizada com sucesso.\n");
                }
                break;
            }
            case 5: {
                int id_remover;
                printf("Digite o ID do usuario a remover: ");
                id_remover = ler_inteiro();

                if (deletar_usuario(&usuario, &id_global, id_remover, &total_usuarios)) {
                    reescrever_arquivo(&usuario, &total_usuarios);
                    printf("Usuario removido com sucesso.\n");
                } else {
                    printf("ID nao encontrado.\n");
                }
                break;
            }
            case 6:
                for (int i = 0; i < total_usuarios; i++) {
                    printf("ID: %d | Nome: %s | Idade: %d | Saldo: %.2f\n",
                           usuario[i].id,
                           usuario[i].nome,
                           usuario[i].idade,
                           usuario[i].saldo);
                }
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
