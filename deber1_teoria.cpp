/* 
* Programa: currency_converter.cpp
* Objetivo: Motor de cambio de divisas con dos modos de operación
*           (continua y sesión) que permite calcular conversiones
*           y estadísticas acumuladas en tiempo real.
*
* Tema: Lazos estructurados, acumuladores, validación de entradas
*       y manejo de excepciones.
*
* Autor: Santiago Hernandez
* Fecha: 25 de Febrero de 2026
*
* IA utilizada: Sí. Se utilizó ChatGPT como apoyo para:
* - Comprender e implementar el bloque try-catch.
* - Convertir string a número con std::stold().
* - Inicializar correctamente el valor mínimo con numeric_limits.
*
* Decisiones de diseño:
* - Uso de while para el menú principal, permitiendo repetición
*   controlada hasta que el usuario decida salir.
* - Separación del programa en funciones (programa1 y programa2)
*   para mantener modularidad y claridad.
* - Inicialización de min con numeric_limits<long double>::infinity()
*   para asegurar comparación correcta en la primera iteración.
* - Uso de acumuladores (total_base, total_convertido, contador)
*   para calcular estadísticas en tiempo real.
* - Lectura de montos como string en modo sesión para permitir
*   la salida con 'q' y conversión segura usando try-catch.
* - Uso de <fstream> para guardar automáticamente las sesiones
*   en un archivo de texto (sesion.txt).
* - Implementar función validar_si_no() usando std::getline() y std::ws.
* - Corregir problemas de buffer al mezclar std::cin >> y std::getline().
* - Mejorar validación del menú principal.
*/
#include <iostream>
#include <string>
#include <cctype>//libreria usada para la funcion validar que tenga caracteres alfabeticos(IA)
#include <iomanip> 
#include <sstream>
#include <chrono>//Libreria usada para determinar tiempo y realizar el timestamp (IA)
#include <ctime>//Libreria usada para determinar tiempo y realizar el timestamp (IA)
#include <unistd.h> //Libreria usada para hacer esperar(IA)
#include <vector>
#include <limits>
#include <fstream> //libreria para crear archivo txt 
//separador de miles
std::string formatearNumero(long double valor) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << valor;
    std::string num = ss.str();

    int punto = num.find('.');
    int inicio = (punto == -1) ? num.length() : punto;

    for (int i = inicio - 3; i > 0; i -= 3) {
        num.insert(i, ",");
    }

    return num;
}

//Valida que los datos ingresados sean str y no otro tipo de datos.
bool validador(std::string x) {
    std::string validas[] ={"USD", "EUR", "JPY", "GBP", "CHF", "CAD", "AUD", "MXN", "COP", "PEN", 
    "BRL", "CLP", "ARS", "CNY", "HKD", "KRW", "SGD", "INR", "NZD", "THB",
    "IDR", "MYR", "PHP", "ILS", "TRY", "ZAR", "AED", "SAR", "SEK", "NOK"};
    bool alfa = false, divisa_valida=false;
    if (x.length() == 3) {
        for (char i : x) { //Informacion sacada de IA, use !isalpha para poder verificar que hay datos alfabeticos.
            if (!isalpha(i)) {
                alfa = true;
            } //fin informacion sacada de IA
        }
        if (alfa) {
            std::cout << "Verifica que ingresaste datos alfabeticos" << std::endl;
            return false;
        }
        for(const std::string v:validas){
            if(x == v){
                divisa_valida=true;
                break;
            }
        }
        if(divisa_valida==false){
            std::cout<<"Ingresa una divisa valida. ";
            return false;
        }
        return true;
    } else {
        std::cout << "Verifica que la divisa este ingresada correctamente" << std::endl;
        return false;
    }
    return true;
}


