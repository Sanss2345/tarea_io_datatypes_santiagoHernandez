#include <iostream>
#include <string>
#include <cctype>//libreria usada para la funcion validar que tenga caracteres alfabeticos(IA)
#include <iomanip> 
#include <locale>
#include <chrono>//Libreria usada para determinar tiempo y realizar el timestamp (IA)
#include <ctime>//Libreria usada para determinar tiempo y realizar el timestamp (IA)
#include <unistd.h> //Libreria usada para hacer esperar(IA)
#include <vector>

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
int main(){
    std::cout << "\033[2J\033[1;1H";//Linea de codigo usada de IA para scrolear terminal.
    std::cout.imbue(std::locale(""));//Linea de codigo proporcionada por IA para generar puntos de mil BASADO EN REGION DEL COMPUTADOR.
    std::vector<long double> historial_totales; //[IA START]--vector para crear datos de cambio---[IA END]
    while(true){
        int  ingresar_programa;
        std :: cout<<"Hola, Bienvenido al programa de cambio de divisas"<< std::endl;
        std::string divisa_base, divisa_cambio, par_cotizado, yes_no, si_no, continuar, finalizar_programa, par_invertido, valor_extra;
        long double taza, valor, total, taza_invertida;
        //SOlICITAR DIVISA BASE
        while(true){
            std :: cout<<"Ingresa la divisa base (USD, EUR, JPY, etc): "<<std::endl; std::cin>>divisa_base;
            for(char &c : divisa_base) c = std::toupper(c);//linea de codigo sacada de IA, transforma todo a upper
            bool n=validador(divisa_base); //VERIFICAR CONDICIONES 
            if (n){
                break;
            }else{std::cout<<"Has ingresado datos incorrectos"<<std::endl; continue;} //SOLICITAR NUEVAMENTE
        }
        //SOLICITAR DIVISA DE CAMBIO 
        while(true){
            std :: cout<<"Ingresa la divisa de cambio (USD, EUR, JPY, etc): "<<std::endl; std::cin>>divisa_cambio;
            for(char &c : divisa_cambio) c = std::toupper(c);//linea de codigo sacada de IA, transforma todo a upper
            bool n=validador(divisa_cambio);
            if (n){
                ingresar_programa=1;
                break;
            }else{std::cout<<"Has ingresado datos incorrectos, ingresalo nuevamente"<<std::endl; continue;} //SOLICITAR NUEVAMENTE
        }
        if(ingresar_programa==1){
            while(true){
                //VERIFICAR DATOS
                std::cout<<"Has seleccionado "<<divisa_base<<" como tu divisa base y "<< divisa_cambio<< " como tu divisa de cambio, esto es correcto?(si/no) "<<std::endl;
                std::cin>>yes_no;
                std::string divi= divisa_base +"/"+ divisa_cambio;
                for(char &c : yes_no) c = std::tolower(c);// [AI-START][AI-END] -----linea de codigo sacada de IA, transforma todo a lower
                //REPETIR EN CASO DE ERROR Y EN CASO DE CONTINUAR, SEGUIR EL PROCESO
                if (yes_no=="si"){
                    std::cout<<"Perfecto, indica la taza respectiva para "<<divi<<" es decir, indica cuanto vale 1 "<< divisa_base <<" en "<< divisa_cambio<< std::endl;
                    while (true) {
                        std::cin >> taza;
                        if (std::cin.fail()) {
                            // [AI-START]
                            std::cout << "Ingresa un caracter numerico valido." << std::endl;
                            std::cin.clear();
                            std::cin.ignore(10000, '\n');
                            // [AI-END]
                            continue;
                        }
                        if (taza <= 0) {
                            std::cout << "Por favor ingresa una taza positiva y mayor a 0: " << std::endl;
                            continue;
                        }
                        break;
                    }
                    std::cout << std::fixed << std::setprecision(10); //[AI-START][AI-END] --- informacion utilizada de IA para usar libreria iomanip
                    std::cout<<"Has indicado que 1 "<<divisa_base<<" equivale a "<< taza<<" " << divisa_cambio <<". Esto es correcto?(si/no)"<<std::endl;
                    std::cin>>si_no;
                    for(char &c : si_no) c = std::tolower(c); //[AI-START][AI-END]---linea de codigo sacada de IA, transforma todo a lower
                    while(si_no=="no"){
                        std::cout <<"Ingresa nuevamente la taza: "<<std::endl;
                        while (true) {
                            std::cin >> taza;
                            if (std::cin.fail()) {
                                // [AI-START]
                                std::cout << "Ingresa un caracter numerico valido: " << std::endl;
                                std::cin.clear();
                                std::cin.ignore(10000, '\n');
                                // [AI-END]
                                continue;
                            }
                            if (taza <= 0) {
                                std::cout << "Por favor ingresa una taza positiva y mayor a 0: " << std::endl;
                            continue;
                            }
                            break;
                        }
                        std::cout<<"Has indicado que 1 "<<divisa_base<<" equivale a "<< taza<<" " << divisa_cambio <<". Esto es correcto?(si/no)"<<std::endl;
                        std::cin>>si_no;
                    }
                }else{
                    finalizar_programa="1";
                    break;
                    //NO ESTAR DE ACUERDO REPETIR PROGRAMA DESDE 0 
                }
                //PARTE FINAL DEL PROGRAMA
                while(true) { 
                    std::cout << "Indica el monto a cambiar de " << divisa_base << " a " << divisa_cambio << ": " << std::endl;
                    std::cin >> valor;

                    // Validación de entrada numérica (Robustez)
                    if (std::cin.fail()) {
                        std::cout << "Ingresa un caracter numerico valido: " << std::endl;
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');
                        continue;
                    }
                    
                    // Validación de valores positivos 
                    if (valor < 0) {
                        std::cout << "Por favor ingresa un valor positivo" << std::endl;
                        continue;
                    } else if (valor == 0) {
                        std::cout << "Por favor ingresa un valor diferente a 0 " << std::endl;
                        continue;
                    }

                    // Cálculo y almacenamiento en la lista dinámica
                    total = valor * taza;
                    historial_totales.push_back(total); // Se guarda en el vector  [AI-START][AI-END]

                    // Preguntar si desea agregar otro monto en este mismo proceso
                    std::string valor_extra;
                    std::cout << "¿Deseas convertir otro monto con la misma tasa? (si/no): "<<std::endl;
                    std::cin >> valor_extra;
                    for(char &c : valor_extra) c = std::tolower(c); //[AI-START][AI-END]

                    if (valor_extra == "si") {
                        continue; // Vuelve al inicio del while(true) para pedir otro monto
                    } else {
                        break; // Sale de este bucle para generar el reporte final
                    }
                }
                taza_invertida=1.0/taza;
                par_invertido=divisa_cambio+"/"+divisa_base;
                auto ahora = std::chrono::system_clock::now(); //[AI-START][AI-END](proceso para realizar timestamp)
                std::time_t t_c = std::chrono::system_clock::to_time_t(ahora);//Fin IA.
                //rREPORTE FINAL
                std::cout << "\n********************************************" << std::endl;
                std::cout << "       REPORTE FINAL [MARKET SNAPSHOT]      " << std::endl;
                std::cout << "********************************************" << std::endl;
                //PRESICION DE DECIMALES DE LA TAZA
                std::cout << std::fixed << std::setprecision(10);
                std::cout << "Divisa Base:      \t" << divisa_base << std::endl;
                std::cout << "Divisa Cotizada:  \t" << divisa_cambio << std::endl;
                std::cout << "Taza de cotizacion:\t" << taza << std::endl;
                std::cout << "Taza invertida:   \t" << taza_invertida << " (" << par_invertido << ")" << std::endl;
                std::cout << "--------------------------------------------" << std::endl;
                std::cout << "Resultado de las conversiones:" << std::endl;
                
                std::cout << std::fixed << std::setprecision(2); // PRESICION DE DECIMALES DE LA TAZA
                for (size_t i = 0; i < historial_totales.size(); i++) { //[IA START]
                    long double v_orig = historial_totales[i] / taza;
                    std::cout << " - " << v_orig << " " << divisa_base           /*ESTE BUCLE CUMPLE LA FUNCION DE IMPRIMIR 
                    TODAS LAS CONVERSIONES DE TODOS LOS MONTOS QUE EL USUARIO INGRESO.*/
                              << " equivalen a " 
                              << historial_totales[i] << " " << divisa_cambio << std::endl;
                } //[IA END]
                std::cout << "--------------------------------------------" << std::endl;

                std::cout << "Fecha/Hora:       \t" 
                          << std::put_time(std::localtime(&t_c), "%d/%m/%Y %H:%M:%S") << std::endl;
                
                std::cout << "********************************************" << std::endl;
                std::cout << "               FIN REPORTE                  " << std::endl;
                std::cout << "********************************************" << std::endl;
                std::cout<<"Deseas realizar otra conversion?(si/no): "<<std::endl;
                std::cin>>continuar;
                for(char &c : continuar) c = std::tolower(c);// [AI-START][AI-END] -------transforma todo a lower
                break;
            }
            if(continuar=="si"){
                std::cout << "\033[2J\033[1;1H"; // [AI-START][AI-END] -------Linea de codigo para scrolear terminal.
                 historial_totales.clear();  // [AI-START][AI-END] ----------Limpia los resultados anteriores
                continue;;
            }else if(finalizar_programa=="1"){
                std::cout<<"Se reiniciara el programa, indica nuevamente los datos"<<std::endl;
                sleep(2);
                std::cout << "\033[2J\033[1;1H";//[AI-START][AI-END] -------Linea de codigo usada de IA para scrolear terminal.
                continue;
            }else{break;}
        }else{continue;}   
    }
}