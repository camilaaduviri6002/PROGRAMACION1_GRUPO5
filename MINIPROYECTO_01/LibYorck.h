#ifndef LIBYORCK_H_INCLUDED
#define LIBYORCK_H_INCLUDED

#include <iostream>
#include <fstream>
#include "ESTRUCTURA.h" 

using namespace std;
bool verificarEstudiante(char ciBuscado[]) {
    ifstream archivoLectura;
    structEstudiante estudianteLeido;
    bool encontrado;

    encontrado = false;
    archivoLectura.open("Estudiantes.bin", ios::binary);

    if (archivoLectura.is_open()) {
        while (!encontrado && archivoLectura.read((char*)&estudianteLeido, sizeof(structEstudiante))) {
            if (compararCadenas(estudianteLeido.ci, ciBuscado, 0)) {
                encontrado = true;
            }
        }
        archivoLectura.close();
    }
    return encontrado;
}

bool verificarNotaRecursiva(ifstream& archivo, char ciBuscado[], char materiaBuscada[]) {
    structNotas notaLeida;

    if (!archivo.read((char*)&notaLeida, sizeof(structNotas))) {
        return false;
    }
    if (compararCadenas(notaLeida.ci, ciBuscado, 0) && compararCadenas(notaLeida.materia, materiaBuscada, 0)) {
        return true;
    } else {
        return verificarNotaRecursiva(archivo, ciBuscado, materiaBuscada);
    }
}

bool verificarNotaUnica(char ciBuscado[], char materiaBuscada[]) {
    ifstream archivoLectura;
    bool existe;

    existe = false;
    archivoLectura.open("Notas.bin", ios::binary);

    if (archivoLectura.is_open()) {
        existe = verificarNotaRecursiva(archivoLectura, ciBuscado, materiaBuscada);
        archivoLectura.close();
    }
    return existe;
}

// REGISTRAR CALIFICACIÓN
void registrarCalificacion() {
    structNotas nuevaNota;
    ofstream archivoEscritura;
    bool existeEst;
    bool notaDuplicada;

    cout << "\n--- REGISTRO DE CALIFICACIONES ---" << endl;
    
    cout << "Ingrese el CI del estudiante: ";
    cin >> nuevaNota.ci;
    
    existeEst = verificarEstudiante(nuevaNota.ci);
    
    if (!existeEst) {
        cout << "Error: El estudiante con CI " << nuevaNota.ci << " no existe en Estudiantes.bin" << endl;
    } else {
        cin.ignore(); 
        
        cout << "Ingrese la materia: ";
        cin.getline(nuevaNota.materia, 30);
        
        notaDuplicada = verificarNotaUnica(nuevaNota.ci, nuevaNota.materia);
        
        if (notaDuplicada) {
            cout << "Error: El estudiante ya tiene una calificacion registrada en " << nuevaNota.materia << "." << endl;
        } else {
            cout << "Ingrese la nota (0 - 100): ";
            cin >> nuevaNota.nota;
            
            if (nuevaNota.nota < 0 || nuevaNota.nota > 100) {
                cout << "Error: La nota debe estar entre 0 y 100." << endl;
            } else {
                archivoEscritura.open("Notas.bin", ios::app | ios::binary);
                if (archivoEscritura.is_open()) {
                    archivoEscritura.write((char*)&nuevaNota, sizeof(structNotas));
                    archivoEscritura.close();
                    cout << "Calificacion registrada exitosamente." << endl;
                }
            }
        }
    }
}

// MODIFICAR DATOS PERSONALES
void modificarDatosPersonales() {
    char ciBuscado[10];
    bool existeEst;
    bool nuevoCiOcupado;
    structEstudiante datosNuevos;
    structEstudiante estudianteLeido;
    fstream archivoModificacion;
    bool modificado;
    int posicion;
	cin.ignore();
    cout << "\n--- MODIFICAR DATOS PERSONALES ---" << endl;
    cout << "Ingrese el CI del estudiante que desea modificar: ";
    cin >> ciBuscado;

    existeEst = verificarEstudiante(ciBuscado);

    if (!existeEst) {
        cout << "Error: No se encontro ningun estudiante con el CI ingresado." << endl;
    } else {
        cin.ignore();
        
        cout << "Ingrese el NUEVO CI: ";
        cin >> datosNuevos.ci;

        nuevoCiOcupado = false;
        if (!compararCadenas(ciBuscado, datosNuevos.ci, 0)) {
            nuevoCiOcupado = verificarEstudiante(datosNuevos.ci);
        }

        if (nuevoCiOcupado) {
            cout << "Error: El nuevo CI ingresado le pertenece a otro estudiante." << endl;
        } else {
            cin.ignore();
            
            cout << "Ingrese los NUEVOS nombres: ";
            cin.getline(datosNuevos.nombres, 30);
            cout << "Ingrese los NUEVOS apellidos: ";
            cin.getline(datosNuevos.apellidos, 30);

            archivoModificacion.open("Estudiantes.bin", ios::in | ios::out | ios::binary);
            modificado = false;

            if (archivoModificacion.is_open()) {
                while (!modificado && archivoModificacion.read((char*)&estudianteLeido, sizeof(structEstudiante))) {
                    if (compararCadenas(estudianteLeido.ci, ciBuscado, 0)) {
                        posicion = archivoModificacion.tellg();
                        posicion = posicion - sizeof(structEstudiante);
                        
                        archivoModificacion.seekp(posicion);
                        archivoModificacion.write((char*)&datosNuevos, sizeof(structEstudiante));
                        
                        modificado = true; 
                        cout << "Datos modificados correctamente." << endl;
                    }
                }
                archivoModificacion.close();
            }
        }
    }
}

#endif 
