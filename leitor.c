//
//  leitor.c
//  LeitorExibidor
//
//  Created on 26/05/17.
//  Copyright © 2017 GrupoSB. All rights reserved.
//

#include "leitor.h"
#include "exibidor.h"

#include <stdlib.h>
#include <string.h>

ClassFile* leitorClasse(char* caminhoClasse) {

    FILE* fp;
    fp = fopen(caminhoClasse, "rb");
    
    if(fp == NULL) {
        printf("Erro ao abrir o arquivo (nao encontrado) ! \n");
        return 0;
    }

    ClassFile* classFile = NULL;
    classFile = (ClassFile*) calloc(sizeof(ClassFile), 1);
    
    if(classFile == NULL) {
        printf("Erro ao alocar espaço para o arquivo ! \n");
    }

    leClassFile(fp, classFile);
    fclose(fp);
    return classFile;
}

void leClassFile(FILE* fp, ClassFile* classFile) {
    if(cafeBabeValido(fp, classFile)) {

        classFile->minorVersion = le2Bytes(fp);

        classFile->majorVersion = le2Bytes(fp);
        classFile->constantPoolCount = le2Bytes(fp);
        leConstantPool(fp, classFile);
        
        classFile->accessFlags = le2Bytes(fp);
        classFile->thisClass = le2Bytes(fp);
        classFile->superClass = le2Bytes(fp);
        classFile->interfacesCount = le2Bytes(fp);
        leInterfaceInfo(fp, classFile);       

        classFile->fieldsCount = le2Bytes(fp);
        leFieldInfo(fp, classFile);     
        
        classFile->methodsCount = le2Bytes(fp);
        leMethodInfo(fp, classFile);       
        
        classFile->attributesCount = le2Bytes(fp);
        leAttributeInfo(fp,classFile);
        
    } else {
        printf("Arquivo .class invalido !! \n");
        exit(0);
    }
}

int cafeBabeValido(FILE* fp, ClassFile* classFile) {
    classFile->magic = le4Bytes(fp);
    return classFile->magic == 0xCAFEBABE;
}

void leConstantPool(FILE* fp, ClassFile* classFile) {
    classFile->constantPool = (CpInfo*) malloc((classFile->constantPoolCount-1) * sizeof(CpInfo));
    CpInfo* cpInfo;
    
    int i = 0;
    for(cpInfo = classFile->constantPool; i < (classFile->constantPoolCount-1); cpInfo++){
        cpInfo->tag = le1Byte(fp);
        switch(cpInfo->tag) {
            case CONSTANT_Class:
                cpInfo->info.Class.nameIndex = le2Bytes(fp);
                break;
            case CONSTANT_Fieldref:
                cpInfo->info.Fieldref.classIndex = le2Bytes(fp);
                cpInfo->info.Fieldref.nameAndTypeIndex = le2Bytes(fp);
                break;
            case CONSTANT_NameAndType:
                cpInfo->info.NameAndType.nameIndex = le2Bytes(fp);
                cpInfo->info.NameAndType.descriptorIndex = le2Bytes(fp);
                break;
            case CONSTANT_Utf8:
                cpInfo->info.Utf8.length = le2Bytes(fp);
                cpInfo->info.Utf8.bytes = (uint8_t*) calloc ((cpInfo->info.Utf8.length) + 1 ,sizeof(uint8_t));
                fread(cpInfo->info.Utf8.bytes,1,cpInfo->info.Utf8.length,fp);
                cpInfo->info.Utf8.bytes[cpInfo->info.Utf8.length] = '\0';
                break;
            case CONSTANT_Methodref:
                cpInfo->info.Methodref.classIndex = le2Bytes(fp);
                cpInfo->info.Methodref.nameAndTypeIndex = le2Bytes(fp);
                break;
            case CONSTANT_InterfaceMethodref:
                cpInfo->info.InterfaceMethodref.classIndex = le2Bytes(fp);
                cpInfo->info.InterfaceMethodref.nameAndTypeIndex = le2Bytes(fp);
                break;
            case CONSTANT_String:
                cpInfo->info.String.stringIndex = le2Bytes(fp);
                break;
            case CONSTANT_Integer:
                cpInfo->info.Integer.bytes = le4Bytes(fp);
                break;
            case CONSTANT_Float:
                cpInfo->info.Float.bytes = le4Bytes(fp);
                break;
            case CONSTANT_Double:
                cpInfo->info.Double.highBytes = le4Bytes(fp);
                cpInfo->info.Double.lowBytes = le4Bytes(fp);
                cpInfo++;
                i++;
                break;
            case CONSTANT_Long:
                cpInfo->info.Long.highBytes = le4Bytes(fp);
                cpInfo->info.Long.lowBytes = le4Bytes(fp);
                cpInfo++;
                i++;
                break;
            default:
                break;
        }
        i++;
    }
}

