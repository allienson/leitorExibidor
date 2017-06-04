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
double hexToDouble(uint32_t, uint32_t);
void printAccessFlag(uint16_t);
void printTopo();
void printBlank();
void printBase();
void printSingleLine();

#endif
