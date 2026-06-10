#ifndef ESTRUCTURA_H_INCLUDED
#define ESTRUCTURA_H_INCLUDED

struct structEstudiante
{
    char ci[10];
    char nombres[30];
    char apellidos[30];
};

struct structNotas
{
    char ci[10];
    char materia[30];
    int nota;
};

bool compararCadenas(char c1[], char c2[], int indice) {
    if (c1[indice] == '\0' && c2[indice] == '\0') {
        return true;
    } else if (c1[indice] != c2[indice]) {
        return false;
    } else {
        return compararCadenas(c1, c2, indice + 1);
    }
}

#endif



