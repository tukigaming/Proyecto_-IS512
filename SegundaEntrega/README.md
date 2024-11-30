# Gestor de Memoria en C++

Este proyecto es una simulación de un gestor de memoria en C++ que implementa esquemas básicos de **paginación** y **segmentación** para la administración de procesos en memoria principal (RAM) y memoria virtual. El código incluye características como manejo de fallos de página, fragmentación interna y externa, y una política de reemplazo FIFO.

## Características

- **Esquema de Paginación:** Divide los procesos en páginas de tamaño fijo y las asigna a RAM o memoria virtual.
- **Esquema de Segmentación:** Divide los procesos en segmentos de tamaño variable para una mayor flexibilidad.
- **FIFO para Reemplazo de Procesos:** Gestiona procesos en memoria utilizando una política de cola FIFO.
- **Manejo de Fragmentación:**
  - **Interna:** Detecta y reporta espacio no utilizado dentro de las páginas.
  - **Externa:** Identifica la falta de espacio contiguo suficiente para asignar procesos.
- **Compactación de Memoria:** Simula la compactación para reorganizar los procesos y liberar espacio contiguo.

## Requisitos del Sistema

- Compilador de C++ compatible con el estándar **C++11** o superior.
- Sistema operativo capaz de ejecutar aplicaciones de línea de comandos.

## Estructura del Código

### Clases y Estructuras Principales

- **`Process`**: Representa un proceso con su ID, tamaño y asignaciones de memoria (páginas o segmentos).
- **`MemoryManager`**: Clase principal para gestionar la memoria. Incluye funciones para agregar procesos, manejar fallos de página, simular fragmentación, y compactar memoria.

### Constantes

- `PAGE_SIZE`: Tamaño de una página para el esquema de paginación (por defecto, 4 unidades).
- `SEGMENT_SIZE`: Tamaño de un segmento para el esquema de segmentación (por defecto, 6 unidades).

## Uso del Programa

### Ejecución

1. Compila el código con un compilador de C++:
   ```bash
   g++ memory_manager.cpp -o memory_manager
