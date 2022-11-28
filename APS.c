#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <sys\timeb.h> 

int comp = 0;	// Variável para o contador de comparações

// Variáveis de controle do vetor
int max = 10;	// Numero de elementos
int dup = 0;	// Duplicidade
int est = 1;	// Estrutura
int arq = 1;	// Arquivo de texto

//Função para receber os arquivos e preparar os vetores
void prepVet(int* vet){
	int i = 0, op1;
	char path[100] = "Dados\\", path_aux[10];
	FILE *pont_arq;
	
	sprintf(path_aux, "%i", max);
	strcat(path, path_aux);
	
	if(dup == 1){
		strcat(path, "\\Com_Duplicidade");	
	} else {
		strcat(path, "\\Sem_Duplicidade");
	}

	if(est == 1){
		strcat(path, "\\Aleatório\\arq_");
	} else if(est == 2){
		strcat(path, "\\Concavo-DecresceCresce\\arq_");
	} else if(est == 3){
		strcat(path, "\\Convexo-CresceDescresce\\arq_");
	} else if(est == 4){
		strcat(path, "\\Crescente\\arq_");
	}else if(est == 5){
		strcat(path, "\\Descrescente\\arq_");
	}
	
	sprintf(path_aux, "%i", arq);
	strcat(path, path_aux);
	
	strcat(path, ".txt");
	
	puts(path);
	
	
	pont_arq = fopen(path, "r");
	
	if(pont_arq == NULL){
		printf("Erro na abertura do arquivo!");
		exit(1);
	}
	
	for (i = 0; i < max; i++){
		fscanf(pont_arq, "%d", &vet[i]);
	}
	fclose(pont_arq);
}


// Bubble sort - O(n^2): Compara o elemento atual com o da próxima posição e, caso o atual seja maior, suas posições são invertidas.
void bubblesort(int* vet, int n) {  // Recebe por parâmetro o ponteiro do vetor a ser organizado e seu tamanho.
	int i, j, tmp;
	
	// Garante que as operações de comparação e ordenção sejam repetidas n-1 vezes, onde n é o tamanho do vetor a ser ordenado.
	for (i = n-1; i >= 1; i--) {
		
		// Percorre o vetor.
		for (j = 0; j < i; j++) {
			
			// Caso o elemento atual seja maior que o próximo, suas posições são invertidas.
			if (vet[j] > vet[j+1]) { 
				tmp = vet[j];		 
				vet[j] = vet[j+1];
				vet[j+1] = tmp;
			}
			comp++; // Incrementa o contador de comparações.
		}
	}
}


// Merge: Recebe um vetor, divide-o em dois e compara os elementos das duas metades,alocando-as em um vetor temporário, até que uma das metades esteja vazia.
void merge(int *vet, int n) {  // Recebe por parâmetro o ponteiro do vetor a ser organizado e seu tamanho.
	int i, j, k, mid;
	int *tmp;
	
	// Aloca um espaço na memória para a criação de um vetor temporário, e armazena o endereço no variável tmp.
	tmp = (int *) malloc(n * sizeof(int));  
	
	// Se tmp não possuir um endereço, significa que não houve memória o suficiente para a alocação, e o programa é encerrado.
	if (tmp == NULL) {
		printf("Memória Insuficiente!\n");
		exit(1);
	}
	
	// Metade do vetor.
	mid = n / 2;
	
	i = 0;	  // Índice da primeira metade do vetor.
	j = mid;  // Índice da segunda metade do vetor.
	k = 0;	  // Índice do vetor temporário.
	
	// Compara os elementos das duas metades do vetor, ordenado-os em um vetor temporário.
	while (i < mid && j < n) {
				
		if (vet[i] < vet[j]) {
		  tmp[k] = vet[i];
		  i++;
		} else {
		  tmp[k] = vet[j];
		  j++;
		}
		k++;
		
		comp++;// Incrementa o contador de comparações.
	}
	
	// Caso uma das metades do vetor chegue à seu elemento final, os demais elementos da outra metade são adicionados ao vetor temporário.
	if (i == mid) {
		while (j < n) {
		  tmp[k] = vet[j];
		  j++;
		  k++;
		}
	}
	else {
		while (i < mid) {
		  tmp[k] = vet[i];
		  i++;
		  k++;
		}
	}
	
	// Armazena os elementos do vetor temporário no vetor inicial.
	for (i = 0; i < n; ++i) {
		vet[i] = tmp[i];
	}
	
	// Libera a memória alocada para o vetor temporário.
	free(tmp);
}


