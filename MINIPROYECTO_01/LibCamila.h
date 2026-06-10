#ifndef LIBCAMILA_H_INCLUDED
#define LIBCAMILA_H_INCLUDED

#include <iostream>
#include <fstream>
#include "ESTRUCTURA.h" 

using namespace std;

void reporteConsolidado() {
    ifstream archEst;
    ifstream archNotas;
    structEstudiante est;
    structNotas n;
    bool hayEstudiantes;
    bool tieneNotas;

    hayEstudiantes = false;
    
    cout << "\n--- REPORTE CONSOLIDADO DE CALIFICACIONES ---" << endl;
    
    archEst.open("Estudiantes.bin", ios::binary);

    if (!archEst.is_open()) {
        cout << "ERROR: No se pudo abrir Estudiantes.bin" << endl;
    } else {
        while (archEst.read((char*)&est, sizeof(structEstudiante))) {
            hayEstudiantes = true;

            cout << "\n+------------------------------------------+" << endl;
            cout << "| CI       : " << est.ci                       << endl;
            cout << "| Nombres  : " << est.nombres                  << endl;
            cout << "| Apellidos: " << est.apellidos                << endl;
            cout << "+--------------------------------+---------+" << endl;
            cout << "| MATERIA                        | NOTA    |" << endl;
            cout << "+--------------------------------+---------+" << endl;

            tieneNotas = false;
            archNotas.open("Notas.bin", ios::binary);
            
            if (archNotas.is_open()) {
                while (archNotas.read((char*)&n, sizeof(structNotas))) {
                    
                   
                    if (compararCadenas(n.ci, est.ci, 0)) {
                        tieneNotas = true;
                        
                        cout << "| ";
                        cout.width(30); cout << left  << n.materia;
                        cout << " | ";
                        cout.width(7);  cout << right << n.nota;
                        cout << " |" << endl;
                    }
                }
                archNotas.close();
            }

            if (!tieneNotas) {
                cout << "| (Sin calificaciones registradas)         |" << endl;
            }

            cout << "+--------------------------------+---------+" << endl;
        }
        
        archEst.close();

        if (!hayEstudiantes) {
            cout << "No hay estudiantes registrados en el sistema." << endl;
        }
    }
}

#endif
