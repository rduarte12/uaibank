# UaiBank

Sistema bancário simples em C para cadastro, consulta, remoção, listagem e transferência de saldo entre usuários, com persistência em arquivos de texto.

---

## Sumário

- [Descrição Geral](#descrição-geral)
- [Tecnologias Utilizadas](#tecnologias-utilizadas)
- [Como Funciona](#como-funciona)
- [Fluxograma do Sistema](#fluxograma-do-sistema)
- [Estrutura dos Dados](#estrutura-dos-dados)
- [Funcionalidades](#funcionalidades)
- [Interação com o Usuário](#interação-com-o-usuário)
- [Exemplo de Uso](#exemplo-de-uso)

---

## Descrição Geral

O **UaiBank** é um sistema de terminal que permite gerenciar usuários bancários, realizando operações como cadastro, busca, remoção, listagem e transferência de saldo. Os dados são armazenados nos arquivos `dados.txt` (informações dos usuários) e `log.txt` (IDs dos usuários), garantindo persistência entre execuções.

---

## Tecnologias Utilizadas

| Tecnologia/Biblioteca | Onde é utilizada                | Função principal                                  |
|-----------------------|---------------------------------|---------------------------------------------------|
| `stdio.h`             | Todo o código                   | Entrada/saída padrão (printf, scanf, fgets, etc.) |
| `stdlib.h`            | Alocação dinâmica, conversões   | malloc, realloc, atoi, atof                       |
| `string.h`            | Manipulação de strings          | strlen, strcpy, strchr, etc.                      |
| `unistd.h`            | Animação do logo                | usleep para pausar a exibição do texto            |
| Sistema de arquivos   | Funções de leitura/escrita      | Persistência dos dados dos usuários               |

---

## Como Funciona

- **Persistência:** Os dados dos usuários são salvos em arquivos de texto (`dados.txt` e `log.txt`).
- **Menu interativo:** O usuário interage via terminal, escolhendo opções numéricas.
- **Validação:** Entradas são validadas para evitar dados inválidos.
- **Operações:** Cadastro, busca, remoção, listagem e transferência de saldo.

---

## Fluxograma do Sistema

```mermaid
flowchart TD
    A[Início do Programa] --> B[Lê dados dos arquivos<br/>(ler_arquivo)]
    B --> C[Exibe logo UaiBank<br/>(escrever_uai_bank)]
    C --> D[Menu Principal]
    D -->|1| E[Inserir usuário<br/>(novo_usuario)]
    D -->|2| F[Inserir vários usuários<br/>(novo_usuario em loop)]
    D -->|3| G[Buscar usuário por ID<br/>(buscar_id)]
    D -->|4| H[Transferir saldo<br/>(realizar_transferencia)]
    D -->|5| I[Remover usuário<br/>(deletar_usuario)]
    D -->|6| J[Listar usuários]
    D -->|7| K[Limpar tela]
    D -->|0| L[Fim]
    E --> M[Salva no arquivo<br/>(atualizar_arquivo)]
    F --> M
    I --> N[Reescreve arquivos<br/>(reescrever_arquivo)]
    H --> N
    E --> D
    F --> D
    G --> D
    H --> D
    I --> D
    J --> D
    K --> D
```

**O que cada função faz no fluxograma:**

- **ler_arquivo:** Lê os dados dos arquivos e preenche o vetor de usuários em memória, utilizando ponteiros e realocação dinâmica (`realloc`) para ajustar o tamanho do vetor conforme a quantidade de usuários.
- **escrever_uai_bank:** Exibe o logo animado do sistema.
- **novo_usuario:** Solicita dados do usuário, valida, armazena no vetor (com realocação dinâmica usando ponteiros) e chama `atualizar_arquivo` para persistir.
- **atualizar_arquivo:** Salva os dados do novo usuário nos arquivos de texto.
- **buscar_id:** Busca e exibe um usuário pelo ID, percorrendo o vetor de usuários via ponteiro.
- **realizar_transferencia:** Transfere saldo entre dois usuários, atualizando o vetor em memória e persistindo as alterações com `reescrever_arquivo`.
- **deletar_usuario:** Remove um usuário do vetor (realocando a memória com ponteiros) e reescreve os arquivos.
- **reescrever_arquivo:** Atualiza completamente os arquivos de dados e log com o vetor atual de usuários.
- **Listar usuários:** Percorre o vetor de usuários e exibe todos os dados.
- **Limpar tela:** Limpa o terminal e reexibe o logo.

---

## Estrutura dos Dados

```c
typedef struct {
    int id;
    char nome[101];
    int idade;
    float saldo;
} Usuarios;
```

O vetor de usuários é manipulado por ponteiros e realocado dinamicamente com `realloc` a cada inclusão ou exclusão, permitindo flexibilidade e uso eficiente de memória.

---

## Funcionalidades

| Função                    | Responsabilidade principal                                                                                 | Uso de ponteiros e realocação dinâmica                |
|---------------------------|-----------------------------------------------------------------------------------------------------------|-------------------------------------------------------|
| `main`                    | Fluxo principal, menu e controle do sistema                                                               | Manipula ponteiros para o vetor de usuários           |
| `escrever_uai_bank`       | Exibe o logo animado                                                                                      | -                                                     |
| `ler_inteiro`/`ler_float` | Lê e valida entradas numéricas                                                                            | -                                                     |
| `novo_usuario`            | Cadastro de novo usuário, valida dados, realoca vetor com `realloc` e atualiza ponteiros                  | Sim                                                   |
| `atualizar_arquivo`       | Salva novo usuário nos arquivos                                                                           | Recebe ponteiro para vetor                            |
| `ler_arquivo`             | Carrega usuários dos arquivos, realocando vetor conforme necessário                                       | Sim                                                   |
| `buscar_id`               | Busca usuário pelo ID no vetor                                                                            | Recebe ponteiro para vetor                            |
| `deletar_usuario`         | Remove usuário, realoca vetor com `realloc` e atualiza ponteiros                                          | Sim                                                   |
| `reescrever_arquivo`      | Atualiza arquivos após remoção/transferência, percorrendo vetor por ponteiro                              | Sim                                                   |
| `realizar_transferencia`  | Transfere saldo entre usuários, altera vetor em memória e persiste alterações                             | Sim                                                   |

**Observação:**  
A manipulação do vetor de usuários é feita sempre por ponteiros, permitindo que as funções alterem diretamente o conteúdo e o tamanho do vetor na memória, garantindo flexibilidade e eficiência.

---

## Interação com o Usuário

O usuário interage via terminal, escolhendo opções do menu principal:

```
======== UaiBank ========
1 - Inserir usuario
2 - Inserir varios usuarios
3 - Buscar usuario por ID
4 - Realizar transferencia
5 - Remover usuario por ID
6 - Listar usuarios
7 - Limpar Tela
0 - Sair
=========================
Escolha uma opcao:
```

Cada operação solicita os dados necessários, valida as entradas e informa o sucesso ou erro das operações.

---

## Exemplo de Uso

1. **Cadastrar usuário:**  
   Escolha a opção 1, informe nome, idade e saldo inicial.

2. **Buscar usuário:**  
   Opção 3, informe o ID.

3. **Transferir saldo:**  
   Opção 4, informe ID de origem, ID de destino e valor.

4. **Remover usuário:**  
   Opção 5, informe o ID.

5. **Listar usuários:**  
   Opção 6.

---



---

