
#include <stdio.h>
#include <stdlib.h>


struct no {
    int valor;
    struct no *esq;
    struct no *dir;
    struct no *cima;
    int salvo=0;
};

struct no *novoNO;
struct no *primeiro = NULL;
struct no *aux;

// protótipos das funções
void inserir(int valor);
void mostrarElemento();
int main();
void remover(int);

//percursos
void preOrdem(); //salvo recebe 1
void emOrdem(); // salvo recebe 2
void posOrdem(); //salvo recebe 3

//fator de balanceamento 
int altura(struct no* no);
int desbalanceamento(struct no* no);

int opcao = 0;
int valor = 0;

int nivelGlobal=0;


int main() {
	printf ("\n-----------------ARVORE BINARIA-----------------");
	for (;;) {
	
		printf ("\n1 - Inserir\n2 - Excluir\n3 - Mostrar elemento\n4 - Nivel da Arvore\n5 - Pre Ordem\n6 - Em Ordem\n7 - Pos Ordem \n8 - Desbalanceamento\n0 - Sair");
		printf ("\n Digite:  ");
		scanf ("%d", &opcao);
		
		if (opcao == 1) {
			 	
			printf ("\n Digite o valor: ");
			scanf ("%d", &valor);
			 	
			inserir(valor);
			
			system("cls");
			 	
			printf ("\n %d foi inserido!\n", valor);
			
		
			
		} else if (opcao == 2) {
			 	
			printf ("\n Digite o valor que deseja excluir:  ");
			scanf ("%d", &valor);
			

			remover(valor);
			system("cls");
			
			printf ("\n%d foi excluido!", valor);
			
			
			 	
		} else if (opcao == 3) {
			system("cls");
			mostrarElemento();
			
		}else if (opcao == 4) {
			printf("Nivel da Arvore: %d", nivelGlobal);
		}else if (opcao == 5) {
			printf("Pre Ordem:\n");
			preOrdem();
		}else if (opcao == 6) {
			printf("Em Ordem:\n");
			emOrdem();
		}else if (opcao == 7) {
			printf("Pos Ordem:\n");
			posOrdem();
		}else if (opcao == 8) {
			if(primeiro==NULL) {
				printf("Arvore Vazia!!!");
			} else {
				int valor = desbalanceamento(primeiro);
				printf ("\n %i \n", valor);
			}
		}else if (opcao == 0) {
			system("pause");
			exit(0);
		} else {
			printf ("\n Opção inválida!");
		}
	}
}

void inserir(int valor) {
	
    struct no *temp;
    int calculaNivel=0;
    novoNO = (struct no*)malloc(sizeof(struct no));
    novoNO -> valor = valor;
    novoNO -> esq = NULL;
    novoNO -> dir = NULL;
    
    if (primeiro == NULL) {//se for o primeiro elementto a ser inserido
    	novoNO -> cima = NULL;
        primeiro = novoNO;
    } else {
    	
		temp = primeiro;
		
        while(1) {
        	
        	// se valor digitado for menor que valor do temp
            if (valor < temp -> valor) { 
   				calculaNivel++;
                if (temp -> esq == NULL) {//se esquerda do temp foi igual a null ele vai setar nessa posição
                	novoNO -> cima = temp;
                	temp -> esq = novoNO;
                    break;
                } else {
                
                	temp = temp -> esq; //se não for ele vai percorrer até achar um temp com esquerda null
				}
			
			// se valor digitado for maior que o valor de temp	
            } else {
            	calculaNivel++;
				if(temp -> dir == NULL) {//se direita do temp for igual a null vai ser setado nessa posição
					novoNO -> cima = temp;
                    temp -> dir = novoNO;
                    break;
                } else {
                  	temp = temp -> dir; //se não for ele vai percorrer até achar um temp com direita null
				}  
			}
        }
    }
    if(calculaNivel>nivelGlobal){
    	nivelGlobal=calculaNivel;
	}
}

