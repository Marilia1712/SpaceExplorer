#pragma once
#include "lib.h"
#include "strutture.h"
#include "inizializzazioni.h"
#include "init_geometrie.h"
#include <random>

extern int width, height;

vec2 randomPosition(int width, int height) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> disX(0.0f, static_cast<float>(width));
    std::uniform_real_distribution<> disY(0.0f, static_cast<float>(height));
    return glm::vec2(disX(gen), disY(gen));
}

// per creare un meteorite 
void create_meteor(Curva* meteor, unsigned int programId) {
    meteor->programId = programId;
    meteor->scale = vec3(80.0, 80.0, 1.0);
    meteor->timerFig = 0.0;
    meteor->angolo = rand() % 360 + 1;
    meteor->position = vec2(width, randomPosition(width, height).y);
    meteor->eltype = METEORITE;
    meteor->isalive = true;
    INIT_VAO_Curva(meteor);

}

// per creare una stella
void create_star(Figura* star, unsigned int programId) {
    star->eltype = STELLA;
    star->nTriangles = 5;
    star->programId = programId;
    star->isalive = true;
    star->scale = vec3(30.0, 30.0, 1.0);
    INIT_STAR(0.0, 0.0, 2.0, 1.0, star);
    star->timerFig = 0.0;
    star->position = vec2(width, randomPosition(width, height).y);
    INIT_VAO(star);
}

// per ruotare le figure animate
void update_angle(Figura* fig) {
    fig->angolo += 0.002f;  // ad ogni frame, ruota la figura di un grado
    if (fig->angolo > 360.0f) {
        fig->angolo = 0.0f;
    }
}

// per aggiornare la posizione delle figure
void update_position(Figura* fig) {
    fig->position.x -= width / 2500.0;

    if (fig->position.x < 0) {
        fig->isalive = false;
        fig->position.x = width;
        fig->position.y = randomPosition(width, height).y;
    }
}

void findBB(Figura* fig) {
    int n;
    n = fig->vertices.size();
    float minx = fig->vertices[0].x;
    float miny = fig->vertices[0].y;

    float maxx = fig->vertices[0].x;
    float maxy = fig->vertices[0].y;

    for (int i = 1; i < n; i++) {
        if (fig->vertices[i].x < minx) {
            minx = fig->vertices[i].x;
        }
        if (fig->vertices[i].x > maxx) {
            maxx = fig->vertices[i].x;
        }

        if (fig->vertices[i].y < miny) {
            miny = fig->vertices[i].y;
        }

        if (fig->vertices[i].y > maxy) {
            maxy = fig->vertices[i].y;
        }
    }

    fig->min_BB_obj = vec4(minx, miny, 0.0, 1.0);
    fig->max_BB_obj = vec4(maxx, maxy, 0.0, 1.0);

}

//ok
bool checkCollision(Figura* player, Figura* obj2) {
    // Check for overlap in the X-axis (horizontal axis)
    if (player->max_BB.x < obj2->min_BB.x || player->min_BB.x > obj2->max_BB.x) {
        // No overlap in X-axis, so no collision
        return false;
    }

    // Check for overlap in the Y-axis (vertical axis)
    if (player->max_BB.y < obj2->min_BB.y || player->min_BB.y > obj2->max_BB.y) {
        // No overlap in Y-axis, so no collision
        return false;
    }
    // If both checks pass, there is a collision
    return true;
}

//ok
void updateBB(Figura* fig)
{
    //Aggiorno le coordinate del Bounding Box applicandogli la stessa matrice di modellazione della sua shape
    fig->min_BB = fig->min_BB_obj;
    fig->max_BB = fig->max_BB_obj;
    fig->min_BB = fig->Model * fig->min_BB;
    fig->max_BB = fig->Model * fig->max_BB;
}