void leInterfaceInfo(FILE* fp, ClassFile* classFile) {
    if(classFile->interfacesCount == 0) {
        return;
    } else {
        classFile->interfaces = (uint16_t*) malloc((classFile->interfacesCount) * sizeof(uint16_t));
        for (int i = 0; i < classFile->interfacesCount; i++) {
            classFile->interfaces[i] = le2Bytes(fp);
        }
    }
}

void leFieldInfo(FILE* fp, ClassFile* classFile) {
    if(classFile->fieldsCount == 0) {
        return;
    } else {
        classFile->fields = (FieldInfo*) malloc(classFile->fieldsCount * sizeof(FieldInfo));
        
        for (int i = 0; i < classFile->fieldsCount; i++) {
            classFile->fields[i].accessFlags = le2Bytes(fp);
            classFile->fields[i].nameIndex = le2Bytes(fp);
            classFile->fields[i].descriptorIndex = le2Bytes(fp);
            classFile->fields[i].attributesCount = le2Bytes(fp);
            classFile->fields[i].attributes = (CvInfo*) malloc(classFile->fields[i].attributesCount * sizeof(CvInfo));
            
            for (int j = 0; j < classFile->fields[i].attributesCount; j++) {
                classFile->fields[i].attributes->attributeNameIndex = le2Bytes(fp);
                classFile->fields[i].attributes->attributeLength = le4Bytes(fp);
                classFile->fields[i].attributes->constantValueIndex = le2Bytes(fp);
            }
        }
    }
}

void leMethodInfo(FILE* fp, ClassFile* classFile) {
    uint16_t nameIndex;
    uint32_t attributesCount;
    
    if(classFile->methodsCount == 0) {
        return;
    } else {
        classFile->methods = (MethodInfo*) malloc(classFile->methodsCount * sizeof(MethodInfo));
        MethodInfo* methodInfo = classFile->methods;
        for(int i = 0; i < classFile->methodsCount; methodInfo++){
            methodInfo->accessFlags = le2Bytes(fp);
            methodInfo->nameIndex = le2Bytes(fp);
            methodInfo->descriptorIndex = le2Bytes(fp);
            methodInfo->attributesCount = le2Bytes(fp);

            for(int j = 0; j < methodInfo->attributesCount; j++) {
                
                nameIndex = le2Bytes(fp);
                
                attributesCount = le4Bytes(fp);
                
                
                if (strcmp( (char*) classFile->constantPool[nameIndex - 1].info.Utf8.bytes, "Code") == 0) {
                    methodInfo->cdAtrb = (CodeAttribute*) malloc(sizeof(CodeAttribute));
                    leCode(fp, &(methodInfo->cdAtrb), nameIndex, attributesCount);
                } else if (strcmp( (char*) classFile->constantPool[nameIndex - 1].info.Utf8.bytes, "Exceptions") == 0) {
                    methodInfo->excAtrb = (ExceptionsAttribute*) malloc(sizeof(ExceptionsAttribute));
                    leExc(fp, &(methodInfo->excAtrb), nameIndex, attributesCount);
                }
            }
            i++;
        }
        
    }
}

void leAttributeInfo(FILE* fp, ClassFile* classFile) {
    if(classFile->attributesCount == 0) {
        return;
    } else {
        classFile->attributes = (AttributeInfo*) malloc(classFile->attributesCount * sizeof(AttributeInfo));
        AttributeInfo* attributeInfo = classFile->attributes;

        for(int i = 0; i < classFile->attributesCount; attributeInfo++){
            attributeInfo->attributeNameIndex = le2Bytes(fp);
            attributeInfo->attributeLength = le4Bytes(fp);
            attributeInfo->info = (uint8_t*) malloc((attributeInfo->attributeLength) * sizeof(uint8_t));


            for(uint32_t j = 0; j < attributeInfo->attributeLength; j++){
                fread(&attributeInfo->info[j], 1, 1, fp);
            }
            i++;
        }
    }
    
}

