#pragma once

#include "lib.h"
#include <string>
#include <vector>


enum eltype{
    PLAYER,
    METEORITE,
    STELLA
};

class Figura {

   public:
       GLuint VAO;
       GLuint VBO_vertices;
       GLuint VBO_colors;
       int nTriangles;

       std::vector<vec3> vertices;
       std::vector<vec4> colors; 
       int nv;
       int render;

       unsigned int programId;

       float angolo;
       mat4 Model;
       vec2 position;
       vec3 scale;

       //Bounding Box
       vec4 min_BB_obj;
       vec4 max_BB_obj;
       vec4 min_BB;
       vec4 max_BB;

       float timerFig;
       bool isalive;              
       eltype eltype;             

};

 
class Curva : public Figura {

    public:
        GLuint VBO_CP;             //per le coordinate dei control points
        GLuint VBO_CP_colors;      //per i colori dei control points
        GLuint VBO_TG;             //per le coordinate delle tangenti
        GLuint VBO_TG_colors;      //per i colori delle tangenti

        std::vector<glm::vec3> CP;        // Coordinate dei control points
        std::vector<glm::vec4> colCP;     // Colori
        std::vector<glm::vec3> tg;        // Coordinate dei vettori tangenti ai control points
        std::vector<glm::vec4> col_tg;   
        int ncp;                    // Numero di control points
        int ntg;                    // Numero di vettori tangenti

        std::vector<glm::vec3> Derivata;
        std::vector<float> Tens;
        std::vector<float> Bias;
        std::vector<float> Cont;

        //Info relative al giocatore
        int numLives;
        int numPoints;
        int pointsRecord;

};
 