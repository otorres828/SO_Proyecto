/*
PARA INSTALAR LA LIBRERIA DE MYSQL, EJECUTAR EN TERMINAL
-$ sudo apt-get install libmysqlclient.dev

Para compilar:
-$ g++ -o plus $(mysql_config --cflags) principal.cpp $(mysql_config --libs)
-$ ./plus

para compilar con mysql e hilos
-$ g++ -o plus $(mysql_config --cflags) principal.cpp $(mysql_config --libs) -pthread
-$ ./plus

//COMO EL PROYECTO TIENE YA CREADO EL EJECUTABLE, EJECUTAR DIRECTAMENTE: 
-$ ./plus

*/
#include <iostream>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include <cstring>
#include <string.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include "conexion.h"
#include "Productos.h"
#include <pthread.h>
using namespace std;

Conexion objeto = Conexion();

void proveedores(){

    int resp=3;
    char c1[100],c2[200];
    char *c3;
    while (resp!=4){
        system("clear");
        cout<<"\t------MENU DE PROVEEDORES---------"<<endl;
        cout<<"\t1: INTRODUCIR PROVEEDOR"<<endl;
        cout<<"\t2: ELIMINAR PROVEEDOR"<<endl;
        cout<<"\t3: VER LISTA DE PROVEEDORES"<<endl; 
        cout<<"\t4: REGRESAR"<<endl;
        cin>>resp;
        system("clear");
        if(resp==1){                    
            system("clear");        
            cin.ignore(); 
            cout << "nombre del proveedor: ";
            cin.getline(c1,80);     
            cout << "descripcion del proveedor:  ";    
            cin.getline(c2,200);
            objeto.introducir(c1,c2,c3,2); 
        }
        if(resp==2){
            cin.ignore(); 
            cout<<"INTRODUZCA EL ID DEL PROVEEDOR QUE QUIERE ELIMINAR: ";
            cin.getline(c1,80); 
            objeto.eliminar(c1,2);
        }
        if(resp==3){
            system("clear");
            objeto.mostrar_proveedores();
        }
        if(resp==4)
            system("clear");

    }  
}
void gestion_almacen(){
    int resp=4,i;
    char c1[100],c2[100],c3[100],p1[100];
    while (resp!=5){
        system("clear");
        cout<<"\t------MENU DE ALMACEN---------"<<endl;
        cout<<"\t1: INTRODUCIR PRODUCTO"<<endl;
        cout<<"\t2: ELIMINAR PRODUCTO"<<endl;
        cout<<"\t3: VER STOCK"<<endl; 
        cout<<"\t4: PROVEEDORES"<<endl; 
        cout<<"\t5: REGRESAR"<<endl;     
        cin>>resp;
        system("clear");
        if(resp==1){               
            cin.ignore(); 
            cout << "nombre producto: ";
            cin.getline(c1,80);     
            cout << "precio:  ";    
            cin.getline(c2,80); 
            cout << "descripcion:  ";
            cin.getline(c3,80);
            
            objeto.introducir(c1,c2,c3,1); 

        }
        if(resp==2){
            cin.ignore(); 
            cout<<"INTRODUZCA EL ID DEL PRODUCTO QUE QUIERE ELIMINAR: ";
            cin.getline(p1,80); 

            objeto.eliminar(p1,1);
        }
        if(resp==3){
            system("clear");
            objeto.mostrar_productos();
        }
        if(resp==4){
            system("clear");
            proveedores();
        }
        if(resp==5){
            system("clear");
        }

    }
    
}
void datos_compra(string c2,string c3,string c4,string c5,string c6){
        char const* codibobarra = c2.c_str();
        char const* idproducto = c3.c_str();
        char const* nombre_c = c4.c_str();
        char const* precio = c5.c_str();
        char const* idproveedor = c6.c_str();      
        objeto.compra(codibobarra,idproducto,nombre_c,precio,idproveedor);
}
void compras(){
    char c1[100],c2[100],c3[100],p1[100];
    system("clear");
    int resp=1;
    while (resp!=4){
        cout<<"\t------MENU DE COMPRAS---------"<<endl;
        cout<<"\t1: VER HISTORIAL DE COMPRAS"<<endl;
        cout<<"\t2: ELIMINAR COMPRAS"<<endl;
        cout<<"\t3: CARGAR UNA COMPRA"<<endl; 
        cout<<"\t4: REGRESAR"<<endl; 
        cin>>resp;cin.ignore(); 
        system("clear");
        if(resp==1){
            objeto.mostrar_compras();          
        }
        if(resp==2){
            objeto.eliminar_historial();
        }
        if(resp==3){
            char consulta[500];
            string s;
            string str;
            cout<<"Ingrese el nombre del archivo con extension .csv: ";
            cin>>s;
            system("clear");
            ifstream archivo(s);
            string linea;
            char delimitador = ',';
            Compras compra = Compras();
            // Leemos la primer línea para descartarla, pues es el encabezado
            getline(archivo, linea);
            // Leemos todas las líneas
            cout << "CB\t\tId Producto\tNombre\t\t\tPrecio de Compra\tId Proveedor" << endl ;

            while (getline(archivo, linea)){
                //GENERA EL NUMERO DE FACTURA
               
                stringstream stream(linea); // Convertir la cadena a un stream
                // Extraer todos los valores de esa fila
                getline(stream, compra.id_codigo_barra, delimitador);
                getline(stream, compra.id_producto, delimitador);
                getline(stream, compra.nombre, delimitador);
                getline(stream, compra.precio_compra, delimitador);
                getline(stream, compra.id_proveedor, delimitador);
                //IMPRIME EN CONSOLA 
                cout <<  compra.id_codigo_barra ;
                cout << "\t\t" << compra.id_producto ;
                cout << "\t\t" << compra.nombre ;
                cout << "\t\t" << compra.precio_compra ;
                cout << "\t\t\t" << compra.id_proveedor ;
                cout<<endl;
                //INTRODUCE LOS DATOS EN LA BASE DE DATOS TABLA
                datos_compra(compra.id_codigo_barra,compra.id_producto,compra.nombre,compra.precio_compra,compra.id_proveedor);
            }
            archivo.close();
            cout<<"\nSE HA CARGADO EXITOSAMENTE LA COMPRA"<<endl;
            cout<<"\npresione enter para continuar"<<endl;
            cin.get();cin.ignore();
            system("clear");
        }
    }   
}
void vender_a_un_cliente(char *c){
    int cuenta = 0;
    char c1[100];
    char *c2;
    char c3;
    while(c3!='n'){
        system("clear");
        cout<<"\tCliente: "<<c<<endl;
        cout<<"\tSu cuenta es: "<<cuenta<<endl;
        cout<<"\nintroduzca el cod de barra: ";
        cin.getline(c1,20);    
        int var = objeto.verificar(c1,2);
        if(var==1){
            cuenta= cuenta + objeto.verificar(c1,3);
            c2=objeto.obtener_nombre(c1);
            objeto.introducir(c,c2,c,4);
            objeto.eliminar(c1,4);

        }else{
            cout<<"El producto no esta disponible"<<endl;

        }
        cout<<"Desea introducir otro producto? s=si n=no: ";
        cin>>c3;cin.ignore();
    }
    system("clear");
    cout<<"\tSu cuenta total es: "<<cuenta<<endl;
    cout<<"\npresione enter para continuar";
    cin.get();  
}
void ventas(){
    char c1[100],c2[100],c3[100];
    system("clear");
    int resp=1;
    while (resp!=7  ){
        system("clear");
        cout<<"\t------MENU DE VENTAS---------"<<endl;
        cout<<"\t1: VENDER A UN CLIENTE"<<endl;
        cout<<"\t2: REGISTRAR CLIENTE"<<endl;
        cout<<"\t3: ELIMINAR CLIENTE"<<endl;   
        cout<<"\t4: VER LISTA DE CLIENTES"<<endl;  
        cout<<"\t5: VER HISTORIAL DE VENTAS"<<endl;  
        cout<<"\t6: ELIMINAR HISTORIAL DE VENTAS"<<endl; 
        cout<<"\t7: REGRESAR"<<endl; 
        cin>>resp;cin.ignore(); 
        system("clear");
        if(resp==1){
            cout << "ingrese la cedula del cliente: ";
            cin.getline(c1,80);    
            int ver = objeto.verificar(c1,1); 
            
            //si ver == 1 existe un cliente, sino no 
            if(ver==1) 
                vender_a_un_cliente(c1);
            else { 
                cout<<"no se encontro cliente con el numero de cedula: "<<c1<<endl;
                cout<<"por favor registre a un nuevo cliente";
                cout<<"\n\npresione enter para continuar"<<endl;
                cin.get();  
                system("clear");         
            }       
        }
        if(resp==2){
            cout << "nombre del cliente: ";
            cin.getline(c1,80);    
            cout << "ingrese numero de cedula:  ";    
            cin.getline(c2,80);       
            cout << "ingrese telefono:  ";    
            cin.getline(c3,80);          
            objeto.introducir(c1,c2,c3,3);            
        }
        if(resp==3){
            cout<<"INTRODUZCA EL ID DEL PROVEEDOR QUE QUIERE ELIMINAR: ";
            cin.getline(c1,80); 
            objeto.eliminar(c1,3);
        }       
        if(resp==4){
            objeto.mostrar_cliente();
        }
        if(resp==5){
            objeto.lista_ventas();
        }
        if(resp==6){
            objeto.eliminar_historial_ventas();
        }
            
    }   
}

int main(){
    int resp=1;
    while (resp!=4  ){
        system("clear");
        cout<<"\t------MENU PRINCIPAL---------"<<endl;
        cout<<"\t1: GESTION DE ALMACEN"<<endl;
        cout<<"\t2: COMPRAS"<<endl;
        cout<<"\t3: VENTAS"<<endl;   
        cout<<"\t4: SALIR"<<endl;   
        cin>>resp;
        if(resp==1)
            gestion_almacen();
        if(resp==2)
            compras();
        if(resp==3)
            ventas();
    }
   return 0;
}
