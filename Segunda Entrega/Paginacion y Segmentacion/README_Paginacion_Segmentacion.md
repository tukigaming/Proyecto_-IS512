# README: Gestión de Memoria con Paginación y Segmentación
Este programa implementa un sistema interactivo para gestionar la memoria de un sistema utilizando Paginación y Segmentación. El usuario puede alternar entre ambos métodos a través de un menú principal, donde se le permite realizar asignaciones, liberar recursos y visualizar el estado actual de la memoria.

#Funcionalidades
Menú Principal
El programa ofrece las siguientes opciones:

Paginación: Administrar memoria basada en marcos y páginas.
Segmentación: Administrar memoria basada en segmentos definidos por los procesos.
Salir: Finalizar el programa.

#Paginación
Asignar páginas a un proceso: Permite asignar páginas a procesos con marcos libres disponibles en memoria.
Liberar páginas de un proceso: Libera las páginas asignadas a un proceso específico.
Mostrar estado de la memoria: Muestra el estado actual de los marcos de memoria.

# Segmentación
Asignar segmentos a un proceso: Permite asignar segmentos a procesos según disponibilidad en memoria.
Liberar segmentos de un proceso: Libera los segmentos asignados a un proceso específico.
Mostrar estado de la memoria: Visualiza los segmentos asignados en memoria, incluyendo direcciones base y límites.

#Ejemplo de Uso
Selecciona una opción del menú principal (Paginación o Segmentación).
Realiza acciones como asignar o liberar memoria según el método elegido.
Revisa el estado actual de la memoria en cualquier momento.
Finaliza el programa seleccionando la opción Salir.

#Requisitos
Compilador compatible con C++98.
Sistema operativo con soporte para ejecución de aplicaciones de consola.