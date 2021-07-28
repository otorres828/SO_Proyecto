#include <stdlib.h>
#include <iostream>
#include <mysql.h>

using namespace std;

class Conexion {  
    public: 
        MYSQL *conn;
        MYSQL_ROW filas;
        MYSQL_RES *resultado;
        char *id;
        
    public:
        Conexion();
        void introducir(char*,char*,char*,int);
        void eliminar(char*,int);
        void eliminar_historial();
        void eliminar_historial_ventas();
        void mostrar_productos();
        void mostrar_proveedores();
        void mostrar_cliente();
        void mostrar_compras();
        void lista_ventas();
        void compra(const char*, const char*,const char*,const char*,const char*);    
        int verificar(char*,int); 
        char *obtener_nombre(char *);
        char *obtener_cantidad(const char *);
};

Conexion::Conexion (){
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,"mysql-41215-0.cloudclusters.net","admin","Eaav68X2","clientes",19946,NULL,0);
    if(conn)
        cout<<"Database CONECTADA."<<endl;
    else   
        cout<<"FALLA EN CONEXION DE LA BASE DE DATOS."<<endl;
}

void Conexion::introducir(char *c1, char* c2,char *c3,int i){  
    char consulta[1000];
    if(i==1){
        sprintf(consulta,"INSERT INTO productos(nombre,precio,descripcion,cantidad)VALUES('%s','%s','%s','%i')",c1,c2,c3,0);
    }
    if(i==2){
        sprintf(consulta,"INSERT INTO proveedores(nombre,descripcion)VALUES('%s','%s')",c1,c2);
    }
    if(i==3){
        sprintf(consulta,"INSERT INTO cliente(nombre,cedula,telefono)VALUES('%s','%s','%s')",c1,c2,c3);
    }
    if(i==4){
        sprintf(consulta,"INSERT INTO ventas(cedula,nombrepro,fecha)VALUES('%s','%s',CURRENT_TIMESTAMP())",c1,c2);
    }   
    if (!mysql_query (conn, consulta)) {
        if(i!=4){
          cout<<"DATO INTRODUCIDO EXITOSAMENTE"<<endl;
          cout<<"\npresione enter para continuar"<<endl;
          cin.get();
          system("clear");   
        }
  
    }
}

void Conexion::compra(const char*c2,const char *c3,const char *c4,const char* c5,const char *c6){
    
    char consulta[1000];
    char c1[1000];
    char update[1000];
    char *cantidad=obtener_cantidad(c3);
    int cant = atoi(cantidad);

    sprintf(consulta,"INSERT INTO compras(fecha,codbarra,idproductos,nombre,precio_compra,idProveedores)VALUES(CURRENT_TIMESTAMP(),'%s','%s','%s','%s','%s')",c2,c3,c4,c5,c6);
    sprintf(c1,"INSERT INTO historial_compra(fecha,codbarra,idproductos,nombre,precio_compra,idProveedores)VALUES(CURRENT_TIMESTAMP(),'%s','%s','%s','%s','%s')",c2,c3,c4,c5,c6);
    mysql_query (conn, c1);
    if (mysql_query (conn, consulta)) {
       cout<<"ERROR AL INTRODUCIR"<<endl;
    }else{
       cant=cant+1;
       sprintf(update,"UPDATE productos SET cantidad='%i' where idproductos='%s'",cant,c3);
       mysql_query (conn, update);
    }   
}

void Conexion::eliminar(char *p1,int i){  
    //si i =1 prodoctos  sino proveedores
    char consulta[100];  
    if(i==1){
       sprintf(consulta,"DELETE FROM productos WHERE idproductos='%s'",p1);   
    }
    if(i==2){
        sprintf(consulta,"DELETE FROM proveedores WHERE idproveedores='%s'",p1);   
    }
    if(i==3){
        sprintf(consulta,"DELETE FROM cliente WHERE idcliente='%s'",p1);   

    }
    if(i==4){
        sprintf(consulta,"DELETE FROM compras WHERE codbarra='%s'",p1);   
    }
    if (!mysql_query (conn, consulta)) {
        if(i!=4){
          cout<<"presione enter para continuar";
          cin.get();
          system("clear");   
        }     
    }         
}
     
void Conexion::mostrar_productos(){
        
        const char * sql = "SELECT * FROM productos";
        int query = mysql_query(conn, sql);
     
        if (query != 0){
          cout << "Ha ocurrido un error al realizar la consulta" << endl;      
        }else{
            resultado = mysql_store_result(conn);
            unsigned long filas_afectadas = mysql_num_rows(resultado);
          
          MYSQL_ROW filas;
          cout << "Id Producto\tNombre\t\t\tPrecio de Compra\tDescripcion\tCant Disponible" << endl ;
          for (int x = 0; x < filas_afectadas; x++){
              //Obtenemos la fila
            filas = mysql_fetch_row(resultado);
            cout << "\t"    <<filas[0];
            cout << "\t"    <<filas[1];
            cout << "\t\t"  <<filas[2];
            cout << "\t\t\t"<<filas[3];
            cout << "\t\t"<<filas[4];
            cout<<endl;
          }
          // Liberar el resultado de la consulta
          mysql_free_result(resultado);
        } 
        cout<<"\n\npresione enter para continuar";
        cin.get();
        cin.ignore();
        system("clear");  
}

