#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <cmath>
#include <algorithm>
#include <string>
using namespace std;

struct Apto {
    int nro;
    string modalidad;
    string dni;
    string nombres;
    string resultado;
};
void bubbleSortDNI(vector<Apto>& datos);
void selectionSortDNI(vector<Apto>& datos);
void insertionSortDNI(vector<Apto>& datos);
void quickSortDNI(vector<Apto>& datos, int inicio, int fin);
void mergeSortDNI(vector<Apto>& datos, int izquierda, int derecha);
void radixSortDNI(vector<Apto>& datos);
int busquedaLineal(vector<Apto>& datos, string objetivo);
int busquedaBinaria(vector<Apto>& datos, string objetivo);
int jumpSearch(vector<Apto>& datos, string objetivo);
int interpolationSearch(vector<Apto>& datos, string objetivo);
int exponentialSearch(vector<Apto>& datos, string objetivo);
//-------------------------------------------------------------

int main() {

    vector<Apto> datos;
    ifstream archivo("datos_apto.csv");
    string linea;
    // Saltar cabecera
    getline(archivo, linea);
    while (getline(archivo, linea)) {
        if (linea.empty()) {
            continue;
        }
        stringstream ss(linea);
        string campo;
        Apto a;
        getline(ss, campo, ';');
        if (campo.empty()) {
            continue;
        }
        a.nro = stoi(campo);
        getline(ss, a.modalidad, ';');
        getline(ss, a.dni, ';');
        getline(ss, a.nombres, ';');
        getline(ss, a.resultado, ';');
        datos.push_back(a);
    }
    archivo.close();
    cout << "Datos cargados correctamente" << endl;

    // CARGAR DNIs DE BUSQUEDA
    vector<string> listaBusquedas;

    ifstream archivoBusquedas("muestras_dni_500.csv");

    string lineaa;

    // saltar cabecera
    getline(archivoBusquedas, lineaa);

    while (getline(archivoBusquedas, lineaa)) {

        if (!lineaa.empty()) {
            listaBusquedas.push_back(lineaa);
        }
    }

    archivoBusquedas.close();
    cout << "DNIs de busqueda cargados correctamente" << endl;
   radixSortDNI(datos);
//------------------------------------
//            MEDIR TIEMPO
//--------------------------------------

auto inicio = chrono::high_resolution_clock::now();

//-------------------------------------------------


for (string dniBuscar : listaBusquedas) {
    exponentialSearch(datos, dniBuscar);
}


//-----------------------------------------

// FIN MEDICIÓN
// =======================

auto fin = chrono::high_resolution_clock::now();

// =======================
// CÁLCULOS DE TIEMPO
// =======================

auto ms = chrono::duration_cast<chrono::milliseconds>(fin - inicio);
auto us = chrono::duration_cast<chrono::microseconds>(fin - inicio);
auto s  = chrono::duration_cast<chrono::seconds>(fin - inicio);

// =======================
// RESULTADO
// =======================

cout << "==============================" << endl;
cout << "TIEMPO DE EJECUCION" << endl;
cout << "ALGORITMO : BUSQUEDA interpolationSearch POR DNI" << endl;
cout << "Datos ORDENADO" << endl;
cout << "==============================" << endl;

cout << "Milisegundos : " << ms.count() << " ms" << endl;
cout << "Microsegundos: " << us.count() << " us" << endl;
cout << "Segundos     : " << s.count() << " s" << endl;

cout << "==============================" << endl;






/*
cout << "==============================" << endl;
cout << "TIEMPO DE EJECUCION" << endl;
cout << "Algorimo : BUSQUEDA LINEAL POR DNI " << endl;
cout << "==============================" << endl;

cout << "Milisegundos : " << ms.count() << " ms" << endl;
cout << "Microsegundos: " << us.count() << " us" << endl;
cout << "Segundos     : " << s.count() << " s" << endl;
d
cout << "==============================" << endl;
*/
    return 0;
}
//-------------------------------------------------
//                Algoritmos de ORDENAMIENTO
//------------------------------------------------

// BUBBLE SORT POR DNI
void bubbleSortDNI(vector<Apto>& datos) {

    int n = datos.size();

    for (int i = 0; i < n - 1; i++) {

        for (int j = 0; j < n - i - 1; j++) {

            if (datos[j].dni > datos[j + 1].dni) {

                swap(datos[j], datos[j + 1]);
            }
        }
    }
}

// SELECTION SORT POR DNI
void selectionSortDNI(vector<Apto>& datos) {

    int n = datos.size();

    for (int i = 0; i < n - 1; i++) {

        int min = i;

        for (int j = i + 1; j < n; j++) {

            if (datos[j].dni < datos[min].dni) {
                min = j;
            }
        }

        swap(datos[i], datos[min]);
    }
}

// INSERTION SORT POR DNI
void insertionSortDNI(vector<Apto>& datos) {

    int n = datos.size();

    for (int i = 1; i < n; i++) {

        Apto key = datos[i];
        int j = i - 1;

        while (j >= 0 && datos[j].dni > key.dni) {

            datos[j + 1] = datos[j];
            j--;
        }

        datos[j + 1] = key;
    }
}

// QUICK SORT POR DNI
int particionDNI(vector<Apto>& datos, int inicio, int fin) {

    string pivote = datos[fin].dni;

    int i = inicio - 1;

    for (int j = inicio; j < fin; j++) {

        if (datos[j].dni < pivote) {

            i++;
            swap(datos[i], datos[j]);
        }
    }

    swap(datos[i + 1], datos[fin]);

    return i + 1;
}

