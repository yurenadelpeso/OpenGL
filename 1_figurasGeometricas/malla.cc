#include "aux.h"
#include "malla.h"

GLuint CrearVBO( GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid *puntero_ram){
  
  GLuint id_vbo;   //resultado: identificador del VBO
  glGenBuffers(1, &id_vbo); // crear nuevo vbo, obtener el identificador(nunca 0)
  glBindBuffer(tipo_vbo, id_vbo); //activar el VBO usando su identificador
  //esta instruccion hace la transferenvia de datos desde la RAM hacia la GPU
  glBufferData( tipo_vbo, tamanio_bytes, puntero_ram, GL_STATIC_DRAW);
  glBindBuffer( tipo_vbo,0); //dasactivacion del VBO (activar 0)
  return id_vbo;
}



void ObjMallaIndexada::draw_ModoInmediato()
{   
  std::cout<<"ENTRANDO EN MODO INMEDIATO \n";
  glEnableClientState( GL_VERTEX_ARRAY );

  // indicar el formato y la dirección de memoria del array de vértices (son tuplas de 3 valores float, sin espacio entre ellas)  
  glVertexPointer( 3, GL_FLOAT, 0, vertices.data() ) ;
  glEnableClientState(GL_COLOR_ARRAY);
  glColorPointer(3, GL_FLOAT, 0, color.data());
  glDrawElements( GL_TRIANGLES, triangulos.size()*3,GL_UNSIGNED_INT, triangulos.data() );  // visualizar, indicando: tipo de primitiva, número de índices, tipo de los índices, y dirección de la tabla de índices

  // deshabilitar arrays
  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState( GL_VERTEX_ARRAY );
}

// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void ObjMallaIndexada::draw_ModoDiferido()
{
  std::cout<<"ENTRANDO EN MODO DIFERIDO \n";

  if(id_VboVertices==0) {
    id_VboVertices=CrearVBO(GL_ARRAY_BUFFER,
                        3*vertices.size()*sizeof(float),
                        vertices.data());
  }
  if(id_VboTriangulos==0) {
    id_VboTriangulos=CrearVBO(GL_ELEMENT_ARRAY_BUFFER,
                        3*triangulos.size()*sizeof(unsigned int),
                        triangulos.data());
  }
   if(id_VboColor==0) {
    id_VboColor=CrearVBO(GL_ELEMENT_ARRAY_BUFFER,
                        3*triangulos.size()*sizeof(unsigned int),
                        color.data());
  }
  
  glBindBuffer( GL_ARRAY_BUFFER, id_VboVertices ); // activar VBO de vértices
  glVertexPointer( 3, GL_FLOAT, 0, 0 );
  glBindBuffer( GL_ARRAY_BUFFER, 0 );
  glEnableClientState( GL_VERTEX_ARRAY );

  glBindBuffer(GL_ARRAY_BUFFER, id_VboColor);//activar VBO de colores
  glColorPointer(3, GL_FLOAT, 0, 0);
  glBindBuffer( GL_ARRAY_BUFFER, 0 ); // desactivar VBO de colores.
  glEnableClientState(GL_COLOR_ARRAY);


  glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_VboTriangulos );// activar VBO de triángulos
  glDrawElements( GL_TRIANGLES, 3*triangulos.size(), GL_UNSIGNED_INT, 0 ) ;
  glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
  
  glDisableClientState( GL_COLOR_ARRAY );
  glDisableClientState( GL_VERTEX_ARRAY );

}
void ObjMallaIndexada::ajedrezado(){
  std::cout<<"entrando nuevo modo ajedrez \n";
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glEnableClientState( GL_VERTEX_ARRAY );

  // indicar el formato y la dirección de memoria del array de vértices(son tuplas de 3 valores float, sin espacio entre ellas)  
  glVertexPointer( 3, GL_FLOAT, 0, vertices.data() ) ;
  //color.clear();
   for(int i=0; i<triangulos.size(); i++){ //recorrer el vector de caras e ir pintando pares e impares de un color distinto.
      if(i%2==0){
        colorVerticesPares.push_back(triangulos[i]);
        
      }else{
        colorVerticesImpares.push_back(triangulos[i]);

      }
      
    }
      
      glColor3f(1,0.4,1);
      glDrawElements(GL_TRIANGLES, colorVerticesPares.size()*3 , GL_UNSIGNED_INT,colorVerticesPares.data() );
     
      glColor3f(0.4,0.4,0.4);
      glDrawElements(GL_TRIANGLES, colorVerticesImpares.size()*3, GL_UNSIGNED_INT, colorVerticesImpares.data());
      

      glDisableClientState( GL_VERTEX_ARRAY );

}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void ObjMallaIndexada::draw(int modo, bool ajedrez)//parametros para ver si es diferido etc...
{
   // completar .....(práctica 1)
 //poner un var booleana para conocer el modo necesario
  if(ajedrez){
     ajedrezado();
  }
  else{
    if(modo==0){
        draw_ModoInmediato();
    }else{
      draw_ModoDiferido();
    }
  }
}
