void Conexion::mostrar_proveedores(){
        resultado = mysql_store_result(conn);
        const char * sql = "SELECT * FROM proveedores";
        int query = mysql_query(conn, sql);
     
        if (query != 0){
          cout << "Ha ocurrido un error al realizar la consulta" << endl;      
        }else{
            resultado = mysql_store_result(conn);
            unsigned long filas_afectadas = mysql_num_rows(resultado);
          
          MYSQL_ROW filas;
          cout << "Id Proveedor\tNombre\t\t\tDescripcion" << endl ;
          for (int x = 0; x < filas_afectadas; x++){
              //Obtenemos la fila
            filas = mysql_fetch_row(resultado);
            cout << "\t" <<filas[0];
            cout << "\t" <<filas[1] ;
            cout << "\t\t"<<filas[2] ;
            cout<<endl;
          }
          // Liberar el resultado de la consulta
          mysql_free_result(resultado);
        } 
        cout<<"\n\npresione enter para continuar";
        cin.get();
        cin.ignore();
        system("clear");  
}

void Conexion::mostrar_cliente(){
        resultado = mysql_store_result(conn);
        const char * sql = "SELECT * FROM cliente";
        int query = mysql_query(conn, sql);
     
        if (query != 0){
          cout << "Ha ocurrido un error al realizar la consulta" << endl;      
        }else{
            resultado = mysql_store_result(conn);
            unsigned long filas_afectadas = mysql_num_rows(resultado);
          
          MYSQL_ROW filas;
          cout << "Id Cliente\tNombre\t\t\tCedula\t\tTelefono" << endl ;
          for (int x = 0; x < filas_afectadas; x++){
              //Obtenemos la fila
            filas = mysql_fetch_row(resultado);
            cout << "\t" <<filas[0];
            cout << "\t" <<filas[1];
            cout << "\t\t"<<filas[2];
            cout << "\t"<<filas[3];
            cout<<endl;
          }
          // Liberar el resultado de la consulta
          mysql_free_result(resultado);
        } 
        cout<<"\n\npresione enter para continuar";
        cin.get();
        system("clear");  
}

void Conexion::mostrar_compras(){   
        const char * sql = "SELECT * FROM historial_compra";
        int query = mysql_query(conn, sql);
        
        if (query != 0){
          cout << "Ha ocurrido un error al realizar la consulta" << endl;      
        }else{
         resultado = mysql_store_result(conn);
          unsigned long filas_afectadas = mysql_num_rows(resultado);
          cout <<"Fecha\t\t\tCB\t\tId Producto\t\tNombre\t\t\tPrecio de Compra\tId Proveedor" << endl ;
          for (int x = 0; x < filas_afectadas; x++){
              //Obtenemos la fila
    
            filas = mysql_fetch_row(resultado);
            cout <<filas[0];
            cout << "\t" <<filas[1] ;
            cout << "\t\t\t" <<filas[2] ;
            cout << "\t\t" <<filas[3];
            cout << "\t\t" <<filas[4] ;
            cout << "\t\t\t\t" <<filas[5];    
            cout<<endl;
          }
          // Liberar el resultado de la consulta
          mysql_free_result(resultado);
        } 
        cout<<"\n\npresione enter para continuar";
        cin.get();
        system("clear");  

}

void Conexion::lista_ventas(){
        const char * sql = "SELECT * FROM ventas";
        int query = mysql_query(conn, sql);
        
        if (query != 0){
          cout << "Ha ocurrido un error al realizar la consulta" << endl;      
        }else{
         resultado = mysql_store_result(conn);
          unsigned long filas_afectadas = mysql_num_rows(resultado);
          cout <<"Cedula\t\tNombre Producto\t\tFecha" << endl ;
          for (int x = 0; x < filas_afectadas; x++){
              //Obtenemos la fila
            filas = mysql_fetch_row(resultado);
            cout <<filas[0];
            cout << "\t" <<filas[1] ;
            cout << "\t\t" <<filas[2] ;
            cout<<endl;
          }
          // Liberar el resultado de la consulta
          mysql_free_result(resultado);
        } 
        cout<<"\n\npresione enter para continuar"<<endl;
        cin.get();
        system("clear");  
}

