/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Segundo Semestre de 2020                           **/
/**   94 - Prof. Luciano Antonio Digiampietri                       **/
/**                                                                 **/
/**   EP2 - Fila Preferencial                                       **/
/**                                                                 **/
/**   Luan Correa Monteiro                   11797021               **/
/**                                                                 **/
/*********************************************************************/

#include "filapreferencial.h"

PFILA criarFila(){
  PFILA res = (PFILA) malloc(sizeof(FILAPREFERENCIAL));
  res->inicioPref = NULL;
  res->fimPref = NULL;
  res->inicioGeral = NULL;
  res->fimGeral = NULL;
  return res;
}

int tamanho(PFILA f){
  PONT atual = f->inicioGeral;
  int tam = 0;
  while (atual) {
    atual = atual->prox;
    tam++;
  }
  return tam;
}

int tamanhoFilaPreferencial(PFILA f){
  PONT atual = f->inicioPref;
  int tam = 0;
  while (atual) {
    atual = atual->prox;
    tam++;
  }
  return tam;
}

PONT buscarID(PFILA f, int id){
  PONT atual = f->inicioGeral;
   while (atual) {
    if (atual->id == id) return atual;
    atual = atual->prox;
  }
  return NULL;
}

void exibirLog(PFILA f){
  int numElementos = tamanho(f);
  printf("\nLog fila geral [elementos: %i] - Inicio:", numElementos);
  PONT atual = f->inicioGeral;
  while (atual){
    printf(" [%i;%i]", atual->id, atual->ehPreferencial);
    atual = atual->prox;
  }
  printf("\n");
  numElementos = tamanhoFilaPreferencial(f);
  printf("\nLog fila preferencial [elementos: %i] - Inicio:", numElementos);
  atual = f->inicioPref;
  while (atual){
    printf(" [%i;%i]", atual->id, atual->ehPreferencial);
    atual = atual->prox;
  }
  printf("\n\n");
}


bool inserirPessoaNaFila(PFILA f, int id, bool ehPreferencial){
  bool resposta = false;

  if(id < 0) return resposta;
  if(buscarID(f, id)) return resposta;
  PONT pessoaGeral = (PONT)malloc(sizeof(ELEMENTO));
  pessoaGeral->id = id;
  pessoaGeral->ehPreferencial = ehPreferencial;
  if(f->fimGeral){
	f->fimGeral->prox = pessoaGeral; 
	f->fimGeral = pessoaGeral;
	f->fimGeral->prox = NULL;
  }else{
	f->inicioGeral = pessoaGeral;
	f->fimGeral = pessoaGeral;
	f->fimGeral->prox = NULL;
	f->inicioGeral->prox = NULL;
  }
  if(ehPreferencial){
	PONT pessoaPref = (PONT)malloc(sizeof(ELEMENTO));
	pessoaPref->id = id;
	pessoaPref->ehPreferencial = ehPreferencial;
	if(f->fimPref){
	  f->fimPref->prox = pessoaPref;
	  f->fimPref = pessoaPref;
	  f->fimPref->prox = NULL;
	}else{
	  f->inicioPref = pessoaPref;
	  f->fimPref = pessoaPref;
	  f->fimPref->prox = NULL;
	  f->inicioPref->prox = NULL;
	} 
  }
  resposta = true;

  return resposta;
}



bool atenderPrimeiraDaFilaPreferencial(PFILA f, int* id){
  bool resposta = false;

  if(f->inicioGeral == NULL) return resposta;
  if(f->inicioPref){
	 PONT pessoaAtendidadaPref;
	 pessoaAtendidadaPref = f->inicioPref;
	 *id = pessoaAtendidadaPref->id;
	 if(pessoaAtendidadaPref->prox){
		f->inicioPref = pessoaAtendidadaPref->prox;
	 }else{
		f->inicioPref = NULL;
		f->fimPref = NULL;
	 }
	 free(pessoaAtendidadaPref);
	 
	 PONT pessoaAtendidaGeral = buscarID(f, *id);
	 if(f->inicioGeral != pessoaAtendidaGeral){
		PONT aux;
		aux = f->inicioGeral;
		while(aux->prox != pessoaAtendidaGeral){
			aux = aux->prox;
		}
		if(pessoaAtendidaGeral->prox == NULL){
			aux->prox = NULL;
			f->fimGeral = aux;
		}else{
			aux->prox = pessoaAtendidaGeral->prox;
		}
	 }else{
		if(f->inicioGeral->prox){
			f->inicioGeral = f->inicioGeral->prox;
		}else{
			f->inicioGeral = NULL;
			f->fimGeral = NULL;
		}
     }
	 free(pessoaAtendidaGeral);
  }else{
	*id = f->inicioGeral->id; 
	PONT pessoaAtendidaGeral = buscarID(f, *id);
	if(f->inicioGeral->prox){
		f->inicioGeral = f->inicioGeral->prox;
	}else{
		f->inicioGeral = NULL;
		f->fimGeral = NULL;
	}
	 free(pessoaAtendidaGeral);
  }
  resposta = true;

  return resposta;
}