void mostrarElemento() {
	
	if (primeiro == NULL) {
		printf ("\n Arvore vazia!");
	} else {
		
		no* temp = primeiro;
		
		while(1) {
			
			//system("cls");
				
			printf ("\n\n Elemento atual: %d\n\n", temp -> valor);
			
			printf ("\n 1 - Pai");
			printf ("\n 2 - Filho esquerdo");
			printf ("\n 3 - Filho direito");
			printf ("\n 4 - Retornar ao menu");
			printf ("\n Digite: ");
			scanf ("%d", &opcao);
			
			if (opcao == 1) {
				
				if (temp -> cima == NULL) {
					printf ("\n Nao ha elementos acima\n");
					system("pause");
					mostrarElemento();
				} else {
					temp = temp -> cima;
				}
				
			} else if (opcao == 2) {
				
				if (temp -> esq == NULL) {
					printf ("\n Nao ha elementos a esquerda\n");
					system("pause");
					mostrarElemento();
				} else {
					temp = temp -> esq;
				}
				
			} else if (opcao == 3) {
								
				if (temp -> dir == NULL) {
					printf ("\n Nao ha elementos a direita\n");
					system("pause");
					mostrarElemento();
				} else {
					temp = temp -> dir;
				}
				
			} else if (opcao == 4) {
				system("cls");
				main();
				
			} else {
				printf ("\n Opção inválida!");
			}
		}
	}
}

void remover(int valor) {
	
	struct no *NOAnt, *NOAtual;
	
	struct no *NOAux1, *NOAux2;
	
	if (primeiro == NULL) {
		system("cls");
		printf ("\n A lista está vazia!\n\n");
		main();
	}
	
	NOAnt=NULL;
	NOAtual=primeiro;
	
	while(NOAtual!=NULL){
		if(valor==NOAtual->valor){//se for igual significa que eu achei o número que deseja remover
			
			if(NOAtual->valor==primeiro->valor){//---------------SE FOR A RAIZ -------------------
				//tratando as remoções
				if(NOAtual->esq==NULL){//SE A ESQUERDA FOR NULL E O NÓ FOR UM NÓ FOLHA
					NOAux2=NOAtual->dir;
					free(NOAtual);
					primeiro=NOAux2;
					if(NOAux2!=NULL){
						primeiro->cima=NULL;
					}
					main();
				}
				
				
				NOAux1=NOAtual;          //INICIAR BUSCA PELO FILHO MAIOR DO LADO ESQUERDO
				NOAux2=NOAtual->esq;
				while(NOAux2->dir!=NULL){ 
					NOAux1=NOAux2;
					NOAux2=NOAux2->dir;
				}
				
				if(NOAux1!=NOAtual){ //EXECUÇÃO DA CÓPIA DO FILHO MAIS A DIREITA DA ÁRVORE PARA O NÓ REMOVIDO
					NOAux1->dir=NOAux2->esq;
					NOAux2->esq=NOAtual->esq; //esquerada do numero removido passa a ser a esquerda do no novo
				}
				NOAux2->dir=NOAtual->dir;
				free(NOAtual);
				primeiro=NOAux2;
				primeiro->cima=NULL;
				
				if(primeiro->dir!=NULL){
					primeiro->dir->cima=NOAux2;
				}
				if(primeiro->esq!=NULL){
					primeiro->esq->cima=NOAux2;
				}
				main();
				
			}else{       //------------------------------------SE ELE NÃO FOR A RAIZ ----------------------------------------
				
				if(NOAnt->dir==NOAtual){//se o atual, nó a ser removido, está à direita do nó anterior
					
					if(NOAtual->esq==NULL){//SE A ESQUERDA FOR NULL OU O NÓ FOR UM NÓ FOLHA
						NOAux2=NOAtual->dir;
						NOAnt->dir=NOAux2;
						if(NOAtual->dir!=NULL){
							NOAux2->cima=NOAnt;
						}
						free(NOAtual);
						main();
					}
					
					
					NOAux1=NOAtual;          //INICIAR BUSCA PELO FILHO MAIOR DO LADO ESQUERDO
					NOAux2=NOAtual->esq;
					while(NOAux2->dir!=NULL){
						NOAux1=NOAux2;
						NOAux2=NOAux2->dir;
					}
					
					if(NOAux1!=NOAtual){ //EXECUÇÃO DA CÓPIA DO FILHO MAIS A DIREITA DA ÁRVORE PARA O NÓ REMOVIDO
						NOAux1->dir=NOAux2->esq;
						NOAux2->esq=NOAtual->esq;
					}
					NOAux2->dir=NOAtual->dir;
					NOAux2->cima=NOAtual->cima;
					if(NOAtual->esq!=NULL){
						NOAtual->esq->cima=NOAnt;
					}
					if(NOAtual->dir!=NULL){
						NOAtual->dir->cima=NOAux2;
					}
					free(NOAtual);
					NOAnt->dir=NOAux2;
					if(NOAux2->dir!=NULL){
						NOAux2->dir->cima=NOAux2;
					}
					
					main();
			
				}else if(NOAnt->esq==NOAtual){//se o atual, nó a ser removido, está a esquerda do nó anterior
					
						if(NOAtual->esq==NULL){//SE A ESQUERDA FOR NULL OU NÓ FOR UM NÓ FOLHA
							NOAux2=NOAtual->dir;
							NOAnt->esq=NOAux2;
							if(NOAtual->dir!=NULL){
								NOAux2->cima=NOAnt;  
							}
							free(NOAtual);
							main();
						}
						NOAux1=NOAtual;          //INICIAR BUSCA PELO FILHO MAIOR DO LADO ESQUERDO
						NOAux2=NOAtual->esq;
						while(NOAux2->dir!=NULL){ //quando sair daqui vai ter achado o maior filho
							NOAux1=NOAux2;
							NOAux2=NOAux2->dir;
						}
						
						if(NOAux1!=NOAtual){ //EXECUÇÃO DA CÓPIA DO FILHO MAIS A DIREITA DA ÁRVORE PARA O NÓ REMOVIDO
							NOAux1->dir=NOAux2->esq;
							NOAux2->esq=NOAtual->esq;
						}
						NOAux2->dir=NOAtual->dir;
						if(NOAtual->dir!=NULL){
							NOAtual->dir->cima=NOAux2;
						}
						if(NOAtual->esq!=NULL){
							NOAtual->esq->cima=NOAnt;
						}
						free(NOAtual);
						NOAnt->esq=NOAux2;
						
						main();
						        
				}
			}
		}
		
		NOAnt=NOAtual; // andando na árvore guardando o anterior ao nó que eu quero remover
		
		if(valor>NOAtual->valor){
			NOAtual=NOAtual->dir;
		}else{
			NOAtual=NOAtual->esq;
		}	
	
	
	}
	system("cls");
	printf("NUMERO NAO ENCONTRADO NA ARVORE");
	main();
	

	}
	