// Merge sort - O(n log n): Procedimento recursivo que divide o vetor em metades, comporando seus elementos e inserindo-os ordenadamente em um vetor.
void mergesort(int *vet, int n) {  // Recebe por parâmetro o ponteiro do vetor a ser organizado e seu tamanho.
	int mid;
	
	// Caso a quantidade de elementos seja maior que 1.
	if (n > 1) {
		
		// Índice da metade do vetor.
		mid = n / 2;
		
		// Chamada recursiva passando as duas metades do vetor por parâmetro.
		mergesort(vet, mid);
		mergesort(vet + mid, n - mid);
		
		// Chamada do merge(), passando o ponteiro do vetor e tamanho recebidos na chamada do mergesort().
		merge(vet, n);
	}
}


// Shell sort - O(n (ln n)^2): Os elementos são comparados em saltos
void shellsort(int *vet, int n) {  // Recebe por parâmetro o ponteiro do vetor a ser organizado e seu tamanho máximo.
    int i, j, tmp;
    int h = 1;
    
    do {
        h = 3 * h + 1;
    } while(h < n);
    
    do {
		h /= 3;
		
		for(i = h; i < n; i++) {
            tmp = vet[i];
            j = i - h;
            
            while (j >= 0 && tmp < vet[j]) {
                vet[j + h] = vet[j];
                j -= h;
                
                comp++;
            }
            
            // Comando para contabilizar a comparação que não entrar no while.
            if(j >= 0){
            	comp++;
			}
            
            vet[j + h] = tmp;
	    }
    } while (h > 1);
}


// Quick sort
void quicksort(int *vet, int n) {
	int a = 1, b = (n - 1), temp, x = vet[0];

	if (n <= 1) {
		return;
	}

	while (1) {
		while ((a < n) && (vet[a] <= x)) {
			a++;
		}
	
		while (vet[b] > x) {
			b--;
		}

		if (a < b) {
			temp = vet[a];
			vet[a] = vet[b];
			vet[b] = temp;
			a++;
			b--;
		}
		comp++;

		if (a >= b) {
			comp++;
			break;
		} else {
			comp++;
		}
	}

	vet[0] = vet[b];
	vet[b] = x;

	quicksort(vet,b);
	quicksort(&vet[a],(n - a));
}


// Heap sort
void percorreArvore(int *vet, int raiz, int folha) {
	int pronto, filhoMax, tmp;
	
	pronto = 0;
	while ((raiz*2 <= folha) && (!pronto)) {
		if (raiz*2 == folha) {
			filhoMax = raiz * 2;
		}
		else if (vet[raiz * 2] > vet[raiz * 2 + 1]) {
			filhoMax = raiz * 2;
		}
		else {
			filhoMax = raiz * 2 + 1;
		}
	
		if (vet[raiz] < vet[filhoMax]) {
			tmp = vet[raiz];
			vet[raiz] = vet[filhoMax];
			vet[filhoMax] = tmp;
			raiz = filhoMax;
			comp++;
	    }
		else {
			pronto = 1;
			comp++;
		}
	}
}

void heapsort(int *vet, int n) {
	int i, tmp;

	for (i = (n / 2); i >= 0; i--) {
		percorreArvore(vet, i, n - 1);
	}

	for (i = n-1; i >= 1; i--) {
		tmp = vet[0];
		vet[0] = vet[i];
		vet[i] = tmp;
		percorreArvore(vet, 0, i-1);
	}
}


