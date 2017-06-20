# Mancala game in C with Artificial Intelligence

## Autors
Thiago Veras Machado - thiagomachado@cjr.org.br\
Vitor Fernandes Dullens - vitordullens@cjr.org.br\
Dep. Ciência da Computação – Universidade de Brası́lia (UnB)\
CiC 116319 - Estrutura de Dados - Turma A

## Game Description
- Pode ser jogado multiplayer ou com a inteligencia artificial, produzida atraves da implementação de uma [Game Tree](https://en.wikipedia.org/wiki/Game_tree);
- A inteligencia artificial possui 4 dificuldades, baseadas na altura da [Game Tree](https://en.wikipedia.org/wiki/Game_tree).

## Game Objectives

- Seu objetivo no jogo é capturar as 'peças' do oponente;
- Cada jogador possui uma área que armazena os pontos na sua direita ( Kalah );
- Quando um jogador não possuir mais peças o jogo acaba;
- O vencedor é quem possui mais peças na sua Kalah.

## Game Rules

- O jogador deve selecionar uma posição;
- Ao fazer isso, todas as peças dessa posição são movidas uma a uma, para a proxima casa a direita (incluindo a Kalah e as casas do outro jogador);
- Quando estiver movendo, se a ultima peça cair na sua Kalah, voce pode jogar novamente;
- Para capturar as peças do adversário, a ultima peça a ser movida, deve cair em um buraco vazio, a casa a frente dela perde as peças e elas vão para a Kalah de quem as roubou.

## Tutorial

- Baixar o arquivo "Mancala", compilar no terminal com o código: "gcc Mancala Mancala.c" e executar o comando ./Mancala.
- [Mancala](Mancala.c)
- [Relatório](Report.pdf)
