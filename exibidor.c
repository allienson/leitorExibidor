//
//  exibidor.c
//  LeitorExibidor
//
//  Created on 30/05/17.
//  Copyright © 2017 GrupoSB. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>

#include "exibidor.h"

void printaCabecalho(){
    
    system("cls");
    printTopo(1);
    printBlank(1);
    printf("\t%c\t      LEITOR-EXIBIDOR .class  \t\t%c\n", 186, 186);

    printBlank(1);
    printLine();
    printBlank(1);
    printf("\t%c\t     Allisson Barros  12/0055619\t%c\n", 186, 186);
    printf("\t%c\t          Daniel Luz  13/0007714\t%c\n", 186, 186);
    printf("\t%c\tLuiz Fernando Vieira  13/0013757\t%c\n", 186, 186);
    printf("\t%c\t   Mariana Pannunzio  12/0055619\t%c\n", 186, 186);
    printf("\t%c\t      Mateus Denucci  12/0053080\t%c\n", 186, 186);
    printBlank(1);
    printLine();
    printBlank(1);
    printf("\t%c\t     Software Basico 2017-01  \t\t%c\n", 186, 186);
    printf("\t%c\t Universidade de Brasilia - UnB \t%c\n", 186, 186);    
    printBlank(1);
    printBase(1);
}

void printaClassFile(ClassFile* classFile) {
    
    // GENERAL INFORMATION 
    printTopo(0);
    printBlank(0);
    printf("\t%c\t\tGENERAL INFORMATION\t\t%c\n", 179, 179);
    printBlank(0);
    printBase(0);
    printf("\n");
    printf("\t\tMagic:                 0x%X\n\n", classFile->magic);                  /* %X printa em formato hexa */
    printf("\t\tMinor Version:         %d\n\n", classFile->minorVersion);
    printf("\t\tMajor Version:         %d\n\n", classFile->majorVersion);
    printf("\t\tConstant Pool Count:   %d\n\n", classFile->constantPoolCount);
    printf("\t\tAccess Flags:          0x%X\n\n", classFile->accessFlags);
    printf("\t\tThis Class:            ");
    imprimeStringPool(classFile->constantPool, classFile->thisClass-1);     // -1 pq o constant Pool comecao no 1 e a struct comeca no 0
    printf("\n\n");
    printf("\t\tSuper Class:           ");
    imprimeStringPool(classFile->constantPool, classFile->superClass-1);
    printf("\n\n");
    printf("\t\tInterfaces Count:      %d\n\n", classFile->interfacesCount);
    printf("\t\tFields Countd:         %d\n\n", classFile->fieldsCount);
    printf("\t\tMethods Count:         %d\n\n", classFile->methodsCount);
    printf("\t\tAttributes Count:      %d\n\n", classFile->attributesCount);

    // CONSTANT POOL
    printTopo(0);
    printBlank(0);
    printf("\t%c\t\t   CONSTANT POOL   \t\t%c\n", 179, 179);
    printBlank(0);
    printBase(0);
    printf("\n");
    printaCpInfo(classFile);

    // INTERFACES
    printTopo(0);
    printBlank(0);
    printf("\t%c\t\t    INTERFACES     \t\t%c\n", 179, 179);
    printBlank(0);
    printBase(0);
    printf("\n");
    printaInterfaces(classFile);

    // FIELD INFO
    printTopo(0);
    printBlank(0);
    printf("\t%c\t\t    FIELD INFO     \t\t%c\n", 179, 179);
    printBlank(0);
    printBase(0);
    printf("\n");
    //printaFieldInfo(classFile);

    // METHOD INFO
    printTopo(0);
    printBlank(0);
    printf("\t%c\t\t   METHOD INFO     \t\t%c\n", 179, 179);
    printBlank(0);
    printBase(0);
    printf("\n");
    //printaMethodInfo(classFile);

    // ATTRIBUTE INFO
    printTopo(0);
    printBlank(0);
    printf("\t%c\t\t  ATTRIBUTE INFO   \t\t%c\n", 179, 179);
    printBlank(0);
    printBase(0);
    printf("\n");
    printaAttributeInfo(classFile);

    printf("\n\n\n");
}

