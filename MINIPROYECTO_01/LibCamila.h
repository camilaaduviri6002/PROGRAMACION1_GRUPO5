#include <iostream>
#include <fstream>
#include <cstring>
#include "cami.h"

struct structEstudiante {
    char ci[10];       
    char nombres[30];
    char apellidos[30];
};
 
struct structNotas {
    char ci[10];        
    char materia[30];   
    int  nota;         
};
 

void reporteConsolidado() {
    cout << "\n--- REPORTE CONSOLIDADO DE CALIFICACIONES ---" << endl;
 
    ifstream archEst("Estudiantes.bin", ios::binary);
    if (!archEst.is_open()) {
        cout << "ERROR: No se pudo abrir Estudiantes.bin" << endl;
        return;
    }
 
    structEstudiante est;
    bool hayEstudiantes = false;
  
    while (archEst.read(reinterpret_cast<char*>(&est), sizeof(est))) {
        hayEstudiantes = true;

        cout << "\n+------------------------------------------+" << endl;
        cout << "| CI       : " << est.ci                       << endl;
        cout << "| Nombres  : " << est.nombres                  << endl;
        cout << "| Apellidos: " << est.apellidos                << endl;
        cout << "+--------------------------------+---------+" << endl;
        cout << "| MATERIA                        | NOTA    |" << endl;
        cout << "+--------------------------------+---------+" << endl;

        ifstream archNotas("Notas.bin", ios::binary);
        structNotas n;
        bool tieneNotas = false;
 
        if (archNotas.is_open()) {
            while (archNotas.read(reinterpret_cast<char*>(&n), sizeof(n))) {
                if (strcmp(n.ci, est.ci) == 0) {
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

void salir() {
    cout << "\nSaliendo del sistema. Hasta luego." << endl;
}
