/*
ENUNCIADO
Una Empresa que vende “productos de seguridad industrial NicTech” nos convoca para la realización
de una App que permita registrar los Pedidos de Artículos de los clientes.

En esta etapa del desarrollo, solo deberemos realizar el módulo “Clientes”

La misma debe permitir:

Gestionar los Clientes
Dar de alta el cliente (el código del cliente se obtiene sumando 100 al índice del Array).
Dar de Baja los clientes x código de cliente.
Modificar los clientes, ingresar el código, mostrarlo y editarlo.
Listar los Clientes.
Listar todos los Clientes.
Buscar un Clientes x código y mostrarlo (imprimir cartel de no encontrado).
.  Todo esto mediante un Menú, Modularizando en Funciones, utilizando Archivos, arreglos y estructuras.


NOTA IMPORTANTE: (personal no parte del enunciado)
    por una cuestion de simplificar el manejo de datos se usaran solo strings simples sin espacios
    ej nombre valido = Juan, no valido Juan Perez
    lo mismo que el nombre de la ciudad: valido = Mardel y no valido = Mar del plata

    el manejo de nombres con mas de una palabra se puede implementar pero hay que guardar los datos 
    al archivo de alguna manera especial para que no se pierda la informacion.
    ahora para simplificar esta guardados con una separacion de espacio entre los campos de la estructura
    ej
    codigo nombre ciudad
    123 Juan Mardel

    */

#include <iostream>                 // libreria para cin y cout
#include <fstream>                  // libreria para manejo de archivos
#include <sstream>
#include <string>
using namespace std;                // simplifica el uso de cout y cin para no usar std::cout y std::cin

const int MAX_CUSTOMERS = 100;  // Constante global para el maximo de clientes (se usara para el array)

typedef struct{         // Estructura de Clientes (codigo, nombre, ciudad)
    int code;
    string name;
    string city;
}Customer;

typedef struct{    // Estructura de Contenedor (array de clientes y numero de clientes=tamano del array)
    Customer customers[MAX_CUSTOMERS];
    int cont;
}Container;

void loadFromfile(Container &CustomerList);    // Carga los datos del archivo al contenedor (array)
void saveToFile(Container &CustomerList);      // Guarda los datos del contenedor (array) al archivo
void addCustomer(Container &CustomerList);     // Función para dar de alta un cliente
void removeCustomer(Container &CustomerList);  // Función para dar de baja un cliente
void updateCustomer(Container &CustomerList);  // Función para modificar un cliente
void listCustomers(Container const &CustomerList);   // Función para listar todos los clientes (se le pasa como const para que no se pueda modificar)
void findCustomer(Container const &CustomerList);    // Función para buscar un cliente por código e imprimirlo (Se le pasa como const para que no se pueda modificar)
void clearConsole();                        // Limpia la consola
void pauseConsole(string txt = "Presione ENTER para continuar...");                        // Pausa la consola y pide presionar ENTER para continuar
bool fileEmpty(ifstream &file);

int main() 
{   
    clearConsole();                         // Limpia la consola todos lo usos de clearConsole() y pauseConsole() usados en el 
                                            //  programa son de uso opcional y estan puesto para una mejor presentación.        
    
    int menu;                               // variable usada para el menú principal
    
    Container CustomerList;                    // variable para el contenedor (podria haber tenido cualquier otro nombre nomina, CustomerList) 
    CustomerList.cont = 0;             // inicializo la cantidad de clientes a cero
    
    loadFromfile(CustomerList);                // Carga los datos del archivo al contenedor CustomerList

    do 
    {
        cout << "-------------- MENU --------------" << endl;
        cout << "1. Dar de alta un cliente" << endl;
        cout << "2. Dar de baja un cliente" << endl;
        cout << "3. Modificar un cliente" << endl;
        cout << "4. Listar todos los clientes" << endl;
        cout << "5. Buscar un cliente por codigo" << endl;
        cout << "6. Salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> menu;                                    // lee una opcion del menu (un entero)
        cout << endl;
        switch (menu)                                    // el SWITCH evalua el valor del entero y ejecuta el CASE correspondiente
        {
            case 1: 
            {   addCustomer(CustomerList);              // llama a la funcion para dar de alta un cliente pasandole la variable CustomerList
                break;
            }
            case 2: 
            {   removeCustomer(CustomerList);          // llama a la funcion para dar de baja un cliente pasandole la variable CustomerList
                break;
            }
            case 3: 
            {   updateCustomer(CustomerList);          // llama a la funcion para modificar un cliente pasandole la variable CustomerList
                break;
            }
            case 4: 
            {   listCustomers(CustomerList);           // llama a la funcion para mostrar todos los clientes pasandole la variable CustomerList
                break;
            }
            case 5: 
            {   findCustomer(CustomerList);            // llama a la funcion para buscar un cliente por código e imprimirlo (Se le pasa como const para que no se pueda modificar)
                break;
            }
            case 6: 
            {   saveToFile(CustomerList);              // Guarda los datos de la CustomerList al archivo
                cout << "Saliendo..." << endl;          // esta operacion se realiza antes de salir del programa
                break;
            }
            default:                                    // la opcion de default es para cuando el usuario ingresa una opcion que no
            {   cout << "Opción invalida" << endl;      // corresponde a ningun CASE que hallamos definido
                pauseConsole("Presione Enter para continuar...");
                break;
            }
        }

    }while (menu != 6);                                 // mientras la variable menu no sea igual a 6, el programa se ejecuta 
    return 0;                                           // si es igual a 6 termina el bucle do-while
} 

