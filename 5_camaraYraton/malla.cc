
#define cimg_use_jpeg
#define cimg_display 0
#include "CImg.h"

#include "aux.h"
#include "ply_reader.h"
#include "malla.h"


using namespace cimg_library;

// Visualización en modo inmediato con 'glDrawElements'
void ObjMallaIndexada::draw_seleccion(int modoDibujo)
{
  std::cout<<"ObjMallaIndexada::draw_seleccion(ModoVis modo_vis) \n";

  glEnableClientState(GL_VERTEX_ARRAY);// habilitar uso de un array de vértices
  glVertexPointer(3, GL_FLOAT, 0, vertices.data());// indicar el formato y la dirección de memoria del array de vértices (son tuplas de 3 valores float, sin espacio entre ellas)
  glDrawElements(GL_TRIANGLES, triangulos.size() * 3,GL_UNSIGNED_INT, triangulos.data());// visualizar, indicando: tipo de primitiva, número de índices, tipo de los índices, y dirección de la tabla de índices
  glDisableClientState(GL_VERTEX_ARRAY);  // deshabilitar array de vértices
}
// Aplica el material de cada objeto
void ObjMallaIndexada::seleccionar()
{
     std::cout<<"ObjMallaIndexada::seleccionar()\n";
    if (!seleccionado){
        std::cout<<"ObjMallaIndexada::seleccionar::no selecionado\n";
        materialAnterior = material;
        material = Bronce;
        colorAnterior = color;
        color.clear();
        for(auto it : triangulos){
            color.push_back({1.0,1.0,0.0});
        }
        seleccionado = true;
    }else{
        std::cout<<"ObjMallaIndexada::seleccionar:: selecionado\n";

        material = materialAnterior;
        color = colorAnterior;
        seleccionado = false;
    }
}

/*
*
* METODOS DE DIBUJO
*
*
*/

// Aplica el material de cada objeto
void ObjMallaIndexada::aplicar_materiales(){
  std::cout<<"ObjMallaIndexada::aplicar_materiales \n";
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material.difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material.ambiente);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material.especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,material.brillo);
}


