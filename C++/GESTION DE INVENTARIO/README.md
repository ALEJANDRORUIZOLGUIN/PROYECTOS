# Sistema de gestión de inventario en C++

Programa de consola para registrar y administrar productos. Guarda los datos automáticamente en un archivo CSV para conservar el inventario entre ejecuciones.

## Requisitos

- Un compilador de C++ (por ejemplo, GCC/MinGW, TDM-GCC o Dev-C++).
- El código está escrito para ser compatible con C++98 y C++11.

## Compilar y ejecutar

Desde esta carpeta, con GCC o MinGW:

```bash
g++ -std=c++98 GESTION_INVENTARIO.cpp -o gestion_inventario
./gestion_inventario
```

En Windows, ejecuta `gestion_inventario.exe` después de compilar.

## Funciones

- Agregar productos con código, nombre, precio, existencias y stock mínimo.
- Dar de baja productos y modificar nombre, precio o stock mínimo.
- Registrar entradas y salidas de existencias.
- Listar productos y buscar por nombre o código.
- Mostrar alertas de stock bajo y un reporte con unidades y valor total.
- Exportar el inventario a otro archivo CSV.
- Cargar y guardar los datos en `inventario_datos.csv` automáticamente.

## Archivo de datos

El programa crea o lee `inventario_datos.csv` en el directorio desde el que se ejecuta. No es necesario crearlo manualmente; se genera al guardar el inventario por primera vez.
