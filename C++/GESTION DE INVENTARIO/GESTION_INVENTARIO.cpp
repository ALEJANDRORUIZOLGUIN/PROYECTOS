// inventario.cpp
// Sistema de inventario con persistencia en archivo CSV.
// Compatible con C++98/C++11 (Dev-C++ / TDM-GCC).

#include <cctype>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const string ARCHIVO_DATOS = "inventario_datos.csv";

// ---------- Estructura de datos ----------
struct Producto {
    string codigo;
    string nombre;
    double precio;
    int existencias;
    int stockMinimo;
};

vector<Producto> inventario;

// ---------- Funciones auxiliares de entrada ----------
string leerLinea(const string& mensaje) {
    cout << mensaje;
    string texto;
    getline(cin, texto);
    return texto;
}

// Convierte texto a entero completo; devuelve false si no es válido
bool aEntero(const string& s, int& salida) {
    if (s.empty()) return false;
    char* fin;
    long valor = strtol(s.c_str(), &fin, 10);
    if (*fin != '\0') return false;
    if (valor < -2147483647L || valor > 2147483647L) return false;
    salida = static_cast<int>(valor);
    return true;
}

// Convierte texto a double completo; devuelve false si no es válido o no es finito
bool aDouble(const string& s, double& salida) {
    if (s.empty()) return false;
    char* fin;
    double valor = strtod(s.c_str(), &fin);
    if (*fin != '\0') return false;
    if (!(valor == valor) || valor > 1e300 || valor < -1e300) return false; // NaN o inf
    salida = valor;
    return true;
}

int leerEntero(const string& mensaje, int minimo) {
    while (true) {
        int valor;
        if (aEntero(leerLinea(mensaje), valor) && valor >= minimo) return valor;
        cout << "Valor no valido (minimo " << minimo << "). Intenta de nuevo.\n";
    }
}

double leerDouble(const string& mensaje, double minimo) {
    while (true) {
        double valor;
        if (aDouble(leerLinea(mensaje), valor) && valor >= minimo) return valor;
        cout << "Valor no valido (minimo " << minimo << "). Intenta de nuevo.\n";
    }
}

string minusculas(string s) {
    for (size_t i = 0; i < s.size(); i++) {
        s[i] = static_cast<char>(tolower(static_cast<unsigned char>(s[i])));
    }
    return s;
}

int buscarPorCodigo(const string& codigo) {
    for (size_t i = 0; i < inventario.size(); i++) {
        if (inventario[i].codigo == codigo) return static_cast<int>(i);
    }
    return -1;
}

// ---------- Manejo de CSV ----------
// Encierra el texto entre comillas si contiene comas o comillas
string escaparCSV(const string& campo) {
    if (campo.find_first_of(",\"") == string::npos) return campo;
    string resultado = "\"";
    for (size_t i = 0; i < campo.size(); i++) {
        if (campo[i] == '"') resultado += "\"\"";
        else resultado += campo[i];
    }
    return resultado + "\"";
}

// Separa una línea CSV en campos, respetando comillas
vector<string> separarCSV(const string& linea) {
    vector<string> campos;
    string campo;
    bool entreComillas = false;
    for (size_t i = 0; i < linea.size(); i++) {
        char c = linea[i];
        if (entreComillas) {
            if (c == '"') {
                if (i + 1 < linea.size() && linea[i + 1] == '"') {
                    campo += '"';
                    i++;
                } else {
                    entreComillas = false;
                }
            } else {
                campo += c;
            }
        } else {
            if (c == '"') entreComillas = true;
            else if (c == ',') { campos.push_back(campo); campo.clear(); }
            else campo += c;
        }
    }
    campos.push_back(campo);
    return campos;
}

// Escribe todo el inventario en formato CSV (sirve para guardar y exportar)
void escribirCSV(ostream& salida) {
    salida << "Codigo,Nombre,Precio,Existencias,StockMinimo\n";
    for (size_t i = 0; i < inventario.size(); i++) {
        const Producto& p = inventario[i];
        salida << escaparCSV(p.codigo) << ","
               << escaparCSV(p.nombre) << ","
               << fixed << setprecision(2) << p.precio << ","
               << p.existencias << ","
               << p.stockMinimo << "\n";
    }
}

