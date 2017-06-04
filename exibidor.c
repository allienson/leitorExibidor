//
//  exibidor.c
//  LeitorExibidor
//
//  Created on 30/05/17.
//  Copyright © 2017 GrupoSB. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "exibidor.h"

void printaClassFile(ClassFile* classFile) {
    
    // GENERAL INFORMATION 
    printTopo();
    printBlank();
    printf("\t%c\t\tGENERAL INFORMATION\t\t%c\n", 179, 179);
    printBlank();
    printBase();
    printf("\t\tMagic:                 0x%08X\n", classFile->magic);                  /* %08X printa em formato hexa */
    printf("\t\tMinor Version:         %d\n", classFile->minorVersion);
    printf("\t\tMajor Version:         %d\n", classFile->majorVersion);
    printf("\t\tConstant Pool Count:   %d\n", classFile->constantPoolCount);
    printf("\t\tAccess Flags:          0x%04X\n", classFile->accessFlags);
    printf("\t\tThis Class:            ");
    imprimeStringPool(classFile->constantPool, classFile->thisClass-1);     // -1 pq o constant Pool comecao no 1 e a struct comeca no 0
    printf("\n");
    printf("\t\tSuper Class:           ");
    imprimeStringPool(classFile->constantPool, classFile->superClass-1);
    printf("\n");
    printf("\t\tInterfaces Count:      %d\n", classFile->interfacesCount);
    printf("\t\tFields Countd:         %d\n", classFile->fieldsCount);
    printf("\t\tMethods Count:         %d\n", classFile->methodsCount);
    printf("\t\tAttributes Count:      %d\n", classFile->attributesCount);
    getchar();

    // CONSTANT POOL
    printTopo();
    printBlank();
    printf("\t%c\t\t   CONSTANT POOL   \t\t%c\n", 179, 179);
    printBlank();
    printBase();
    printaCpInfo(classFile);
    getchar();

    // INTERFACES
    printTopo();
    printBlank();
    printf("\t%c\t\t    INTERFACES     \t\t%c\n", 179, 179);
    printBlank();
    printBase();
    printf("\n");
    printaInterfaces(classFile);
    getchar();
    
    // FIELD INFO
    printTopo();
    printBlank();
    printf("\t%c\t\t    FIELD INFO     \t\t%c\n", 179, 179);
    printBlank();
    printBase();
    printf("\n");
    printaFieldInfo(classFile);
    getchar();

    // METHOD INFO
    printTopo();
    printBlank();
    printf("\t%c\t\t   METHOD INFO     \t\t%c\n", 179, 179);
    printBlank();
    printBase();    
    printaMethodInfo(classFile);
    getchar();
    
    // ATTRIBUTE INFO
    printTopo();
    printBlank();
    printf("\t%c\t\t  ATTRIBUTE INFO   \t\t%c\n", 179, 179);
    printBlank();
    printBase();
    printf("\n");
    printaAttributeInfo(classFile);
    printf("\n");
}

