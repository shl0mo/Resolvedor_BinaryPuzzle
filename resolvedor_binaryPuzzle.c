#include <stdio.h>
#include <stdlib.h>

typedef struct linha {
	int indice;
	int valor;
	struct linha *prox, *ant;
}LINHA;

typedef LINHA* LINHAptr;

typedef struct matriz {
	int indice;
	LINHAptr linha;
	struct matriz *prox, *ant;
}MATRIZ;

typedef MATRIZ* MATRIZptr;

LINHAptr inicializa_linha(int valor) {
	LINHAptr linha = (LINHAptr) malloc(sizeof(LINHA));
	linha->indice = 0;
	linha->valor = valor;
	linha->ant = NULL;
	linha->prox = NULL;
	return linha;
}

MATRIZptr inicializa_matriz() {
	MATRIZptr matriz = (MATRIZptr) malloc(sizeof(MATRIZ));
	matriz->indice = -1;
	matriz->linha = NULL;
	matriz->ant = NULL;
	matriz->prox = NULL;
	return matriz;
}

void insere_elementos_linha(LINHAptr linha, int elementos[]) {
	int i = 0;
	LINHAptr final_linha = linha;
	for (i = 1; i < 6; i++) {
		LINHAptr nova_linha = (LINHAptr) malloc(sizeof(LINHA));
		nova_linha->indice = i;
		nova_linha->valor = elementos[i];
		nova_linha->ant = final_linha;
		nova_linha->prox = NULL;
		final_linha->prox = nova_linha;
		final_linha = nova_linha;
	}
}

void insere_linha_matriz(MATRIZptr matriz, LINHAptr linha, int indice) {
	MATRIZptr percorre_matriz = matriz;
	while (percorre_matriz->prox != NULL) {
		percorre_matriz = percorre_matriz->prox;
	}
	MATRIZptr nova_linha_matriz = (MATRIZptr) malloc(sizeof(MATRIZ));
	nova_linha_matriz->indice = indice;
	nova_linha_matriz->linha = linha;
	nova_linha_matriz->ant = percorre_matriz;
	nova_linha_matriz->prox = NULL;
	percorre_matriz->prox = nova_linha_matriz;
}

void imprime_linha(LINHAptr linha) {
	LINHAptr percorre_linha = linha;
	while (percorre_linha) {
		printf("%i ", percorre_linha->valor);
		percorre_linha = percorre_linha->prox;
	}
}

void imprime_matriz(MATRIZptr matriz) {
	MATRIZptr percorre_matriz = matriz;
	while (percorre_matriz) {
		imprime_linha(percorre_matriz->linha);
		printf("\n");
		percorre_matriz = percorre_matriz->prox;
	}
}

void isola_dupla_horizontal(MATRIZptr matriz, int analisado) {
	MATRIZptr percorre_matriz = matriz->prox;
	while (percorre_matriz) {
		LINHAptr percorre_linha = percorre_matriz->linha;
		while (percorre_linha) {
			if (percorre_linha->indice >= 1 && percorre_linha->indice <= 4) {
				if (percorre_linha->ant->valor == analisado && percorre_linha->prox->valor == analisado) {
					if (analisado == 0) {
						percorre_linha->valor = 1;
					} else {
						percorre_linha->valor = 0;
					}
				}
			}
			if (percorre_linha->indice == 0) {
				if (percorre_linha->valor == analisado && percorre_linha->prox->valor == analisado) {
					if (analisado == 0) {
						percorre_linha->prox->prox->valor = 1;
					} else {
						percorre_linha->prox->prox->valor = 0;
					}				
				}
			} else if (percorre_linha->indice <= 3) {
				if (percorre_linha->valor == analisado && percorre_linha->prox->valor == analisado) {
					if (analisado == 0) {
						percorre_linha->prox->prox->valor = 1;
						percorre_linha->ant->valor = 1;
					} else {
						percorre_linha->prox->prox->valor = 0;
						percorre_linha->ant->valor = 0;
					}
				}
			} else if (percorre_linha->indice == 4) {
				if (percorre_linha->valor == analisado && percorre_linha->prox->valor == analisado) {
					if (analisado == 0) {
						percorre_linha->ant->valor = 1;
					} else {
						percorre_linha->ant->valor = 0;
					}
				}
			}
			percorre_linha = percorre_linha->prox;
		}
		percorre_matriz = percorre_matriz->prox;
	}
}

MATRIZptr transpoe_matriz(MATRIZptr matriz) {
	MATRIZptr matriz_resultante = inicializa_matriz();
	MATRIZptr percorre_matriz = matriz->prox;
	int i = 0;
	int j = 0;
	while (i < 6) {
		int elementos[6];
		int k = 0;
		while (percorre_matriz) {
			LINHAptr percorre_linha = percorre_matriz->linha;
			for (j = 0; j < i; j++) {
				percorre_linha = percorre_linha->prox;
			}
			elementos[k] = percorre_linha->valor;
			k++;
			percorre_matriz = percorre_matriz->prox;
		}
		LINHAptr nova_linha = inicializa_linha(elementos[0]);
		insere_elementos_linha(nova_linha, elementos);
		insere_linha_matriz(matriz_resultante, nova_linha, i);
		i++;
		percorre_matriz = matriz->prox;
	}
	return matriz_resultante;
}

