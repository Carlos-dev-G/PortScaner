#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <vector>
#include <thread>

#pragma comment(lib, "ws2_32.lib")

// Función para escanear un puerto específico
void EscanearPuerto(const char *IP, int PORT)
{
    // Variables
    SOCKET SocketVar;
    struct sockaddr_in server;

    // Crear el socket
    SocketVar = socket(AF_INET, SOCK_STREAM, 0);
    if (SocketVar == INVALID_SOCKET)
    {
        std::cout << "No se pudo crear el socket." << std::endl;
        return; // Salir de la función si falla
    }

    // Configuración de la estructura del servidor
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr(IP); // Cambiar inet_pton por inet_addr

    // Intentar conectarse al puerto
    if (connect(SocketVar, (struct sockaddr *)&server, sizeof(server)) == 0)
    {
        std::cout << "PUERTO: " << PORT << " [ ABIERTO ]" << std::endl;
    }
    // Cerrar el socket
    closesocket(SocketVar);
}

void IniciarEscaner(const char *IP, int PORT_INIT, int PORT_END)
{
    // Iniciar Winsock
    WSADATA WinSock;
    if (WSAStartup(MAKEWORD(2, 2), &WinSock) != 0)
    {
        std::cout << "Fallo en la inicialización de Winsock." << std::endl;
        return;
    }

    // Variables
    std::vector<std::thread> Hilos;

    // Bucle para iniciar el escáner en cada puerto
    for (int port = PORT_INIT; port <= PORT_END; port++)
    {
        Hilos.emplace_back(EscanearPuerto, IP, port);
    }

    // Esperar que terminen todos los hilos
    for (auto &Hilo : Hilos)
    {
        Hilo.join();
    }

    // Limpiar Winsock
    WSACleanup();
}

int main(int argc, char *argv[])
{
    // Verificar que se proporcionaron los argumentos correctos
    if (argc != 4)
    {
        std::cout << "Uso: " << argv[0] << " <IP> <PUERTO_INICIAL> <PUERTO_FINAL>" << std::endl;
        return 1; // Salir si no se proporciona la IP y puertos
    }

    const char *IP = argv[1];           // Obtener la IP desde los argumentos
    int PORT_INIT = std::stoi(argv[2]); // Convertir el argumento a entero
    int PORT_END = std::stoi(argv[3]);  // Convertir el argumento a entero

    std::cout << "Escaneando puertos en " << IP << " desde el puerto " << PORT_INIT << " hasta el puerto " << PORT_END << "..." << std::endl;

    // Iniciar el escáner
    IniciarEscaner(IP, PORT_INIT, PORT_END);

    return 0;
}
