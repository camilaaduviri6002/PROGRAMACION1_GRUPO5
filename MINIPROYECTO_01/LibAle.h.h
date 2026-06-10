#ifndef LIBALE_H
#define LIBALE_H

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

//----------------------------------------
//Estructura (Estudiante y Nota)

struct Estudiante
{
    char ci[10];
    char nombres[30];
    char apellidos[30];
};

struct Nota
{
    char ci[10];
    char materia[30];
    int nota;
};

//-------------------------------------------------------------
//FUNCION BUSCAR CI

bool buscarCI(const char ci[])
{
    ifstream archivo("Estudiantes.bin", ios::binary);

    Estudiante est;

    while (archivo.read((char*)&est, sizeof(Estudiante)))
    {
        if (strcmp(est.ci, ci) == 0)
        {
            archivo.close();
            return true;
        }
    }

    archivo.close();

    return false;
}

//PARTE 1---------------------------------------------------------------
//ADICIONAR ESTUDIANTE

void agregarEstudiante()
{
    Estudiante e;

    cout << "CI: ";
    cin.getline(e.ci, 10);

    if (buscarCI(e.ci))
    {
        cout << "El estudiantes ya está registrado, intente nuevamente ";
        return;
    }

    cout << "Nombres: ";
    cin.getline(e.nombres, 30);

    cout << "Apellidos: ";
    cin.getline(e.apellidos, 30);

    ofstream archivo("Estudiantes.bin",ios::binary | ios::app);

    archivo.write((char*)&e, sizeof(Estudiante));

    archivo.close();

    cout << "Estudiante registrado"<<endl;
}

//PARTE 4-------------------------------------------------------
//MODIFICACION DE NOTAS

void modificarNota()
{
    char ci[10];
    char materia[30];

    cout << "CI del estudiante: ";
    cin.getline(ci, 10);

    if (!buscarCI(ci))
    {
        cout << "El estudiante no existe." << endl;
        return;
    }

    cout << "Materia: ";
    cin.getline(materia, 30);

    fstream archivo("Notas.bin", ios::binary | ios::in | ios::out);

    if (!archivo)
    {
        cout << "No existe el archivo Notas.bin" << endl;
        return;
    }

    Nota reg;
    bool encontrado = false;

    while (archivo.read((char*)&reg, sizeof(Nota)))
    {
        if (strcmp(reg.ci, ci) == 0 &&
            strcmp(reg.materia, materia) == 0)
        {
            encontrado = true;

            cout << "Nota actual: " << reg.nota << endl;

            cout << "Nueva nota: ";
            cin >> reg.nota;
            cin.ignore();

            archivo.seekp(-sizeof(Nota), ios::cur);

            archivo.write((char*)&reg, sizeof(Nota));

            cout << "Nota modificada correctamente." << endl;

            break;
        }
    }

    if (!encontrado)
    {
        cout << "La materia no esta registrada para este estudiante." << endl;
    }

    archivo.close();
}
#endif
