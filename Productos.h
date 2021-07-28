#include <stdlib.h>
#include <iostream>
#include <mysql.h>

using namespace std;

class Compras {
    public:
        string id_codigo_barra;
        string id_producto;
        string nombre; 
        string precio_compra;
        string id_proveedor;
        char *id;
    public:
        Compras ();
};
Compras::Compras (){
 
}