bool atenderPrimeiraDaFilaGeral(PFILA f, int* id){
  bool resposta = false;

  if(f->inicioGeral == NULL) return resposta;
  if(f->inicioGeral->ehPreferencial){
	*id = f->inicioGeral->id;
	PONT pessoaAtendidaGeral = f->inicioGeral;
	if(f->inicioGeral->prox){
		f->inicioGeral = f->inicioGeral->prox;
	}else{
		f->inicioGeral = NULL;
		f->fimGeral = NULL;
	}
	free(pessoaAtendidaGeral);
	 
	PONT aux;
	aux = f->inicioPref;
	while(aux->id != *id){
		aux = aux->prox;
	}
	PONT pessoaAtendidaPref = aux;
	
	if(f->inicioPref != pessoaAtendidaPref){
		aux = f->inicioPref;
		while(aux->prox != pessoaAtendidaPref){
			aux = aux->prox;
		}
		if(pessoaAtendidaPref->prox == NULL){
			aux->prox = NULL;
			f->fimPref = aux;
		}else{
			aux->prox = pessoaAtendidaPref->prox;
		}
	}else{
		if(pessoaAtendidaPref->prox){
			f->inicioPref = pessoaAtendidaPref->prox;
		}else{
			f->inicioPref = NULL;
			f->fimPref = NULL;
		}
	}
	free(pessoaAtendidaPref);
  }else{
	PONT pessoaAtendidaGeral = f->inicioGeral;
	*id = f->inicioGeral->id;
	if(pessoaAtendidaGeral->prox){
		f->inicioGeral = f->inicioGeral->prox;
	}else{
		f->inicioGeral = NULL;
		f->fimGeral = NULL;
	}
	free(pessoaAtendidaGeral);
  }
  resposta = true;

  return resposta;
}



bool desistirDaFila(PFILA f, int id){
  bool resposta = false;

  if(!buscarID(f, id)) return resposta;
  PONT desistenteGeral = buscarID(f, id);
  if(desistenteGeral->ehPreferencial){
	if(f->inicioGeral != desistenteGeral){
		PONT aux;
		aux = f->inicioGeral;
		while(aux->prox != desistenteGeral){
			aux = aux->prox;
		}
		if(desistenteGeral->prox == NULL){
			aux->prox = NULL;
			f->fimGeral = aux;
		}else{
			aux->prox = desistenteGeral->prox;
		}
	}else{
		if(f->inicioGeral->prox){
			f->inicioGeral = f->inicioGeral->prox;
		}else{
			f->inicioGeral = NULL;
			f->fimGeral = NULL;
		}
    }
	free(desistenteGeral);

	PONT aux;
	aux = f->inicioPref;
	while(aux->id != id){
		aux = aux->prox;
	}
	PONT desistentePref = aux;
	if(f->inicioPref != desistentePref){
		aux = f->inicioPref;
		while(aux->prox != desistentePref){
			aux = aux->prox;
		}
		if(desistentePref->prox == NULL){
			aux->prox = NULL;
			f->fimPref = aux;
		}else{
			aux->prox = desistentePref->prox;
		}
	}else{
		if(desistentePref->prox){
			f->inicioPref = desistentePref->prox;
		}else{
			f->inicioPref = NULL;
			f->fimPref = NULL;
		}
	}
	free(desistentePref);
  }else{
	if(f->inicioGeral != desistenteGeral){
		PONT aux;
		aux = f->inicioGeral;
		while(aux->prox != desistenteGeral){
			aux = aux->prox;
		}
		if(desistenteGeral->prox == NULL){
			aux->prox = NULL;
			f->fimGeral = aux;
		}else{
			aux->prox = desistenteGeral->prox;
		}
	}else{
		if(f->inicioGeral->prox){
			f->inicioGeral = f->inicioGeral->prox;
		}else{
			f->inicioGeral = NULL;
			f->fimGeral = NULL;
		}
    }
	free(desistenteGeral);
  }
  
  resposta = true;

  return resposta;
}

