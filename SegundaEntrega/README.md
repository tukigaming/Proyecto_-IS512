# Simulador de Gestión de Memoria en C++

Este proyecto es una simulación educativa que ilustra cómo los sistemas operativos manejan la memoria utilizando **paginación** y **segmentación**. Proporciona una representación interactiva de la administración de memoria principal (RAM) y memoria virtual, incluyendo el manejo de fallos de página, fragmentación y una política FIFO de reemplazo de procesos.

---

## Tabla de Contenidos

1. [Introducción](#introducción)  
2. [Características](#características)  
3. [Requisitos del Sistema](#requisitos-del-sistema)  
4. [Instrucciones de Instalación](#instrucciones-de-instalación)  
5. [Uso del Programa](#uso-del-programa)  
6. [Ejemplo Práctico](#ejemplo-práctico)  
7. [Detalles Técnicos](#detalles-técnicos)  
8. [Cómo Contribuir](#cómo-contribuir)  
9. [Licencia](#licencia)  

---

## Introducción

En este programa, puedes gestionar procesos simulando los esquemas básicos de memoria utilizados en sistemas operativos modernos:

- **Paginación:** Divide los procesos en páginas de tamaño fijo para simplificar la asignación de memoria.  
- **Segmentación:** Divide los procesos en segmentos de tamaño variable para un manejo más flexible.  

Incluye funciones avanzadas para gestionar memoria de manera eficiente, como el manejo de fallos de página, fragmentación interna y externa, compactación de memoria, y reemplazo de procesos usando la política FIFO.

---

## Características

### Funcionalidades Clave

1. **Gestión de Memoria Dual:**
   - Memoria RAM (limitada) para procesos activos.
   - Memoria Virtual como respaldo para procesos que no caben en RAM.

2. **Modos de Asignación:**
   - **Paginación:** Divide un proceso en páginas de tamaño fijo definido por `PAGE_SIZE`.  
   - **Segmentación:** Divide un proceso en segmentos según su tamaño y ajustados a `SEGMENT_SIZE`.

3. **Políticas de Memoria:**
   - **FIFO:** Los procesos más antiguos se eliminan primero al liberar espacio.
   - **Compactación:** Reorganiza procesos en memoria para reducir la fragmentación externa.

4. **Manejo de Fragmentación:**
   - **Interna:** Espacio desperdiciado dentro de las páginas.
   - **Externa:** Espacio insuficiente contiguo para asignar procesos.

5. **Interfaz Interactiva:** Un menú que permite:
   - Agregar procesos (usando paginación o segmentación).  
   - Visualizar el estado de la memoria.  
   - Simular la compactación y reemplazo de procesos.

### Parámetros Configurables

- **`PAGE_SIZE` (4 por defecto):** Tamaño de las páginas.  
- **`SEGMENT_SIZE` (6 por defecto):** Tamaño de los segmentos.  
- **RAM y Memoria Virtual:** Configurables en el constructor `MemoryManager`.  

---

## Requisitos del Sistema

- Compilador **C++11** o superior (e.g., `g++`, `clang++`).  
- Acceso a terminal para ejecutar aplicaciones de línea de comandos.  

---

## Instrucciones de Instalación

1. **Clona o descarga este repositorio.**  
2. **Compila el código fuente:**
   ```bash
   g++ memory_manager.cpp -o memory_manager
