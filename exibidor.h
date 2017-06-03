//
//  exibidor.h
//  LeitorExibidor
//
//  Created on 30/05/17.
//  Copyright © 2017 GrupoSB. All rights reserved.
//

#ifndef exibidor_h
#define exibidor_h

#include <stdio.h>

#include "leitor.h"

void printaClassFile(ClassFile*);
void printaCpInfo(ClassFile*);
void printaInterfaces(ClassFile*);
void printaFieldInfo(ClassFile*);
void printaMethodInfo(ClassFile*);
void printaAttributeInfo(ClassFile*);
void imprimeStringPool(CpInfo*, int);
void printTopo(int);
void printBlank(int);
void printBase(int);
void printaCabecalho();
void printLine();
void printSingleLine();

#endif