void printaCpInfo(ClassFile* classFile) {
    double valorDouble;                   // usada para converter doubles e longs
    float valorFloat;                       // usada para imprimir valores float                   
    
    for (int i = 0; i < classFile->constantPoolCount-1; ++i) {

        switch (classFile->constantPool[i].tag) {
            case CONSTANT_Class:
                printf("\t[%d] CONSTANT_Class_Info:   cp_info_#%d  ",i+1, classFile->constantPool[i].info.Class.nameIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.Class.nameIndex -1);
                printf("\n");
                break;
            case CONSTANT_Fieldref:
                printf("\t[%d] CONSTANT_Fieldref_Info", i+1);
                printf("\n");
                printf("\t\tClassIndex:        cp_info_#%d  ", classFile->constantPool[i].info.Fieldref.classIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.Fieldref.classIndex-1);
                printf("\n");
                printf("\t\tNameAndTypeIndex:  cp_info_#%d  ", classFile->constantPool[i].info.Fieldref.nameAndTypeIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.Fieldref.nameAndTypeIndex-1);
                printf("\n");
                break;
                
            case CONSTANT_NameAndType:
                printf("\t[%d] CONSTANT_NameAndType_Info", i+1);
                printf("\n");
                printf("\t\tNameIndex:          cp_info_#%d  ", classFile->constantPool[i].info.NameAndType.nameIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.NameAndType.nameIndex-1);                
                printf("\n");
                printf("\t\tDescriptorIndex:    cp_info_#%d  ", classFile->constantPool[i].info.NameAndType.descriptorIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.NameAndType.descriptorIndex-1);
                printf("\n");
                break;
            case CONSTANT_Utf8:
                printf("\t[%d] CONSTANT_Utf8_Info", i+1);
                printf("\n");
                printf("\t\tLength: %d", classFile->constantPool[i].info.Utf8.length);
                printf("\n");
                printf("\t\tBytes:  %s", classFile->constantPool[i].info.Utf8.bytes);
                printf("\n");
                break;
            case CONSTANT_Methodref:
                printf("\t[%d] CONSTANT_Methodref_Info",i+1); 
                printf("\n");
                printf("\t\tClassIndex:        cp_info_#%d  ", classFile->constantPool[i].info.Methodref.classIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.Methodref.classIndex -1);
                printf("\n");
                printf("\t\tNameAndTypeIndex:  cp_info_#%d  ", classFile->constantPool[i].info.Methodref.nameAndTypeIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.Methodref.nameAndTypeIndex -1);
                printf("\n");
                break;
            case CONSTANT_InterfaceMethodref:
                printf("\t[%d] CONSTANT_InterfaceMethodref_Info",i+1);
                printf("\n");
                printf("\t\tClassIndex:        cp_info_#%d  ",classFile->constantPool[i].info.InterfaceMethodref.classIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.InterfaceMethodref.classIndex -1);                
                printf("\n");
                printf("\t\tNameAndTypeIndex:  cp_info_#%d  ",i+1, classFile->constantPool[i].info.InterfaceMethodref.nameAndTypeIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.InterfaceMethodref.nameAndTypeIndex -1);
                printf("\n");
                break;
            case CONSTANT_String:
                printf("\t[%d] CONSTANT_String_Info", i+1);
                printf("\n");
                printf("\t\tStringIndex:       cp_info_#%d  ", classFile->constantPool[i].info.String.stringIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.String.stringIndex -1);
                printf("\n");
                break;
            case CONSTANT_Integer:
                printf("\t[%d] CONSTANT_Integer_Info", i+1);
                printf("\n");
                printf("\t\tValor: %d", classFile->constantPool[i].info.Integer.bytes);
                printf("\n");
                break;
            case CONSTANT_Float:
                memcpy(&valorFloat, &classFile->constantPool[i].info.Float.bytes, sizeof(int32_t));
                printf("\t[%d] CONSTANT_Float_Info", i+1);
                printf("\n");
                printf("\t\tValor: %d", valorFloat);
                printf("\n");
                break;
            case CONSTANT_Double:
                printf("\t[%d] CONSTANT_Double_Info", i+1);
                printf("\n");
                printf("\t\tHighBytes: 0x%08X", classFile->constantPool[i].info.Double.highBytes);
                printf("\n");
                printf("\t\tLowBytes: 0x%08X", classFile->constantPool[i].info.Double.lowBytes);
                printf("\n");
                valorDouble = hexToDouble(classFile->constantPool[i].info.Double.highBytes, classFile->constantPool[i].info.Double.lowBytes);
                printf("\t\tDouble: %g", valorDouble);
                printf("\n");
                printf("\t[%d] (large numeric continued)", i+2);
                printf("\n");
                i++;                // A posicao i e a posicao i+1 sao usadas para o msm double
                break;
            case CONSTANT_Long:
                printf("\t[%d] CONSTANT_Long_Info", i+1);
                printf("\n");
                printf("\tHighBytes: 0x%08X", classFile->constantPool[i].info.Long.highBytes);
                printf("\n");
                printf("\tLowBytes: 0x%08X", classFile->constantPool[i].info.Long.lowBytes);
                printf("\n");
                printf("\t[%d] (large numeric continued)", i+2);
                printf("\n");
                i++;                // A posicao i e a posicao i+1 sao usadas para o msm double
                break;
            default:
                break;
        }
    }
}

