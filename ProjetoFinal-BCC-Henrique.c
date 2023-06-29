#include <stdio.h>
#include <math.h>
#include <string.h>
#define TAM_GRADE 1000
#define TAM_PALAVRA 100 

typedef struct {
    int li, ci, lf, cf;
} Roi;

void carregarCacaPalavra(char[]);
void printVetorEmMatriz(char[]);
void opcoes();
Roi localizaPalavra(char[]);
Roi inicializaRoi();
Roi localizadores(Roi, char[], char[]);
Roi locEsqDir(Roi, char[], char[], int, int); 
Roi locDirEsq(Roi, char[], char[], int, int);
Roi locCimBai(Roi, char[], char[], int, int);
Roi locBaiCim(Roi, char[], char[], int, int);
Roi locDiagCEBD(Roi, char[], char[], int, int);
Roi locDiagCDBE(Roi, char[], char[], int, int);
Roi locDiagBECD(Roi, char[], char[], int, int);
Roi locDiagBDCE(Roi, char[], char[], int, int);


int main() {
    char grade[TAM_GRADE];
    carregarCacaPalavra(grade);
    printVetorEmMatriz(grade);
    localizaPalavra(grade);    
}

void carregarCacaPalavra(char grade[]) { 
    printf("\nInsira o vetor do caça-palavras: ");
    scanf("%s", grade);
    
    float tamM = sqrt(strlen(grade));
    
    if (tamM - (int)tamM != 0) {
        printf("\nCaça-palavras inválido, ele precisa ser uma matriz quadrada!\n");
        carregarCacaPalavra(grade);
    }
}

void printVetorEmMatriz(char grade[]) {
    int tamM, l, c;
    tamM = sqrt(strlen(grade));
    printf("\nCAÇA-PALAVRAS:\n");
    for (l=0; l<tamM; l++) {
        printf("\n\t");
        for (c=0; c<tamM; c++) {
            printf("%c  ", grade[(l*tamM+c)]); 
        }
    }
}

Roi localizaPalavra(char grade[]) {
    char palavra[TAM_PALAVRA];
    do {
        printf("\n\nInsira a palavra a ser pesquisada (0 para finalizar): ");
        scanf("%s", palavra);
        
        Roi posicao = inicializaRoi();
        
        posicao = localizadores(posicao, grade, palavra);
        printf("LI:%i CI:%i LF:%i CF:%i ", posicao.li, posicao.ci, posicao.lf, posicao.cf);
    } while (palavra[0] != '0');
    opcoes();
}

void opcoes() {
    int op;
    printf("\n\nOpções:\n\t1. Novo caça-palavras\n\t2. Sair\nEscolha: ");
    scanf("%i", &op);
    if (op == 1) {
        main();
    }
}

Roi inicializaRoi() { 
    Roi posicao;
    posicao.li = 0;
    posicao.ci = 0;
    posicao.lf = 0;
    posicao.cf = 0;
    
    return posicao;
}

int palavraEncontrada(Roi posicao){
    if ((posicao.li + posicao.lf + posicao.ci + posicao.cf) > 0)
        return 1;
    else
        return 0;
}

