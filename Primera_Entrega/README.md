# Proyecto_-IS512

# Simulador de Gestión de Memoria

# Este proyecto es un simulador de gestión de memoria que implementa dos esquemas de particionamiento:

Particionamiento Fijo.
Particionamiento Dinámico.
Descripción

El simulador permite al usuario interactuar con un sistema de gestión de memoria donde puede asignar procesos, liberar memoria, y visualizar el estado actual de la memoria. Los usuarios pueden elegir entre particionamiento fijo o dinámico según sus necesidades.

# Características

# Particionamiento Fijo:

Divide la memoria total en particiones de tamaño fijo.
Asigna procesos a particiones disponibles.
Verifica que los procesos no excedan el tamaño de las particiones.


# Particionamiento Dinámico:

Permite asignar bloques de memoria de tamaño variable según las necesidades del proceso.
Crea particiones dinámicas cuando se asigna un proceso.
Optimiza el uso de la memoria dividiendo bloques libres.


# Funcionalidades Principales

Asignar Proceso:
Asigna un proceso a una partición disponible.
Crea una nueva partición dinámica (en particionamiento dinámico).

# Liberar Proceso:
Libera una partición ocupada por un proceso.


# Mostrar Estado de Memoria:
Muestra el estado actual de las particiones (inicio, tamaño y estado).

# Salir:
Termina el simulador.