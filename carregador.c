//
//  carregador.c
//  LeitorExibidor
//
//  Created on 26/05/17.
//  Copyright © 2017 GrupoSB. All rights reserved.
//

#include "carregador.h"
#include "areaMetodos.h"
#include "leitor.h"
#include "exibidor.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_EXTENSAO_PONTO_CLASS 10

bool jaCarregou = false;

AreaMetodos areaMetodos;

void carregaClasseParaMemoria(char* caminhoClasse) {
    areaMetodos.quantidadeClasses = 0;
    areaMetodos.quantidadeClasses++;
    char* caminhoClasseAtualizado = malloc(strlen(caminhoClasse) + TAM_EXTENSAO_PONTO_CLASS);
    sprintf(caminhoClasseAtualizado, "%s", caminhoClasse);
    areaMetodos.classes[areaMetodos.quantidadeClasses - 1] = leitorClasse(caminhoClasseAtualizado);
}

void carregaMemClasse(char* nomeClass){
	int aux;

    // se eh a primeira classe a ser carregada
    if (jaCarregou == false)
    {
        area_met.num_classes = 0;
        jaCarregou = true; 
    }

	//Se ja esta carregado retorna posição no array de classes.
	for (int32_t i = 0; i < area_met.num_classes; i++) {
		if (strcmp(nomeClass, retornaNomeClasse(area_met.array_classes[i])) == 0){
			return i;
		}
	}

	//Se não está carregado carrega e salva no array de classes.

	//uma classe nova vai entrar na lista de classes carregadas.
	area_met.num_classes++;
	aux = area_met.num_classes;

	classFile** arrayClassesTemp = NULL;

	//Realoca o tamanho do vetor para adicionar a nova classe carregada.
	//Classes previamente carregas não são perdidas com o realloc.
	arrayClassesTemp = (classFile**) realloc(area_met.array_classes, (aux*sizeof(classFile *)));
	//printf("ponteiro tempo: %d\n",*arrayClassesTemp);

    area_met.array_classes = (classFile**) calloc(1, sizeof(classFile*));
    area_met.array_classes = arrayClassesTemp;

    //Atualiza o nome do path para adicionar .class a um path
    //Aloca espaço do tamanho do nome da classe mais espaço para .class /0 e ./
    char* destino = malloc(strlen(nomeClass) + 10);
    if (strstr(nomeClass,".class") != NULL) {
		sprintf(destino, "%s", nomeClass);
	} else {
		sprintf(destino, "./%s.class",nomeClass);
	}

	//printf("destino: %s\n",destino);

    area_met.array_classes[area_met.num_classes - 1] = leitorClasse(destino);  
    
	if(area_met.array_classes[area_met.num_classes -1] == NULL){
		printf("Erro ao carregar classe!\n");
		exit(0);
	}

}



ClassFile* buscaClassFile() {
    return areaMetodos.classes[0];
}