// ---------- Persistencia ----------
void cargarDatos() {
    ifstream entrada(ARCHIVO_DATOS.c_str());
    if (!entrada) {
        cout << "No se encontro archivo de datos. Se iniciara un inventario nuevo.\n";
        return;
    }
    string linea;
    getline(entrada, linea); // Saltar encabezado
    int cargados = 0, omitidos = 0;
    while (getline(entrada, linea)) {
        if (linea.empty()) continue;
        vector<string> c = separarCSV(linea);
        if (c.size() < 5) { omitidos++; continue; }

        Producto p;
        p.codigo = c[0];
        p.nombre = c[1];
        if (!aDouble(c[2], p.precio) ||
            !aEntero(c[3], p.existencias) ||
            !aEntero(c[4], p.stockMinimo) ||
            p.codigo.empty() || p.precio < 0 || p.existencias < 0 || p.stockMinimo < 0 ||
            buscarPorCodigo(p.codigo) != -1) {
            omitidos++;
            continue;
        }
        inventario.push_back(p);
        cargados++;
    }
    cout << cargados << " producto(s) cargados desde " << ARCHIVO_DATOS << ".\n";
    if (omitidos > 0) cout << "Advertencia: " << omitidos << " linea(s) no validas se omitieron.\n";
}

void guardarDatos() {
    ofstream salida(ARCHIVO_DATOS.c_str());
    if (!salida) {
        cout << "Advertencia: no se pudo guardar en " << ARCHIVO_DATOS << ".\n";
        return;
    }
    escribirCSV(salida);
}

// ---------- Visualización ----------
void mostrarEncabezado() {
    cout << left << setw(10) << "Codigo" << setw(25) << "Nombre"
         << right << setw(10) << "Precio" << setw(12) << "Existencias"
         << setw(12) << "Stock min." << "\n";
    cout << string(69, '-') << "\n";
}

void mostrarProducto(const Producto& p) {
    cout << left << setw(10) << p.codigo << setw(25) << p.nombre
         << right << fixed << setprecision(2) << setw(10) << p.precio
         << setw(12) << p.existencias << setw(12) << p.stockMinimo;
    if (p.existencias <= p.stockMinimo) cout << "  <-- BAJO";
    cout << "\n";
}

// ---------- Operaciones ----------
void agregarProducto() {
    Producto p;
    p.codigo = leerLinea("Codigo: ");
    if (p.codigo.empty()) {
        cout << "El codigo no puede estar vacio.\n";
        return;
    }
    if (buscarPorCodigo(p.codigo) != -1) {
        cout << "Ya existe un producto con ese codigo.\n";
        return;
    }
    p.nombre = leerLinea("Nombre: ");
    if (p.nombre.empty()) {
        cout << "El nombre no puede estar vacio.\n";
        return;
    }
    p.precio = leerDouble("Precio: ", 0);
    p.existencias = leerEntero("Existencias iniciales: ", 0);
    p.stockMinimo = leerEntero("Stock minimo (para alertas): ", 0);

    inventario.push_back(p);
    cout << "Producto agregado correctamente.\n";
}

void eliminarProducto() {
    string codigo = leerLinea("Codigo del producto a dar de baja: ");
    int i = buscarPorCodigo(codigo);
    if (i == -1) {
        cout << "Producto no encontrado.\n";
        return;
    }
    string confirma = leerLinea("Confirmar baja de '" + inventario[i].nombre + "' (s/n): ");
    if (confirma == "s" || confirma == "S") {
        inventario.erase(inventario.begin() + i);
        cout << "Producto dado de baja.\n";
    } else {
        cout << "Operacion cancelada.\n";
    }
}

void modificarProducto() {
    string codigo = leerLinea("Codigo del producto a modificar: ");
    int i = buscarPorCodigo(codigo);
    if (i == -1) {
        cout << "Producto no encontrado.\n";
        return;
    }
    Producto& p = inventario[i];
    cout << "Datos actuales -> Nombre: " << p.nombre << ", Precio: "
         << fixed << setprecision(2) << p.precio
         << ", Stock minimo: " << p.stockMinimo << "\n";
    cout << "1) Nombre  2) Precio  3) Stock minimo  0) Cancelar\n";
    int op = leerEntero("Opcion: ", 0);

    switch (op) {
        case 1: {
            string nuevo = leerLinea("Nuevo nombre: ");
            if (nuevo.empty()) { cout << "El nombre no puede estar vacio.\n"; return; }
            p.nombre = nuevo;
            break;
        }
        case 2: p.precio = leerDouble("Nuevo precio: ", 0); break;
        case 3: p.stockMinimo = leerEntero("Nuevo stock minimo: ", 0); break;
        default: cout << "Sin cambios.\n"; return;
    }
    cout << "Producto modificado.\n";
}