void quickSortDNI(vector<Apto>& datos, int inicio, int fin) {

    if (inicio < fin) {

        int pi = particionDNI(datos, inicio, fin);

        quickSortDNI(datos, inicio, pi - 1);

        quickSortDNI(datos, pi + 1, fin);
    }
}

// MERGE SORT POR DNI
void mergeDNI(vector<Apto>& datos, int izquierda, int medio, int derecha) {

    int n1 = medio - izquierda + 1;
    int n2 = derecha - medio;

    vector<Apto> L(n1);
    vector<Apto> R(n2);

    for (int i = 0; i < n1; i++) {
        L[i] = datos[izquierda + i];
    }

    for (int j = 0; j < n2; j++) {
        R[j] = datos[medio + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = izquierda;

    while (i < n1 && j < n2) {

        if (L[i].dni <= R[j].dni) {

            datos[k] = L[i];
            i++;

        } else {

            datos[k] = R[j];
            j++;
        }

        k++;
    }

    while (i < n1) {
        datos[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        datos[k] = R[j];
        j++;
        k++;
    }
}

void mergeSortDNI(vector<Apto>& datos, int izquierda, int derecha) {

    if (izquierda < derecha) {

        int medio = izquierda + (derecha - izquierda) / 2;

        mergeSortDNI(datos, izquierda, medio);

        mergeSortDNI(datos, medio + 1, derecha);

        mergeDNI(datos, izquierda, medio, derecha);
    }
}
// RADIX SORT POR DNI
int getMaxDNI(vector<Apto>& datos) {

    int maximo = stoi(datos[0].dni);

    for (int i = 1; i < datos.size(); i++) {

        int dni = stoi(datos[i].dni);

        if (dni > maximo) {
            maximo = dni;
        }
    }

    return maximo;
}
void countingSortDNI(vector<Apto>& datos, int exp) {

    int n = datos.size();

    vector<Apto> output(n);

    int count[10] = {0};

    // Contar ocurrencias
    for (int i = 0; i < n; i++) {

        int dni = stoi(datos[i].dni);

        int index = (dni / exp) % 10;

        count[index]++;
    }

    // Acumular
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // Construir output
    for (int i = n - 1; i >= 0; i--) {

        int dni = stoi(datos[i].dni);

        int index = (dni / exp) % 10;

        output[count[index] - 1] = datos[i];

        count[index]--;
    }

    // Copiar al vector original
    for (int i = 0; i < n; i++) {
        datos[i] = output[i];
    }
}
void radixSortDNI(vector<Apto>& datos) {

    int maximo = getMaxDNI(datos);

    for (int exp = 1; maximo / exp > 0; exp *= 10) {

        countingSortDNI(datos, exp);
    }
}

//-------------------------------------------------
//                Algoritmos de BUSQUEDA
//------------------------------------------------
// BUSQUEDA LINEAL POR DNI
int busquedaLineal(vector<Apto>& datos, string objetivo) {

    for (int i = 0; i < datos.size(); i++) {

        if (datos[i].dni == objetivo) {
            return i;
        }
    }

    return -1;
}
// BUSQUEDA BINARIA POR DNI
int busquedaBinaria(vector<Apto>& datos, string objetivo) {

    int izquierda = 0;
    int derecha = datos.size() - 1;

    while (izquierda <= derecha) {

        int medio = (izquierda + derecha) / 2;

        if (datos[medio].dni == objetivo) {
            return medio;
        }

        if (datos[medio].dni < objetivo) {
            izquierda = medio + 1;
        } else {
            derecha = medio - 1;
        }
    }

    return -1;
}
// JUMP SEARCH POR DNI
int jumpSearch(vector<Apto>& datos, string objetivo) {

    int n = datos.size();

    int paso = sqrt(n);

    int prev = 0;

    while (datos[min(paso, n) - 1].dni < objetivo) {

        prev = paso;

        paso += sqrt(n);

        if (prev >= n) {
            return -1;
        }
    }

    for (int i = prev; i < min(paso, n); i++) {

        if (datos[i].dni == objetivo) {
            return i;
        }
    }

    return -1;
}
// INTERPOLATION SEARCH
int interpolationSearch(vector<Apto>& datos, string objetivo) {

    int izquierda = 0;
    int derecha = datos.size() - 1;

    int objetivoNum = stoi(objetivo);

    while (izquierda <= derecha &&
           objetivoNum >= stoi(datos[izquierda].dni) &&
           objetivoNum <= stoi(datos[derecha].dni)) {

        int izq = stoi(datos[izquierda].dni);
        int der = stoi(datos[derecha].dni);

        if (izq == der) {

            if (izq == objetivoNum)
                return izquierda;

            return -1;
        }

        int pos = izquierda +
            ((double)(derecha - izquierda) /
            (der - izq)) *
            (objetivoNum - izq);

        int valor = stoi(datos[pos].dni);

        if (valor == objetivoNum) {
            return pos;
        }

        if (valor < objetivoNum) {
            izquierda = pos + 1;
        } else {
            derecha = pos - 1;
        }
    }

    return -1;
}
// EXPONENTIAL SEARCH
int exponentialSearch(vector<Apto>& datos, string objetivo) {

    int n = datos.size();

    if (datos[0].dni == objetivo) {
        return 0;
    }

    int i = 1;

    while (i < n && datos[i].dni <= objetivo) {
        i *= 2;
    }

    int izquierda = i / 2;
    int derecha = min(i, n - 1);

    while (izquierda <= derecha) {

        int medio = (izquierda + derecha) / 2;

        if (datos[medio].dni == objetivo) {
            return medio;
        }

        if (datos[medio].dni < objetivo) {
            izquierda = medio + 1;
        } else {
            derecha = medio - 1;
        }
    }

    return -1;
}