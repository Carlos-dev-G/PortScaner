# Escáner de Puertos en C++

Este es un escáner de puertos básico escrito en C++ que utiliza hilos para escanear puertos en una dirección IP específica. El escáner verifica si los puertos están abiertos.

## Características

- Escaneo de puertos utilizando múltiples hilos para mejorar la velocidad.
- Soporte para un rango de puertos especificado por el usuario.
- Muestra solo los resultados de los puertos abiertos.

## Requisitos

- Windows
- Compilador C++ que soporte la biblioteca Winsock (por ejemplo, TDM-GCC)

## Instalación

1. Clona este repositorio o descarga los archivos.
2. Asegúrate de tener un compilador C++ instalado (TDM-GCC recomendado).
3. Compila el programa usando el siguiente comando:

   ```bash
   g++ main.cpp -o portScanner -lws2_32
   ```

## Uso

Ejecuta el escáner con la siguiente sintaxis:

```bash
.\portScanner.exe <IP> <PUERTO_INICIAL> <PUERTO_FINAL>
```

### Ejemplo

Para escanear los puertos del 1 al 1024 en la IP `192.168.1.1`, usa:

```bash
.\portScanner.exe 192.168.1.1 1 1024
```
