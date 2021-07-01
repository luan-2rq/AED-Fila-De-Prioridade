/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Segundo Semestre de 2020                           **/
/**   94 - Prof. Luciano Antonio Digiampietri                       **/
/**                                                                 **/
/**   EP3 - Fila de Prioridade (utilizando heap)                    **/
/**                                                                 **/
/**   Luan Correa Monteiro                   11797021               **/
/**                                                                 **/
/*********************************************************************/

#include "filaDePrioridade.h"

PFILA criarFila(int max){
  PFILA res = (PFILA) malloc(sizeof(FILADEPRIORIDADE));
  res->maxElementos = max;
  res->arranjo = (PONT*) malloc(sizeof(PONT)*max);
  res->heap = (PONT*) malloc(sizeof(PONT)*max);
  int i;
  for (i=0;i<max;i++) {
    res->arranjo[i] = NULL;
    res->heap[i] = NULL;
  }
  res->elementosNoHeap = 0;
  return res;
}

void exibirLog(PFILA f){
  printf("Log [elementos: %i]\n", f->elementosNoHeap);
  PONT atual;
  int i;
  for (i=0;i<f->elementosNoHeap;i++){
    atual = f->heap[i];
    printf("[%i;%f;%i] ", atual->id, atual->prioridade, atual->posicao);
  }
  printf("\n\n");
}

int tamanho(PFILA f){
  int tam = 0;
  
  tam = f->elementosNoHeap;
  
  return tam;
}

bool inserirElemento(PFILA f, int id, float prioridade){
  bool res = false;
  
  if(id < 0 || id >= f->maxElementos) return res;
  if(f->arranjo[id] != NULL) return res;
  PONT elemento = (PONT)malloc(sizeof(ELEMENTO));
  elemento->id = id;
  elemento->prioridade = prioridade;
  elemento->posicao = tamanho(f);
  f->arranjo[id] = elemento;
  f->heap[elemento->posicao] = elemento;
  f->elementosNoHeap++;
  aumentarPrioridadeAux2(f, elemento);
  res = true;
  
  return res;
}

bool aumentarPrioridade(PFILA f, int id, float novaPrioridade){
  bool res = false;
  
  if(id < 0 || id >= f->maxElementos) return res;
  if(f->arranjo[id] == NULL) return res;
  if(f->arranjo[id]->prioridade >= novaPrioridade) return res;
  PONT elemento = f->arranjo[id];
  elemento->prioridade = novaPrioridade;
  aumentarPrioridadeAux2(f, elemento);
  res = true;
  
  return res;
}

bool reduzirPrioridade(PFILA f, int id, float novaPrioridade){
  bool res = false;
  
  if(id < 0 || id >= f->maxElementos) return res;
  if(f->arranjo[id] == NULL) return res;
  if(f->arranjo[id]->prioridade <= novaPrioridade) return res;
  PONT elemento = f->arranjo[id];
  elemento->prioridade = novaPrioridade;
  reduzirPrioridadeAux2(f, elemento);
  res = true;
  
  return res;
}

PONT removerElemento(PFILA f){
  PONT res = NULL;
  
  if(tamanho(f) == 0) return NULL; 
  f->arranjo[f->heap[0]->id] = NULL;
  res = f->heap[0];
  f->heap[0] = f->heap[tamanho(f) - 1];
  f->heap[tamanho(f) - 1]->posicao = 0;
  f->heap[tamanho(f) - 1] = NULL;
  f->elementosNoHeap--;
  reduzirPrioridadeAux2(f, f->heap[0]);
  
  return res;
}

bool consultarPrioridade(PFILA f, int id, float* resposta){
  bool res = false;
  
  if(id < 0 || id >= f->maxElementos) return res;
  if(f->arranjo[id] == NULL) return res;
  *resposta = f->arranjo[id]->prioridade;
  res = true;
  
  return res;
}

void reduzirPrioridadeAux2(PFILA f, PONT atual){
	if(atual != NULL){
		int e = (atual->posicao *2) + 1;
		int d = (atual->posicao *2) + 2;
		int m = -1;
		while(atual != NULL && m != atual->posicao){
			if(f->heap[e] != NULL && e < tamanho(f)){
				if(f->heap[e]->prioridade > atual->prioridade){
					m = e;
				}else{
					m = atual->posicao;
				}
			}
			if(f->heap[d] != NULL && d < tamanho(f)){
				if(f->heap[d]->prioridade > f->heap[m]->prioridade){
					m = d;
				}
			}
			if(m != atual->posicao && m != -1){
				f->heap[atual->posicao] = f->heap[m];
				f->heap[m] = atual;
				f->heap[atual->posicao]->posicao = atual->posicao;
				atual->posicao = m;
				e = (atual->posicao *2) + 1;
				d = (atual->posicao *2) + 2;
				m = -1;
			}else{
				break;
			}
		}
	}
}

void aumentarPrioridadeAux2(PFILA f, PONT atual){
	if(atual->posicao != 0){
		while(f->heap[(atual->posicao - 1)/2]->prioridade < f->heap[atual->posicao]->prioridade && atual->posicao > 0){
			f->heap[atual->posicao] = f->heap[(atual->posicao - 1)/2];
			f->heap[(atual->posicao - 1)/2] = atual;
			f->heap[atual->posicao]->posicao = atual->posicao;
			atual->posicao = (atual->posicao - 1)/2;
			if(atual->posicao <= 0)break;
		}
	}
}