void printaInterfaces(ClassFile* classFile) {

    if (classFile->interfacesCount) {
        for (int i = 0; i < classFile->interfacesCount; ++i) {
            
            int index = classFile->constantPool[classFile->interfaces[i]-1].info.Class.nameIndex;
            
            printf("\tInterface %d:   cp_info_#%d   ", i, classFile->interfaces[i], index);
            imprimeStringPool(classFile->constantPool, classFile->interfaces[i]-1);
            printf("\n");
        }
    } else {
        printf("\t     !! Esse classe nao possui Interfaces !!");
        printf("\n");
    }   
}

void printaFieldInfo(ClassFile* classFile) {    
    
    if(classFile->fieldsCount != 0) {
        for (int i = 0; i < classFile->fieldsCount; i++) {

            // imprime informacoes
            printf("\tName:           cp_info_#%d   ", classFile->fields[i].nameIndex);
            imprimeStringPool(classFile->constantPool, classFile->fields[i].nameIndex - 1);
            printf("\n");
            printf("\tDescriptor:     cp_info_#%d   ", classFile->fields[i].descriptorIndex);
            imprimeStringPool(classFile->constantPool, classFile->fields[i].descriptorIndex - 1);
            printf("\n");
            printf("\tAccess Flag:    0x%04X        ", classFile->fields[i].accessFlags);
            printAccessFlag(classFile->fields[i].accessFlags);
            printf("\tNumero de Atributos:  %d", classFile->fields[i].attributesCount);
            printf("\n\n");
            
            for (int j = 0; j < classFile->fields[i].attributesCount; j++) {                
                
                printf("\tGeneric Info %c", 196);
                printSingleLine();
                printf("\n");
                printf("\t\tattribute_name_index:   cp_info_#%d  ", classFile->fields[i].attributes->attributeNameIndex);
                imprimeStringPool(classFile->constantPool, classFile->fields[i].attributes->attributeNameIndex - 1);
                printf("\n");
                printf("\t\tattribute_length:       %d\n", classFile->fields[i].attributes->attributeLength);
                printf("\n");
                
                printf("\tSpecific Info ");
                printSingleLine();
                printf("\n");
                printf("\t\tconstant_value_index:   cp_info_#%d  ", classFile->fields[i].attributes->constantValueIndex);
                imprimeStringPool(classFile->constantPool, classFile->fields[i].attributes->constantValueIndex - 1);
                printf("\n\n\n");
            }
        }
    } else {
        printf("\t      !! Essa classe nao possui Campos !!");
    }
}

void printaMethodInfo(ClassFile* classFile) {
    
    uint16_t name_ind; 
    uint32_t att_len; 
    uint16_t methodsCount = classFile->methodsCount; 

    printf("Methods Count: %d\n", classFile->methodsCount);
    if(methodsCount == 0)
        return;
    else{
        MethodInfo* cp = classFile->methods;
        for(int i = 0; i < methodsCount; cp++){
            printf("access_flag: 0x%0x ",cp->accessFlags);
            printAccessFlag(cp->accessFlags);
            printf("name_index: cp info #%d ",cp->nameIndex);
            imprimeStringPool(classFile->constantPool, cp->nameIndex - 1);
            printf("\n");
            printf("descriptor_index: cp info #%d ",cp->descriptorIndex);
            imprimeStringPool(classFile->constantPool, cp->descriptorIndex - 1);
            printf("\n");
            printf("attributes_count: %d\n",cp->attributesCount);

            // imprime code 
            imprimeCode(classFile, cp->cdAtrb);

            // se o metodo tem dois atributos, eh pq um eh code e o outro exceptions
            if (cp->attributesCount == 2) {
                imprime_exc(classFile, cp->excAtrb); 
            }
            i++;
        }
    }
}