// Função que exibe o menu de opções e retorna a opção escolhida.
int menu(){
	int op;
	
	system("cls");
	printf("--------------------------------------");
	printf("\n\tAlgoritmos de Ordenação");
	printf("\n--------------------------------------");
	printf("\n1 - Bubble Sort");
	printf("\n2 - Merge Sort");
	printf("\n3 - Shell Sort");
	printf("\n4 - Quick Sort");
	printf("\n5 - Heap Sort");
	printf("\n6 - Comparação dos Algoritmos");
	printf("\n7 - Alterar vetor inicial");
	printf("\n8 - Sair");
	printf("\n--------------------------------------");
	printf("\nDigite a opção desejada: ");
	
	scanf("%i", &op);
	getchar();
	
	return op;
	
}


// Função para alterar o número de elementos do vetor.
int alterMax(){
	int sair = 0, resp = max;
	char op, cont = 'n';
	
	do{
		system("cls");
		printf("-----------------------------------------");
		printf("\n\tEscolha o tamanho do vetor");
		printf("\n-----------------------------------------");
		printf("\nA - 10     Elementos");
		printf("\nB - 50     Elementos");
		printf("\nC - 100    Elementos");
		printf("\nD - 500    Elementos");
		printf("\nE - 1000   Elementos");
		printf("\nF - 5000   Elementos");
		printf("\nG - 10000  Elementos");
		printf("\nH - 50000  Elementos");
		printf("\nI - 100000 Elementos");
		printf("\nJ - Cancelar");
		printf("\n\nTamanho Atual do Vetor: %i", max);
		printf("\n-----------------------------------------");
		printf("\nDigite a opção desejada: ");
	
		scanf("%c", &op);
		getchar();
		
		switch(tolower(op)){
			
			case 'a':  // 10 Elementos
				if(max == 10){
					system("cls");
					
					printf("---------------------------------");
		            printf("\n\tQuantidade Atual!");
		            printf("\n---------------------------------\n\n");
		            
		            system("pause");
		            
				} else {
					resp = 10;
					sair = 1;
				}
				
				break;
				
			case 'b':  // 50 Elementos
				if(max == 50){
					system("cls");
					
					printf("---------------------------------");
		            printf("\n\tQuantidade Atual!");
		            printf("\n---------------------------------\n\n");
		            
		            system("pause");
		            
				} else {
					resp = 50;
					sair = 1;
				}
				
				break;
				
			case 'c':  // 100 Elementos
				if(max == 100){
					system("cls");
					
					printf("---------------------------------");
		            printf("\n\tQuantidade Atual!");
		            printf("\n---------------------------------\n\n");
		            
		            system("pause");
		            
				} else {
					resp = 100;
					sair = 1;
				}
				
				break;
				
			case 'd':  // 500 Elementos
				if(max == 500){
					system("cls");
					
					printf("---------------------------------");
		            printf("\n\tQuantidade Atual!");
		            printf("\n---------------------------------\n\n");
		            
		            system("pause");
		            
				} else {
					resp = 500;
					sair = 1;
				}
				
				break;
				
			case 'e':  // 1000 Elementos
				if(max == 1000){
					system("cls");
					
					printf("---------------------------------");
		            printf("\n\tQuantidade Atual!");
		            printf("\n---------------------------------\n\n");
		            
		            system("pause");
		            
				} else {
					resp = 1000;
					sair = 1;
				}
				
				break;
			
			case 'f':  // 5000 Elementos
				if(max == 5000){
					system("cls");
					
					printf("---------------------------------");
		            printf("\n\tQuantidade Atual!");
		            printf("\n---------------------------------\n\n");
		            
		            system("pause");
		            
				} else {
					resp = 5000;
					sair = 1;
				}
				
				break;
				
			case 'g':  // 10000 Elementos
				if(max == 10000){
					system("cls");
					
					printf("---------------------------------");
		            printf("\n\tQuantidade Atual!");
		            printf("\n---------------------------------\n\n");
		            
		            system("pause");
		            
				} else {
					resp = 10000;
					sair = 1;
				}
				
				break;
				
			case 'h':  // 50000 Elementos
				if(max == 50000){
					system("cls");
					
					printf("---------------------------------");
		            printf("\n\tQuantidade Atual!");
		            printf("\n---------------------------------\n\n");
		            
		            system("pause");
		            
				} else {
					resp = 50000;
					sair = 1;
				}
				
				break;
				
			case 'i':  // 100000 Elementos
				if(max == 100000){
					system("cls");
					
					printf("---------------------------------");
		            printf("\n\tQuantidade Atual!");
		            printf("\n---------------------------------\n\n");
		            
		            system("pause");
		            
				} else {
					resp = 100000;
					sair = 1;
				}
				
				break;
				
			case 'j':
				sair = 1;
				break;
				
			default:
				op = 0;
				
				system("cls");
				printf("------------------------------");
	            printf("\n\tOpção Inválida!");
	            printf("\n------------------------------\n\n");
	            
	            system("pause");
	            
				break;
		}
	} while(!sair);
	
	return resp;
}