Roi localizadores(Roi posicao, char grade[], char palavra[]) {
    int tamM = sqrt(strlen(grade));
    int tamP = strlen(palavra);
    
    posicao = locEsqDir(posicao, grade, palavra, tamM, tamP);
    if (palavraEncontrada(posicao)) {
        return posicao;
    } else {
        posicao = locDirEsq(posicao, grade, palavra, tamM, tamP);
        if (palavraEncontrada(posicao)) {
            return posicao;
        } else {
            posicao = locCimBai(posicao, grade, palavra, tamM, tamP);
            if (palavraEncontrada(posicao)) {
                return posicao;
            } else {
                posicao = locBaiCim(posicao, grade, palavra, tamM, tamP);
                if (palavraEncontrada(posicao)) {
                    return posicao;
                } else {
                    posicao = locDiagCEBD(posicao, grade, palavra, tamM, tamP);
                    if (palavraEncontrada(posicao)) {
                        return posicao;
                    } else {
                        posicao = locDiagCDBE(posicao, grade, palavra, tamM, tamP);
                        if (palavraEncontrada(posicao)) {
                            return posicao;
                        } else {
                            posicao = locDiagBECD(posicao, grade, palavra, tamM, tamP);
                            if (palavraEncontrada(posicao)) {
                                return posicao;
                            } else {
                                posicao = locDiagBDCE(posicao, grade, palavra, tamM, tamP);
                                if (palavraEncontrada(posicao)) {
                                    return posicao;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    return posicao;
}

Roi locEsqDir(Roi posicao, char grade[], char palavra[], int tamM, int tamP) {
    int l, c, cont;
    
    for (l=0; l<tamM; l++) {
        for (c=0; c<tamM; c++) {
            cont = 0;
            while ((grade[l*tamM+c+cont] == palavra[cont]) && (cont<tamM) && ((c+cont) < tamM)) {
                cont++; 
                if (cont == tamP) {
                    posicao.li = l;
                    posicao.ci = c;
                    posicao.lf = l;
                    posicao.cf = c + tamP - 1;
                    
                    return posicao;
                }
            }
        }
    }
    return posicao;
}

Roi locDirEsq(Roi posicao, char grade[], char palavra[], int tamM, int tamP) {
    int l, c, cont;
    
    for (l=0; l<tamM; l++) {
        for (c=0; c<tamM; c++) {
            cont = 0;
            while ((grade[l*tamM+c-cont] == palavra[cont]) && (cont<tamM) && ((c-cont) >= 0) && ((c-cont) < tamM)) {
                cont++; 
                if (cont == tamP) {
                    posicao.li = l;
                    posicao.ci = c;
                    posicao.lf = l;
                    posicao.cf = c - tamP + 1;
                    
                    return posicao;
                }
            }
        }
    }
    return posicao;
}

Roi locCimBai(Roi posicao, char grade[], char palavra[], int tamM, int tamP) {
    int l, c, cont;
    
    for (l=0; l<tamM; l++) {
        for (c=0; c<tamM; c++) {
            cont = 0;
            while ((grade[(l+cont)*tamM+c] == palavra[cont]) && (cont<tamM) && ((l+cont) < tamM)) {
                cont++; 
                if (cont == tamP) {
                    posicao.li = l;
                    posicao.ci = c;
                    posicao.lf = l + tamP - 1;
                    posicao.cf = c;
                    
                    return posicao;
                }
            }
        }
    }
    return posicao;
}

Roi locBaiCim(Roi posicao, char grade[], char palavra[], int tamM, int tamP) {
    int l, c, cont;
    
    for (l=0; l<tamM; l++) {
        for (c=0; c<tamM; c++) {
            cont = 0;
            while ((grade[(l-cont)*tamM+c] == palavra[cont]) && (cont<tamM) && ((l-cont) < tamM)) {
                cont++; 
                if (cont == tamP) {
                    posicao.li = l;
                    posicao.ci = c;
                    posicao.lf = l - tamP + 1;
                    posicao.cf = c;
                    
                    return posicao;
                }
            }
        }
    }
    return posicao;
}

Roi locDiagCEBD(Roi posicao, char grade[], char palavra[], int tamM, int tamP) {
    int l, c, cont;
    
    for (l=0; l<tamM; l++) {
        for (c=0; c<tamM; c++) {
            cont = 0;
            while ((grade[(l+cont)*tamM+(c+cont)] == palavra[cont]) && (cont<tamM) && ((c+cont) < tamM) && ((l+cont) < tamM)) {
                cont++; 
                if (cont == tamP) {
                    posicao.li = l;
                    posicao.ci = c;
                    posicao.lf = l + tamP - 1;
                    posicao.cf = c + tamP - 1;
                    
                    return posicao;
                }
            }
        }
    }
    return posicao;
}

Roi locDiagCDBE(Roi posicao, char grade[], char palavra[], int tamM, int tamP) {
    int l, c, cont;
    
    for (l=0; l<tamM; l++) {
        for (c=0; c<tamM; c++) {
            cont = 0;
            while ((grade[(l+cont)*tamM+(c-cont)] == palavra[cont]) && (cont<tamM) && ((c-cont) < tamM) && ((l+cont) < tamM)) {
                cont++; 
                if (cont == tamP) {
                    posicao.li = l;
                    posicao.ci = c;
                    posicao.lf = l + tamP - 1;
                    posicao.cf = c - tamP + 1;
                    
                    return posicao;
                }
            }
        }
    }
    return posicao;
}

Roi locDiagBECD(Roi posicao, char grade[], char palavra[], int tamM, int tamP) {
    int l, c, cont;
    
    for (l=0; l<tamM; l++) {
        for (c=0; c<tamM; c++) {
            cont = 0;
            while ((grade[(l-cont)*tamM+(c+cont)] == palavra[cont]) && (cont<tamM) && ((c+cont) < tamM) && ((l-cont) < tamM)) {
                cont++; 
                if (cont == tamP) {
                    posicao.li = l;
                    posicao.ci = c;
                    posicao.lf = l - tamP + 1;
                    posicao.cf = c + tamP - 1;
                    
                    return posicao;
                }
            }
        }
    }
    return posicao;
}

Roi locDiagBDCE(Roi posicao, char grade[], char palavra[], int tamM, int tamP) {
    int l, c, cont;
    
    for (l=0; l<tamM; l++) {
        for (c=0; c<tamM; c++) {
            cont = 0;
            while ((grade[(l-cont)*tamM+(c-cont)] == palavra[cont]) && (cont<tamM) && ((c-cont) < tamM) && ((l-cont) < tamM)) {
                cont++; 
                if (cont == tamP) {
                    posicao.li = l;
                    posicao.ci = c;
                    posicao.lf = l - tamP + 1;
                    posicao.cf = c - tamP + 1;
                    
                    return posicao;
                }
            }
        }
    }
    return posicao;
}