int Conexion::verificar(char *c,int i){
   
      const char * sql;
      if(i==1)
        sql = "SELECT * FROM cliente";
      else if(i==2)  
        sql = "SELECT * FROM compras";
      else if(i==3)  
        sql = "SELECT * FROM productos";
      int query = mysql_query(conn, sql);

      if (query != 0){
          cout << "Ha ocurrido un error al realizar la consulta" << endl;      
      }else{
          resultado = mysql_store_result(conn);
          unsigned long filas_afectadas = mysql_num_rows(resultado);     
          MYSQL_ROW filas;
          for (int x = 0; x < filas_afectadas; x++){
            //Obtenemos la fila
            filas = mysql_fetch_row(resultado);
            //VERIFICA SI ES UN CLIENTE
            if(i==1){
              if(strcmp(c,filas[2])==0)
                return 1;
            }
            //VERIFICAMOS SI EL PRODUCTO SE ENCUENTRA POR EL CODIGO DE BARRAS
            if(i==2){
              if(strcmp(c,filas[1])==0){
                id=filas[2];  //GUARDAMOS EL ID DEL PRODUCTO
                return 1;
              }            
            }
            //OBTENEMOS EL PRECIO
            if(i==3){
                if(strcmp(id,filas[0])==0){
                    int precio;
                    precio = atoi(filas[2]);
                    cout<<"--------------------"<<endl; 
                    cout<<"PRODUCTO: "<<filas[1]<<"\nPRECIO: "<<filas[2]<<endl;
                    cout<<"--------------------"<<endl; 

                    //DECREMENTAMOS UN NUMERO DEL STOCK SEGUN SU ID
                    char update[1000];
                    char *cantidad=obtener_cantidad(id);
                    int cant = atoi(cantidad); //CONVERTIMOS LA CANTIDAD A ENTERO
                    cant=cant-1;
                    sprintf(update,"UPDATE productos SET cantidad='%i' where idproductos='%s'",cant,id);
                    mysql_query (conn, update);
                    return precio;
                }

            }    
          }
          mysql_free_result(resultado);      
      }      
    return 0; 
}

char* Conexion::obtener_nombre(char * c){
      const char * sql = "SELECT * FROM compras";

      int query = mysql_query(conn, sql);

      if (query != 0){
          cout << "Ha ocurrido un error al realizar la consulta" << endl;      
      }else{
          resultado = mysql_store_result(conn);
          unsigned long filas_afectadas = mysql_num_rows(resultado);     
          MYSQL_ROW filas;
          for (int x = 0; x < filas_afectadas; x++){
            //Obtenemos la fila
            filas = mysql_fetch_row(resultado);

            //VERIFICAMOS SI EL PRODUCTO SE ENCUENTRA POR EL CODIGO DE BARRAS
            if(strcmp(c,filas[1])==0){
              c=filas[3];  //GUARDAMOS EL NOMBRE DEL PRODUCTO
            }            
              
          }
          mysql_free_result(resultado);      
      }        
  return c;
}

char*Conexion::obtener_cantidad(const char *c){
    const char * sql = "SELECT * FROM productos";
    char *cc;
    int query = mysql_query(conn, sql);

    if (query != 0){
          cout << "Ha ocurrido un error al realizar la consulta" << endl;      
   }else{
          resultado = mysql_store_result(conn);
          unsigned long filas_afectadas = mysql_num_rows(resultado);     
          MYSQL_ROW filas;
          for (int x = 0; x < filas_afectadas; x++){
            //Obtenemos la fila
            filas = mysql_fetch_row(resultado);
            //VERIFICAMOS SI EL PRODUCTO SE ENCUENTRA POR EL CODIGO DE BARRAS
            if(strcmp(c,filas[0])==0){
              cc=filas[4];  //GUARDAMOS LA CANTIDAD DEL PRODUCTO
            }            
              
          }
          mysql_free_result(resultado);      
    }        
    return cc; //RETORNAMOS LA CANTIDAD DEL PRODUCTO
}

void Conexion::eliminar_historial(){
    const char * c1 = "DELETE FROM compras";
    const char * c2 = "DELETE FROM historial_compra";
    const char * c3 = "UPDATE productos SET cantidad=0"; 
    mysql_query(conn, c1);
    mysql_query(conn, c2);
    mysql_query(conn, c3);
    cout<<"\nHISTORIAL ELIMINADO CON EXITO"<<endl;
    cout<<"LA CANTIDAD DE PRODUCTOS VUELVE A SER 0"<<endl;
    cout<<"\n\npresione enter para continuar";
    cin.get();
    system("clear");  
}

void Conexion::eliminar_historial_ventas(){
    const char * c1 = "DELETE FROM ventas";
    mysql_query(conn, c1);
    cout<<"\nHISTORIAL ELIMINADO CON EXITO"<<endl;
    cout<<"\n\npresione enter para continuar";
    cin.get();
    system("clear");  
}