// *****************************************************************************
//
// CADA OBJETO QUE PODEMOS CREAR SE DEFINE EN UNA CLASE
//
// *****************************************************************************
// *****************************************************************************
//
// Clase Cubo (práctica 1)
//
// *****************************************************************************
Frontera::Frontera(float tam){
   // inicializar la tabla de vértices
   vertices =  {  { -tam, -tam, -tam }, // 0
                  { -tam, -tam, +tam }, // 1
                  { -tam, +tam, -tam }, // 2
                  { -tam, +tam, +tam }, // 3
                  { +tam, -tam, -tam }, // 4
                  { +tam, -tam, +tam }, // 5
                  { +tam, +tam, -tam }, // 6
                  { +tam, +tam, +tam }  // 7
               };

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

   triangulos = { { 0, 2, 4 }, { 4, 2, 6 },
                  { 1, 5, 3 }, { 3, 5, 7 },
                  { 1, 3, 0 }, { 0, 3, 2 },
                  { 5, 4, 7 }, { 7, 4, 6 },
                  { 1, 0, 5 }, { 5, 0, 4 },
                  { 3, 7, 2 }, { 2, 7, 6 }
                } ;
     color.clear();    
  for(int i=0;i<vertices.size();i++){
        color.push_back({0.4,0.4,0.4});
    }

}
Cubo::Cubo()
{

   // inicializar la tabla de vértices
   vertices =  {  { -0.5, -0.5, -0.5 }, // 0
                  { -0.5, -0.5, +0.5 }, // 1
                  { -0.5, +0.5, -0.5 }, // 2
                  { -0.5, +0.5, +0.5 }, // 3
                  { +0.5, -0.5, -0.5 }, // 4
                  { +0.5, -0.5, +0.5 }, // 5
                  { +0.5, +0.5, -0.5 }, // 6
                  { +0.5, +0.5, +0.5 }  // 7
               };

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

   triangulos = { { 0, 2, 4 }, { 4, 2, 6 },
                  { 1, 5, 3 }, { 3, 5, 7 },
                  { 1, 3, 0 }, { 0, 3, 2 },
                  { 5, 4, 7 }, { 7, 4, 6 },
                  { 1, 0, 5 }, { 5, 0, 4 },
                  { 3, 7, 2 }, { 2, 7, 6 }
                } ;
     color.clear();    
  for(int i=0;i<vertices.size();i++){
        color.push_back({0.4,0.4,0.4});
    }
}

// *****************************************************************************
//
// Clase Tetraedro (práctica 1)
//
// *****************************************************************************



Tetraedro::Tetraedro()
{

   // inicializar la tabla de vértices
   vertices =  {  { -0.5, -0.5, -0.5 }, // 0
                  { 0, -0.5, +0.5 }, // 1
                  { 0.5, -0.5, -0.5 }, // 2
                  { 0, +0.5, 0 }, // 3
               };

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

   triangulos = { { 0, 1, 3 }, { 1, 2, 3 },
                  { 2, 0, 3 }, { 0, 2, 1 },

                } ;
 color.clear();
for(int i=0;i<triangulos.size();i++){
        color.push_back({0.4,0.4,0.4});
    }
    }
