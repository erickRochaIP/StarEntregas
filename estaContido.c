int estaContido(int procurado, int *vetor, int ateOndeProcurar){
	for(int i=0; i<ateOndeProcurar; i++){
		if(vetor[i]==procurado){
			return 1;
		}

	}
	return 0;

}



