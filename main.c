//
//  main.c
//  LeitorExibidor
//
//  Created on 26/05/17.
//  Copyright © 2017 GrupoSB. All rights reserved.
//

#include "exibidor.h"  

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_ARQUIVO 100

char* nomeArquivo;

int main(int argc, char* argv[]) {
    nomeArquivo = calloc(TAMANHO_ARQUIVO, sizeof(argv[1]));
    
    system("cls");
    if (argc < 2) {
    	printf("\n\nInsira o caminho do arquivo \".class\" que contem o main:\n");
    	scanf("%s", nomeArquivo);
    	getchar();
    } else {
    	strcpy(nomeArquivo, argv[1]);	
    }
    
    ClassFile* classFile = leitorClasse(nomeArquivo);

    printaClassFile(classFile);
    free(nomeArquivo);
    return 0;
}