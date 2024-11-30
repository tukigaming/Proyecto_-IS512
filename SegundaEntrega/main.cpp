#include <iostream>
#include <queue>
#include <map>

using namespace std;

class MemoryManager {
private:
    int ramCapacity, virtualCapacity;
    int usedRam, usedVirtual;
    queue<int> fifoQueue;
    map<int, int> ramAllocation;
    map<int, int> virtualAllocation;
    int segmentSize = 4;  // Tamaño inicial del segmento

    void freeSpace(int requiredSize) {
        cout << "Liberando espacio para el nuevo proceso..." << endl;
        while (usedRam + requiredSize > ramCapacity) {
            if (fifoQueue.empty()) {
                cout << "Error: No se puede liberar suficiente espacio." << endl;
                return;
            }
            int oldestID = fifoQueue.front();
            fifoQueue.pop();

            if (ramAllocation.count(oldestID)) {
                int size = ramAllocation[oldestID];
                ramAllocation.erase(oldestID);
                usedRam -= size;
                virtualAllocation[oldestID] = size;
                usedVirtual += size;
                cout << "Moviendo Proceso ID " << oldestID << " a Memoria Virtual." << endl;
            }
        }
    }

    string generateMemoryState(const map<int, int>& allocation, int capacity) {
        string memoryState(capacity, '0');
        int position = 0;

        for (auto& entry : allocation) {
            int id = entry.first;
            int size = entry.second;
            int segments = (size + segmentSize - 1) / segmentSize;

            for (int i = 0; i < segments; ++i) {
                for (int j = 0; j < segmentSize && position < capacity; ++j) {
                    if (i * segmentSize + j < size) {
                        memoryState[position++] = '0' + id;  // ID del proceso
                    } else {
                        memoryState[position++] = '/';  // Fragmentación interna
                    }
                }
                if (position >= capacity) break;
            }
        }
        return memoryState;
    }

public:
    MemoryManager(int ramCapacity, int virtualCapacity)
        : ramCapacity(ramCapacity), virtualCapacity(virtualCapacity),
          usedRam(0), usedVirtual(0) {}

    void setSegmentSize(int size) {
        segmentSize = size;
        cout << "Tamaño de segmento definido en " << segmentSize << endl;
    }

    void addProcess(int id, int size) {
        cout << "Intentando agregar Proceso ID: " << id << ", Tamaño: " << size << endl;
        if (size > ramCapacity + virtualCapacity) {
            cout << "Error: El proceso es demasiado grande para la memoria total." << endl;
            return;
        }

        if (ramAllocation.count(id) || virtualAllocation.count(id)) {
            cout << "Proceso ID " << id << " ya existe." << endl;
            return;
        }

        freeSpace(size);

        int ramPart = min(size, ramCapacity - usedRam);
        int virtualPart = size - ramPart;

        if (ramPart > 0) {
            ramAllocation[id] = ramPart;
            usedRam += ramPart;
            fifoQueue.push(id);
            cout << "Parte del Proceso ID " << id << " colocada en RAM." << endl;
        }
        if (virtualPart > 0) {
            virtualAllocation[id] = virtualPart;
            usedVirtual += virtualPart;
            cout << "Parte del Proceso ID " << id << " colocada en Memoria Virtual." << endl;
        }
    }

    void displayMemory() {
        cout << "\nEstado de la memoria:" << endl;
        cout << "RAM usada: " << usedRam << "/" << ramCapacity << endl;
        cout << "RAM: " << generateMemoryState(ramAllocation, ramCapacity) << endl;
        cout << "Memoria Virtual usada: " << usedVirtual << "/" << virtualCapacity << endl;
        cout << "Memoria Virtual: " << generateMemoryState(virtualAllocation, virtualCapacity) << endl;
        cout << "-----------------------------" << endl;
    }
};

int main() {
    int ramCapacity, virtualCapacity;
    cout << "Ingrese la capacidad total de la RAM: ";
    cin >> ramCapacity;
    cout << "Ingrese la capacidad total de la Memoria Virtual: ";
    cin >> virtualCapacity;

    MemoryManager manager(ramCapacity, virtualCapacity);

    int choice;
    do {
        cout << "\nMenú de opciones:" << endl;
        cout << "1. Agregar proceso" << endl;
        cout << "2. Mostrar estado de la memoria" << endl;
        cout << "3. Definir tamaño de segmento" << endl;
        cout << "4. Salir" << endl;
        cout << "Elija una opción: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id, size;
                cout << "Ingrese ID del proceso: ";
                cin >> id;
                cout << "Ingrese tamaño del proceso: ";
                cin >> size;
                manager.addProcess(id, size);
                break;
            }
            case 2:
                manager.displayMemory();
                break;
            case 3: {
                int segmentSize;
                cout << "Ingrese el nuevo tamaño del segmento: ";
                cin >> segmentSize;
                manager.setSegmentSize(segmentSize);
                break;
            }
            case 4:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opción no válida. Intente nuevamente." << endl;
        }
    } while (choice != 4);

    return 0;
}
