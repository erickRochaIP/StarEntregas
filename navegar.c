#include<stdlib.h>
#include<stdio.h>
#include"staren.h"

static int estaContido (int procurado, int *vetor, int ateOndeProcurar){
    int i;
	for(i = 0; i < ateOndeProcurar; i += 1){
		if(vetor[i] == procurado){
			return 1;
		}

	}
	return 0;

}


void nav_viajePara (plan ** grafo, int gfAtual, int * tempo, int gfDestino){
	int proximoPasso = dijkstra_proximo(grafo, gfAtual, gfDestino);
	if(grafo[proximoPasso] == 0){
        // Somar distancia da pos atual com o proximopasso em relaçao a atual
        plan * aux = grafo[gfAtual];
        for (; aux->gfIndice != proximoPasso; aux = aux->prox); // Executa ate achar

        tempo += aux->iTempo; // Depois de achar incrementa o tempo
        gfAtual = proximoPasso;
    }else{
        tempo++;
    }

    //situacaografo=atualizeSituacao(situacaoPlanetas);

    if(gfAtual != gfDestino){
        nav_viajePara(grafo, gfAtual, tempo, gfDestino);
    }

}

int noCaminhoTemNumeroNovo(plan **grafo, int posicao, int destino, int *expressao, int numero){
  while(posicao != destino){
    posicao = dijkstra_proximo(grafo, posicao, destino);
   if(!estaContido(posicao, expressao, numero)){
      return 0;
    }
  }
  return 1;

}

int podeSerColocado(int i, int numero, int * distancias, int * expressao, plan **grafo){
	if(numero < distancias[i]){
		return 0;
	}
	if(estaContido(i, expressao, numero)){
		return 0;
	}
  if(noCaminhoTemNumeroNovo(grafo, expressao[numero-1], i, expressao, numero)){
    return 0;
  }

	return 1;
}


int * transfereVetor(int * origem, int * destino){
	for(int i=0; i<QPLANETAS; i++){
		destino[i]=origem[i];
	}
	return destino;
}


int somaCaminho(plan ** grafo, int * expressao){
	int som = 0;
	
	for(int i = 0; i + 1 < QPLANETAS; i += 1){
		som += dijkstra_pesototal(grafo, expressao[i], expressao[i+1]);
	}

	som += dijkstra_pesototal(grafo, expressao[QPLANETAS-1], expressao[0]);


	return som;
}



void nav_vertices (plan ** grafo, int * distancias, int * expressao, int ** menorCaminho, int numero){
    int soma;
    if(numero >= QPLANETAS){ //se a expressao ja esta pronta compara com o atual menorCaminho
		
        soma = somaCaminho(grafo, expressao);
        int z;
		if(soma <= menorCaminho[1][0]){
			menorCaminho[0] = transfereVetor(expressao, menorCaminho[0]);
			menorCaminho[1][0] = soma;
		}
		
		
    }else{   //senao continua o processo de construção
        int i;
        
        for(i = 0; i < QPLANETAS; i++){
			if(podeSerColocado(i, numero, distancias, expressao)){
				expressao[numero] = i;
				nav_vertices(grafo, distancias, expressao, menorCaminho, numero+1);
			}

        }

       

     }


}