void printaAttributeInfo(ClassFile* classFile) {
    
    if (classFile->attributesCount) {
        
        AttributeInfo* attrInfo = classFile->attributes;
        
        for(int i = 0; i < classFile->attributesCount; attrInfo++){
            printf("\tGeneric Info %c", 196);
            printSingleLine();
            printf("\n\n");
            printf("\tAttribute name index:  cp_info_#%d  ", attrInfo->attributeNameIndex);
            imprimeStringPool(classFile->constantPool, attrInfo->attributeNameIndex-1);
            printf("\n");
            printf("\tAttribute length:  %d", attrInfo->attributeLength);
            printf("\n\n\n");
            printf("\tSpecific Info ");
            printSingleLine();
            printf("\n\n");
            for(uint32_t j = 0; j < attrInfo->attributeLength; attrInfo->info++){
                if(*(attrInfo->info)){
                    printf("\tSource file name index:  cp_info_#%d  ",*(attrInfo->info));
                    imprimeStringPool(classFile->constantPool, *(attrInfo->info) - 1);
                    printf("\n");
                }
                j++;
            }
            i++;
            printf("\n\n");
        }
    } else {
        printf("\t     !! Essa classe nao possui Atributos !!");
        printf("\n\n");
    }    
}

void imprimeStringPool(CpInfo* cp, int pos) {
    int tag;

    // pega tag 
    tag = cp[pos].tag;

    // se a tag for o de um class info 
    if (tag == CONSTANT_Utf8)
    {
        // imprime informacao e sai
        printf("%s", cp[pos].info.Utf8.bytes);
        return;
    }
    // senao, de acordo com a tag, decide qual sera a proxima posicao da cte pool que iremos olhar
    switch(tag)
    {
        case CONSTANT_Class:
            imprimeStringPool(cp, cp[pos].info.Class.nameIndex - 1);
            break;

        case CONSTANT_Fieldref:
            imprimeStringPool(cp, cp[pos].info.Fieldref.classIndex - 1); 
            imprimeStringPool(cp, cp[pos].info.Fieldref.nameAndTypeIndex - 1); 
            break;

        case CONSTANT_NameAndType:
            imprimeStringPool(cp, cp[pos].info.NameAndType.nameIndex - 1 ); 
            imprimeStringPool(cp, cp[pos].info.NameAndType.descriptorIndex - 1); 
            break;

        case CONSTANT_Methodref:
            imprimeStringPool(cp, cp[pos].info.Methodref.classIndex - 1); 
            imprimeStringPool(cp, cp[pos].info.Methodref.nameAndTypeIndex - 1); 
            break;
            
        case CONSTANT_InterfaceMethodref:
            imprimeStringPool(cp, cp[pos].info.InterfaceMethodref.classIndex - 1); 
            imprimeStringPool(cp, cp[pos].info.InterfaceMethodref.nameAndTypeIndex - 1); 
            break;
            
        case CONSTANT_String:
            imprimeStringPool(cp, cp[pos].info.String.stringIndex - 1); 
            break;

        case CONSTANT_Integer:
            printf("%u", cp[pos].info.Integer.bytes);
            break;

        case CONSTANT_Float:
            printf("%u", cp[pos].info.Float.bytes);
            break;

        default:
            break;
    }
}

double hexToDouble(uint32_t highBytes, uint32_t lowBytes){

    double retorno;
    uint64_t checkBoundaries;

    checkBoundaries = highBytes;
    checkBoundaries <<= 32;
    checkBoundaries |= lowBytes;

    long s = ((checkBoundaries >> 63) == 0) ? 1 : -1;
    long e = ((checkBoundaries >> 52) & 0x7ffL);
    long m = (e == 0) ? (checkBoundaries & 0xfffffffffffffL) << 1 : (checkBoundaries & 0xfffffffffffffL) | 0x10000000000000L;
     
    retorno = s * m * pow(2, (e-1023));
 
    return retorno;
}

