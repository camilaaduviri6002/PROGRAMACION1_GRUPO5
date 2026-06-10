#include <iostream>
#include "LibAle.h" 
#include "LibYorck.h"       
#include "LibCamila.h" 

using namespace std;

// Materia: Programación I, Paralelo 4
// Grupo: 5
// Integrantes: Camila Aduviri Quisbert, Yorck Legolas Quiroz Villalobos, Alejandra Briggette Romero Aro
// Fecha creación: 27-05-2026
// Nombre del miniproyecto: EJERCICIO 1. Sistema de Registro Académico Consolidado 

int main() {
    int opcion;
    bool salir = false;
    while (!salir) {
        cout << "--- MENU PRINCIPAL ---" << endl;
        cout << "1. Adicionar Estudiante" << endl;
        cout << "2. Registrar Calificacion" << endl;
        cout << "3. Reporte Consolidado" << endl;
        cout << "4. Modificar Notas" << endl;
        cout << "5. Modificar Datos Personales" << endl;
        cout << "6. Salir" << endl;
        cout << "Elija una opcion: ";
        cin >> opcion;
      
        switch (opcion) {
            case 1:
                adicionarEstudiante(); 
                break;
            case 2:
                registrarCalificacion(); 
                break;
            case 3:
                reporteConsolidado(); 
                break;
            case 4:
                modificarNotas();
                break;
            case 5:
                modificarDatosPersonales();
                break;
            case 6:
                salir = true;
                break;
        }
    }
    return 0;
}
