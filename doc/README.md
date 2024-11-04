# Interpretador DBASE

## Descrição
Este projeto é um interpretador simples para comandos DBASE, implementado em C. Ele permite abrir um banco de dados SQLite, listar registros, adicionar novos registros e atualizar registros existentes.

## Estrutura do Projeto
- `Doc/`: Contém a documentação do projeto.
- `Source/`: Contém o código-fonte do projeto.
- `Examples/`: Contém exemplos de uso do interpretador.

## Como Compilar
Para compilar o projeto, execute o seguinte comando no terminal:

```sh
gcc -o interpretador Source/main.c Source/commands.c -lsqlite3
```

## Como Executar
Para executar o interpretador, use o comando:

```sh
./interpretador
```

## Comandos Disponíveis
- `USE <nome>`: Seleciona a base de dados.
- `LIST`: Lista os registros.
- `APPEND <dados>`: Adiciona um registro.
- `REPLACE <id> <dados>`: Atualiza um registro.

## Exemplo de Uso
Veja o arquivo `Examples/examples.txt` para exemplos de comandos que podem ser usados no interpretador.

## Autor
- Eliseu Rodrigues Guimarães