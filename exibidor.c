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
    printf("\n");
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

    // CONSTANT POOL
    printTopo();
    printBlank();
    printf("\t%c\t\t   CONSTANT POOL   \t\t%c\n", 179, 179);
    printBlank();
    printBase();
    printf("\n");
    printaCpInfo(classFile);

    // INTERFACES
    printTopo();
    printBlank();
    printf("\t%c\t\t    INTERFACES     \t\t%c\n", 179, 179);
    printBlank();
    printBase();
    printf("\n");
    printaInterfaces(classFile);
    
    // FIELD INFO
    printTopo();
    printBlank();
    printf("\t%c\t\t    FIELD INFO     \t\t%c\n", 179, 179);
    printBlank();
    printBase();
    printaFieldInfo(classFile);

    // METHOD INFO
    printTopo();
    printBlank();
    printf("\t%c\t\t   METHOD INFO     \t\t%c\n", 179, 179);
    printBlank();
    printBase();    
    //printaMethodInfo(classFile);
    
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
                printf("\n\n");
                break;
            case CONSTANT_Fieldref:
                printf("\t[%d] CONSTANT_Fieldref_Info", i+1);
                printf("\n");
                printf("\t\tClassIndex:        cp_info_#%d  ", classFile->constantPool[i].info.Fieldref.classIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.Fieldref.classIndex-1);
                printf("\n");
                printf("\t\tNameAndTypeIndex:  cp_info_#%d  ", classFile->constantPool[i].info.Fieldref.nameAndTypeIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.Fieldref.nameAndTypeIndex-1);
                printf("\n\n");
                break;
                
            case CONSTANT_NameAndType:
                printf("\t[%d] CONSTANT_NameAndType_Info", i+1);
                printf("\n");
                printf("\t\tNameIndex:          cp_info_#%d  ", classFile->constantPool[i].info.NameAndType.nameIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.NameAndType.nameIndex-1);                
                printf("\n");
                printf("\t\tDescriptorIndex:    cp_info_#%d  ", classFile->constantPool[i].info.NameAndType.descriptorIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.NameAndType.descriptorIndex-1);
                printf("\n\n");
                break;
            case CONSTANT_Utf8:
                printf("\t[%d] CONSTANT_Utf8_Info", i+1);
                printf("\n");
                printf("\t\tLength: %d", classFile->constantPool[i].info.Utf8.length);
                printf("\n");
                printf("\t\tBytes:  %s", classFile->constantPool[i].info.Utf8.bytes);
                printf("\n\n");
                break;
            case CONSTANT_Methodref:
                printf("\t[%d] CONSTANT_Methodref_Info",i+1); 
                printf("\n");
                printf("\t\tClassIndex:        cp_info_#%d  ", classFile->constantPool[i].info.Methodref.classIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.Methodref.classIndex -1);
                printf("\n");
                printf("\t\tNameAndTypeIndex:  cp_info_#%d  ", classFile->constantPool[i].info.Methodref.nameAndTypeIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.Methodref.nameAndTypeIndex -1);
                printf("\n\n");
                break;
            case CONSTANT_InterfaceMethodref:
                printf("\t[%d] CONSTANT_InterfaceMethodref_Info",i+1);
                printf("\n");
                printf("\t\tClassIndex:        cp_info_#%d  ",classFile->constantPool[i].info.InterfaceMethodref.classIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.InterfaceMethodref.classIndex -1);                
                printf("\n");
                printf("\t\tNameAndTypeIndex:  cp_info_#%d  ",i+1, classFile->constantPool[i].info.InterfaceMethodref.nameAndTypeIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.InterfaceMethodref.nameAndTypeIndex -1);
                printf("\n\n");
                break;
            case CONSTANT_String:
                printf("\t[%d] CONSTANT_String_Info", i+1);
                printf("\n");
                printf("\t\tStringIndex:       cp_info_#%d  ", classFile->constantPool[i].info.String.stringIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.String.stringIndex -1);
                printf("\n\n");
                break;
            case CONSTANT_Integer:
                printf("\t[%d] CONSTANT_Integer_Info", i+1);
                printf("\n");
                printf("\t\tValor: %d", classFile->constantPool[i].info.Integer.bytes);
                printf("\n\n");
                break;
            case CONSTANT_Float:
                memcpy(&valorFloat, &classFile->constantPool[i].info.Float.bytes, sizeof(int32_t));
                printf("\t[%d] CONSTANT_Float_Info", i+1);
                printf("\n");
                printf("\t\tValor: %d", valorFloat);
                printf("\n\n");
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
                printf("\n\n");
                printf("\t[%d] (large numeric continued)", i+2);
                printf("\n\n");
                i++;                // A posicao i e a posicao i+1 sao usadas para o msm double
                break;
            case CONSTANT_Long:
                printf("\t[%d] CONSTANT_Long_Info", i+1);
                printf("\n");
                printf("\tHighBytes: 0x%08X", classFile->constantPool[i].info.Long.highBytes);
                printf("\n");
                printf("\tLowBytes: 0x%08X", classFile->constantPool[i].info.Long.lowBytes);
                printf("\n\n");
                printf("\t[%d] (large numeric continued)", i+2);
                printf("\n\n");
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
            printf("\tName %d:      cp_info_#%d ", classFile->fields[i].nameIndex);
            imprimeStringPool(classFile->constantPool, classFile->fields[i].nameIndex - 1);
            printf("\n");
            printf("\tDescriptor:   cp_info_#%d  ", classFile->fields[i].descriptorIndex);
            imprimeStringPool(classFile->constantPool, classFile->fields[i].descriptorIndex - 1);
            printf("\n");
            printf("\tAccess Flag:  0x%04X  ", classFile->fields[i].accessFlags);
            printAccessFlag(classFile->fields[i].accessFlags);
 exit(0);
            /*for (int j = 0; j < classFile->fields[i].attributesCount; j++)
            {
                printf("\t\t----Attribute Info do Field----\n");
                
                // imprime informacao dos atributos
                printf("attribute_name_index: cp info #%d\n", cf->fields[i].attributes->attribute_name_index);
                printf("attribute_length: %d\n", cf->fields[i].attributes->attribute_length);

                // imprime constant value index 
                printf("constant_value_index: cp info #%d", cf->fields[i].attributes->constantvalue_index);
                imprime_string_pool(cf->constant_pool, cf->fields[i].descriptor_index - 1);
                printf("\n");

                printf("\t\t----Fim da Attribute Info do Field----\n");
            }*/
        }

        printf("----End Fields----\n");
    }
}

