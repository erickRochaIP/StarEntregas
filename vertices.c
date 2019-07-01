int *vertices (int *distancias, int *expressao, int *menorCaminho, int menorCaminhoValor, int numero, int **grafo){

int soma;
if(numero>=qtdPlanetas){
	soma=0;
	for(int z=0; z+1<qtdPlanetas; z++){
		soma += djistra(expressao[z], djistra[z+1], grafo);
	}

	soma += djistra(expressao[qtdPlanetas-1], 0);
	if(menorCaminho>soma || menorCaminho==NULL){
		menorCaminho=expressao;
		menorCaminhoValor=soma;
	}
}else{
	for(int i=0; i<qtdPlanetas; i++){
		if(numero>=distancias[i]){
			if(!estacontido(i, expressao, numero)){
				expressao[numero]=i;
				menorCaminho=vertices(distancias, expressao, menorCaminho, menorCaminhoValor, ++numero, grafo);

			}

		}

	}
	
	
}
return menorCaminho;

}
