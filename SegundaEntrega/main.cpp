#include <iostream>
#include <queue>
#include <vector>
#include <map>

using namespace std;

#define PAGE_SIZE 4  // Tamaño de página para simular el manejo de páginas
#define SEGMENT_SIZE 6  // Tamaño de segmento para simular la segmentación

// Estructura para representar un proceso
struct Process {
    int id;    // Identificador del proceso
    int size;  // Tamaño del proceso
    vector<int> pages;   // Páginas del proceso (para el esquema de paginación)
    vector<int> segments; // Segmentos del proceso (para el esquema de segmentación)
};

// Clase para gestionar la memoria
class MemoryManager {
private:
    int ramCapacity, virtualCapacity; // Capacidad de RAM y memoria virtual
    int usedRam, usedVirtual;         // Espacios usados en RAM y memoria virtual
    queue<int> fifoQueue;             // Cola FIFO para el orden de los procesos
    map<int, int> ramAllocation;      // Asignación de procesos en RAM
    map<int, int> virtualAllocation;  // Asignación de procesos en memoria virtual
    map<int, vector<int>> pageTable; // Tabla de páginas para el esquema de paginación
    map<int, vector<int>> segmentTable; // Tabla de segmentos para el esquema de segmentación

    // Función para liberar espacio utilizando FIFO
    void freeSpace(int requiredSize) {
        cout << "Liberando espacio para el nuevo proceso..." << endl;

        while (usedRam + usedVirtual + requiredSize > ramCapacity + virtualCapacity) {
            if (fifoQueue.empty()) {
                cout << "Error: No se puede liberar suficiente espacio." << endl;
                return;
            }

            // Eliminar el proceso más antiguo (FIFO)
            int oldestID = fifoQueue.front();
            fifoQueue.pop();

            // Eliminar de RAM
            if (ramAllocation.count(oldestID)) {
                int ramSize = ramAllocation[oldestID];
                usedRam -= ramSize;
                ramAllocation.erase(oldestID);
                cout << "Eliminado de RAM: Proceso ID " << oldestID << ", Tamaño: " << ramSize << endl;
            }

            // Eliminar de Memoria Virtual
            if (virtualAllocation.count(oldestID)) {
                int virtualSize = virtualAllocation[oldestID];
                usedVirtual -= virtualSize;
                virtualAllocation.erase(oldestID);
                cout << "Eliminado de Memoria Virtual: Proceso ID " << oldestID << ", Tamaño: " << virtualSize << endl;
            }
        }
    }

    // Función para manejar fallos de página (reemplazo de páginas)
    void handlePageFault(int processID) {
        cout << "Falló la página del Proceso ID: " << processID << endl;

        // Simulación de reemplazo de página utilizando FIFO
        if (pageTable[processID].size() >= ramCapacity / PAGE_SIZE) {
            int oldestPageID = fifoQueue.front();
            fifoQueue.pop();
            pageTable[processID].erase(pageTable[processID].begin());
            cout << "Reemplazada la página del Proceso ID: " << oldestPageID << endl;
        }

        // Cargar la página del proceso
        pageTable[processID].push_back(PAGE_SIZE);
        fifoQueue.push(processID);
        cout << "Página del Proceso ID " << processID << " cargada en memoria." << endl;
    }

    // Función para manejar la fragmentación interna
    void simulateInternalFragmentation(int processID, int size) {
        int pageFragment = size % PAGE_SIZE;
        if (pageFragment != 0) {
            cout << "Fragmentación interna detectada en Proceso ID " << processID << ": " << (PAGE_SIZE - pageFragment) << " unidades de espacio no utilizadas." << endl;
        }
    }

    // Función para manejar la fragmentación externa
    void simulateExternalFragmentation(int size) {
        if (usedRam + usedVirtual < ramCapacity + virtualCapacity) {
            cout << "Fragmentación externa: No hay suficiente espacio contiguo para el proceso." << endl;
        }
    }

    // Función para simular la fragmentación externa
    void compactMemory() {
        cout << "Iniciando la compactación de memoria..." << endl;

        // Mover los procesos en memoria RAM
        vector<int> ramProcesses;
        for (auto& entry : ramAllocation) {
            ramProcesses.push_back(entry.first);
        }

        // Reasignar los procesos contiguos
        ramAllocation.clear();
        usedRam = 0;
        for (int i = 0; i < ramProcesses.size(); ++i) {
            int id = ramProcesses[i];
            ramAllocation[id] = PAGE_SIZE;  // Suponemos que cada proceso ocupa una página completa
            usedRam += PAGE_SIZE;
            cout << "Proceso ID " << id << " movido a una nueva ubicación en RAM." << endl;
        }

        // Mover los procesos en Memoria Virtual
        vector<int> virtualProcesses;
        for (auto& entry : virtualAllocation) {
            virtualProcesses.push_back(entry.first);
        }

        // Reasignar los procesos contiguos
        virtualAllocation.clear();
        usedVirtual = 0;
        for (int i = 0; i < virtualProcesses.size(); ++i) {
            int id = virtualProcesses[i];
            virtualAllocation[id] = PAGE_SIZE;
            usedVirtual += PAGE_SIZE;
            cout << "Proceso ID " << id << " movido a una nueva ubicación en Memoria Virtual." << endl;
        }
    }