void leExc(FILE* fp, ExceptionsAttribute** excAtrb, uint16_t nameIndex, uint32_t attributesCount) {
    (*excAtrb)->attributeNameIndex = nameIndex;
    (*excAtrb)->attributeLength = attributesCount;
    (*excAtrb)->numberExceptions = le2Bytes(fp);
    (*excAtrb)->exceptionIndexTable = (uint16_t*) malloc((*excAtrb)->numberExceptions * sizeof(ExceptionTable));
    for (int k = 0; k < (*excAtrb)->numberExceptions; k++) {
        (*excAtrb)->exceptionIndexTable[k] = le2Bytes(fp);
    }
}

void leCode(FILE* fp, CodeAttribute** cdAtrb, uint16_t nameIndex, uint32_t attributesCount) {
    int posicaoInicial = (int) ftell(fp);
    
    (*cdAtrb)->attributeNameIndex = nameIndex;
    (*cdAtrb)->attributeLength = attributesCount;
    (*cdAtrb)->maxStack = le2Bytes(fp);                     // Ta no MISC
    (*cdAtrb)->maxLocals = le2Bytes(fp);                    // Ta no MISC
    (*cdAtrb)->codeLength = le4Bytes(fp);
    
    salvaInstrucoes(cdAtrb, fp);

    (*cdAtrb)->exceptionTableLength = le2Bytes(fp);
    (*cdAtrb)->exceptionTable = (ExceptionTable*) malloc((*cdAtrb)->exceptionTableLength * sizeof(ExceptionTable));
    for (int k = 0; k < (*cdAtrb)->exceptionTableLength; k++) {
        (*cdAtrb)->exceptionTable[k].startPc = le2Bytes(fp);
        (*cdAtrb)->exceptionTable[k].endPc = le2Bytes(fp);
        (*cdAtrb)->exceptionTable[k].catchType = le2Bytes(fp);
    }
    
    (*cdAtrb)->attributesCount = le2Bytes(fp);
    (*cdAtrb)->attributes = (AttributeInfo*) malloc ((*cdAtrb)->attributesCount * sizeof(AttributeInfo));
    
    while (ftell(fp) - posicaoInicial < (int32_t)((*cdAtrb)->attributeLength)) {
        le1Byte(fp);
    }
}