int preencher_lacunas_parcial(MATRIZptr matriz) {
	MATRIZptr percorre_matriz = matriz->prox;
	while (percorre_matriz) {
		LINHAptr percorre_linha = percorre_matriz->linha;
		while (percorre_linha) {
			if (percorre_linha->indice >= 1 && percorre_linha->indice <= 4) {
				if (percorre_linha->ant->valor == 0 && percorre_linha->prox->valor == 0) {
					if (percorre_linha->valor != 1) {
						return 1;
					}
				}
				if (percorre_linha->ant->valor == 1 && percorre_linha->prox->valor == 1) {
					if (percorre_linha->valor != 0) {
						return 1;
					}
				}
			}
			if (percorre_linha->indice == 0) {
				if (percorre_linha->valor == 0 && percorre_linha->prox->valor == 0) {
					if (percorre_linha->prox->prox->valor != 1) {
						return 1;
					}
				}
				if (percorre_linha->valor == 1 && percorre_linha->prox->valor == 1) {
					if (percorre_linha->prox->prox->valor != 0) {
						return 1;
					}
				}
			} else if (percorre_linha->indice <= 3) {
				if (percorre_linha->valor == 0 && percorre_linha->prox->valor == 0) {
					if (percorre_linha->ant->valor != 1 || percorre_linha->prox->prox->valor != 1) {
						return 1;
					}
				}
				if (percorre_linha->valor == 1 && percorre_linha->prox->valor == 1) {
					if (percorre_linha->ant->valor != 0 || percorre_linha->prox->prox->valor != 0) {
						return 1;
					}
				}
			} else if (percorre_linha->indice == 4) {
				if (percorre_linha->valor == 0 && percorre_linha->prox->valor == 0) {
					if (percorre_linha->ant->valor != 1) {
						return 1;
					}
				}
				if (percorre_linha->valor == 1 && percorre_linha->prox->valor == 1) {
					if (percorre_linha->ant->valor != 0) {
						return 1;
					}
				}
			}
			percorre_linha = percorre_linha->prox;
		}
		percorre_matriz = percorre_matriz->prox;
	}
	return 0;
}

int preencher_restantes(MATRIZptr matriz) {
	MATRIZptr percorre_matriz = matriz->prox;
	while (percorre_matriz) {
		LINHAptr percorre_linha = percorre_matriz->linha;
		while (percorre_linha) {
			if (percorre_linha->valor != 1 || percorre_linha->valor != 0) {
				return 1;
			}
			percorre_linha = percorre_linha->prox;
		}
		percorre_matriz = percorre_matriz->prox;
	}
	return 0;
}

int main(void) {
	int elementos[6];
	int e1, e2, e3, e4, e5, e6;
	int i = 0;
	MATRIZptr matriz = inicializa_matriz();
	for (i = 0; i < 6; i++) {
		scanf("%i %i %i %i %i %i", &e1, &e2, &e3, &e4, &e5, &e6);
		elementos[1] = e2;
		elementos[2] = e3;
		elementos[3] = e4;
		elementos[4] = e5;
		elementos[5] = e6;
		LINHAptr linha = inicializa_linha(e1);
		insere_elementos_linha(linha, elementos);
		insere_linha_matriz(matriz, linha, i);
	}
	int preencher_lacunas = preencher_lacunas_parcial(matriz);
	while (preencher_lacunas == 1) {
		isola_dupla_horizontal(matriz, 0);
		isola_dupla_horizontal(matriz, 1);
		preencher_lacunas = preencher_lacunas_parcial(matriz);
	}
	MATRIZptr matriz_transposta = transpoe_matriz(matriz);
	preencher_lacunas = preencher_lacunas_parcial(matriz_transposta);
	while (preencher_lacunas == 1) {
		isola_dupla_horizontal(matriz_transposta, 0);
		isola_dupla_horizontal(matriz_transposta, 1);
		preencher_lacunas = preencher_lacunas_parcial(matriz_transposta);
	}
	MATRIZptr matriz_normal = transpoe_matriz(matriz_transposta);
	int restantes = preencher_restantes(matriz_normal);
	while (restantes) {
		isola_dupla_horizontal(matriz_normal, 0);
		isola_dupla_horizontal(matriz_normal, 1);
		if (restantes) {
			MATRIZptr matriz_transposta2 = transpoe_matriz(matriz_normal);
			isola_dupla_horizontal(matriz_transposta2, 0);
			isola_dupla_horizontal(matriz_transposta2, 1);
			MATRIZptr matriz_resultante = transpoe_matriz(matriz_transposta2);
			matriz_normal = matriz_resultante;
			break;
		}
		restantes = preencher_restantes(matriz_normal);
	}
	imprime_matriz(matriz_normal);
}