// *****************************************************************************
//
// Clase Cilindro
//
// *****************************************************************************

float crearFrontera( const std::vector<Tupla3f> & perfil) {
  float max=0;
  for(int i=0;i<perfil.size()-1;i++){
    if(fabs(perfil[i][0]>max)){
      max=perfil[i][0];
    }
     if(fabs(perfil[i][1]>max)){
      max=perfil[i][1];
    }
     if(fabs(perfil[i][2]>max)){
      max=perfil[i][2];
    }
  }
  return max;
}

// NUMERO DE VERTICES7 PUNTOS PARA CONSTRUIR EL PERFIL
//NUMERO DE VECES QUE SE PINTA PARA HACER EL CIRCULO
Cilindro::Cilindro( const int num_vert_perfil, const int num_instancias_perfil ){
  

 if(num_instancias_perfil!=0){
  std::vector<Tupla3f> perfilCilindro;
  perfilCilindro.push_back({0.5,-0.5,0});
  perfilCilindro.push_back({0.5,0.5,0});

  tam=crearFrontera(perfilCilindro);
  crearMalla(perfilCilindro, num_instancias_perfil); 
   color.clear();
for(int i=0;i<triangulos.size();i++){
        color.push_back({0.4,0.4,0.4});
    }

  }
}







// *****************************************************************************
//
// Clase Cono
//
// *****************************************************************************

Cono::Cono( const int num_vert_perfil, const int num_instancias_perfil ){

    std::vector<Tupla3f> perfil_original;
    float subdiv = 1.0 / (num_vert_perfil-1);
    float x = radio_base;
    float y = -altura;


    for (int i = 0; i < num_vert_perfil - 1; ++i) {
        perfil_original.push_back({x, y, 0});
        x -= subdiv;
        y += subdiv;
    }

    crearMalla(perfil_original, num_instancias_perfil);
    //ponerTapas(altura, num_instancias_perfil);
    color.clear();
    for(int i=0;i<triangulos.size();i++){
        color.push_back({0.4,0.4,0.4});
    }
}

// *****************************************************************************
//
// Clase Esfera
//
// *****************************************************************************

Esfera::Esfera(const int num_vert_perfil, const int num_instancias_perf){
  std::cout<<"CONSTRUCTOR DE LA ESFERA";
  int num=40;



  /**********************************************************************************/

/*******************CONSTRUCTOR**************************************************************/
  

  float r = radio_base;
  std::vector<Tupla3f> perfil_original;
  float x,y,z;

// Generación puntos del perfil ")"
  for(int i=1; i<num ; i++){

    float a = -(M_PI/2) + (i*M_PI/(num+1));
    x=r*cos(a);
    y=r*sin(a);
    z=0.0;
    perfil_original.push_back({x,y,z});
  }


    crearMalla(perfil_original, num_instancias_perf);
    //ponerTapas(radio_base, num_instancias_perf);
     
    color.clear();
    
    for(int i=0;i<triangulos.size();i++){
        color.push_back({0.4,0.4,0.4});
    }

   
}





ObjRevolucion::ObjRevolucion(){}