GLuint CrearVBO( GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid *puntero_ram){
  std::cout<<" CrearVBO \n";
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
  //std::cout<<"ENTRANDO EN MODO INMEDIATO \n";
  glEnableClientState( GL_VERTEX_ARRAY );

  // indicar el formato y la dirección de memoria del array de vértices
  // (son tuplas de 3 valores float, sin espacio entre ellas)  
  glVertexPointer( 3, GL_FLOAT, 0, vertices.data() ) ;

  glEnableClientState(GL_COLOR_ARRAY);
  glColorPointer(3, GL_FLOAT, 0, color.data());
  // visualizar, indicando: tipo de primitiva, número de índices,
  // tipo de los índices, y dirección de la tabla de índices
  glDrawElements( GL_TRIANGLES, triangulos.size()*3,GL_UNSIGNED_INT, triangulos.data() );
  // deshabilitar array de vértices
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

  // indicar el formato y la dirección de memoria del array de vértices
  // (son tuplas de 3 valores float, sin espacio entre ellas)  
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
       glColor3f(1,0.2,0.8);
      glDrawElements(GL_TRIANGLES, colorVerticesImpares.size()*3, GL_UNSIGNED_INT, colorVerticesImpares.data());
      

      glDisableClientState( GL_VERTEX_ARRAY );

}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void ObjMallaIndexada::draw(int modo, bool ajedrez)//parametros para ver si es diferido etc...
{
   // completar .....(práctica 1)

  if(ajedrez){
     ajedrezado();
  }
  else{
    if(modo==0){
      usarDiferido=false;
        draw_ModoInmediato();

    }else{
      usarDiferido=true;
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
    calcular_normales();
    material = Bronce;

color.clear();
    for(int i=0;i<triangulos.size();i++){
        color.push_back({1.0,0.5,0.0});
    }
}

// *****************************************************************************
//
// Clase Tetraedro (práctica 1)
//
// *****************************************************************************



Tetraedro::Tetraedro()
{

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
  
   for(int i=0;i<triangulos.size();i++){
        color.push_back({0.5,0.5,1.0});
    }
}

// *****************************************************************************
//
// Clase Cilindro
//
// *****************************************************************************


// NUMERO DE VERTICES7 PUNTOS PARA CONSTRUIR EL PERFIL
//NUMERO DE VECES QUE SE PINTA PARA HACER EL CIRCULO
Cilindro::Cilindro( const int num_vert_perfil, const int num_instancias_perfil ){

 if(num_instancias_perfil!=0){
  std::vector<Tupla3f> perfilCilindro;
  perfilCilindro.push_back({0.5,-0.5,0});
  perfilCilindro.push_back({0.5,0.5,0});
  
  
  crear_malla(perfilCilindro, num_instancias_perfil); 
  calcular_normales();
  material = Esmeralda;
  for(int i=0;i<triangulos.size();i++){
        color.push_back({1.0,0.0,0.0});
    }

  }
  material = Esmeralda;

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

    crear_malla(perfil_original, num_instancias_perfil);
   
    
  for(int i=0;i<triangulos.size();i++){
        color.push_back({0.0,1.0,1.0});
    }

    calcular_normales();
    material = Esmeralda;
}

// *****************************************************************************
//
// Clase Esfera
//
// *****************************************************************************

Esfera::Esfera(const int num_vert_perfil, const int num_instancias_perf){
  std::cout<<"CONSTRUCTOR DE LA ESFERA";
  int num=40;
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


    crear_malla(perfil_original, num_instancias_perf);
    //ponerTapas(radio_base, num_instancias_perf);
     
     color.clear();
  for(int i=0;i<triangulos.size();i++){
        color.push_back({0.8,0.2,1});
      }
  calcular_normales();
    material = Esmeralda; 

}



// *****************************************************************************
//
// TRATAMIEBNTO DE ARCHIVOS PLY
//
// *****************************************************************************
// ****************************************************************************

// *****************************************************************************
//
// Clase ObjPLY (práctica 2)
//
// *****************************************************************************

ObjPLY::ObjPLY( const std::string & nombre_archivo )
{
   // leer la lista de caras y vértices
   ply::read( nombre_archivo, vertices, triangulos );
}


// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion(){}

ObjRevolucion::ObjRevolucion( const std::string & nombre_ply_perfil , int nrev)
{
  std::cout << "\nTamano del vector Antes leer ply: \n "<<vertices.size();
  ply::read_vertices(nombre_ply_perfil, vertices);
  std::cout << "\nTamano del vector  Despues leer ply: \n "<<vertices.size();
  //antes de revolucionar ver si el perfil original esta ordenado en y ascendente
  if(nrev!=0) 
    {
    crear_malla(vertices, nrev);
    calcular_normales();
    material = Esmeralda;
  }
}

void ObjRevolucion::crear_malla(const std::vector<Tupla3f> &perfil_original,
  const int num_instancias_perfil)
{

  float x=0,y=0,z=0;
  int x_=0,y_=0,z_=0;
  int num_aux=perfil_original.size(); //tamaño del perfil
  vertices.resize(num_aux*num_instancias_perfil);

  std::cout<<"ObjRevolucion::crear_malla   PREPARANDO VERTICES\n";

  for (int j=0;j<num_instancias_perfil;j++) //for del numero de lados
    {for (int i=0;i<num_aux;i++) //for de puntos de la forma
       {
        //std::cout<<"VERTICE  "<<i;std::cout<<"\n";
        //std::cout<<"CALCULO X : "<<x;std::cout<<"\n";
        x=perfil_original[i][0]*cos(2.0*M_PI*j/(1.0*num_instancias_perfil))+
                      perfil_original[i][2]*sin(2.0*M_PI*j/(1.0*num_instancias_perfil));//std::cout<<"CALCULO Z : "<<z;std::cout<<"\n";
        y=perfil_original[i][1]; //std::cout<<"CALCULO Y : "<<y;std::cout<<"\n";
        z=-perfil_original[i][0]*sin(2.0*M_PI*j/(1.0*num_instancias_perfil))+
                      perfil_original[i][2]*cos(2.0*M_PI*j/(1.0*num_instancias_perfil));
     
        
         //std::cout<<"anadimos al vertice  I+J*num_aux:  "<<i+j*num_aux;std::cout<<"\n";
        vertices[i+j*num_aux][0]=x; //std::cout<<"anadimos X  "<<x;//std::cout<<"\n"; 
        vertices[i+j*num_aux][1]=y;//std::cout<<"añadimos y "<<y;std::cout<<"\n";
        vertices[i+j*num_aux][2]=z;//std::cout<<"añadimos Z  "<<z; std::cout<<"\n";
  
       }
    }

// tratamiento de las caras
std::cout<<"ObjRevolucion::crear_malla   PREPARANDO CARAS\n";
  for (int j=0;j<num_instancias_perfil;j++){ //j para los perfiles
    for (int i=0;i<num_aux-1;i++){ //i para los puntos
      x_=i+((j+1)%num_instancias_perfil)*num_aux; //el modulo de num
        //se usa para crear la ultima cara (enganchar ultimo perfil con el primero)
     
      //Forma las caras triangulo de arriba
     // std::cout<<"calculando cara numero "<<i;
       // std::cout<<"valor de la cordena da X : "<<x_;std::cout<<"\n";
        y_=i+1+((j+1)%num_instancias_perfil)*num_aux; //std::cout<<"valor de la cordena da Y : "<<y_;std::cout<<"\n";
        z_=i+1+j*num_aux;//std::cout<<"valor de la cordena da Z : "<<z_;std::cout<<"\n";
        
        
        triangulos.push_back({x_,y_,z_});

      //Forma las caras triangulo de abajo
        //std::cout<<"cara numero "<<i;
        x_=i+1+j*num_aux;//std::cout<<"valor de la cordena da X: "<<x_;std::cout<<"\n";
        y_=i+j*num_aux;  //std::cout<<"valor de la cordena da Y : "<<y_;std::cout<<"\n";
        z_=i+((j+1)%num_instancias_perfil)*num_aux; //std::cout<<"valor de la cordena da Z : "<<z_;std::cout<<"\n";
       
        triangulos.push_back({x_,y_,z_});

       }
}


   // tapa inferior
std::cout<<"ObjRevolucion::crear_malla    TAPA INFERIOR\n";
  if (fabs(perfil_original[0][0])>0.0) // si el perfil del primer punto es mayor que 0 hacemos una tapa
    {
      // primero almacenamos un punto nuevo
      y=perfil_original[0][1];
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
    std::cout<<"ObjRevolucion::crear_malla    TAPA SUPERIOR\n";
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




// *****************************************************************************
//
//  CLASE CUADRO
//
// *****************************************************************************
// *****************************************************************************
//
// Clase Cubo (práctica 4)
//
// *****************************************************************************

Cuadro::Cuadro(const std::string& nombre, const std::vector<Tupla2f> vertices_textura){
    
    verticesTextura = vertices_textura;
    nombre_archivo = nombre;

    // inicializar la tabla de vértices
    vertices = {
        { -15, -15,  0.0 }, // 0
        { -15,  15,  0.0 }, // 1
        {  15,  15,  0.0 }, // 2
        {  15, -15,  0.0 }, // 3
    };
    // inicializar la tabla de caras o triángulos SELECCIONA LA PARTE DEL LIENZO
    triangulos = { { 0, 2, 1 }, { 0, 3, 2 } };
    //std::cout<<"LLAMANDO A NORMALES:: CONSTRUCTOR DEL CUBO \n";
    calcular_normales();
    material= Blanco;

}

// *****************************************************************************
//
// NORMALES (práctica 4)
//
// *****************************************************************************


void ObjMallaIndexada::calcular_normales()
{
  std::cout<<"ObjMallaIndexada::calcular_normales   CARAS NORMALIZANDO \n";
    Tupla3f normal;
    Tupla3f vector1, vector2, triangulo_v1, triangulo_v2, triangulo_v3, vector_cross;
    for (auto& triangulo : triangulos) {
        triangulo_v1 = vertices[triangulo(0)];
        triangulo_v2 = vertices[triangulo(1)];
        triangulo_v3 = vertices[triangulo(2)];

        vector1 = triangulo_v2 - triangulo_v1;
        vector2 = triangulo_v3 - triangulo_v1;

        vector_cross = vector1.cross(vector2);
        normal = vector_cross.normalized();
        triangulosNormales.emplace_back(normal);
    }

    calcular_normales_vertices();
}

// -----------------------------------------------------------------------------
// Recalcula la tabla de normales de vértices (el contenido anterior se pierde)
void ObjMallaIndexada::calcular_normales_vertices()
{
  std::cout<<"ObjMallaIndexada::calcular_normales_vertices\n";
    verticesNormales.resize(vertices.size());
    for (int i = 0; i < verticesNormales.size(); ++i) {
        verticesNormales[i] = { 0.0, 0.0, 0.0 };
    }

    int v1, v2, v3;
    for (int i = 0; i < triangulosNormales.size(); ++i) {
        v1 = triangulos[i](0);
        v2 = triangulos[i](1);
        v3 = triangulos[i](2);

        verticesNormales[v1] = verticesNormales[v1] + triangulosNormales[i];
        verticesNormales[v2] = verticesNormales[v2] + triangulosNormales[i];
        verticesNormales[v3] = verticesNormales[v3] + triangulosNormales[i];
    }

    for (int i = 0; i < verticesNormales.size(); ++i) {
        verticesNormales[i] = verticesNormales[i].normalized();
    }
}

// *****************************************************************************
//
// TEXTURA (práctica 4)
//
// *****************************************************************************

void ObjMallaIndexada::prepara_textura()
{
    std::cout<<"ObjMallaIndexada::prepara_textura \n";

    std::vector<unsigned char> datos;
    char * nombreArchivo = new char [nombre_archivo.length()+1];
    strcpy (nombreArchivo, nombre_archivo.c_str());

    CImg<unsigned char> textura;
    textura.load(nombreArchivo);

    // empaquetamos bien los datos
    for (long y = 0; y < textura.height(); y++)
        for (long x = 0; x < textura.width(); x++) {
            unsigned char* r = textura.data(x, y, 0, 0);
            unsigned char* g = textura.data(x, y, 0, 1);
            unsigned char* b = textura.data(x, y, 0, 2);
            datos.push_back(*r);
            datos.push_back(*g);
            datos.push_back(*b);
        }

    glGenTextures(1, &id_textura);
    glBindTexture(GL_TEXTURE_2D, id_textura);

    glActiveTexture(GL_TEXTURE0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // TRASFIERE LOS DATOS A GPU
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textura.width(), textura.height(),
        0, GL_RGB, GL_UNSIGNED_BYTE, &datos[0]);
}