void salvaInstrucoes(CodeAttribute** cdAtrb, FILE* file){
    int opcode, posReferencia; 
    int bytesPreench, offsets;
    uint32_t defaultV, low, high, npairs; 

    // obtem decodificador de instrucoes 
    Decodificador dec[NUM_INSTRUCAO];
    inicializaDecodificador(dec); 

    // leitura do bytecode relacionado a instrucoes do metodo 
    // aloca espaco conveniente
    (*cdAtrb)->code = (uint8_t*) malloc((*cdAtrb)->codeLength * \
            sizeof(uint8_t));

    // poe valor no espacos corretos
    // incrementamos k conforme formos passando no loop
    for(uint32_t k = 0; k < (*cdAtrb)->codeLength; ) 
    {    
        // le opcode da instrucao atual
        fread(&((*cdAtrb)->code[k]), 1, 1, file);
        
        // pega opcode da instrucao
        opcode = (*cdAtrb)->code[k];
        k++; 

        if (opcode == TABLESWITCH)
        {
            // a posicao de referencia eh o label numerico associado a tableswitch 
            // k - 1 pois ja incrementamos o k para a proxima instrucao 
            posReferencia = k - 1;

            // pega bytes de preenchimento 
            //bytesPreench = k % 4;  
            bytesPreench = (4 - (k % 4)) % 4;  
            for (int l = 0; l < bytesPreench; l++)
            {
                k++; 
                fread(&((*cdAtrb)->code[k]), 1, 1, file);
            }

            // pega bytes do target default
            defaultV = 0;
            for (int l = 0; l < 4; l++)
            {
                fread(&((*cdAtrb)->code[k]), 1, 1, file);
                defaultV = (defaultV << 8) + (*cdAtrb)->code[k];   
                k++; 
            }       

            // pega bytes low
            low = 0;
            for (int l = 0; l < 4; l++)
            {
                fread(&((*cdAtrb)->code[k]), 1, 1, file);
                low = (low << 8) + (*cdAtrb)->code[k];   
                k++; 
            }       

            // pega bytes high 
            high = 0;
            for (int l = 0; l < 4; l++)
            {
                fread(&((*cdAtrb)->code[k]), 1, 1, file);
                high = (high << 8) + (*cdAtrb)->code[k];   
                k++; 
            }       
            
            // pega bytes de offset 
            offsets = 1 + high - low;
            for (int l = 0; l < offsets; l++)
            {
                // pega valor do offset atual 
                for (int i = 0; i < 4; i++)
                {
                    fread(&((*cdAtrb)->code[k]), 1, 1, file);
                    k++; 
                }

            } 
        }

        else if (opcode == LOOKUPSWITCH)
        {
            // a posicao de referencia eh o label numerico associado a tableswitch 
            // k - 1 pois ja incrementamos o k para a proxima instrucao 
            posReferencia = k - 1;

            // pega bytes de preenchimento - nao salva em nenhum lugar
            //bytesPreench = k % 4;  
            bytesPreench = (4 - (k % 4)) % 4;  
            for (int l = 0; l < bytesPreench; l++)
            {
                k++; 
                fread(&((*cdAtrb)->code[k]), 1, 1, file);
            }

            // pega bytes do target default
            defaultV = 0;
            for (int l = 0; l < 4; l++)
            {
                fread(&((*cdAtrb)->code[k]), 1, 1, file);
                defaultV = (defaultV << 8) + (*cdAtrb)->code[k];   
                k++; 
            }       

            // pega npairs
            npairs = 0;
            for (int l = 0; l < 4; l++)
            {
                fread(&((*cdAtrb)->code[k]), 1, 1, file);
                npairs = (npairs << 8) + (*cdAtrb)->code[k];   
                k++; 
            }       

            // pega npairs 
            for (uint32_t l = 0; l < npairs; l++)
            {
                // pega valor do match atual 
                for (int i = 0; i < 4; i++)
                {
                    fread(&((*cdAtrb)->code[k]), 1, 1, file);
                    k++; 
                }

                // pega valor do offset 
                for (int i = 0; i < 4; i++)
                {
                    fread(&((*cdAtrb)->code[k]), 1, 1, file);
                    k++; 
                }

            } 

        }

        else if (opcode == WIDE)
        {

            // pega opcode que segue
            fread(&((*cdAtrb)->code[k]), 1, 1, file);
            opcode = (*cdAtrb)->code[k];
            k++; 

            // se o opcode for um iload, fload, ...
            if (opcode == ILOAD || opcode == FLOAD || opcode == ALOAD || opcode == LLOAD || \
                    opcode == DLOAD || opcode == ISTORE || opcode == FSTORE || opcode == ASTORE || \
                    opcode == LSTORE || opcode == DSTORE || opcode == RET)
            {
                // pega index byte1 
                fread(&((*cdAtrb)->code[k]), 1, 1, file);
                k++; 

                // pega index byte2
                fread(&((*cdAtrb)->code[k]), 1, 1, file);
                k++; 
            }

            // se for um iinc 
            else if (opcode == IINC)
            {

                // pega indexbyte1
                fread(&((*cdAtrb)->code[k]), 1, 1, file);
                k++; 

                // pega indexbyte2
                fread(&((*cdAtrb)->code[k]), 1, 1, file);
                k++; 

                // pega constbyte1
                fread(&((*cdAtrb)->code[k]), 1, 1, file);
                k++; 

                // pega constbyte2
                fread(&((*cdAtrb)->code[k]), 1, 1, file);
                k++; 

            }

            // senao
            else
            { 
                // arquivo .class corrompido! 
                printf("arquivo .class invalido na instrucao wide");
                exit(1);
            }
        }

        else
        {

            // obtem quantos operandos a instrucao tem e vai lendo operandos
            int num_bytes = dec[opcode].bytes;
            for (int l = 0; l < num_bytes; l++)
            {

                // pega operando 
                fread(&((*cdAtrb)->code[k]), 1, 1, file);
                // atualiza valor de k 
                k++;
            }

        }
    }
}



uint8_t le1Byte(FILE* fp) {
    uint8_t retorno = getc(fp);
    //uint8_t retorno;
    //fread(&retorno, sizeof(uint8_t), 1, fp); 
    
    return retorno;
}

uint16_t le2Bytes(FILE* fp) {
    uint16_t retorno = getc(fp);
    retorno = (retorno << 8) | (getc(fp));
    
    //uint16_t retorno;
    //fread(&retorno, sizeof(uint16_t), 1, fp);
    return retorno;
}

uint32_t le4Bytes(FILE* fp) {
    uint32_t retorno = getc(fp);
    retorno = (retorno << 8) | (getc(fp));
    retorno = (retorno << 8) | (getc(fp));
    retorno = (retorno << 8) | (getc(fp));
    
    //uint32_t retorno;
    //fread(&retorno, sizeof(uint32_t), 1, fp);   /* TRETA COM LITTLE ENDIAN */
    return retorno;
}