void ObjRevolucion::crearMallaSinTapas(const std::vector<Tupla3f> &perfil_original,
  const int num_instancias_perfil)
{
  float x=0,y=0,z=0;
  int x_=0,y_=0,z_=0;
  int num_aux=perfil_original.size(); //tamaño del perfil
  vertices.resize(num_aux*num_instancias_perfil);

  std::cout<<"PREPARANDO VERTICES\n";

  for (int j=0;j<num_instancias_perfil;j++) //for del numero de lados
    {for (int i=0;i<num_aux;i++) //for de puntos de la forma
       {
        //std::cout<<"VERTICE  "<<i;
        //std::cout<<"\n";
        x=perfil_original[i][0]*cos(2.0*M_PI*j/(1.0*num_instancias_perfil))+
                      perfil_original[i][2]*sin(2.0*M_PI*j/(1.0*num_instancias_perfil));
        //std::cout<<"CALCULO X : "<<x;
        //std::cout<<"\n";
        y=perfil_original[i][1];
        //std::cout<<"CALCULO Y : "<<y;
        //std::cout<<"\n";
        z=-perfil_original[i][0]*sin(2.0*M_PI*j/(1.0*num_instancias_perfil))+
                      perfil_original[i][2]*cos(2.0*M_PI*j/(1.0*num_instancias_perfil));
        //std::cout<<"CALCULO Z : "<<z;
        //std::cout<<"\n";
         

        //std::cout<<"anadimos al vertice  I+J*num_aux:  "<<i+j*num_aux;
        //std::cout<<"\n";
        vertices[i+j*num_aux][0]=x;
        //std::cout<<"anadimos X  "<<x;
        //std::cout<<"\n";
        vertices[i+j*num_aux][1]=y;
        //std::cout<<"añadimos y "<<y;
        //std::cout<<"\n";
        vertices[i+j*num_aux][2]=z;
        //std::cout<<"añadimos Z  "<<z;
       // std::cout<<"\n";

        //vertices.push_back({x,y,z});
       }
    }

// tratamiento de las caras
std::cout<<"PREPARANDO CARAS\n";
  for (int j=0;j<num_instancias_perfil;j++){ //j para los perfiles
    for (int i=0;i<num_aux-1;i++){ //i para los puntos
      x_=i+((j+1)%num_instancias_perfil)*num_aux; //el modulo de num
        //se usa para crear la ultima cara (enganchar ultimo perfil con el primero)
      //Forma las caras triangulo de arriba
     // std::cout<<"calculando cara numero "<<i;
        //std::cout<<"valor de la cordena da X : "<<x_;
       // std::cout<<"\n";
        y_=i+1+((j+1)%num_instancias_perfil)*num_aux;
       // std::cout<<"valor de la cordena da Y : "<<y_;
     //   std::cout<<"\n";
        z_=i+1+j*num_aux;
     //   std::cout<<"valor de la cordena da Z : "<<z_;
      //  std::cout<<"\n";
        triangulos.push_back({x_,y_,z_});

      //Forma las caras triangulo de abajo
        x_=i+1+j*num_aux;
       // std::cout<<"cara numero "<<i;
      //  std::cout<<"valor de la cordena da X: "<<x_;
      //  std::cout<<"\n";
        y_=i+j*num_aux;
       // std::cout<<"valor de la cordena da Y : "<<y_;
       // std::cout<<"\n";
        z_=i+((j+1)%num_instancias_perfil)*num_aux;
       
     
        triangulos.push_back({x_,y_,z_});// std::cout<<"valor de la cordena da Z : "<<z_;   std::cout<<"\n";

       }
}

}




