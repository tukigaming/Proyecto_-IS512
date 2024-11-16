#include <iostream>
#include <vector>
#include <map>

using namespace std;

// ----------------- Funciones y estructuras para Paginación -----------------

struct Page {
    int processId;
    int pageNumber;
};

void displayMemoryPagination(const vector<Page>& memory, int frameCount) {
    cout << "\n";
    cout << "                            ------------- Estado actual de la memoria: ----------------\n";
    for (int i = 0; i < frameCount; i++) {
        if (memory[i].processId == -1) {
            cout << "                                   Marco " << i << ": Vacio\n";
        } else {
            cout << "                                   Marco " << i << ": Proceso " << memory[i].processId 
                 << ", Pagina " << memory[i].pageNumber << "\n";
        }
    }
    cout << "                           -------------------------------------------------------------\n";
}

void runPagination() {
    int totalFrames, processCount;

    cout << "                                  Ingrese el numero total de marcos de memoria: ";
    cin >> totalFrames;

    vector<Page> memory(totalFrames);
    for (int i = 0; i < totalFrames; ++i) {
        memory[i].processId = -1;
        memory[i].pageNumber = -1;
    }

    cout << "                                        Ingrese la cantidad de procesos: ";
    cin >> processCount;

    map<int, vector<int> > processes;

    for (int i = 1; i <= processCount; i++) {
        int processSize, pageSize;
        cout << "                                   Ingrese la cantidad del proceso " << i << " (en KB): ";
        cin >> processSize;
        cout << "                                   Ingrese la cantidad de una pagina (en KB): ";
        cin >> pageSize;

        int pageCount = (processSize + pageSize - 1) / pageSize;
        vector<int> pages(pageCount, -1);
        processes[i] = pages;

        cout << "                             El proceso " << i << " necesita " << pageCount << " paginas.\n";
    }

    char option;
    do {
        cout << "\n";
        cout << "                                    ----------  Opciones: --------------\n";
        cout << "                                    1. Asignar paginas a un proceso\n";
        cout << "                                    2. Liberar paginas de un proceso\n";
        cout << "                                    3. Mostrar estado de la memoria\n";
        cout << "                                    4. Salir\n";
        cout << "                                      Seleccione una opcion: ";
        cin >> option;

        switch (option) {
        case '1': {
            int processId;
            cout << "                                  Ingrese el ID del proceso: ";
            cin >> processId;

            if (processes.find(processId) == processes.end()) {
                cout << "                                Proceso no encontrado.\n";
                break;
            }

            for (size_t i = 0; i < processes[processId].size(); ++i) {
                bool assigned = false;
                for (int j = 0; j < totalFrames; j++) {
                    if (memory[j].processId == -1) {
                        memory[j].processId = processId;
                        memory[j].pageNumber = i;
                        processes[processId][i] = j;
                        assigned = true;
                        break;
                    }
                }
                if (!assigned) {
                    cout << "                    No hay suficientes marcos disponibles para asignar la pagina " << i 
                         << " del proceso " << processId << ".\n";
                    break;
                }
            }
            cout << "                                       Asignacion completada.\n";
            break;
        }
        case '2': {
            int processId;
            cout << "                                  Ingrese el ID del proceso a liberar: ";
            cin >> processId;

            if (processes.find(processId) == processes.end()) {
                cout << "                                  Proceso no encontrado.\n";
                break;
            }

            for (int i = 0; i < totalFrames; i++) {
                if (memory[i].processId == processId) {
                    memory[i].processId = -1;
                    memory[i].pageNumber = -1;
                }
            }
            for (size_t i = 0; i < processes[processId].size(); ++i) {
                processes[processId][i] = -1;
            }
            cout << "                                 Memoria liberada para el proceso " << processId << ".\n";
            break;
        }
        case '3':
            displayMemoryPagination(memory, totalFrames);
            break;
        case '4':
            cout << "Saliendo...\n";
            break;
        default:
            cout << "Opcion invalida. Intente de nuevo.\n";
            break;
        }
    } while (option != '4');
}

// ----------------- Funciones y estructuras para Segmentación -----------------

struct SegmentData {
    int segmentNumber;
    int segmentSize;
};

struct Segment {
    int processId;
    int segmentNumber;
    int baseAddress;
    int limit;
};

