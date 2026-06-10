#ifndef LIBALE_H_INCLUDED
#define LIBALE_H_INCLUDED

#include "ESTRUCTURA.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;


// BUSCAR CI
bool buscarCI(const char ci[])
{
    ifstream archivo("Estudiantes.bin", ios::binary);

    if (!archivo)
    {
        return false;
    }

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


// ADICIONAR ESTUDIANTE
void adicionarEstudiante()
{
    structEstudiante e;

    cin.ignore();

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


// MODIFICAR NOTA
void modificarNotas()
{
    structNotas datosBuscados;

    cin.ignore();

    cout << "CI del estudiante: ";
    cin.getline(datosBuscados.ci, 10);

    if (!buscarCI(datosBuscados.ci))
    {
        cout << "El estudiante no existe." << endl;
        return;
    }

    cout << "Materia: ";
    cin.getline(datosBuscados.materia, 30);

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
        if (strcmp(reg.ci, datosBuscados.ci) == 0 &&
            strcmp(reg.materia, datosBuscados.materia) == 0)
        {
            encontrado = true;

            cout << "Nota actual: " << reg.nota << endl;

            do
            {
                cout << "Nueva nota (0-100): ";
                cin >> reg.nota;
            }
            while (reg.nota < 0 || reg.nota > 100);

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