std::string validar_si_no() {
    std::string respuesta;
    while (true) {
        std::getline(std::cin >> std::ws, respuesta );//[IA START]
        // std::ws limpia espacios y saltos de línea pendientes
        for (char &c : respuesta) {
            c = std::tolower(c);
        } //[IA END]
        if (respuesta == "si" or respuesta == "no") {
            return respuesta;
        } 
        else {
            std::cout << "Respuesta invalida. Escribe 'si' o 'no': "<<std::endl;
        }
    }
}

void programa1(){
    std::ofstream archivo("sesion.txt", std::ios::app);
    archivo<<"----------------------------------------"<<"\nCAMBIO DE DIVISAS POR OPERACION CONTINUA\n"<<std::endl;
    std::cout << "\033[2J\033[1;1H";//Linea de codigo usada de IA para scrolear terminal.
    std::cout << std::fixed << std::setprecision(2);//Linea de codigo proporcionada por IA para generar puntos de mil BASADO EN REGION DEL COMPUTADOR.
    
    while(true){
        int ingresar_programa;
        std :: cout<<"Ingresaste al programa de cambio de divisas por sesión "<< std::endl;

        std::string divisa_base, divisa_cambio, yes_no, si_no, continuar;
        long double taza, valor, total;

        //SOlICITAR DIVISA BASE
        while(true){
            std :: cout<<"Ingresa la divisa base (USD, EUR, JPY, etc): "<<std::endl; 
            std::cin>>divisa_base;

            for(char &c : divisa_base) c = std::toupper(c);//linea de codigo sacada de IA, transforma todo a upper
            
            bool n=validador(divisa_base); //VERIFICAR CONDICIONES 
            if (n){
                break;
            }else{
                std::cout<<"Has ingresado datos incorrectos"<<std::endl; 
                continue;
            }
        }

        //SOLICITAR DIVISA DE CAMBIO 
        while(true){
            std :: cout<<"Ingresa la divisa de cambio (USD, EUR, JPY, etc): "<<std::endl; 
            std::cin>>divisa_cambio;

            for(char &c : divisa_cambio) c = std::toupper(c);//linea de codigo sacada de IA, transforma todo a upper
            
            bool n=validador(divisa_cambio);
            if (n){
                ingresar_programa=1;
                break;
            }else{
                std::cout<<"Has ingresado datos incorrectos, ingresalo nuevamente"<<std::endl; 
                continue;
            }
        }

        if(ingresar_programa==1){

            //VERIFICAR DATOS
            std::cout<<"Has seleccionado "<<divisa_base<<" como tu divisa base y "<<divisa_cambio<< " como tu divisa de cambio, esto es correcto?(si/no) "<<std::endl;
            yes_no = validar_si_no();

            if (yes_no!="si"){
                std::cout << "\033[2J\033[1;1H";
                continue;
            }

            //SOLICITAR TASA
            std::cout<<"Perfecto, indica la tasa respectiva para "<<divisa_base<<"/"<<divisa_cambio<<std::endl;

            while (true) {
                std::cin >> taza;

                if (std::cin.fail()) {
                    std::cout << "Ingresa un caracter numerico valido." << std::endl;
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    continue;
                }

                if (taza <= 0) {
                    std::cout << "Por favor ingresa una tasa positiva y mayor a 0: " << std::endl;
                    continue;
                }

                break;
            }

            std::cout << std::fixed << std::setprecision(5);
            std::cout<<"Has indicado que 1 "<<divisa_base<<" equivale a "<< taza<<" " << divisa_cambio <<". Esto es correcto?(si/no)"<<std::endl;
            si_no = validar_si_no();
            if(si_no!="si"){
                std::cout << "\033[2J\033[1;1H";
                continue;
            }

            //SOLICITAR MONTO
            while(true) { 
                std::cout << "Indica el monto a cambiar de " << divisa_base << " a " << divisa_cambio << ": " << std::endl;
                std::cin >> valor;
                if (std::cin.fail()) {
                    std::cout << "Ingresa un caracter numerico valido: " << std::endl;
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    continue;
                }
                if (valor <= 0) {
                    std::cout << "Por favor ingresa un valor positivo mayor a 0" << std::endl;
                    continue;
                }

                break;
            }

            // CALCULO
            total = valor * taza;

            // SALIDA
            std::cout << "\n=== CONVERSIÓN DE DIVISAS ===" << std::endl;
            std::cout << "Par: " << divisa_base << "/" << divisa_cambio << std::endl;

            std::cout << std::fixed << std::setprecision(5);
            std::cout << "Tasa: " << taza << std::endl;

            std::cout << std::fixed << std::setprecision(2);
            std::cout << "Monto base: " << formatearNumero(valor) << " " << divisa_base << std::endl;
            std::cout << "Monto convertido: " << formatearNumero(total) << " " << divisa_cambio << std::endl;
            //GUARDAR EN ARCHIVO TXT
            archivo << "\n=== CONVERSIÓN DE DIVISAS ==="  << std::endl;
            archivo << "Par: " << divisa_base << "/" << divisa_cambio << std::endl;
            archivo << std::fixed << std::setprecision(5);
            archivo << "Tasa: " << taza << std::endl;
            archivo << std::fixed << std::setprecision(2);
            archivo << "Monto base: " << formatearNumero(valor) << " " << divisa_base << std::endl;
            archivo << "Monto convertido: " << formatearNumero(total) << " " << divisa_cambio << std::endl;

            //REPETIR PROGRAMA
            std::cout<<"Deseas realizar otra conversion?(si/no): "<<std::endl;
            continuar = validar_si_no();
            if(continuar=="si"){
                std::cout << "\033[2J\033[1;1H";
                continue;
            }else{
                std::cout << "\nRegresando al menú principal...\n" << std::endl;
                archivo<<"\nFIN DE SESION POR OPERACION CONTINUA\n"<<"----------------------------------------"<<std::endl;
                archivo.close();
                sleep(3);
                std::cout << "\033[2J\033[1;1H";
                break;
            }
        }
    }
}