void printAccessFlag(uint16_t accessFlags){

    switch(accessFlags){
        case 0x0001:
            printf("Public\n");
        break;
        case 0x0009:
            printf("Public Static\n");
        break;
        case 0x0041:
            printf("Public Volatile\n");
        break;
        case 0x00019:
            printf("Public Static Final\n");
        break;
        case 0x0002:
            printf("Private\n");
        break;
        case 0x000A:
            printf("Private Static\n");
        break;
        case 0x0042:
            printf("Private Volatile\n");
        break;
        case 0x0001A:
            printf("Private Static Final\n");
        break;
        case 0x0004:
            printf("Protected\n");
        break;
        case 0x000C:
            printf("Protected Static\n");
        break;
        case 0x0044:
            printf("Protected Volatile\n");
        break;
        case 0x0001C:
            printf("Protected Static Final\n");
        break;
        case 0x0008:
            printf("Static\n");
        break;
        case 0x0010:
            printf("Final\n");
        break;
        case 0x0040:
            printf("Volatile\n");
        break;
        case 0x0080:
            printf("Transient\n");
        break;

    }
}

void imprimeCode(ClassFile* classFile, CodeAttribute* cdAtrb) {
    int opcode, posReferencia; 
    int bytesPreench, offsets;
    uint32_t default_v, low, high, npairs, temp; 
    
    printf("\n----Code Info----\n");
    printf("attribute_name_index: cp info #%d ",cdAtrb->attributeNameIndex);
    imprimeStringPool(classFile->constantPool, cdAtrb->attributeNameIndex - 1);
    printf("\n");
    printf("attribute_length: %d\n",cdAtrb->attributeLength);

    // imprime informacoes do stack
    printf("Tamanho maximo do Stack: %d\n", cdAtrb->maxStack);
    printf("Numero maximo de variaveis locais: %d\n",cdAtrb->maxLocals);
    printf("Tamanho do codigo: %d\n", cdAtrb->codeLength);

    // obtem decodificador de instrucoes 
    Decodificador dec[NUM_INSTRUCAO];
    inicializaDecodificador(dec); 

    // incrementamos k conforme formos passando no loop
    for(uint32_t k = 0; k < cdAtrb->codeLength; ) {    
        // pega opcode da instrucao
        opcode = cdAtrb->code[k];
        printf("%d: %s  ", k, dec[opcode].instrucao);

        // toda vez que lemos bytes devemos incrementar k 
        k++; 

        if (opcode == TABLESWITCH) {
            // a posicao de referencia eh o label numerico associado a tableswitch 
            // k - 1 pois ja incrementamos o k para a proxima instrucao 
            posReferencia = k - 1;

            // pega bytes de preenchimento - nao salva em nenhum lugar
            //bytesPreench = k % 4;  
            bytesPreench = (4 - (k % 4)) % 4;  
            for (int l = 0; l < bytesPreench; l++) {
                k++; 
            }

            // pega bytes do target default
            default_v = 0;
            for (int l = 0; l < 4; l++) {
                default_v = (default_v << 4) + cdAtrb->code[k];   
                k++; 
            }       

            // pega bytes low
            low = 0;
            for (int l = 0; l < 4; l++) {
                low = (low << 4) + cdAtrb->code[k];   
                k++; 
            }       

            // pega bytes high 
            high = 0;
            for (int l = 0; l < 4; l++) {
                high = (high << 4) + cdAtrb->code[k];   
                k++; 
            }       

            printf("  de  %d ateh %d\n", low, high);

            // pega bytes de offset 
            offsets = 1 + high - low;
            for (int l = 0; l < offsets; l++) {
                // pega valor do offset atual 
                temp = 0; 
                for (int i = 0; i < 4; i++) {
                    temp = (temp << 4) + cdAtrb->code[k];   
                    k++; 
                }
                printf("\t%d: %d (+%d)\n", l, (posReferencia + temp), temp);
            } 
            printf("\tdefault: %d (+%d)\n", (default_v + posReferencia), default_v);
        
        } else if (opcode == LOOKUPSWITCH) {
            // a posicao de referencia eh o label numerico associado a tableswitch 
            // k - 1 pois ja incrementamos o k para a proxima instrucao 
            posReferencia = k - 1;

            // pega bytes de preenchimento 
            //bytesPreench = k % 4;  
            bytesPreench = (4 - (k % 4)) % 4;  
            for (int l = 0; l < bytesPreench; l++) {
                k++; 
            }

            // pega bytes do target default
            default_v = 0;
            for (int l = 0; l < 4; l++) {
                default_v = (default_v << 4) + cdAtrb->code[k];   
                k++; 
            }       

            // pega bytes low
            npairs = 0;
            for (int l = 0; l < 4; l++) {
                npairs = (npairs << 4) + cdAtrb->code[k];   
                k++; 
            }       

            printf("  %d\n", npairs);

            // pega npairs 
            for (uint32_t l = 0; l < npairs; l++) {
                // pega valor do match atual 
                temp = 0; 
                for (int i = 0; i < 4; i++) {
                    temp = (temp << 8) + cdAtrb->code[k];   
                    k++; 
                }
                printf("\t%d:  ", temp);

                // pega valor do offset 
                temp = 0; 
                for (int i = 0; i < 4; i++) {
                    temp = (temp << 8) + cdAtrb->code[k];   
                    k++; 
                }
                printf("%d (+%d)\n", temp + posReferencia, temp);

            } 
            printf("\tdefault: %d (+%d)\n", default_v + posReferencia, default_v);

        } else if (opcode == WIDE) {
            printf("\n");

            // pega opcode que segue
            opcode = cdAtrb->code[k];
            k++; 

            // se for um opcode do iload, fload, ...
            if (opcode == ILOAD || opcode == FLOAD || opcode == ALOAD || opcode == LLOAD || \
                    opcode == DLOAD || opcode == ISTORE || opcode == FSTORE || opcode == ASTORE || \
                    opcode == LSTORE || opcode == DSTORE || opcode == RET) {

                printf("%d: %s  ", k - 1, dec[opcode].instrucao);

                // pega index byte1 
                k++; 

                // pega index byte2
                k++; 
                temp = cdAtrb->code[k-2] << 8;
                temp += cdAtrb->code[k-1];
                printf(" %u \n", temp);
            
            } else if (opcode == IINC) {  // se for um iinc
                printf("%d: iinc ", k - 1);

                // pega indexbyte1
                k++; 

                // pega indexbyte2
                k++; 

                // adiciona o 1 pois comecamos a contar em 1
                temp = cdAtrb->code[k-2] << 8;
                temp += cdAtrb->code[k-1];
                printf(" %u ", temp); 

                // pega constbyte1
                k++; 

                // pega constbyte2
                k++; 

                temp = cdAtrb->code[k-2] << 8; 
                temp += cdAtrb->code[k-1];
                printf(" por  %u \n", temp); 
            
            } else { 
                // arquivo .class corrompido! 
                printf("arquivo .class invalido na instrucao wide");
                exit(1);
            }

        } else {
            // obtem quantos operandos a instrucao tem e vai imprimindo operandos
            int num_bytes = dec[opcode].bytes;
            for (int l = 0; l < num_bytes; l++) {

                printf("%d  ", cdAtrb->code[k]);
                if(cdAtrb->code[k] != 0)
                    imprimeStringPool(classFile->constantPool, cdAtrb->code[k] - 1);
                // atualiza valor de k 
                k++;
            }
            printf("\n");
        }
    }      
}

void imprime_exc(ClassFile* classFile, ExceptionsAttribute* excAtrb) {
    printf("\n----Exception Info----\n");
    printf("attribute_name_index: cp_info_#%d ", excAtrb->attributeNameIndex);
    imprimeStringPool(classFile->constantPool, excAtrb->attributeNameIndex - 1);
    printf("\n");
    printf("# - Excecao\n");
    for (int k = 0; k < excAtrb->numberExceptions; k++) {
        printf("%d - %d\n", k, excAtrb->exceptionIndexTable[k]);
    }
}

void printTopo() {
 
    printf("\n\t%c", 218);
    for (int i = 0; i < 47; ++i) {
        printf("%c", 196);  
    }
    printf("%c\n", 191);
}

void printBlank() {

    printf("\t%c", 179);
    for (int i = 0; i < 47; ++i) {
        printf("%c", 32);  
    }
    printf("%c\n", 179);
}

void printBase() {

    printf("\t%c", 192);
    for (int i = 0; i < 47; ++i) {
        printf("%c", 196);  
    }
    printf("%c\n", 217);
}

void printSingleLine(){
    for (int i = 0; i < 34; ++i) {
        printf("%c", 196);  
    }
    printf("%c", 170);
}