void ObjRevolucion::crearMalla(const std::vector<Tupla3f> &perfil_original,
  const int num_instancias_perfil)
{

  float x=0,y=0,z=0;
  int x_=0,y_=0,z_=0;
  int num_aux=perfil_original.size(); //tamaño del perfil
  vertices.resize(num_aux*num_instancias_perfil);

  std::cout<<"PREPARANDO VERTICES\n";

  for (int j=0;j<num_instancias_perfil;j++) //for del numero de lados
    {for (int i=0;i<num_aux;i++) //for de puntos de la forma
       {
        //std::cout<<"VERTICE  "<<i;
        //std::cout<<"\n";
        x=perfil_original[i][0]*cos(2.0*M_PI*j/(1.0*num_instancias_perfil))+
                      perfil_original[i][2]*sin(2.0*M_PI*j/(1.0*num_instancias_perfil));
        //std::cout<<"CALCULO X : "<<x;
        //std::cout<<"\n";
        y=perfil_original[i][1];
        //std::cout<<"CALCULO Y : "<<y;
        //std::cout<<"\n";
        z=-perfil_original[i][0]*sin(2.0*M_PI*j/(1.0*num_instancias_perfil))+
                      perfil_original[i][2]*cos(2.0*M_PI*j/(1.0*num_instancias_perfil));
        //std::cout<<"CALCULO Z : "<<z;
        //std::cout<<"\n";
         

        //std::cout<<"anadimos al vertice  I+J*num_aux:  "<<i+j*num_aux;
        //std::cout<<"\n";
        vertices[i+j*num_aux][0]=x;
        //std::cout<<"anadimos X  "<<x;
        //std::cout<<"\n";
        vertices[i+j*num_aux][1]=y;
        //std::cout<<"añadimos y "<<y;
        //std::cout<<"\n";
        vertices[i+j*num_aux][2]=z;
        //std::cout<<"añadimos Z  "<<z;
       // std::cout<<"\n";

        //vertices.push_back({x,y,z});
       }
    }

// tratamiento de las caras
std::cout<<"PREPARANDO CARAS\n";
  for (int j=0;j<num_instancias_perfil;j++){ //j para los perfiles
    for (int i=0;i<num_aux-1;i++){ //i para los puntos
      x_=i+((j+1)%num_instancias_perfil)*num_aux; //el modulo de num
        //se usa para crear la ultima cara (enganchar ultimo perfil con el primero)
      //Forma las caras triangulo de arriba
     // std::cout<<"calculando cara numero "<<i;
        //std::cout<<"valor de la cordena da X : "<<x_;
       // std::cout<<"\n";
        y_=i+1+((j+1)%num_instancias_perfil)*num_aux;
       // std::cout<<"valor de la cordena da Y : "<<y_;
     //   std::cout<<"\n";
        z_=i+1+j*num_aux;
     //   std::cout<<"valor de la cordena da Z : "<<z_;
      //  std::cout<<"\n";
        triangulos.push_back({x_,y_,z_});

      //Forma las caras triangulo de abajo
        x_=i+1+j*num_aux;
       // std::cout<<"cara numero "<<i;
      //  std::cout<<"valor de la cordena da X: "<<x_;
      //  std::cout<<"\n";
        y_=i+j*num_aux;
       // std::cout<<"valor de la cordena da Y : "<<y_;
       // std::cout<<"\n";
        z_=i+((j+1)%num_instancias_perfil)*num_aux;
       
     
        triangulos.push_back({x_,y_,z_});// std::cout<<"valor de la cordena da Z : "<<z_;   std::cout<<"\n";

       }
}





   // tapa inferior
std::cout<<"TAPA INFERIOR\n";
  if (fabs(perfil_original[0][0])>0.0) // si el perfil del primer punto es mayor que 0 hacemos una tapa
    {
      // primero almacenamos un punto nuevo
      if(perfil_original[0][1]==altura)y=altura;
      else y=perfil_original[0][1];
      x=0;
      z=0;
      vertices.push_back({x,y,z});
      x_=num_aux*num_instancias_perfil; // punto central
      for (int j=0;j<num_instancias_perfil;j++) // recorremos num de lados para unir con el punto
      {
        y_=((j+1)%num_instancias_perfil)*num_aux;   // num_aux num pntos, %num par que la ultima cara no se salga de rango
        z_=j*num_aux;
        triangulos.push_back({x_,y_,z_});

       }

    }

  // tapa superior
    std::cout<<"TAPA SUPERIOR\n";
  if (fabs(perfil_original[num_aux-1][0])>0.0) // me quedaria con el punto final del perfil
  {
    if(perfil_original[num_aux -1][1]==-altura)y=altura;
      else y=perfil_original[num_aux-1][1];
    x=0;
    //y=perfil_original[num_aux-1][1]; // defino el punto de arriba del cono
    z=0;
    vertices.push_back({x,y,z});
    x_=num_aux*num_instancias_perfil+1;

    for (int i=0;i<num_instancias_perfil;i++)
       {
        y_=(i+1)*num_aux-1;
        z_=((i+1)%num_instancias_perfil)*num_aux+num_aux-1;
        triangulos.push_back({x_,y_,z_});
       }

  }







}

