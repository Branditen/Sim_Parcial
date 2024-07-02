#include <iostream>
#include <string>
using namespace std;

struct estructura{
    int numero;
    string texto;
};

int main(){
    estructura estructuraV;
    estructura estructuraV2;

    estructuraV.texto = "Hola como estas";
    estructuraV2.numero = 0;
    return 0;
}