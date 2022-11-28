# Ordenação de Algoritmos em C

Projeto em C, destinado à disciplina de Estrutura de Dados.

A proposta era a comparação de eficáfia entre alguns dos algoritmos de ordenação apresentados em aula.

Para isto, desenvolvi um software que implementa os algoritmos:
- Bubble sort,
- Merge sort,
- Shell sort,
- Quick sort,
- e Heap sort,
e os aplica sobre os dados fornecidos pelo professor, que consistem em números inteiros em determinadas ordens ou desordenados.

Ao fim da ordenação, são armazenados os tempos e o número de comparações por algoritmo, para que seja feita a conferência entre eles.

O projeto consite em uma pasta contendo os dados fornecidos pelo professor, e o algoritmo, cuja implementação foi repartida em subprogramas, à fim de facilitar a compreensão e manutenção do código. Sendo os subprogramas:
- bubblesort, merge, mergesort, shellsort, quicksort, percorreArvore, heapsort: Procedimentos que recebem por parâmetro o ponteiro do vetor e seu tamanho, e o ordena através do determinado algoritmo. É válido ressaltar que alguns algortimos estão divididos em dois subprogramas, sendo estes: merge - mergesort e percorreArvore - heapsort).
- prepVet: Procedimento que recebe o ponteiro do vetor por parâmetro, e o preenche com os dados do determinado arquivo.
- vetorAleatorio: Procedimento similar ao anterior, porém, os dados são preenchidos aleatoriamente, apenas com a opção de com/sem duplicidade nos números gerados.

- menu: Função que apresenta o menu inicial e retorna a opção escolhida.
- alterMax, alterEst, alterArq: Funções que apresentam, respectivamente, os menus para a alteração do numero de elementos do vetor, a estrutura na qual seus dados estão organizados e o número do arquivo específico que contém os dados, e, em seguida, retornam o valor escolhido.
- menuVetor: Função que apresenta o menu com opções para modificação do vetor incial, lançando o menu de alteração selecionado, e, por fim, alterando as variáveis globais de controle do vetor.

- main: subprograma principal que exibe o menu incial e realiza a chamada das demais sub-rotinas.