void printaCpInfo(ClassFile* classFile) {
    float valorFloat;
    for (int i = 0; i < classFile->constantPoolCount-1; ++i) {
    
        switch (classFile->constantPool[i].tag) {
            case CONSTANT_Class:
                printf("\t[%d] CONSTANT_Class_Info:   cp_info_#%d  ",i+1, classFile->constantPool[i].info.Class.nameIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.Class.nameIndex -1);
                printf("\n\n\n");
                break;
            case CONSTANT_Fieldref:
                printf("\t[%d] CONSTANT_Fieldref_Info", i+1);
                printf("\n");
                printf("\t\tClassIndex:        cp_info_#%d  ", classFile->constantPool[i].info.Fieldref.classIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.Fieldref.classIndex-1);
                printf("\n");
                printf("\t\tNameAndTypeIndex:  cp_info_#%d  ", classFile->constantPool[i].info.Fieldref.nameAndTypeIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.Fieldref.nameAndTypeIndex-1);
                printf("\n\n\n");
                break;
                
            case CONSTANT_NameAndType:
                printf("\t[%d] CONSTANT_NameAndType_Info", i+1);
                printf("\n");
                printf("\t\tNameIndex:          cp_info_#%d  ", classFile->constantPool[i].info.NameAndType.nameIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.NameAndType.nameIndex-1);                
                printf("\n");
                printf("\t\tDescriptorIndex:    cp_info_#%d  ", classFile->constantPool[i].info.NameAndType.descriptorIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.NameAndType.descriptorIndex-1);
                printf("\n\n\n");
                break;
            case CONSTANT_Utf8:
                printf("\t[%d] CONSTANT_Utf8_Info", i+1);
                printf("\n");
                printf("\t\tLength: %d", classFile->constantPool[i].info.Utf8.length);
                printf("\n");
                printf("\t\tBytes:  %s", classFile->constantPool[i].info.Utf8.bytes);
                printf("\n\n\n");
                break;
            case CONSTANT_Methodref:
                printf("\t[%d] CONSTANT_Methodref_Info",i+1); 
                printf("\n");
                printf("\t\tClassIndex:        cp_info_#%d  ", classFile->constantPool[i].info.Methodref.classIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.Methodref.classIndex -1);
                printf("\n");
                printf("\t\tNameAndTypeIndex:  cp_info_#%d  ", classFile->constantPool[i].info.Methodref.nameAndTypeIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.Methodref.nameAndTypeIndex -1);
                printf("\n\n\n");
                break;
            case CONSTANT_InterfaceMethodref:
                printf("\t[%d] CONSTANT_InterfaceMethodref_Info",i+1);
                printf("\n");
                printf("\t\tClassIndex:        cp_info_#%d  ",classFile->constantPool[i].info.InterfaceMethodref.classIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.InterfaceMethodref.classIndex -1);                
                printf("\n");
                printf("\t\tNameAndTypeIndex:  cp_info_#%d  ",i+1, classFile->constantPool[i].info.InterfaceMethodref.nameAndTypeIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.InterfaceMethodref.nameAndTypeIndex -1);
                printf("\n\n\n");
                break;
            case CONSTANT_String:
                printf("\t[%d] CONSTANT_String_Info", i+1);
                printf("\n");
                printf("\t\tStringIndex:       cp_info_#%d  ", classFile->constantPool[i].info.String.stringIndex);
                imprimeStringPool(classFile->constantPool, classFile->constantPool[i].info.String.stringIndex -1);
                printf("\n\n\n");
                break;
            case CONSTANT_Integer:
                printf("\t[%d] CONSTANT_Integer_Info", i+1);
                printf("\n");
                printf("\t\tValor: %d", classFile->constantPool[i].info.Integer.bytes);
                printf("\n\n\n");
                break;
            case CONSTANT_Float:
                memcpy(&valorFloat, &classFile->constantPool[i].info.Float.bytes, sizeof(int32_t));
                printf("\t[%d] CONSTANT_Float_Info", i+1);
                printf("\n");
                printf("\t\tValor: %d", valorFloat);
                printf("\n\n\n");
                break;
            case CONSTANT_Double:
                printf("\tHighBytes: %d", classFile->constantPool[i].info.Double.highBytes);
                printf("\n");
                printf("\tLowBytes: %d", classFile->constantPool[i].info.Double.lowBytes);
                printf("\n\n\n");
                break;
            case CONSTANT_Long:
                printf("\tHighBytes: %d", classFile->constantPool[i].info.Long.highBytes);
                printf("\n");
                printf("\tLowBytes: %d", classFile->constantPool[i].info.Long.lowBytes);
                printf("\n\n");
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
            printf("\n\n\n");
        }
    } else {
        printf("\t     !! Esse classe nao possui Interfaces !!");
        printf("\n\n");
    }    
}

void printaFieldInfo(ClassFile* classFile) {    
    printf("FieldInfo: \n");
    printf("    AccessFlags: %d\n", classFile->fields->accessFlags);
    printf("    NameIndex: %d\n", classFile->fields->nameIndex);
    printf("    DescriptorIndex: %d\n", classFile->fields->descriptorIndex);
    printf("    AttributesCount: %d\n", classFile->fields->attributesCount);
    printf("    CvInfo: \n");
    printf("        AttributeNameIndex: %d\n", classFile->fields->attributes->attributeNameIndex);
    printf("        AttributeLength: %d\n", classFile->fields->attributes->attributeLength);
    printf("        ConstantValueIndex: %d\n", classFile->fields->attributes->constantValueIndex);
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

void printTopo(int option) {
    
    if(option){
        printf("\n\n\t%c", 201);
        for (int i = 0; i < 47; ++i) {
            printf("%c", 205);  
        }
        printf("%c\n", 187);
    } else {
        printf("\n\n\t%c", 218);
        for (int i = 0; i < 47; ++i) {
            printf("%c", 196);  
        }
        printf("%c\n", 191);
    }
}

void printBlank(int option) {
    if(option){
        printf("\t%c", 186);
        for (int i = 0; i < 47; ++i) {
            printf("%c", 32);  
        }
        printf("%c\n", 186);
    } else {
        printf("\t%c", 179);
        for (int i = 0; i < 47; ++i) {
            printf("%c", 32);  
        }
        printf("%c\n", 179);
    }
}

void printBase(int option) {
    if(option){
        printf("\t%c", 200);
        for (int i = 0; i < 47; ++i) {
            printf("%c", 205);  
        }
        printf("%c\n", 188);
    } else {
        printf("\t%c", 192);
        for (int i = 0; i < 47; ++i) {
            printf("%c", 196);  
        }
        printf("%c\n\n", 217);
    }   
}

void printLine(){
    printf("\t%c", 204);
    for (int i = 0; i < 47; ++i) {
        printf("%c", 205);  
    }
    printf("%c\n", 185);
}

void printSingleLine(){
    for (int i = 0; i < 34; ++i) {
        printf("%c", 196);  
    }
    printf("%c", 170);
}