// Função para alterar a estrutura do vetor.
int alterEst(){
	int op, resp = est, cont = 1;
	
	do{
		system("cls");
		printf("-----------------------------------------");
		printf("\n\tEscolha a estrutura do vetor");
		printf("\n-----------------------------------------");
		printf("\n1 - Aleatória");
		printf("\n2 - Côncavo-Decresce-Cresce");
		printf("\n3 - Convexo-Cresce-Decresce");
		printf("\n4 - Crescente");
		printf("\n5 - Decrescente");
		printf("\n6 - Cancelar");
		printf("\n\nEstrutura atual: ");
		if(est == 1){
			printf("Aleatória");
		} else if(est == 2){
			printf("Côncavo-Decresce-Cresce");
		} else if(est == 3){
			printf("Convexo-Cresce-Decresce");
		} else if(est == 4){
			printf("Crescente");
		}else if(est == 5){
			printf("Decrescente");
		}
		printf("\n-----------------------------------------");
		printf("\nDigite a opção desejada: ");
	
		scanf("%i", &op);
		getchar();
		
		if(op == est){
			system("cls");
			
			printf("---------------------------------");
	        printf("\n\Estrutura Atual!");
	        printf("\n---------------------------------\n\n");
		    system("pause");
		} else if (op >= 1 && op <= 5){
			resp = op;
			cont = 0;
		} else if(op == 6){
			cont = 0;
		} else {
			system("cls");
			printf("------------------------------");
            printf("\n\tOpção Inválida!");
            printf("\n------------------------------\n\n");
            
            system("pause");
		}
	} while(cont);
	
	return resp;
}

int alterArq(){
	int op, resp = arq, cont = 1;
	
	do{
		system("cls");
		printf("-----------------------------------------------------");
		printf("\n\tArquivo de texto com os elementos do vetor");
		printf("\n-----------------------------------------------------");
		printf("\n- Digite um número de 1 à 10.");
		printf("\n- Ou digite outro valor para cancelar.");
		printf("\n>>");
		
		scanf("%i", &op);
		getchar();
		
		if(op == arq){
			system("cls");
		
			printf("---------------------------------");
	        printf("\n\Estrutura Atual!");
	        printf("\n---------------------------------\n\n");
		    system("pause");	
		} else if(op >= 1 && op <= 10){
			resp = op;
			cont = 0;
		} else{
			cont = 0;
		}
	} while(cont);
	
	return resp;
}