void loadFromfile(Container &CustomerList) 
{
    ifstream file("customers.txt", ios::binary | ios::ate);
    
    cout << "\nSe intenta leer el archivo..." << endl;
    pauseConsole();
    clearConsole();
    
    if (file.is_open()) 
    {
        
        if (!fileEmpty(file)){
            file.close();
            ifstream file("customers.txt");
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string field;
                int code;

                Customer nuevoEmpleado;

                // Leer el código
                getline(ss, field, ',');
                code = stoi(field);
                CustomerList.customers[CustomerList.cont].code = code;
                
                // Leer el nombre
                getline(ss, field, ',');
                CustomerList.customers[CustomerList.cont].name = field;

                // Leer el puesto
                getline(ss, field, ',');
                CustomerList.customers[CustomerList.cont].city = field;
                
                CustomerList.cont++;                       // cada vez que leo un elemento, aumento el cont de clientes
            }
            cout << "\nSe han encontrado " << CustomerList.cont << " clientes."<< endl;
            pauseConsole();
            clearConsole();
        }else {
            cout << endl << "El archivo esta vacio." << endl;
            pauseConsole();
            clearConsole();
        }

        file.close();
    } 
    else 
    {
        cout << "No se pudo abrir el archivo." << endl;                     // si no se pudo abrir el archivo porque no existe, crea uno nuevo
        cout << "Desea crear un nuevo archivo? (1 = SI, 0 = NO)" << endl;   // pregunta si se quiere crear un nuevo archivo
        int newFileOption;                                             // variable para guardar la respuesta
        cin >> newFileOption;
        if (newFileOption == 1)                                        // si la respuesta es 1 crea el archivo
        {       
            ofstream file("customers.txt");
            file.close();
            cout << "Archivo creado correctamente." << endl;
        } 
        else                                                                // si la respuesta es 0 termina el programa
        {
            cout << "Saliendo (sin crear archivo nuevo)..." << endl;
            pauseConsole();
            exit(1);                                                        // sale del programa devolviendo un 1 marcando error
        }
        
    }
}   

void saveToFile(Container &CustomerList)
{
    ofstream file("customers.txt");
    if (file.is_open())                         // funcion interna del fstream para abrir el archivo devuelve true si se pudo abrir
    {   
        if (CustomerList.cont != 0) // si la lista es distinta de cero entonces procedo a guardar
        {
            /* Guardo los clientes al archivo menos el ultimo, y luego 
            guardo el ultimo sin usar endl para que no agregue una fila mas al archivo*/
            for (int i = 0; i < CustomerList.cont-1; i++) 
            {
                file << CustomerList.customers[i].code << "," << CustomerList.customers[i].name << "," << CustomerList.customers[i].city << ","<< endl;
            }
            /* Guardo el ultimo cliente sin endl para que no agregue una fila mas al archivo*/
            file << CustomerList.customers[CustomerList.cont-1].code << "," << CustomerList.customers[CustomerList.cont-1].name << "," << CustomerList.customers[CustomerList.cont-1].city << ",";
            file.close();
        }
        else        // si la lista es cero no hay clientes para guardar por lo que no se hace nada para evitar guardar basura
        {
            file.close();
        }
    }
    else            // si el archivo no se pudo abrir para escritura al dar file.is_open() = false
    {
        cout << "No se pudo Guardar el archivo." << endl;
        pauseConsole();
    }
}

void addCustomer(Container &CustomerList) 
{   
    clearConsole();
    Customer newCustomer;                   // se crea un nuevo cliente

    if (CustomerList.cont == 0)    // si hay 0 clientes empieza con el 100
    {   
        newCustomer.code = 100;
    }
    else
    {
        newCustomer.code = (CustomerList.customers[CustomerList.cont - 1].code) + 1;  // si ya hay clientes se le suma 1 al ultimo
    }
    
    if (!(CustomerList.cont >= MAX_CUSTOMERS))   // se verifica que haya lugar para el nuevo cliente
    {   
        cin.sync();
        cout << "\nIngrese el nombre del cliente: ";
        getline (cin,newCustomer.name); 
        cout << "Ingrese la ciudad del cliente: ";
        getline(cin,newCustomer.city);
                
        CustomerList.customers[CustomerList.cont] = newCustomer;        
        CustomerList.cont++;
        cout << "Cliente agregado correctamente." << endl;
        pauseConsole();
        clearConsole();
    } 
    else   // al ser la cantidad de cont mayor o igual a MAX_CUSTOMERS no se puede agregar mas clientes
    {
        cout << "No se pueden agregar mas clientes. Maximo alcanzado." << endl;
        pauseConsole();
        clearConsole();
    }
}