    // Generar el estado de la memoria
    string generateMemoryState(const map<int, int>& allocation, int capacity) {
        string memoryState(capacity, '0'); // Inicializar memoria vacía
        int position = 0;

        for (auto it = allocation.begin(); it != allocation.end(); ++it) {
            int id = it->first;
            int size = it->second;
            for (int i = 0; i < size && position < capacity; ++i) {
                memoryState[position++] = '0' + id; // Mostrar ID del proceso
            }
        }
        return memoryState;
    }

    // Función para dividir un proceso en páginas (Paginación)
    void paginateProcess(int id, int size) {
        int totalPages = (size + PAGE_SIZE - 1) / PAGE_SIZE; // Número total de páginas necesarias
        vector<int> pages(totalPages, PAGE_SIZE);
        pageTable[id] = pages;
        cout << "Proceso ID " << id << " dividido en " << totalPages << " páginas." << endl;
    }

    // Función para dividir un proceso en segmentos (Segmentación)
    void segmentProcess(int id, int size) {
        int totalSegments = (size + SEGMENT_SIZE - 1) / SEGMENT_SIZE; // Número total de segmentos necesarios
        vector<int> segments(totalSegments, SEGMENT_SIZE);
        segmentTable[id] = segments;
        cout << "Proceso ID " << id << " dividido en " << totalSegments << " segmentos." << endl;
    }

public:
    // Constructor
    MemoryManager(int ramCapacity, int virtualCapacity)
        : ramCapacity(ramCapacity), virtualCapacity(virtualCapacity),
          usedRam(0), usedVirtual(0) {}

    // Agregar un nuevo proceso
    void addProcess(int id, int size, int mode) {
    cout << "Intentando agregar Proceso ID: " << id << ", Tamaño: " << size << endl;

    // Liberar espacio si es necesario
    freeSpace(size);

    if (mode == 1) {  // Paginación
        // Dividir el proceso en páginas
        int pages = (size + PAGE_SIZE - 1) / PAGE_SIZE;  // Número de páginas necesarias
        cout << "Proceso ID " << id << " dividido en " << pages << " páginas." << endl;

        // Intentar asignar en la RAM primero
        int ramPages = min(pages, (ramCapacity - usedRam) / PAGE_SIZE);
        int virtualPages = pages - ramPages;

        // Asignar a RAM
        if (ramPages > 0) {
            usedRam += ramPages * PAGE_SIZE;
            ramAllocation[id] = ramPages * PAGE_SIZE;
            cout << "Proceso ID " << id << " (" << ramPages << " páginas) agregado a la RAM." << endl;
        }

        // Asignar a Memoria Virtual
        if (virtualPages > 0) {
            usedVirtual += virtualPages * PAGE_SIZE;
            virtualAllocation[id] = virtualPages * PAGE_SIZE;
            cout << "Proceso ID " << id << " (" << virtualPages << " páginas) agregado a la Memoria Virtual." << endl;
        }

    } else if (mode == 2) {  // Segmentación
        // Dividir el proceso en segmentos
        int segments = (size + SEGMENT_SIZE - 1) / SEGMENT_SIZE;  // Número de segmentos necesarios
        cout << "Proceso ID " << id << " dividido en " << segments << " segmentos." << endl;

        // Intentar asignar en la RAM primero
        int ramSegments = min(segments, (ramCapacity - usedRam) / SEGMENT_SIZE);
        int virtualSegments = segments - ramSegments;

        // Asignar a RAM
        if (ramSegments > 0) {
            usedRam += ramSegments * SEGMENT_SIZE;
            ramAllocation[id] = ramSegments * SEGMENT_SIZE;
            cout << "Proceso ID " << id << " (" << ramSegments << " segmentos) agregado a la RAM." << endl;
        }

        // Asignar a Memoria Virtual
        if (virtualSegments > 0) {
            usedVirtual += virtualSegments * SEGMENT_SIZE;
            virtualAllocation[id] = virtualSegments * SEGMENT_SIZE;
            cout << "Proceso ID " << id << " (" << virtualSegments << " segmentos) agregado a la Memoria Virtual." << endl;
        }
    }

    // Añadir a la cola FIFO
    fifoQueue.push(id);
}


    // Mostrar el estado de la memoria
    void displayMemory() {
        cout << "Memoria RAM: " << generateMemoryState(ramAllocation, ramCapacity) << endl;
        cout << "Memoria Virtual: " << generateMemoryState(virtualAllocation, virtualCapacity) << endl;
        cout << "\n" << endl;
    }
};

int main() {
    MemoryManager manager(20, 30);  // 20 unidades de RAM, 30 unidades de Memoria Virtual
    int choice;
    
    while (true) {
        cout << "1. Agregar Proceso (Paginación)\n";
        cout << "2. Agregar Proceso (Segmentación)\n";
        cout << "3. Mostrar Memoria\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id, size;
                cout << "Ingrese el ID del proceso: ";
                cin >> id;
                cout << "Ingrese el tamaño del proceso: ";
                cin >> size;
                manager.addProcess(id, size, 1);  // 1 para Paginación
                break;
            }
            case 2: {
                int id, size;
                cout << "Ingrese el ID del proceso: ";
                cin >> id;
                cout << "Ingrese el tamaño del proceso: ";
                cin >> size;
                manager.addProcess(id, size, 2);  // 2 para Segmentación
                break;
            }
            case 3:
                manager.displayMemory();
                break;
            case 4:
                return 0;
        }
    }

    return 0;
}