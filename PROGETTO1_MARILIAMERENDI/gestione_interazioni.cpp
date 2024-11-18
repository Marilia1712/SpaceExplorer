#pragma once
#include "lib.h"
#include "strutture.h"
#include "gestione_interazioni.h"

extern GLFWwindow* window;
extern Curva player;
extern int height, width;
extern mat4 Projection;
extern float  w_update, h_update;
extern bool restart_game;


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

    // Se il tasto ESCAPE è premuto, chiude la finestra
    switch (key) {
    case GLFW_KEY_ESCAPE:

        if (action == GLFW_PRESS)
            //Imposta a True il flag booleano di chiusura della finestr
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        break;

    case GLFW_KEY_A:
        if ((action == GLFW_REPEAT || action == GLFW_PRESS) && player.position.y <= height) {
            player.position.y += 25;
        }
        break;

    case GLFW_KEY_Z:
        if ((action == GLFW_REPEAT || action == GLFW_PRESS) && player.position.y >= 0) {
            player.position.y -= 25;
        }
        break;

    case GLFW_KEY_R:
        if (action == GLFW_PRESS) {
            restart_game = true;
        }

    default:
        break;
    }

}

void framebuffer_size_callback(GLFWwindow* window, int w, int h)
{
    if (h == 0) h = 1;

    Projection = ortho(0.0f, (float)width, 0.0f, (float)height);

    float AspectRatio_mondo = (float)(width) / (float)(height);

    if (AspectRatio_mondo > w / h)   //Se ridimensioniamo la larghezza della Viewport
    {
        w_update = (float)w;
        h_update = w / AspectRatio_mondo;
    }
    else {  

        w_update = h * AspectRatio_mondo; 
        h_update = (float)h;
    }
    glViewport(0.0, 0.0, w_update, h_update);

}

