# Simulador de Gestión de Memoria: Particionamiento Fijo y Dinámico

Este programa simula un sistema de gestión de memoria, permitiendo gestionar particiones de memoria de manera fija o dinámica. Está diseñado para la asignación y liberación de procesos, y muestra el estado actual de la memoria en el sistema.

# Descripción
El programa implementa dos esquemas de particionamiento:

Particionamiento Fijo: La memoria se divide en particiones de tamaño fijo. Los procesos se asignan a particiones libres, y si el tamaño del proceso es mayor que el tamaño de una partición, se deniega la asignación.

Particionamiento Dinámico: La memoria se asigna dinámicamente según la cantidad solicitada por los procesos. Si no hay suficiente memoria, el proceso no puede ser asignado. También permite dividir las particiones grandes en varias más pequeñas cuando es necesario.

# Estructuras y Clases
## Partition
Representa una partición de memoria. Incluye atributos como:

id: Identificador único de la partición.
size: Tamaño de la partición.
startAddress: Dirección de inicio de la partición.
occupiedSize: Espacio ocupado por el proceso (si está ocupado).
isOccupied: Bandera que indica si la partición está ocupada.

# MemoryManager
Clase para gestionar el particionamiento dinámico. Permite:

Asignar un proceso a una partición.
Liberar un proceso.
Mostrar el estado de la memoria.


# FixedPartitionMemoryManager
Clase para gestionar el particionamiento fijo. Permite:

Asignar procesos a particiones de tamaño fijo.
Liberar procesos de particiones.
Mostrar el estado de la memoria.
Funciones
allocateProcess
Asigna un proceso a una partición de memoria. En particionamiento dinámico, se puede dividir una partición si es más grande que el tamaño solicitado. En particionamiento fijo, se asigna el proceso a la primera partición libre.

## deallocateProcess
Libera una partición de memoria que estaba ocupada por un proceso. El proceso es identificado por su id.

## displayMemoryState
Muestra el estado actual de la memoria, indicando si las particiones están ocupadas o libres.

## showMenu
Muestra el menú principal del programa, permitiendo al usuario elegir entre particionamiento fijo o dinámico, o salir del simulador.

## showMemoryManagerMenu
Muestra el menú para gestionar las particiones, con opciones para asignar procesos, liberar procesos y ver el estado de la memoria.

# Ejecución
El programa tiene un menú principal desde el cual el usuario puede seleccionar entre los siguientes esquemas de gestión de memoria:

Particionamiento Fijo: El sistema divide la memoria en particiones de tamaño fijo.
Particionamiento Dinámico: La memoria se asigna según el tamaño solicitado por los procesos.