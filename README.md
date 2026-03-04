Nombre completo: Santiago Hernandez
NRC 2684
## Descripción
Este programa es un convertidor de divisas desarrollado en C++.
Permite realizar conversiones entre diferentes monedas internacionales como USD, EUR, JPY, GBP, entre otras.
El programa cuenta con dos modos de operación:
    Modo Operación Continua
        Permite realizar una conversión individual y repetir el proceso si el usuario lo desea.
    Modo Sesión
        Permite realizar múltiples conversiones dentro de una misma sesión, mostrando estadísticas acumuladas en tiempo real, como:
            Total de conversiones realizadas
            Total base acumulado
            Total convertido acumulado
            Promedio por conversión
            Conversión mínima
            Conversión máxima

El programa incluye:
    Validación de entradas
    Manejo de errores con std::cin.fail()
    Conversión segura de texto a número usando try-catch
    Separador de miles en los resultados
    Guardado automático de resultados en un archivo sesion.txt
    
## Cómo compilar y ejecutar
-Linux / WSL / Git Bash
    g++ currency_converter.cpp -o conversor  
    ./conversor

-Windows (MinGW)
    g++ currency_converter.cpp -o conversor.exe  
    conversor.exe