// Função para alterar o vetor utilizado.
int menuVetor(){
	int op, cont = 1, mudou = 0, max_aux = max, dup_aux = dup, est_aux = est, arq_aux = arq;
	char resp = 'n';
	
	do {
		system("cls");
		printf("\n---------------------------------------------------------------------------");
		printf("\n\t\t\tAlterar Vetor Inicial");
		printf("\n---------------------------------------------------------------------------");
		printf("\nAtual: %i Elementos, ", max);
		if(dup){
			printf("Com Duplicidade, ");
		} else {
			printf("Sem Duplicidade, ");
		}
		
		if(est == 1){
			printf("Aleatório, ");
		} else if(est == 2){
			printf("Côncavo-Decresce-Cresce, ");
		} else if(est == 3){
			printf("Convexo-Cresce-Decresce, ");
		} else if(est == 4){
			printf("Crescente, ");
		}else if(est == 5){
			printf("Decrescente, ");
		}
		
		printf("arq_%i", arq);
		
		printf("\n---------------------------------------------------------------------------");
		printf("\n1 - Tamanho do Vetor - %i", max_aux);
		
		if(dup_aux){
			printf("\n2 - Desativar Duplicidade");
		} else {
			printf("\n2 - Ativar Duplicidade");
		}
		
		printf("\n3 - Estrutura do vetor - ");
		if(est_aux == 1){
			printf("Aleatória");
		} else if(est_aux == 2){
			printf("Côncavo-Decresce-Cresce");
		} else if(est_aux == 3){
			printf("Convexo-Cresce-Decresce");
		} else if(est_aux == 4){
			printf("Crescente");
		}else if(est_aux == 5){
			printf("Decrescente");
		}
		
		printf("\n4 - Arquivo de texto - %i", arq_aux);
		
		printf("\n\n5 - Aplicar alterações");
		printf("\n6 - Cancelar");
		printf("\n---------------------------------------------------------------------------");
		printf("\nDigite a opção desejada: ");
		
		scanf("%i", &op);
		getchar();
		
		switch(op){
			case 1:
				max_aux = alterMax();
				break;
			case 2:
				if(dup_aux){
					dup_aux = 0;
				} else {
					dup_aux = 1;
				}
				break;
			case 3:
				
				est_aux = alterEst();
				
				break;
				
			case 4:
				
				arq_aux = alterArq();
				
				break;	
			
			case 5:
				
				if(max_aux == max && dup_aux == dup && est_aux == est && arq == arq_aux){
					system("cls");
					
					printf("----------------------------------------");
		            printf("\n\tCondições do Vetor Atual!");
		            printf("\n----------------------------------------\n\n");
		            
		            system("pause");
					
				} else {
					
					system("cls");
					printf("============================================================");
					printf("\nAVISO: Alterar o vetor irá resetar todas as estatíticas!");
					printf("\n============================================================");
					printf("\n\nDigite 's' para continuar, ou digite outro valor para cancelar.");
					printf("\n>>");
					
					scanf("%c", &cont);
					getchar();
					
					if(cont == 's' || cont == 'S'){
						max = max_aux;
						dup = dup_aux;
						est = est_aux;
						arq = arq_aux;
						
						mudou = 1;
					}			
				}
				
				cont = 0;
				
				break;
			case 6:
				cont = 0;
				break;		
		}
		
	} while(cont);

	return mudou;
}


// Função para gerar vetores aleatórios.
void vetorAleatorio(int *vet){
	int op = 0, i = 0, sair = 0;
	
	do{
		system("cls");
		printf("--------------------------------------");
		printf("\n\tEscolha o tipo de vetor");
		printf("\n--------------------------------------");
		printf("\n1 - Vetor com Duplicidade");
		printf("\n2 - Vetor sem Duplicidade");
		printf("\n--------------------------------------");
		printf("\nDigite a opção desejada: ");
	
		scanf("%i", &op);
		getchar();
		
		switch(op){
			case 1:
				// Para cada elemento do vetor é gerado um número aleatótio entre 0 e o máximo
				for (i = 0; i < max; i++) {
					vet[i] = rand() % max;
				}
				
				sair++;
				break;
				
			case 2:
				// O vetor é preenchido com números de 0 até o máximo
				for (i = 0; i < max; i++) {
					vet[i] = i;
				}
				
				// Os números são embralhados
				for (i = 0; i < max; i++) {
				    int temp = vet[i];
				    int indexRandom = rand() % max;
				
				    vet[i] = vet[indexRandom];
				    vet[indexRandom] = temp;
				}
			
				sair++;
				break;
				
			default:
				op = 0;
				
				system("cls");
				printf("------------------------------");
	            printf("\n\tOpção Inválida!");
	            printf("\n------------------------------\n\n");
	            
	            system("pause");
	            
				break;
		}
	} while(!sair);
}