void printaMethodInfo(ClassFile* classFile) {
    printf("MethodInfo: \n");
    printf("    AccessFlags: %d\n", classFile->methods->accessFlags);
    printf("    NameIndex: %d\n", classFile->methods->nameIndex);
    printf("    DescriptorIndex: %d\n", classFile->methods->descriptorIndex);
    printf("    AttributesCount: %d\n", classFile->methods->attributesCount);
    printf("    CodeAttribute: \n");
    printf("        AttributeNameIndex: %d\n", classFile->methods->cdAtrb->attributeNameIndex);
    printf("        AttributeLength: %d\n", classFile->methods->cdAtrb->attributeLength);
    printf("        MaxStack: %d\n", classFile->methods->cdAtrb->maxStack);
    printf("        MaxLocals: %d\n", classFile->methods->cdAtrb->maxLocals);
    printf("        CodeLength: %d\n", classFile->methods->cdAtrb->codeLength);
    printf("        Code: %d\n", &classFile->methods->cdAtrb->code);
    printf("        ExceptionTableLength: %d\n", classFile->methods->cdAtrb->exceptionTableLength);
    printf("        AttributesCount: %d\n", classFile->methods->cdAtrb->attributesCount);
    printf("        ExceptionsAttribute: \n");
    printf("            StartPC: %d\n", classFile->methods->cdAtrb->exceptionTable->startPc);
    printf("            EndPC: %d\n", classFile->methods->cdAtrb->exceptionTable->endPc);
    printf("            CatchType: %d\n", classFile->methods->cdAtrb->exceptionTable->catchType);
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
        printf("%s  ", cp[pos].info.Utf8.bytes);
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
            // nunca cairemos aqui
            break;

        case CONSTANT_Float:
            // nunca cairemos aqui
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

    if(accessFlags == 0x0000)           // nenhuma flag
        printf("\n");
    if(accessFlags == PUBLIC);          // public
        printf("Public\n");
    if(accessFlags == PRIVATE)          // private
        printf("Private\n");
    if(accessFlags == PROTECTED)        // 
        printf("Protected\n");
    if(accessFlags == STATIC)
        printf("Static\n");
    if(accessFlags == FINAL)
        printf("Final\n");
    if(accessFlags == VOLATILE)
        printf("Volatile\n");
    if(accessFlags == TRASIENT)
        printf("Transient\n");
}

void printTopo() {
 
    printf("\n\n\t%c", 218);
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
    printf("%c\n\n", 217);
}

void printSingleLine(){
    for (int i = 0; i < 34; ++i) {
        printf("%c", 196);  
    }
    printf("%c", 170);
}