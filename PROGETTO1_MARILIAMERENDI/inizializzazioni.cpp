#pragma once
#include <glad/glad.h>
#include "ShaderMaker.h"
#include "strutture.h"

extern unsigned int programId, programIdS, programId_text;
extern unsigned int VAO_Text, VBO_Text;

void INIT_SHADER(void)
{
    GLenum ErrorCheckValue = glGetError();

    char* vertexShader = (char*)"vertexshaderM.glsl";
    char* fragmentShader = (char*)"fragmentshaderM.glsl";
    // La funzione successiva crea un programma shader completo a partire da due shader individuali: 
    // uno per la gestione dei vertici e uno per la gestione dei pixel. 
    // Il programma shader risultante viene identificato da un numero univoco (il programId) che verr  utilizzato in seguito per associarlo ad un oggetto grafico e per renderizzarlo.
     //All'interno della funzione ShaderMaker::createProgram
        //Compilazione degli shader : La funzione compila i due shader individuali, verificando che non ci siano errori di sintassi.
        //Linkaggio : Una volta compilati, i due shader vengono collegati insieme per formare un programma shader completo.
        // Creazione dell'identificativo: Viene generato un identificativo univoco per il programma shader e viene restituito alla funzione chiamante.

    programId = ShaderMaker::createProgram(vertexShader, fragmentShader);



    //CCrea un program shader per la renderizzazione del background
    vertexShader = (char*)"vertexshaderSf.glsl";
    fragmentShader = (char*)"fragmentShader_Space.glsl";

    programIdS = ShaderMaker::createProgram(vertexShader, fragmentShader);

    //Generazione del program shader per la gestione del testo
    vertexShader = (char*)"VertexShader_Text.glsl";
    fragmentShader = (char*)"FragmentShader_Text.glsl";

    programId_text = ShaderMaker::createProgram(vertexShader, fragmentShader);


}