// Função main do programa.
int main() {
	int i = 0, op = 0, sair = 0;
	int tipo_vet = 0, comp_bubble = 0, comp_merge = 0, comp_shell = 0, comp_quick = 0, comp_heap = 0;
	int* vetor,* vetor_ini;
	float diff = 0, tempo_bubble = 0, tempo_merge = 0, tempo_shell = 0, tempo_quick = 0, tempo_heap = 0;
	struct timeb start, end;
	
	setlocale(LC_ALL, "Portuguese");
	
	vetor_ini = (int *) malloc(max * sizeof(int));
	
	// Verifica se houve espaço suficiente em memória
	if (vetor_ini == NULL) {
		printf("Memória Insuficiente!\n");
		exit(1);
	}
		
	prepVet(vetor_ini);
	
	// Preenche o vetor inicial com números aleatórios.
	//vetorAleatorio(vetor_ini);
	
	do{		
		switch(menu()){
			// 1 - Bubble sort
			case 1:				
				// Reseta o contador de repetições.
				comp = 0;
				
				// Armazena espaço em memória para o vetor
				vetor = (int *) malloc(max * sizeof(int));
				
				// Verifica se houve espaço suficiente em memória
				if (vetor == NULL) {
					printf("Memória Insuficiente!\n");
					exit(1);
				}
				
				for (i = 0; i < max; i++) {
					vetor[i] = vetor_ini[i];
				}
				
				ftime(&start);				 // Início do timer.
				
				bubblesort(vetor,max);  // Chamada do algotimo de ordenação.
				
				ftime(&end);				 // Fim do timer.
				
				// Cáculo do tempo de ordenação em milissegundos
				diff = (float) (1000.0 * (end.time - start.time) + (end.millitm - start.millitm));
				
				system("cls");	// Limpa o console.
				
				// Exibição do vetor ordenado.
				for (i = 0; i < max; i++) {
					printf("%d ", vetor[i]);
				}
				
				comp_bubble = comp;
				tempo_bubble = diff;
				
				// Exibição do tempo e quantidade de comparações.
				
				printf("\n\nTempo: %.2f", tempo_bubble/1000);
				printf("\nQuantidade de comparações: %i", comp_bubble);
				
				printf("\n\n----------------------------------------------\n\n");
				
				system("pause");
				
				// Libera a memória alocada para o vetor
				free(vetor);
				
				break;
				
			// 2 - Merge sort
			case 2:				
				comp = 0;
				
				vetor = (int *) malloc(max * sizeof(int));
				
				if (vetor == NULL) {
					printf("Memória Insuficiente!\n");
					exit(1);
				}
				
				for (i = 0; i < max; i++) {
					vetor[i] = vetor_ini[i];
				}
				
				ftime(&start);
				
				mergesort(vetor,max);
				
				ftime(&end);		
				
				system("cls");
				
				for (i = 0; i < max; i++) {
					printf("%d ", vetor[i]);
				}
				
				comp_merge = comp;
				tempo_merge = diff;
				
				printf("\n\nTempo: %.2f", tempo_merge/1000);
				printf("\nQuantidade de comparações: %i", comp_merge);
				
				printf("\n\n----------------------------------------------\n\n");
				
				system("pause");
				
				free(vetor);
				
				break;
				
			// 3 - Shell sort
			case 3:				
				comp = 0;
				
				vetor = (int *) malloc(max * sizeof(int));
				
				if (vetor == NULL) {
					printf("Memória Insuficiente!\n");
					exit(1);
				}
				
				for (i = 0; i < max; i++) {
					vetor[i] = vetor_ini[i];
				}
				
				ftime(&start);
	
				shellsort(vetor,max);
				
				ftime(&end);	
				
				system("cls");
				
				for (i = 0; i < max; i++) {
					printf("%d ", vetor[i]);
				}
				
				comp_shell = comp;
				tempo_shell = diff;
				
				printf("\n\nTempo: %.2f", tempo_shell/1000);
				printf("\nQuantidade de comparações: %i", comp_shell);
				
				printf("\n\n----------------------------------------------\n\n");
				
				system("pause");
				
				free(vetor);
				
				break;
				
			// 4 - Quick sort
			case 4:				
				comp = 0;
				
				vetor = (int *) malloc(max * sizeof(int));
				
				if (vetor == NULL) {
					printf("Memória Insuficiente!\n");
					exit(1);
				}
				
				for (i = 0; i < max; i++) {
					vetor[i] = vetor_ini[i];
				}
				
				ftime(&start);
	
				quicksort(vetor,max);
				
				ftime(&end);	
				
				system("cls");
				
				for (i = 0; i < max; i++) {
					printf("%d ", vetor[i]);
				}
				
				comp_quick = comp;
				tempo_quick = diff;
				
				printf("\n\nTempo: %.2f", tempo_quick/1000);
				printf("\nQuantidade de comparações: %i", comp_quick);
				
				printf("\n\n----------------------------------------------\n\n");
				
				system("pause");
				
				free(vetor);
				
				break;
				
			// 5 - Heap sort
			case 5:				
				comp = 0;
				
				vetor = (int *) malloc(max * sizeof(int));
				
				if (vetor == NULL) {
					printf("Memória Insuficiente!\n");
					exit(1);
				}
				
				for (i = 0; i < max; i++) {
					vetor[i] = vetor_ini[i];
				}
				
				ftime(&start);
	
				heapsort(vetor,max);
				
				ftime(&end);	
				
				system("cls");
				
				for (i = 0; i < max; i++) {
					printf("%d ", vetor[i]);
				}
				
				comp_heap = comp;
				tempo_heap = diff;
				
				printf("\n\nTempo: %.2f", tempo_heap/1000);
				printf("\nQuantidade de comparações: %i", comp_heap);
				
				printf("\n\n----------------------------------------------\n\n");
				
				system("pause");
				
				free(vetor);
				
				break;
				
			// 6 - Exibir a comparação entre os algoritmos.
			case 6:
				system("cls");
				
				printf("-------------------------------------------------------\n");
				printf("\t\tComparação dos Algoritmos\n");
				printf("-------------------------------------------------------\n");
				printf("Bubble Sort: %.2f segundo(s), %i comparações.\n", tempo_bubble/1000, comp_bubble);
				printf("Merge Sort:  %.2f segundo(s), %i comparações.\n", tempo_merge /1000, comp_merge );
				printf("Shell Sort:  %.2f segundo(s), %i comparações.\n", tempo_shell /1000, comp_shell );
				printf("Quick Sort:  %.2f segundo(s), %i comparações.\n", tempo_quick /1000, comp_quick );
				printf("Heap Sort:   %.2f segundo(s), %i comparações.\n", tempo_heap  /1000, comp_heap  );
				printf("-------------------------------------------------------\n\n");
				
				system("pause");
				
				break;
			
			// Alterar o vetor
			case 7:	
				
				// Caso	o tamanho do vetor tenha sido alterado, as estatísticas são resetadas.
				if(menuVetor()){
					free(vetor_ini);
					
					vetor_ini = (int *) malloc(max * sizeof(int));
	
					// Verifica se houve espaço suficiente em memória
					if (vetor_ini == NULL) {
						printf("Memória Insuficiente!\n");
						exit(1);
					}
					
					prepVet(vetor_ini);
					
					comp_bubble  = 0;
					tempo_bubble = 0;
					
					comp_merge  = 0;
					tempo_merge = 0;
					
					comp_shell  = 0;
					tempo_shell = 0;
					
					comp_quick  = 0;
					tempo_quick = 0;
					
					comp_heap  = 0;
					tempo_heap = 0;
				}
				
				break;
				
			// 8 - Sair
			case 8:
				system("cls");
				sair = 1;
				break;
				
			// Opção Inválida
			default :
				system("cls");
				printf("------------------------------");
	            printf("\n\tOpção Inválida!");
	            printf("\n------------------------------\n\n");
	            
	            system("pause");
	            
	            break;
		}	
		
	} while (!sair);
	
	free(vetor_ini);

	return(0);
}
