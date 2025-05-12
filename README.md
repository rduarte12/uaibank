# UaiBank 💰

**UaiBank** é um sistema bancário simples, escrito em linguagem C, que permite gerenciar usuários, realizar transferências entre contas e armazenar dados de forma persistente em arquivo.

---

## 📋 Funcionalidades

- ✅ Cadastro de um ou mais usuários  
- 🔍 Busca de usuário por ID  
- 🔄 Transferência de saldo entre contas  
- ❌ Remoção de usuários por ID  
- 📄 Listagem de todos os usuários  
- 💾 Armazenamento persistente no arquivo `dados.txt`  

---

## 📦 Estrutura de Dados

Os usuários são representados por uma `struct` chamada `Usuarios`, contendo os seguintes campos:

```c
typedef struct {
    int id;
    char nome[101];
    int idade;
    float saldo;
} Usuarios;
```

---

## 🔧 Compilação e Execução

1. Compile o código com o `gcc`:
   ```bash
   gcc -o uaibank uaibank.c
   ```

2. Execute o programa:
   ```bash
   ./uaibank
   ```

> O programa criará um arquivo `dados.txt` na pasta atual, se ele ainda não existir.

---

## 🧪 Exemplo de uso

```text
======== UaiBank ========
1 - Inserir usuario
2 - Inserir varios usuarios
3 - Buscar usuario por ID
4 - Realizar transferencia
5 - Remover usuario por ID
6 - Listar usuarios
0 - Sair
=========================
Escolha uma opcao: 1
Digite o nome: João Silva
Digite a idade: 30
Digite o saldo: 1000.50
Usuario cadastrado com sucesso.
```

---

## 📁 Formato do Arquivo `dados.txt`

Os dados são armazenados no formato CSV:

```
1, João da Silva, 30, 1000.00
2, Maria Souza, 25, 500.50
```

---

## 🛠️ Funções principais

- `novo_usuario` → Cadastra um novo usuário  
- `ler_arquivo` → Carrega dados do arquivo para a memória  
- `reescrever_arquivo` → Atualiza o arquivo com os dados atuais  
- `buscar_id` → Busca um usuário pelo ID  
- `deletar_usuario` → Remove um usuário  
- `realizar_transferencia` → Faz a transferência de saldo entre contas  
- `ler_inteiro` / `ler_float` → Leitura segura de entrada do usuário  

---

## 🚧 TODO (Melhorias futuras)

- 🔐 Implementar autenticação de usuários  
- 🖥️ Criar interface gráfica (ex: com GTK ou integração via Python)  
- ➕ Adicionar funcionalidades de depósito e saque  
- 📤 Exportar dados para formatos como CSV ou JSON  

---

## 👤 Autor

Desenvolvido por [@rduarte12](https://github.com/rduarte12)

---

💡 Projeto feito para fins de aprendizado em C e gerenciamento de arquivos.