void programa2(){

    std::cout << "\033[2J\033[1;1H";//Linea de codigo usada de IA para scrolear terminal.
    std::cout << std::fixed << std::setprecision(2);//Linea de codigo proporcionada por IA para generar puntos de mil BASADO EN REGION DEL COMPUTADOR.
    
    while(true){
        std::ofstream archivo("sesion.txt", std::ios::app);
        archivo<<"----------------------------------------"<<"\nCAMBIO DE DIVISAS POR SESION\n"<<std::endl;
        // Inicializar estadísticas
        int contador = 0;
        long double total_base = 0;
        long double total_convertido = 0;
        long double min = std::numeric_limits<long double>::infinity(); //[IA START] [IA END]
        long double max = 0;
        long double promedio = 0;

        int ingresar_programa;
        std::cout<<"Hola, Bienvenido al programa de cambio de divisas"<< std::endl;

        std::string divisa_base, divisa_cambio, yes_no, si_no, continuar, entrada;
        long double taza, valor, total;

        //SOlICITAR DIVISA BASE
        while(true){
            std::cout<<"Ingresa la divisa base (USD, EUR, JPY, etc): "<<std::endl; 
            std::cin>>divisa_base;

            for(char &c : divisa_base) c = std::toupper(c);
            bool n=validador(divisa_base);

            if (n) break;
            else{
                std::cout<<"Has ingresado datos incorrectos"<<std::endl; 
                continue;
            }
        }

        //SOLICITAR DIVISA DE CAMBIO 
        while(true){
            std::cout<<"Ingresa la divisa de cambio (USD, EUR, JPY, etc): "<<std::endl; 
            std::cin>>divisa_cambio;

            for(char &c : divisa_cambio) c = std::toupper(c);
            bool n=validador(divisa_cambio);

            if (n){
                ingresar_programa=1;
                break;
            }else{
                std::cout<<"Has ingresado datos incorrectos, ingresalo nuevamente"<<std::endl; 
                continue;
            }
        }

        if(ingresar_programa==1){

            std::cout<<"Has seleccionado "<<divisa_base<<" como tu divisa base y "<<divisa_cambio<< " como tu divisa de cambio, esto es correcto?(si/no) "<<std::endl;
            yes_no = validar_si_no();
            if (yes_no!="si"){
                std::cout << "\033[2J\033[1;1H";
                continue;
            }

            std::cout<<"Perfecto, indica la taza respectiva para " <<divisa_base<<"/"<<divisa_cambio<<std::endl;

            while (true) {
                std::cin >> taza;

                if (std::cin.fail()) {
                    std::cout << "Ingresa un caracter numerico valido." << std::endl;
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    continue;
                }

                if (taza <= 0) {
                    std::cout << "Por favor ingresa una taza positiva y mayor a 0: " << std::endl;
                    continue;
                }

                break;
            }

            std::cout << "\n=== SESIÓN DE CONVERSIÓN ===" << std::endl;
            std::cout << "Par: " << divisa_base << "/" << divisa_cambio << std::endl;
            std::cout << std::fixed << std::setprecision(6);
            std::cout << "Tasa: " << taza << std::endl;

            // CICLO DE CONVERSIONES
            while(true){

                std::cout << "\nIngrese monto a convertir (o 'q' para salir): ";
                std::cin >> entrada;

                if(entrada == "q" or entrada == "Q")
                    break;

                try{       //[IA START]
                    valor = std::stold(entrada); 
                }
                catch(...){
                    std::cout << "Ingresa un valor númerico." << std::endl;
                    continue;
                } //[IA END]

                if(valor <=0){
                    std::cout << "Ingrese un valor positivo." << std::endl;
                    continue;
                }

                total = valor * taza;

                // Actualizar estadísticas
                contador++;
                total_base += valor;
                total_convertido += total;

                if(valor > max) max = valor;
                if(valor < min) min = valor;

                promedio = total_base / contador;

                // Mostrar conversión
                std::cout << "\nConversión número " << contador << ":" << std::endl;
                std::cout << std::fixed << std::setprecision(2);
                std::cout << "Monto base: " << formatearNumero(valor) << " " << divisa_base << std::endl;
                std::cout << "Monto convertido: " << formatearNumero(total) << " " << divisa_cambio << std::endl;

                // Mostrar estadísticas
                std::cout << "\n--- Estadísticas de la sesión ---" << std::endl;
                std::cout << "Total de conversiones: " << contador << std::endl;
                std::cout << "Total base acumulado: " << formatearNumero(total_base) << std::endl;
                std::cout << "Total convertido acumulado: " << formatearNumero(total_convertido) << std::endl;
                std::cout << "Promedio por conversión: " << formatearNumero(promedio) << std::endl;
                std::cout << "Monto mínimo: " << formatearNumero(min) << std::endl;
                std::cout << "Monto máximo: " << formatearNumero(max) << std::endl; 
                //GUARDAR EN TXT 
                archivo << "\nConversión número " << contador << ":" << std::endl;
                archivo << std::fixed << std::setprecision(2);
                archivo << "Monto base: " << valor << " " << divisa_base << std::endl;
                archivo << "Monto convertido: " << total << " " << divisa_cambio << std::endl;
                archivo << "\n--- Estadísticas de la sesión ---" << std::endl;
                archivo << "Total de conversiones: " << contador << std::endl;
                archivo << "Total base acumulado: " << formatearNumero(total_base)<< std::endl;
                archivo << "Total convertido acumulado: " << formatearNumero(total_convertido)<< std::endl;
                archivo << "Promedio por conversión: " << formatearNumero(promedio)<< std::endl;
                archivo << "Monto mínimo: " << formatearNumero(min)<< std::endl;
                archivo << "Monto máximo: " << formatearNumero(max)<< std::endl;
                archivo << "----------------------------------------" << std::endl;
            }

            // RESUMEN FINAL EXACTO
           if(contador > 0){ 
                std::cout << "\n=== RESUMEN FINAL DE SESIÓN ===" << std::endl;
                std::cout << "Par: " << divisa_base << "/" << divisa_cambio << std::endl;
                std::cout << std::fixed << std::setprecision(6);
                std::cout << "Tasa: " << taza << std::endl;
                std::cout << "Total de conversiones realizadas: " << contador << std::endl;
                std::cout << "Total base: " << formatearNumero(total_base) << " " << divisa_base << std::endl;
                std::cout << "Total convertido: " << formatearNumero(total_convertido) << " " << divisa_cambio << std::endl;
                std::cout << "Promedio por conversión: " << formatearNumero(promedio) << " " << divisa_base << std::endl;
                std::cout << "Conversión mínima: " << formatearNumero(min) << " " << divisa_base << std::endl;
                std::cout << "Conversión máxima: " << formatearNumero(max) << " " << divisa_base << std::endl;
                // GUARDAR EN ARCHIVO 
                archivo << "\n=== RESUMEN FINAL DE SESIÓN ===" << std::endl;
                archivo << "Par: " << divisa_base << "/" << divisa_cambio << std::endl;
                archivo << std::fixed << std::setprecision(6);
                archivo << "Tasa: " << taza << std::endl;
                archivo << "Total de conversiones realizadas: " << contador << std::endl;
                archivo << "Total base: " << formatearNumero(total_base) << " " << divisa_base << std::endl;
                archivo << "Total convertido: " << formatearNumero(total_convertido) << " " << divisa_cambio << std::endl;
                archivo << "Promedio por conversión: " << formatearNumero(promedio) << " " << divisa_base << std::endl;
                archivo << "Conversión mínima: "  << formatearNumero(min) << " " << divisa_base << std::endl;
                archivo << "Conversión máxima: " << formatearNumero(max) << " " << divisa_base << std::endl;
                
            }

            std::cout<<"\nDeseas realizar otra conversion?(si/no): "<<std::endl;
            std::cin>>continuar;

            for(char &c : continuar) c = std::tolower(c);

            if(continuar=="si"){
                std::cout << "\033[2J\033[1;1H";
                continue;
            }else{
                archivo << "\nFIN DE SESION\n" << "----------------------------------------"  << std::endl;
                archivo.close();
                std::cout<<"Regresando al menu principal...."<<std::endl;
                std::cout << "\033[2J\033[1;1H";
                sleep(3);
                break;
            }
        }
    }
}