void INIT_VAO(Figura* fig)
{
    //La funzione INIT_VAO  ha per input Figura* fig, che è  un puntatore  che punta all'indirizzo ricevuto.
    //In questo modo è  possibile modificare direttamente i dati della struttura originale, evitando la creazione di copie inutili.

    glGenVertexArrays(1, &fig->VAO);
    glBindVertexArray(fig->VAO);
    //Genero , rendo attivo, riempio il VBO della geometria dei vertices
    glGenBuffers(1, &fig->VBO_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, fig->VBO_vertices);

    //fig->vertices.size() : Ottiene il numero di elementi nel vettore vertices della struttura Figura puntata da fig.
    // sizeof(vec3) : Ottiene la dimensione in byte di un singolo elemento di tipo vec3.
    //La moltiplicazione fig->vertices.size() * sizeof(vec3): calcola la dimensione totale in byte dei dati dei vertici. Calcola la dimensione totale in byte di tutti i dati dei vertici.

    //fig->vertices.data() : fornisce un puntatore all'inizio dei dati del vettore vertices. Questo puntatore indica la posizione esatta in memoria dove sono memorizzati i dati

    glBufferData(GL_ARRAY_BUFFER, fig->vertices.size() * sizeof(vec3), fig->vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    //Genero , rendo attivo, riempio il VBO dei colori
    glGenBuffers(1, &fig->VBO_colors);
    glBindBuffer(GL_ARRAY_BUFFER, fig->VBO_colors);
    glBufferData(GL_ARRAY_BUFFER, fig->colors.size() * sizeof(vec4), fig->colors.data(), GL_STATIC_DRAW);
    //Adesso carico il VBO dei coloris nel layer 2
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

}

void INIT_VAO_DYNAMIC(Figura* fig)
{
    //La funzione INIT_VAO  ha per input Figura* fig, che è  un puntatore  che punta all'indirizzo ricevuto.
    //In questo modo è  possibile modificare direttamente i dati della struttura originale, evitando la creazione di copie inutili.

    glGenVertexArrays(1, &fig->VAO);
    glBindVertexArray(fig->VAO);
    //Genero , rendo attivo, riempio il VBO della geometria dei vertices
    glGenBuffers(1, &fig->VBO_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, fig->VBO_vertices);

    //fig->vertices.size() : Ottiene il numero di elementi nel vettore vertices della struttura Figura puntata da fig.
    // sizeof(vec3) : Ottiene la dimensione in byte di un singolo elemento di tipo vec3.
    //La moltiplicazione fig->vertices.size() * sizeof(vec3): calcola la dimensione totale in byte dei dati dei vertici. Calcola la dimensione totale in byte di tutti i dati dei vertici.

    //fig->vertices.data() : fornisce un puntatore all'inizio dei dati del vettore vertices. Questo puntatore indica la posizione esatta in memoria dove sono memorizzati i dati

     //GL_DYNAMIC_DRAW indica che il contenuto del buffer verrà modificato frequentemente durante l'esecuzione del programma

    glBufferData(GL_ARRAY_BUFFER, fig->vertices.size() * sizeof(vec3), fig->vertices.data(), GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    //Genero , rendo attivo, riempio il VBO dei colori
    glGenBuffers(1, &fig->VBO_colors);
    glBindBuffer(GL_ARRAY_BUFFER, fig->VBO_colors);
    glBufferData(GL_ARRAY_BUFFER, fig->colors.size() * sizeof(vec4), fig->colors.data(), GL_DYNAMIC_DRAW);
    //Adesso carico il VBO dei coloris nel layer 2
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

}

void INIT_VAO_DYNAMIC_NULL(Figura* fig)
{
    //La funzione INIT_VAO  ha per input Figura* fig, che è  un puntatore  che punta all'indirizzo ricevuto.
    //In questo modo è  possibile modificare direttamente i dati della struttura originale, evitando la creazione di copie inutili.

    glGenVertexArrays(1, &fig->VAO);
    glBindVertexArray(fig->VAO);
    //Genero , rendo attivo, riempio il VBO della geometria dei vertices
    glGenBuffers(1, &fig->VBO_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, fig->VBO_vertices);

    //fig->vertices.size() : Ottiene il numero di elementi nel vettore vertices della struttura Figura puntata da fig.
    // sizeof(vec3) : Ottiene la dimensione in byte di un singolo elemento di tipo vec3.
    //La moltiplicazione fig->vertices.size() * sizeof(vec3): calcola la dimensione totale in byte dei dati dei vertici. Calcola la dimensione totale in byte di tutti i dati dei vertici.

    //NULL: Questo parametro indica che al momento della creazione del buffer non stiamo copiando alcun dato al suo interno. 
    // Stiamo semplicemente allocando lo spazio necessario.
    //GL_DYNAMIC_DRAW indica che il contenuto del buffer verrà modificato frequentemente durante l'esecuzione del programma

    glBufferData(GL_ARRAY_BUFFER, fig->nv * sizeof(vec3), NULL, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    //Genero , rendo attivo, riempio il VBO dei colori
    glGenBuffers(1, &fig->VBO_colors);
    glBindBuffer(GL_ARRAY_BUFFER, fig->VBO_colors);
    glBufferData(GL_ARRAY_BUFFER, fig->nv * sizeof(vec4), NULL, GL_DYNAMIC_DRAW);
    //Adesso carico il VBO dei coloris nel layer 2
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

}

void UPDATE_VAO_DYNAMIC(Figura* fig)
{


    glBindVertexArray(fig->VAO);
    //Rendo attivo il VBO della geometria dei vertices
    glBindBuffer(GL_ARRAY_BUFFER, fig->VBO_vertices);


    //glBufferSubData copia le posizioni dei vertici aggiornate da fig->vertices nell'oggetto vertex buffer object. 
    // Questo consente aggiornamenti efficienti senza dover ricreare l'intero VBO ogni volta che i dati cambiano.

    glBufferSubData(GL_ARRAY_BUFFER, 0, fig->vertices.size() * sizeof(vec3), fig->vertices.data());

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);



    glBindBuffer(GL_ARRAY_BUFFER, fig->VBO_colors);
    glBufferSubData(GL_ARRAY_BUFFER, 0, fig->colors.size() * sizeof(vec4), fig->colors.data());

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

}

void INIT_VAO_Curva(Curva* fig)
{

    glGenVertexArrays(1, &fig->VAO);
    glBindVertexArray(fig->VAO);

    //Genero , rendo attivo, riempio il VBO della geometria dei vertici di COntrollo
    glGenBuffers(1, &fig->VBO_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, fig->VBO_vertices);
    glBufferData(GL_ARRAY_BUFFER, fig->nv * sizeof(vec3), fig->vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    //Genero , rendo attivo, riempio il VBO dei colori nei vertici di controllo
    glGenBuffers(1, &fig->VBO_colors);
    glBindBuffer(GL_ARRAY_BUFFER, fig->VBO_colors);
    glBufferData(GL_ARRAY_BUFFER, fig->nv * sizeof(vec4), fig->colors.data(), GL_STATIC_DRAW);
    //Adesso carico il VBO dei colori nel layer 2
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);


    //Genero , rendo attivo, riempio il VBO della geometria dei vertici di COntrollo
    glGenBuffers(1, &fig->VBO_CP);
    glBindBuffer(GL_ARRAY_BUFFER, fig->VBO_CP);
    glBufferData(GL_ARRAY_BUFFER, fig->ncp * sizeof(vec3), fig->CP.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(2);

    //Genero , rendo attivo, riempio il VBO dei colori nei vertici di controllo
    glGenBuffers(1, &fig->VBO_CP_colors);
    glBindBuffer(GL_ARRAY_BUFFER, fig->VBO_CP_colors);
    glBufferData(GL_ARRAY_BUFFER, fig->ncp * sizeof(vec4), fig->colCP.data(), GL_STATIC_DRAW);
    //Adesso carico il VBO dei colori nel layer 2
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(3);

    //Genero , rendo attivo, riempio il VBO della geometria dei vertici di COntrollo
    glGenBuffers(1, &fig->VBO_TG);
    glBindBuffer(GL_ARRAY_BUFFER, fig->VBO_TG);
    glBufferData(GL_ARRAY_BUFFER, fig->ntg * sizeof(vec3), fig->tg.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(4);

    //Genero , rendo attivo, riempio il VBO dei colori nei vertici di controllo
    glGenBuffers(1, &fig->VBO_TG_colors);
    glBindBuffer(GL_ARRAY_BUFFER, fig->VBO_TG_colors);
    glBufferData(GL_ARRAY_BUFFER, fig->ntg * sizeof(vec4), fig->col_tg.data(), GL_STATIC_DRAW);
    //Adesso carico il VBO dei colori nel layer 2
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(5);


}

void INIT_VAO_Text(void)
{

    // configure VAO/VBO for texture quads
    // -----------------------------------
    glGenVertexArrays(1, &VAO_Text);
    glGenBuffers(1, &VBO_Text);
    glBindVertexArray(VAO_Text);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Text);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
}