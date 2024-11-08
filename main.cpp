#include <iostream>
#include <vector>

using namespace std;

struct Partition {
    int id;
    int size;
    int startAddress;
    bool isOccupied;

    Partition(int id, int size, int startAddress, bool isOccupied)
        : id(id), size(size), startAddress(startAddress), isOccupied(isOccupied) {}
};

class MemoryManager {
    vector<Partition> partitions;
    int totalMemory;
    int lastPartitionId;

public:
    MemoryManager(int totalMemory) : totalMemory(totalMemory), lastPartitionId(0) {
        // Inicializa toda la memoria como una única partición libre.
        partitions.push_back(Partition(0, totalMemory, 0, false));
    }

    void allocateProcess(int processSize) {
        for (int i = 0; i < partitions.size(); i++) {
            if (!partitions[i].isOccupied && partitions[i].size >= processSize) {
                // Asigna el proceso dividiendo la partición si sobra espacio.
                partitions[i].isOccupied = true;
                partitions[i].id = ++lastPartitionId;

                if (partitions[i].size > processSize) {
                    partitions.insert(partitions.begin() + i + 1, 
                                      Partition(0, partitions[i].size - processSize, partitions[i].startAddress + processSize, false));
                    partitions[i].size = processSize;
                }

                cout << "                             Proceso " << partitions[i].id << " asignado en direccion " << partitions[i].startAddress
                     << "con cantidad " << processSize << " KB.\n";
                     cout << "";
                return;
            }
        }
        cout << "                                     No hay suficiente memoria para el proceso de " << processSize << " KB.\n";
        cout << "";
    }

    void deallocateProcess(int processId) {
        for (int i = 0; i < partitions.size(); i++) {
            if (partitions[i].isOccupied && partitions[i].id == processId) {
                partitions[i].isOccupied = false;
                cout << "                             Proceso " << processId << " liberado.\n";
                return;
            }
        }
        cout << "                                     Proceso " << processId << " no encontrado.\n";
    }

    void displayMemoryState() {
        cout << "\nEstado de la memoria:\n";
        for (int i = 0; i < partitions.size(); i++) {
            cout << "Inicio: " << partitions[i].startAddress << " KB, con cantidad: " << partitions[i].size
                 << " KB, " << (partitions[i].isOccupied ? "Ocupado" : "Libre") << "\n";
        }
        cout << endl;
    }
};

void showMemoryManagerMenu() {
    cout << "                                               MENU DE PARTICIONAMIENTO DINAMICO:\n";
    cout << "                                                    1. Asignar proceso\n";
    cout << "                                                    2. Liberar proceso\n";
    cout << "                                                    3. Mostrar estado de memoria\n";
    cout << "                                                    4. Salir\n";
}

void dynamicPartitioning() {
    int totalMemory;
    cout << "\n";
    cout << "                                   --------------------------------------------------------\n";
    cout << "                                         Ingrese la cantidad total de la memoria en KB: ";
    cin >> totalMemory;

    MemoryManager memoryManager(totalMemory);
    bool running = true;

    while (running) {
        showMemoryManagerMenu();
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                int processSize;
                cout << "\n";
    			cout << "                                   --------------------------------------------------------\n";
                cout << "                                              Ingrese la cantidad del proceso en KB: ";
                cin >> processSize;
                memoryManager.allocateProcess(processSize);
                break;
            }
            case 2: {
                int processId;
                cout << "\n";
    			cout << "                                   --------------------------------------------------------\n";
                cout << "                                              Ingrese el ID del proceso a liberar: ";
                cin >> processId;
                memoryManager.deallocateProcess(processId);
                break;
            }
            case 3:
                memoryManager.displayMemoryState();
                break;
            case 4:
                running = false;
                cout << "\n";
                cout << "                                      Saliendo del administrador de particionamiento dinamico.\n";
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo.\n";
        }
    }
}

void showMenu() {
    cout << "                                   --------------------------------------------------------\n";
    cout << "                                      HOLA MUY BUEN DIA, TARDE O NOCHE A TU SIMULADOR\n";
    cout << "                                   --------------------------------------------------------\n";
    cout << "                                       Seleccione el esquema de gestion de memoria:\n";
    cout << "                                                 1. Particionamiento Fijo\n";
    cout << "                                                 2. Particionamiento Dinamico\n";
    cout << "                                                 3. Paginacion\n";
    cout << "                                                 4. Segmentacion\n";
    cout << "                                                 5. Salir\n";
}

int main() {
    int choice;
    bool running = true;

    while (running) {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                // Inicializar el particionamiento fijo
                cout << "Particionamiento Fijo no implementado aun.\n";
                break;
            case 2:
                // Inicializar el particionamiento dinámico
                dynamicPartitioning();
                break;
            case 3:
                // Inicializar paginación
                cout << "Paginacion no implementada aun.\n";
                break;
            case 4:
                // Inicializar segmentación
                cout << "Segmentación no implementada aun.\n";
                break;
            case 5:
                running = false;
                cout << "\n";
                cout << "                                                Saliendo del simulador.\n";
                cout << "                                   --------------------------------------------------------\n";
                break;
            default:
                cout << "\n";
                cout << "                                           Opcion no valida, intente de nuevo.\n";
                cout << "\n";
        }
    }
    return 0;
}


