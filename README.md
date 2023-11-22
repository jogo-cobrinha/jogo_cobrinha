# cli-lib
Command Line Interface library(CLI). Biblioteca para desenvolvimento de jogos em C. Possui funções para acessar 
o teclado, a tela e gerenciar tarefas de temporização.

## Requisitos
- Essa biblioteca funciona nos seguintes sistemas operacionais:
   - Linux based (Ubuntu, etc)
   - MacOS
- É necesaário ter o GCC instalado na sua máquina. 

- Para saber se você tem o GCC instalado na sua máquina basta rodar o seguinte comando no terminal:
   - gcc --version


## Uso
Na pasta src temos o `main.c`, nesse arquivo temos toda a lógica para funcionar o jogo. 

Para compilar este exemplo via linha de comando, basta mudar para o diretório raiz da biblioteca e digitar o seguinte comando:
```
$ gcc ./src/*.c -I./include -o cli-lib-jogo-cobrinha
```
Ao rodar esse comando, aparecerá um arquico cli-lib-jogo-cobrinha. Rode o comando ./cli-lib-jogo-cobrinha no terminal e jogo iniciará. Usaremos as teclas i, j, k ,l para movimentar a cobrinha. 
i = para cima
j = para esquerda
k = para baixo
l = para direita

Para usar esta biblioteca para criar seus próprios aplicativos, basta adicionar os arquivos de origem e cabeçalho ao seu projeto e compilá-los junto com seu próprio código, substituindo o arquivo main.c pelo seu próprio.