void controlExistencias() {
    string codigo = leerLinea("Codigo del producto: ");
    int i = buscarPorCodigo(codigo);
    if (i == -1) {
        cout << "Producto no encontrado.\n";
        return;
    }
    Producto& p = inventario[i];
    cout << "Existencia actual de " << p.nombre << ": " << p.existencias << "\n";
    cout << "1) Entrada (compra)  2) Salida (venta)\n";
    int op = leerEntero("Opcion: ", 1);
    int cantidad = leerEntero("Cantidad: ", 1);

    if (op == 1) {
        p.existencias += cantidad;
        cout << "Entrada registrada. Nueva existencia: " << p.existencias << "\n";
    } else if (op == 2) {
        if (cantidad > p.existencias) {
            cout << "No hay suficiente existencia. Disponible: " << p.existencias << "\n";
            return;
        }
        p.existencias -= cantidad;
        cout << "Salida registrada. Nueva existencia: " << p.existencias << "\n";
    } else {
        cout << "Opcion no valida.\n";
    }
}

void mostrarTodos() {
    if (inventario.empty()) {
        cout << "El inventario esta vacio.\n";
        return;
    }
    mostrarEncabezado();
    for (size_t i = 0; i < inventario.size(); i++) mostrarProducto(inventario[i]);
}

void buscarProducto() {
    string termino = minusculas(leerLinea("Buscar por nombre o codigo: "));
    int encontrados = 0;
    mostrarEncabezado();
    for (size_t i = 0; i < inventario.size(); i++) {
        const Producto& p = inventario[i];
        if (minusculas(p.codigo) == termino ||
            minusculas(p.nombre).find(termino) != string::npos) {
            mostrarProducto(p);
            encontrados++;
        }
    }
    if (encontrados == 0) cout << "No se encontraron productos.\n";
    else cout << encontrados << " resultado(s).\n";
}

void alertasStockBajo() {
    int total = 0;
    mostrarEncabezado();
    for (size_t i = 0; i < inventario.size(); i++) {
        if (inventario[i].existencias <= inventario[i].stockMinimo) {
            mostrarProducto(inventario[i]);
            total++;
        }
    }
    if (total == 0) cout << "No hay productos con stock bajo.\n";
    else cout << "ALERTA: " << total << " producto(s) con stock bajo.\n";
}

void reporteInventario() {
    if (inventario.empty()) {
        cout << "El inventario esta vacio.\n";
        return;
    }
    double valorTotal = 0;
    int unidadesTotales = 0, bajos = 0;
    for (size_t i = 0; i < inventario.size(); i++) {
        const Producto& p = inventario[i];
        valorTotal += p.precio * p.existencias;
        unidadesTotales += p.existencias;
        if (p.existencias <= p.stockMinimo) bajos++;
    }
    cout << "\n===== REPORTE DE INVENTARIO =====\n";
    cout << "Productos registrados: " << inventario.size() << "\n";
    cout << "Unidades totales:      " << unidadesTotales << "\n";
    cout << "Productos en alerta:   " << bajos << "\n";
    cout << "Valor total:           $" << fixed << setprecision(2) << valorTotal << "\n\n";
    mostrarEncabezado();
    for (size_t i = 0; i < inventario.size(); i++) mostrarProducto(inventario[i]);
}

void exportarCSV() {
    string archivo = leerLinea("Nombre del archivo (ej. reporte.csv): ");
    if (archivo.empty()) {
        cout << "Nombre no valido.\n";
        return;
    }
    ofstream salida(archivo.c_str());
    if (!salida) {
        cout << "No se pudo crear el archivo.\n";
        return;
    }
    escribirCSV(salida);
    cout << "Exportacion completada: " << archivo << "\n";
}

// ---------- Menú principal ----------
void mostrarMenu() {
    cout << "\n===== SISTEMA DE INVENTARIO =====\n"
         << "1) Agregar producto (alta)\n"
         << "2) Dar de baja producto\n"
         << "3) Modificar producto\n"
         << "4) Control de existencias (entradas/salidas)\n"
         << "5) Listar todos los productos\n"
         << "6) Buscar por nombre o codigo\n"
         << "7) Alertas de stock bajo\n"
         << "8) Reporte de inventario\n"
         << "9) Exportar a CSV\n"
         << "0) Salir\n";
}

int main() {
    cargarDatos();

    int opcion;
    do {
        mostrarMenu();
        opcion = leerEntero("Selecciona una opcion: ", 0);
        switch (opcion) {
            case 1: agregarProducto();    guardarDatos(); break;
            case 2: eliminarProducto();   guardarDatos(); break;
            case 3: modificarProducto();  guardarDatos(); break;
            case 4: controlExistencias(); guardarDatos(); break;
            case 5: mostrarTodos();       break;
            case 6: buscarProducto();     break;
            case 7: alertasStockBajo();   break;
            case 8: reporteInventario();  break;
            case 9: exportarCSV();        break;
            case 0: guardarDatos(); cout << "Datos guardados. Hasta luego.\n"; break;
            default: cout << "Opcion no valida.\n";
        }
    } while (opcion != 0);
    return 0;
}