int main(){
    bool controlador=true;
    while(controlador){
        std::ofstream archivo("sesion.txt", std::ios::app);
        archivo<<"Menu de acceso"<<std::endl;
        //variables
        int ingreso_menu;
        std::cout<<"Bienvenido al programa de convertidor de divisas"<<"\nSelecciona un modo\n(1) Continua,\n(2) Sesión,\n(3) Salir"<<std::endl;
        std::cin>>ingreso_menu;
        //Determinar si no es numero
        if(std::cin.fail()){ //[IA START]
           std::cin.clear();
           std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
           std::cout << "Opcion invalida, asegurate de escoger la opcion usando sus numeros.\n";
           std::cout << "Presiona Enter para continuar...";
           std::cin.get();  // solo uno
           std::cout << "\033[2J\033[1;1H";
           continue;
        } //[IA END]
        std::cout << "\033[2J\033[1;1H";
        switch (ingreso_menu)
        {
        case 1:
            archivo<<"Entraste a la opcion 1.(Operacion Continua)"<<std::endl;
            std::cout << "\033[2J\033[1;1H";
            programa1();
            break;
        case 2:
            archivo<<"Entraste a la opcion 2.(Sesion)"<<std::endl;
            std::cout << "\033[2J\033[1;1H";
            programa2();
            break;
        case 3:
            archivo<<"Has salido del programa, regresa pronto :') "<<std::endl;
            std::cout<<"Has salido del programa, regresa pronto :') "<<std::endl;
            controlador=false;
            break;
       default:
            std::cout << "Opcion invalida. Unicamente puedes elegir 1, 2 o 3\n";
            continue;
        }
    }

}

