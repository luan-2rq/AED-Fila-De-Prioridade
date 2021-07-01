/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Segundo Semestre de 2020                           **/
/**   94 - Prof. Luciano Antonio Digiampietri                       **/
/**                                                                 **/
/**   EP1 - Fila de Prioridade                                      **/
/**                                                                 **/
/**   Luan Correa Monteiro                   11797021               **/
/**                                                                 **/
/*********************************************************************/

#include "filaDePrioridade.h"

PFILA criarFila(int max){
  PFILA res = (PFILA) malloc(sizeof(FILADEPRIORIDADE));
  res->maxElementos = max;
  res->arranjo = (PONT*) malloc(sizeof(PONT)*max);
  int i;
  for (i=0;i<max;i++) res->arranjo[i] = NULL;
  PONT cabeca = (PONT) malloc(sizeof(ELEMENTO));
  res->fila = cabeca;
  cabeca->ant = cabeca;
  cabeca->prox = cabeca;
  cabeca->id = -1;
  cabeca->prioridade = 1000000;
  return res;
}

void exibirLog(PFILA f){
  printf("Log [elementos: %i (alem do no cabeca)]\n", tamanho(f));
  PONT atual = f->fila;
  printf("%p[%i;%f;%p]%p ", atual->ant, atual->id, atual->prioridade, atual, atual->prox);
  atual = atual->prox;
  while (atual != f->fila){
    printf("%p[%i;%f;%p]%p ", atual->ant, atual->id, atual->prioridade, atual, atual->prox);
    atual = atual->prox;
  }
  printf("\nElementos validos: ");
  atual = atual->prox;
  while (atual != f->fila){
    printf("[%i;%f;%p] ", atual->id, atual->prioridade, atual);
    atual = atual->prox;
  }

  printf("\nValores do arrajo:\n\[ ");
  int x;
  for (x=0;x<f->maxElementos;x++) printf("%p ",f->arranjo[x]);
  printf("]\n\n");
}



int tamanho(PFILA f){
  int tam = 0;

  //Passando pelos elementos da lista e adicionando 1 ao tamanho a cada elemento passado
  PONT aux = f->fila->prox;
  while(aux != f->fila){
	tam++;
	aux = aux->prox;
  }

  return tam;
}



bool inserirElemento(PFILA f, int id, float prioridade){
  bool resposta = false;

  if(id < 0 || id >= f->maxElementos) return resposta; 
  if(f->arranjo[id] != NULL) return resposta;
  if(prioridade > 999999) return resposta;
  resposta = true;
  //Fazendo a busca do elemento que vai auxiliar na insercao do novo elemento na lista
  PONT aux;
  aux = f->fila->ant;
  while(aux->prioridade < prioridade  && aux != f->fila){
	aux = aux->ant;
  }
  //Adicionando elemento a lista de prioridade
  PONT elemento = (PONT)malloc(sizeof(ELEMENTO));
  elemento->prox = aux->prox;
  elemento->ant = aux;
  elemento->prox->ant = elemento;
  elemento->ant->prox = elemento;
  //Atualizando o id e a prioridade
  elemento->id = id;
  elemento->prioridade = prioridade;
  //Adicionando elemento ao arranjo
  f->arranjo[id] = elemento;

  return resposta;
}



bool aumentarPrioridade(PFILA f, int id, float novaPrioridade){
  bool resposta = false;

  if(id < 0 || id >= f->maxElementos) return resposta;
  if(f->arranjo[id] == NULL) return resposta;
  if(f->arranjo[id]->prioridade >= novaPrioridade || novaPrioridade > 999999) return resposta;
  //Atualizando prioridade
  f->arranjo[id]->prioridade = novaPrioridade;
  //Verificando se o elemento ja esta na posicao de maior prioridade da fila
  if(f->arranjo[id]->ant != f->fila){
  //Fazendo a busca do elemento que ira auxiliar na insercao do elemento na nova posicao
	PONT aux = f->arranjo[id]->ant;
	while(aux->prioridade < novaPrioridade && aux != f->fila){
	  aux = aux->ant;
	}
	//Verificando se eh necessario alterar a posicao do elemento
	if(aux->prox != f->arranjo[id]){
		//Removendo o elemento de sua posicao
		f->arranjo[id]->prox->ant = f->arranjo[id]->ant;
		f->arranjo[id]->ant->prox = f->arranjo[id]->prox;
		//Adicionando o elemento na nova posicao
		f->arranjo[id]->prox = aux->prox;
		f->arranjo[id]->ant = aux;
		aux->prox = f->arranjo[id];
		f->arranjo[id]->prox->ant = f->arranjo[id];
	}
  }
  resposta = true;

  return resposta;
}



bool reduzirPrioridade(PFILA f, int id, float novaPrioridade){
  bool resposta = false;

  if(id < 0 || id >= f->maxElementos) return resposta;
  if(f->arranjo[id] == NULL) return resposta;
  if(f->arranjo[id]->prioridade <= novaPrioridade) return resposta;
  //Atualizando prioridade
  f->arranjo[id]->prioridade = novaPrioridade;
  //Verificando se o elemento ja esta na posicao de menor prioridade da lista
  if(f->arranjo[id]->prox != f->fila){
  //Fazendo a busca do elemento que ira auxialiar na insercao do elemento na nova posicao
	PONT aux = f->arranjo[id]->prox;
	while(aux->prioridade > novaPrioridade && aux != f->fila){
	  aux = aux->prox;
	}
	//Verificando se eh necessario alterar a posicao do elemento
	if(aux->ant != f->arranjo[id]){
		//Removendo o elemento de sua posicao
		f->arranjo[id]->prox->ant = f->arranjo[id]->ant;
		f->arranjo[id]->ant->prox = f->arranjo[id]->prox;
		//Adicionando o elemento na nova posicao
		f->arranjo[id]->prox = aux;
		f->arranjo[id]->ant = aux->ant;
		aux->ant = f->arranjo[id];
		f->arranjo[id]->ant->prox = f->arranjo[id];
	}
  }
  resposta = true;

  return resposta;
}



PONT removerElemento(PFILA f){
  PONT resposta = NULL;

  if(f->fila->prox == f->fila) return resposta;
  //Adicionando o elemento na variavel resposta
  resposta = f->arranjo[f->fila->prox->id];
  //Removendo elemento do arranjo e da lista
  f->arranjo[f->fila->prox->id] = NULL;
  f->fila->prox = f->fila->prox->prox;
  f->fila->prox->ant = f->fila;

  return resposta;
}



bool consultarPrioridade(PFILA f, int id, float* resposta){
  bool resp = false;

  if(id < 0 || id >= f->maxElementos) return resp;
  if(f->arranjo[id] == NULL) return resp;
  //Implementando a prioridade do elemento buscado no parametro resposta
  *resposta = f->arranjo[id]->prioridade;
  resp = true;

  return resp;
}