void displayMemorySegmentation(const vector<Segment>& memory) {
    cout << "\n";
    cout << "                            ------------- Estado actual de la memoria: ----------------\n";
    if (memory.empty()) {
        cout << "                                   Memoria vacia.\n";
    } else {
        for (size_t i = 0; i < memory.size(); ++i) {
            const Segment& seg = memory[i];
            cout << "                                   Proceso " << seg.processId 
                 << ", Segmento " << seg.segmentNumber 
                 << " -> Base: " << seg.baseAddress 
                 << ", Limite: " << seg.limit << "\n";
        }
    }
    cout << "                           -------------------------------------------------------------\n";
}

void runSegmentation() {
    int totalMemory, processCount;

    cout << "                                  Ingrese la cantidad total de la memoria (en KB): ";
    cin >> totalMemory;

    vector<Segment> memory;
    int usedMemory = 0;

    cout << "                                        Ingrese la cantidad de procesos: ";
    cin >> processCount;

    map<int, vector<SegmentData> > processes;

    for (int i = 1; i <= processCount; i++) {
        int segmentCount;
        cout << "                                   Ingrese la cantidad de segmentos para el proceso " << i << ": ";
        cin >> segmentCount;

        vector<SegmentData> segments;
        for (int j = 0; j < segmentCount; j++) {
            int segmentSize;
            cout << "                                   Ingrese la cantidad del segmento " << j << " (en KB): ";
            cin >> segmentSize;
            segments.push_back({j, segmentSize});
        }
        processes[i] = segments;
    }

    char option;
    do {
        cout << "\n";
        cout << "                                    ----------  Opciones: --------------\n";
        cout << "                                    1. Asignar segmentos a un proceso\n";
        cout << "                                    2. Liberar segmentos de un proceso\n";
        cout << "                                    3. Mostrar estado de la memoria\n";
        cout << "                                    4. Salir\n";
        cout << "                                      Seleccione una opcion: ";
        cin >> option;

        switch (option) {
        case '1': {
            int processId;
            cout << "                                  Ingrese el ID del proceso: ";
            cin >> processId;

            if (processes.find(processId) == processes.end()) {
                cout << "                                Proceso no encontrado.\n";
                break;
            }

            for (size_t i = 0; i < processes[processId].size(); ++i) {
                const SegmentData& segData = processes[processId][i];

                if (usedMemory + segData.segmentSize > totalMemory) {
                    cout << "                    No hay suficiente memoria disponible para asignar el segmento " 
                         << segData.segmentNumber << " del proceso " << processId << ".\n";
                    break;
                }

                Segment newSegment = {processId, segData.segmentNumber, usedMemory, segData.segmentSize};
                memory.push_back(newSegment);
                usedMemory += segData.segmentSize;

                cout << "                                  Segmento " << segData.segmentNumber 
                     << " del proceso " << processId 
                     << " asignado. Base: " << newSegment.baseAddress 
                     << ", Limite: " << newSegment.limit << "\n";
            }
            break;
        }
        case '2': {
            int processId;
            cout << "                                  Ingrese el ID del proceso a liberar: ";
            cin >> processId;

            vector<Segment>::iterator it = memory.begin();
            while (it != memory.end()) {
                if (it->processId == processId) {
                    usedMemory -= it->limit;
                    it = memory.erase(it);
                } else {
                    ++it;
                }
            }
            cout << "                                 Memoria liberada para el proceso " << processId << ".\n";
            break;
        }
        case '3':
            displayMemorySegmentation(memory);
            break;
        case '4':
            cout << "Saliendo...\n";
            break;
        default:
            cout << "Opcion invalida. Intente de nuevo.\n";
            break;
        }
    } while (option != '4');
}

// ----------------- Menú Principal -----------------

int main() {
    char option;

    do {
        cout << "\n";
        cout << "                                    ----------  Menu Principal --------------\n";
        cout << "                                    1. Administrar memoria por paginacion\n";
        cout << "                                    2. Administrar memoria por segmentacion\n";
        cout << "                                    3. Salir\n";
        cout << "                                      Seleccione una opcion: ";
        cin >> option;

        switch (option) {
        case '1':
            runPagination();
            break;
        case '2':
            runSegmentation();
            break;
        case '3':
            cout << "Saliendo...\n";
            break;
        default:
            cout << "Opcion invalida. Intente de nuevo.\n";
            break;
        }
    } while (option != '3');

    return 0;
}





