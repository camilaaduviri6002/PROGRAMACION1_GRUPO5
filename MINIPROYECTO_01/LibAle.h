#ifndef LIBALE_H_INCLUDED
#define LIBALE_H_INCLUDED

#include "Estructuras.h"
#include <iostream>
#include <fstream>
#include <cstring>


using namespace std;

bool buscarCI(const char ci[])
{
    ifstream archivo("Estudiantes.bin", ios::binary);

    structEstudiante est;

    while (archivo.read((char*)&est, sizeof(structEstudiante)))
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
//ADICIONAR ESTUDIANTE
void agregarEstudiante()
{
    structEstudiante e;

    cout << "CI: ";
    cin.getline(e.ci, 10);

    if (buscarCI(e.ci))
    {
        cout << "El estudiante ya esta registrado." << endl;
        return;
    }

    cout << "Nombres: ";
    cin.getline(e.nombres, 30);

    cout << "Apellidos: ";
    cin.getline(e.apellidos, 30);

    ofstream archivo("Estudiantes.bin",
                     ios::binary | ios::app);

    archivo.write((char*)&e, sizeof(structEstudiante));

    archivo.close();

    cout << "Estudiante registrado correctamente." << endl;
}

//MODIFICAR NOTA
void modificarNota()
{
    char ci[10];
    char materia[30];

    cout << "CI del estudiante: ";
    cin.getline(ci,10);

    if (!buscarCI(ci))
    {
        cout << "El estudiante no existe." << endl;
        return;
    }

    cout << "Materia: ";
    cin.getline(materia,30);

    fstream archivo("Notas.bin",
                    ios::binary | ios::in | ios::out);

    if (!archivo)
    {
        cout << "No existe el archivo Notas.bin." << endl;
        return;
    }

    structNotas reg;
    bool encontrado = false;

    while (archivo.read((char*)&reg, sizeof(structNotas)))
    {
        if (strcmp(reg.ci, ci) == 0 &&
            strcmp(reg.materia, materia) == 0)
        {
            encontrado = true;

            cout << "Nota actual: " << reg.nota << endl;

            cout << "Nueva nota: ";
            cin >> reg.nota;
            cin.ignore();

            archivo.seekp(-sizeof(structNotas), ios::cur);

            archivo.write((char*)&reg, sizeof(structNotas));

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

