#include <iostream>
#include <vector>

using namespace std;

// Estructura de Partición
struct Partition {
    int id;
    int size;
    int startAddress;
    int occupiedSize;
    bool isOccupied;

    Partition(int size) : id(0), size(size), occupiedSize(0), isOccupied(false) {}
    Partition(int id, int size, int startAddress, bool isOccupied)
        : id(id), size(size), startAddress(startAddress), isOccupied(isOccupied), occupiedSize(size) {}
};

// Clase para Particionamiento Dinámico
class MemoryManager {
    vector<Partition> partitions;
    int totalMemory;
    int lastPartitionId;

public:
    MemoryManager(int totalMemory) : totalMemory(totalMemory), lastPartitionId(0) {
        partitions.push_back(Partition(0, totalMemory, 0, false));
    }

    void allocateProcess(int processSize) {
        for (int i = 0; i < partitions.size(); i++) {
            if (!partitions[i].isOccupied && partitions[i].size >= processSize) {
                partitions[i].isOccupied = true;
                partitions[i].id = ++lastPartitionId;

                if (partitions[i].size > processSize) {
                    partitions.insert(partitions.begin() + i + 1, 
                                      Partition(0, partitions[i].size - processSize, partitions[i].startAddress + processSize, false));
                    partitions[i].size = processSize;
                }

                cout << "                             Proceso " << partitions[i].id << " asignado en direccion " << partitions[i].startAddress
                     << " con cantidad " << processSize << " KB.\n";
                return;
            }
        }
        cout << "                                     No hay suficiente memoria para el proceso de " << processSize << " KB.\n";
    }

    void deallocateProcess(int processId) {
        for (int i = 0; i < partitions.size(); i++) {
            if (partitions[i].isOccupied && partitions[i].id == processId) {
                partitions[i].isOccupied = false;
                cout << "                                Proceso " << processId << " liberado.\n";
                return;
            }
        }
        cout << "                                     Proceso " << processId << " no encontrado.\n";
    }

    void displayMemoryState() {
    	cout << "                                     ---------------------------------------------------\n";
        cout << "                                                     Estado de la memoria:\n";
        for (int i = 0; i < partitions.size(); i++) {
            cout << "                                        Inicio: " << partitions[i].startAddress << " KB, con cantidad: " << partitions[i].size
                 << " KB, " << (partitions[i].isOccupied ? "Ocupado" : "Libre") << "\n";
        }
        cout << endl;
    }
};

// Clase para Particionamiento Fijo
class FixedPartitionMemoryManager {
    vector<Partition> partitions;
    int partitionSize;
    int lastProcessId;

public:
    FixedPartitionMemoryManager(int totalMemory, int partitionSize) : partitionSize(partitionSize), lastProcessId(0) {
        int numPartitions = totalMemory / partitionSize;
        for (int i = 0; i < numPartitions; i++) {
            partitions.push_back(Partition(partitionSize));
        }
    }

    void allocateProcess(int processSize) {
        if (processSize > partitionSize) {
            cout << "                           El proceso de " << processSize << " KB es demasiado grande para una particion.\n";
            return;
        }

        for (int i = 0; i < partitions.size(); i++) {
            if (!partitions[i].isOccupied) {
                partitions[i].isOccupied = true;
                partitions[i].id = ++lastProcessId;
                partitions[i].occupiedSize = processSize;
                cout << "                                  Proceso " << partitions[i].id << " asignado a la particion " << i + 1 
                     << " con cantidad " << processSize << " KB.\n";
                return;
            }
        }
        cout << "No hay particiones libres.\n";
    }

    void deallocateProcess(int processId) {
        for (int i = 0; i < partitions.size(); i++) {
            if (partitions[i].isOccupied && partitions[i].id == processId) {
                partitions[i].isOccupied = false;
                partitions[i].occupiedSize = 0;
                cout << "                                         Proceso " << processId << " liberado de la particion " << i + 1 << ".\n";
                return;
            }
        }
        cout << "                                             Proceso " << processId << " no encontrado.\n";
    }

    void displayMemoryState() {
        cout << "                                     ---------------------------------------------------\n";
        cout << "                                                  Estado de la memoria:\n";
        for (int i = 0; i < partitions.size(); i++) {
            cout << "                                                Particion " << i + 1 << ": ";
            if (partitions[i].isOccupied) {
                cout << "Ocupado (Proceso " << partitions[i].id << ", cantidad " << partitions[i].occupiedSize << " KB)";
            } else {
                cout << "Libre";
            }
            cout << "\n";
        }
        cout << "                                 ---------------------------------------------------\n";
    }
};

void showMemoryManagerMenu() {
	cout << "                                     ---------------------------------------------------\n";
    cout << "                                                   MENU DE PARTICIONAMIENTO:\n";
    cout << "                                                    1. Asignar proceso\n";
    cout << "                                                    2. Liberar proceso\n";
    cout << "                                                    3. Mostrar estado de memoria\n";
    cout << "                                                    4. Salir\n";
}

void dynamicPartitioning() {
    int totalMemory;
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
                cout << "                                              Ingrese la cantidad del proceso en KB: ";
                cin >> processSize;
                memoryManager.allocateProcess(processSize);
                break;
            }
            case 2: {
                int processId;
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
                cout << "                                      Saliendo del administrador de particionamiento dinamico.\n";
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo.\n";
        }
    }
}

void fixedPartitioning() {
    int totalMemory, partitionSize;
    cout << "                                     ---------------------------------------------------\n";
    cout << "                                       Ingrese la cantidad total de la memoria en KB: ";
    cin >> totalMemory;
    cout << "                                       Ingrese la cantidad de cada particion en KB:";
    cin >> partitionSize;

    FixedPartitionMemoryManager memoryManager(totalMemory, partitionSize);
    bool running = true;

    while (running) {
        showMemoryManagerMenu();
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                int processSize;
                cout << "                                          Ingrese la cantidad del proceso en KB: ";
                cin >> processSize;
                memoryManager.allocateProcess(processSize);
                break;
            }
            case 2: {
                int processId;
                cout << "                                           Ingrese el ID del proceso a liberar: ";
                cin >> processId;
                memoryManager.deallocateProcess(processId);
                break;
            }
            case 3:
                memoryManager.displayMemoryState();
                break;
            case 4:
                running = false;
                cout << "                                 Saliendo del administrador de particionamiento fijo.\n";
                break;
            default:
                cout << "                                          Opcion no valida. Intente de nuevo.\n";
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
    cout << "                                                 3. Salir\n";
}

int main() {
    int choice;
    bool running = true;

    while (running) {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                fixedPartitioning();
                break;
            case 2:
                dynamicPartitioning();
                break;
            case 3:
                running = false;
                cout << "                                                Saliendo del simulador.\n";
                break;
            default:
                cout << "                                            Opcion no valida. Intente de nuevo.\n";
        }
    }

    return 0;
}

