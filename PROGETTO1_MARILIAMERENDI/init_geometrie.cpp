#pragma once
#include "strutture.h"
#include "Utilities.h"
#include "gestione_curve.h"
#include <fstream>
#include "init_geometrie.h"
#pragma warning(disable:4996)
#define PI 3.14159265358979323
extern float alpha;


// Disegna una stella come funzione matematica basata su un centro e due raggi, uno per le punte e uno per le indentazioni
void INIT_STAR(float cx, float cy, float raggioInterno, float raggioEsterno, Figura* fig)
{
    int t, i;
    float xx, yy;
    float stepA = (2 * PI) / fig->nTriangles;
    fig->vertices.push_back(vec3(cx, cy, 0.0));      //centro
    fig->colors.push_back(vec4(1.0, 1.0, 1.0, 1.0));

    for (i = 0; i <= fig->nTriangles; i++)
    {
        float angle = i * stepA;
        //punte
        xx = raggioEsterno * cos(angle);
        yy = raggioEsterno * sin(angle);

        fig->vertices.push_back(vec3(xx, yy, 0.0));
        fig->colors.push_back(vec4(1.0, 1.0, 0.0, 1.0));

        //indentazioni
        angle += stepA / 2;  //Le punte e le indentazioni si discostano di mezzo angolo l'una dall'altra
        xx = raggioInterno * cos(angle);
        yy = raggioInterno * sin(angle);

        fig->vertices.push_back(vec3(xx, yy, 0.0));
        fig->colors.push_back(vec4(1.0, 1.0, 0.0, 1.0));
    }

    findBB(fig);
    fig->vertices.push_back(vec3(fig->min_BB_obj.x, fig->min_BB_obj.y, 0.0));
    fig->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    fig->vertices.push_back(vec3(fig->max_BB_obj.x, fig->min_BB_obj.y, 0.0));
    fig->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    fig->vertices.push_back(vec3(fig->max_BB_obj.x, fig->max_BB_obj.y, 0.0));
    fig->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    fig->vertices.push_back(vec3(fig->min_BB_obj.x, fig->max_BB_obj.y, 0.0));
    fig->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));

    fig->nv = fig->vertices.size();
    fig->render = GL_TRIANGLE_FAN;
}

void INIT_PIANO(Figura* fig) {
    fig->vertices.clear();

    fig->vertices.push_back(vec3(-0.5, -0.5, 0.0));
    fig->colors.push_back(vec4(0.0, 0.0, 0.0, 1.0));
    fig->vertices.push_back(vec3(0.5, -0.5, 0.0));
    fig->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    fig->vertices.push_back(vec3(0.5, 0.5, 0.0));
    fig->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    fig->vertices.push_back(vec3(-0.5, 0.5, 0.0));
    fig->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));

    fig->nv = fig->vertices.size();
    fig->render = GL_TRIANGLE_FAN;

}

Curva INIT_FORMA(std::string nomefile, vec4 color_top, vec4 color_bot, eltype type)
{
    Curva curva;
    float* t;
    float step_t;
    int i;
    struct Dati {
        float x;
        float y;
        float z;
    };

    FILE* file = fopen(nomefile.c_str(), "r");
    if (file == NULL) {
        perror("Impossibile aprire il file");
    }

    // Vettore per memorizzare i dati
    struct Dati dati[1000]; // Supponiamo che ci siano al massimo 100 righe nel file

    int riga = 0;
    while (fscanf(file, "%f %f %f", &dati[riga].x, &dati[riga].y, &dati[riga].z) == 3) {
        // Incrementa l'indice della riga
        riga++;

        // Puoi aggiungere un controllo qui per evitare il superamento dell'array dati
        if (riga >= 1000) {
            printf("Troppe righe nel file. L'array dati   stato completamente riempito.\n");
            break;
        }
    }
    // Chiudi il file
    fclose(file);


    for (int i = 0; i < riga; i++) {
        curva.CP.push_back(vec3(dati[i].x, dati[i].y, dati[i].z));
        curva.colCP.push_back(vec4(0.0, 0.0, 0.0, 1.0));
        curva.Derivata.push_back(vec3(0.0, 0.0, 0.0));
    }
    curva.ncp = curva.CP.size();

    t = new float[curva.CP.size()];
    step_t = 1.0 / (curva.CP.size() - 1);
    for (i = 0; i < curva.CP.size(); i++)
        t[i] = (float)i * step_t;

    t[curva.CP.size()] = 1.0;
    vec3 centro = vec3(0.0, 0.0, 0.0);
    
    CostruisciHermite(t, &curva, centro, color_top, color_bot);


    // Nel caso della navicella spaziale (il giocatore), oltre alla curva viene 
    // inserito, un piccolo cerchio che rappresenta l'oblò della navicella

    if (type == PLAYER) {
        
        int ii;
        float cx = 0.0f, cy = 0.0f;             //centro oblò
        float raggiox = 0.17f, raggioy = 0.17f; //raggio oblò
        float stepA = (2 * PI) / 30;
        float xx, yy, tt = 0;

        curva.vertices.push_back(vec3(cx, cy, 0.0));
        curva.colors.push_back(vec4(0.0, 1.0, 1.0, 1.0));

        for (ii = 0; ii <= 30; ii++)
        {
            tt = (float)ii * stepA;
            xx = cx + raggiox * cos(tt);
            yy = cy + raggioy * sin(tt);
            curva.vertices.push_back(vec3(xx, yy, 0.0));
            curva.colors.push_back(vec4(0.2, 0.28, 0.5, 1.0));
        }
    }

    findBB(&curva);
    curva.vertices.push_back(vec3(curva.min_BB_obj.x, curva.min_BB_obj.y, 0.0));
    curva.colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    curva.vertices.push_back(vec3(curva.max_BB_obj.x, curva.min_BB_obj.y, 0.0));
    curva.colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    curva.vertices.push_back(vec3(curva.max_BB_obj.x, curva.max_BB_obj.y, 0.0));
    curva.colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    curva.vertices.push_back(vec3(curva.min_BB_obj.x, curva.max_BB_obj.y, 0.0));
    curva.colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));


    curva.nv = curva.vertices.size();
    curva.render = GL_TRIANGLE_FAN;

    return curva;
}