void removeCustomer(Container &CustomerList) 
{
    int code;                                                   // variable para pedir el codigo que se quiere borrar
    cout << "\nIngrese el codigo del cliente a dar de baja: ";    
    cin >> code;    
    clearConsole();
    for (int i = 0; i < CustomerList.cont; i++)        // busca el cliente en la lista desde 0 hasta la cantidad de clientes
    {
        if (CustomerList.customers[i].code == code)            // si lo encuentro
        {
            for (int j = i; j < CustomerList.cont - 1; j++)     // este for recorre desde el lugar que se encontro (i) ahora asignado a j hasta la cantidad total de clientes menos 1
            {
                CustomerList.customers[j] = CustomerList.customers[j + 1];  // se le asigna a la posicion que se borro el valor de la posicion siguiente
            }
            CustomerList.cont--;           // se le resta uno a la cantidad de clientes
            cout << "\nCliente eliminado correctamente." << endl;
            pauseConsole();
            clearConsole();
            return;
        }
    }
    cout << "\nCliente no encontrado." << endl;
    pauseConsole();
    clearConsole();
}   

void updateCustomer(Container &CustomerList) 
{
    int code;                                       // variable para buscar el cliente por su codigo
    cout << "\nIngrese el codigo del cliente a modificar: ";
    cin >> code;
    clearConsole();
    for (int i = 0; i < CustomerList.cont; i++)    // se busca el cliente desde 0 hasta la cantidad de clientes 
    {
        if (CustomerList.customers[i].code == code)    // si lo encuentra se imprime y luego se piden los datos para sobreescibirlos
        {
            cout << "El cliente a modificar es: " << endl;
            cout << endl;
            cout << "Codigo: " << CustomerList.customers[i].code << endl;
            cout << "Nombre: " << CustomerList.customers[i].name << endl;
            cout << "Ciudad: " << CustomerList.customers[i].city << endl;
            cout << endl;
            
            cin.sync();
            cout << "Ingrese el nuevo nombre del cliente: ";
            getline(cin, CustomerList.customers[i].name);
            cout << "Ingrese la nueva ciudad del cliente: ";
            getline(cin,CustomerList.customers[i].city);
            cout << "Cliente modificado correctamente." << endl;
            pauseConsole();
            clearConsole();
            return;                             // sale de la funcion (sin retornar nada)
        }
    }
    cout << "Cliente no encontrado." << endl;
    pauseConsole();
    clearConsole();
}

void listCustomers(Container const &CustomerList) 
{
    clearConsole();
    if (CustomerList.cont != 0)       // revisa que haya clientes
    {
        cout << endl <<"Lista de clientes:" << endl;
        for (int i = 0; i < CustomerList.cont; i++)        // recorre todos los clientes imprimiendo en cada iteracion de i
        {
            cout << "-------------------------------------" << endl;
            cout << "Codigo: " << CustomerList.customers[i].code <<   "\nNombre: "  << CustomerList.customers[i].name << "\nCiudad: " << CustomerList.customers[i].city << endl;
        }
        cout << "-------------------------------------" << endl;
    } 
    else                    // al no haber clientes se informa
    {
        cout << endl << "No hay clientes registrados." << endl;
        pauseConsole();
        clearConsole();
    }
}

void findCustomer(Container const &CustomerList) 
{
    int code;                                                    // variable para buscar el código del cliente
    cout << endl << "Ingrese el codigo del cliente a buscar: ";
    cin >> code;
    for (int i = 0; i < CustomerList.cont; i++)         // bucle para buscar el cliente desde 0 hasta la cantidad de clientes 
    {                                                            // cont es la variable que indica la cantidad de clientes   
        if (CustomerList.customers[i].code == code) 
        {
            cout << endl << "Cliente encontrado: " << endl;
            cout << "Codigo: " << CustomerList.customers[i].code << endl;
            cout << "Nombre: " << CustomerList.customers[i].name << endl;
            cout << "Ciudad: " << CustomerList.customers[i].city << endl << endl;
            pauseConsole();
            clearConsole();
            return;                                              // sale del bucle si encuentra el cliente. este return no devuelve nada 
        }                                                        // ya que la funcion es void
    }
    cout << endl << "Cliente no encontrado." << endl;
    pauseConsole();
    clearConsole();
}

void clearConsole()                                         // Función para limpiar la consola
{                                                           // Implementada por el Profesor Gabriel Ferreira
    #ifdef __unix__                                         // para funcionar en cualquier sistema operativo
        system("clear");
    #elif __APPLE__
        system("clear");
    #elif defined(_WIN32) || defined(WIN64)
        system("cls");
    #endif
}

void pauseConsole(string txt)                                         // Función para pausar la consola
{
cout << "\n" << txt << endl;
cin.sync();                                               // Limpia el buffer
cin.get();                                                // espera a que el usuario presione enter
}  

bool fileEmpty(ifstream &file) {
    
    // Obtener la posición actual que será la longitud del archivo
    streampos fileSize = file.tellg();
    
    
    // Comprobar si el tamaño del archivo es 0
    return fileSize == 0;
}