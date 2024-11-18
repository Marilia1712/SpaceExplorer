#pragma once
#include "lib.h"
#include "ShaderMaker.h"
#include "strutture.h" 
#include "inizializzazioni.h"
#include "init_geometrie.h"
#include "gestione_interazioni.h"
#include "Utilities.h"

extern unsigned int programId, programIdS, programId_text;
extern GLint frameVar;
extern float r, g, b, PI;
extern unsigned int MatProjS, MatModelS, MatProj, MatModel, vec_resS, loc_time, loc_numberOfClouds;
extern mat4 Projection;
extern vec2 resolution;
extern int  height, width;
extern float deltaTime;
extern unsigned int programId_text, VAO_Text, VBO_Text;
extern vector<float> timerFig;
extern vector<Figura> Scena;
extern bool show_bounding_boxes;
extern Figura background, star;
extern Curva player;


void render(float currentFrame, int frame) {
    int n_deleted = 0;
    int i;
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    //Localizzo e associo le variabili di input allo shader dello sfondo
    //iFrame rappresenta il numero di frame corrente e serve a rendere lo sfondo animato
    GLint frameVar = glGetUniformLocation(programIdS, "iFrame");
    glUseProgram(Scena[0].programId);
    glUniform1i(frameVar, frame);

    //height corrisponde all'altezza della finestra di gioco
    GLint heightVar = glGetUniformLocation(programIdS, "height");
    glUseProgram(Scena[0].programId);
    glUniform1i(heightVar, height);


    //DIsegna il piano di sfondo
    Scena[0].Model = mat4(1.0);
    Scena[0].Model = scale(Scena[0].Model, background.scale);
    glUniformMatrix4fv(MatProjS, 1, GL_FALSE, value_ptr(Projection));
    glUniformMatrix4fv(MatModelS, 1, GL_FALSE, value_ptr(Scena[0].Model));
    glUniform2fv(vec_resS, 1, value_ptr(resolution));
    //glUniform1f(loc_time, currentFrame);
    glBindVertexArray(Scena[0].VAO);
    glDrawArrays(Scena[0].render, 0, Scena[0].nv);


    //Disegna il player
    player.angolo = cos(radians(float(frame))) * 0.8;
    glUseProgram(Scena[1].programId);
    glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));
    player.Model = mat4(1.0);
    player.Model = translate(player.Model, vec3(player.position.x, player.position.y, 0.0));
    player.Model = rotate(player.Model, radians(player.angolo), vec3(0.0, 0.0, 1.0));
    player.Model = scale(player.Model, player.scale);
    glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(player.Model));
    glBindVertexArray(player.VAO);
    glDrawArrays(player.render, 0, player.nv - 4);
    if (show_bounding_boxes)
        glDrawArrays(GL_LINE_LOOP, player.nv - 4, 4);


    //Disegna le forme animate (meteoriti e stella)
    for (i = 1; i < Scena.size(); i++) {

        // le forme sono renderizzate solo se non sono entrate in collisione con la navicella
        // e non sono uscite dallo schermo
        if (Scena[i].isalive == true)
        {

            Scena[i].timerFig += deltaTime;
            if (Scena[i].timerFig >= 1.0f) { // Aggiorna ogni 1 second0
                Scena[i].timerFig = 0.0f;
            };

            update_angle(&Scena[i]);
            update_position(&Scena[i]);


            glUseProgram(Scena[i].programId);
            glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));

            Scena[i].Model = mat4(1.0);
            Scena[i].Model = translate(Scena[i].Model, vec3(Scena[i].position.x, Scena[i].position.y, 1.0));
            Scena[i].Model = scale(Scena[i].Model, Scena[i].scale);
            Scena[i].Model = rotate(Scena[i].Model, Scena[i].angolo, vec3(0.0, 0.0, 1.0));

            //update Bounding Box
            updateBB(&Scena[i]);

            glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(Scena[i].Model));
            glBindVertexArray(Scena[i].VAO);
            //renderizza la shape
            glDrawArrays(Scena[i].render, 0, Scena[i].nv - 4);
            //renderizza il bounding box (contenuto nelle ultime quattro posizioni dei vertici)
            if (show_bounding_boxes)
                glDrawArrays(GL_LINE_LOOP, Scena[i].nv - 4, 4);

            updateBB(&player);
            updateBB(&Scena[i]);

            //verifica delle collisioni
            if (checkCollision(&player, &Scena[i])) {
                Scena[i].isalive = false;
                // Se la figura entrata in collisione e un meteorite, il giocatore perde una vita
                if (Scena[i].eltype == METEORITE && player.isalive == true) {
                    player.numLives--;
                    if (player.numLives == 0) {
                        player.isalive = false;
                    }
                }
                //se invece si tratta di una stella, il giocatore guadagna 50 punti
                else if (Scena[i].eltype == STELLA && player.isalive == true) {
                    player.numPoints += 50;
                }
            }
        }

        //in caso di collisione o di fine schermo, la figura riappare sul lato destro ad un'altezza casuale
        else if (Scena[i].isalive == false) {
            Scena[i].position.x = width;
            Scena[i].position.y = randomPosition(width,height).y;
            Scena[i].isalive = true;
        }
    }

    glUseProgram(Scena[1].programId);
}