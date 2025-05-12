# UaiBank 💰

UaiBank é um sistema bancário simples feito em linguagem C, que permite gerenciar usuários, realizar transferências entre contas e armazenar dados em arquivo.

## 📋 Funcionalidades

- Cadastro de um ou mais usuários
- Busca de usuário por ID
- Transferência de saldo entre usuários
- Remoção de usuários por ID
- Listagem de todos os usuários
- Armazenamento persistente em `dados.txt`

## 📦 Estrutura de Dados

Os usuários são armazenados em uma estrutura `struct` chamada `Usuarios` com os seguintes campos:

```c
typedef struct {
    int id;
    char nome[101];
    int idade;
    float saldo;
} Usuarios;
```

## 🔧 Como compilar e executar

1. Compile o programa com `gcc`:
   ```bash
   gcc -o uaibank uaibank.c
   ```

2. Execute o programa:
   ```bash
   ./uaibank
   ```

> Certifique-se de estar na mesma pasta do arquivo `dados.txt`, ou o programa criará um novo.

## 🧪 Exemplo de uso

```text
==================================
======Bem-vindo ao UaiBank!=======
==================================


1 - Isnserir usuario
2 - Inserir varios usuarios
3 - Buscar usuario por ID
4 - Realizar transferencia
5 - Remover usuario por ID
6 - Listar usuarios
0 - Sair

==================================


Escolha uma opcao: 1
Digite o nome: João Silva
Digite a idade: 30
Digite o saldo: 1000.50
Usuario cadastrado com sucesso.
Usuario: João Silva
ID: 1
Saldo: 1000.500000
```

## 📁 Armazenamento

Os dados dos usuários são armazenados no arquivo `dados.txt` no seguinte formato:
```
1, João da Silva, 30, 1000.00
2, Maria Souza, 25, 500.50
```

## 🛠️ Funções principais

- `novo_usuario`: cadastra um novo usuário
- `ler_arquivo`: carrega os dados do arquivo para a memória
- `reescrever_arquivo`: sobrescreve o arquivo com os dados atuais
- `buscar_id`: busca usuário por ID
- `deletar_usuario`: remove usuário
- `encontrar_indice_por_id`: auxilia a localizar índices no vetor
- `ler_inteiro` / `ler_float`: fazem validação segura da entrada do usuário

## 🧹 TODO (possíveis melhorias)

- Implementar autenticação de usuário
- Criar interface gráfica (usando GTK, por exemplo)
- Adicionar operações como depósito e saque
- Exportar dados em CSV ou JSON

## 👤 Autor

**Rafael Duarte**