void preOrdem(){//raiz - esquerda - direita

	struct no *NOAtual;
	NOAtual=primeiro;
	
	while (1) {
		if (NOAtual->salvo!=1) {
            printf("%d-", NOAtual->valor);
            NOAtual->salvo=1;
        }

        if (NOAtual->esq!=NULL && NOAtual->esq->salvo!=1) {
            NOAtual = NOAtual->esq;
        } else if (NOAtual->dir!=NULL && NOAtual->dir->salvo!=1) {
            NOAtual = NOAtual->dir;
        } else if (NOAtual->salvo==1){
        	if(NOAtual->cima!=NULL){
				NOAtual=NOAtual->cima;
			}else{
				break;
			}
		
		}

        
    };
    
}

void emOrdem(){//esquerda- raiz - direita

	struct no *NOAtual;
	NOAtual=primeiro;
	
	while (1) {
		if (NOAtual->esq!=NULL && NOAtual->esq->salvo!=2) {
            NOAtual = NOAtual->esq;
            continue;
        }

        if (NOAtual->salvo!=2) {
            printf("%d-", NOAtual->valor);
            NOAtual->salvo = 2;
        }

        if (NOAtual->dir!=NULL && NOAtual->dir->salvo!=2) {
            NOAtual = NOAtual->dir;
            continue;
        }
		
		if(NOAtual->cima!=NULL){
				NOAtual=NOAtual->cima;
			}else{
				break;
			}
      
    };
	
	main();
}

void posOrdem() {//esquerda - direita - raiz
  
	struct no *NOAtual;
	NOAtual=primeiro;
    
    while (1) {
        if (NOAtual->esq!=NULL && NOAtual->esq->salvo!=3) {
            NOAtual = NOAtual->esq;
            continue;
        } else if (NOAtual->dir!=NULL && NOAtual->dir->salvo!=3) {
            NOAtual = NOAtual->dir;
            continue;
        }

        if (NOAtual->salvo!=3) {
            printf("%d-", NOAtual->valor);
            NOAtual->salvo = 3;
        }
		
		if(NOAtual->cima!=NULL){
				NOAtual=NOAtual->cima;
			}else{
				break;
			}
       
    };
    main();
}


int desbalanceamento(struct no* no) {
	if (no == NULL) {
		return 0;
	} else {
		return (altura(no->dir) - altura(no->esq));
	}
}

int altura(struct no* no)  {

   if (no == NULL) {
       return 0;
   } else {
   	
   		int alturaEsq = altura(no->esq);
   		int alturaDir = altura(no->dir);
   		
   		if (alturaEsq > alturaDir) {
   			return 1 + alturaEsq;
		} else {
			return 1 + alturaDir;
		}
   }
}

	






