# Sistema de Gestión de Inventario

Aplicación de consola desarrollada en C++ para administrar productos y controlar existencias. Los datos se conservan entre ejecuciones mediante un archivo CSV.

## Características

- Alta, modificación y baja de productos
- Control de entradas y salidas de existencias
- Buscador por código o nombre
- Alertas de productos con stock bajo
- Reporte general del inventario
- Exportación personalizada a archivos CSV
- Persistencia automática en `inventario_datos.csv`
- Validación de entradas numéricas y cadenas vacías
- Compatibilidad con C++98 y C++11

## Archivo principal

El código fuente se encuentra en [`GESTION_INVENTARIO.cpp`](GESTION_INVENTARIO.cpp).

## Datos de cada producto

Cada producto contiene:

- Código único
- Nombre
- Precio
- Existencias actuales
- Stock mínimo

## Compilar y ejecutar

Compila el programa con MinGW, TDM-GCC o cualquier compilador compatible:

```bash
g++ GESTION_INVENTARIO.cpp -o GESTION_INVENTARIO
```

Ejecuta el archivo generado:

```bash
./GESTION_INVENTARIO
```

En Windows también puede ejecutarse directamente:

```bash
GESTION_INVENTARIO.exe
```

## Uso

Al iniciar el programa se carga el archivo `inventario_datos.csv`, si existe. Después se muestra un menú con las siguientes opciones:

| Opción | Función |
|---|---|
| 1 | Agregar un producto |
| 2 | Dar de baja un producto |
| 3 | Modificar nombre, precio o stock mínimo |
| 4 | Registrar entradas o salidas |
| 5 | Mostrar todos los productos |
| 6 | Buscar por nombre o código |
| 7 | Consultar productos con stock bajo |
| 8 | Generar el reporte de inventario |
| 9 | Exportar el inventario a CSV |
| 0 | Guardar los datos y salir |

Los cambios se guardan automáticamente al agregar, eliminar, modificar o controlar existencias.

## Persistencia

El programa utiliza el archivo `inventario_datos.csv` con este formato:

```csv
Codigo,Nombre,Precio,Existencias,StockMinimo
A001,Lápiz,5.50,20,5
```

Los nombres y códigos que contienen comas o comillas se representan correctamente mediante el formato CSV estándar.

## Alertas de stock

Un producto aparece como stock bajo cuando sus existencias son menores o iguales que su stock mínimo.

## Requisitos

- Compilador compatible con C++98 o C++11
- Sistema operativo compatible con consola
- Permisos de escritura en el directorio donde se ejecuta el programa

## Autor

Alejandro Ruiz Olguin
