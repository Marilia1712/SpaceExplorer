#include "lib.h"
#include "ShaderMaker.h"
#include "strutture.h" 
#include "inizializzazioni.h"
#include "init_geometrie.h"
#include "gestione_interazioni.h"
#include "Utilities.h"
#include "rendering.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "Gui.h"
#define PI 3.14159265358979323

//Variabili globali -------------------------------------------------------------------
unsigned int programId, programIdS, programId_text;
unsigned int VAO_Text, VBO_Text;

int i, j;
float w_update, h_update;
float deltaTime = 0.0f;
float frame;
float lastFrame = 0.0f;
float refreshTime = 0.001f;

float r = 0.0, g = 0.2, b = 1.0;
int height = 1000, width = 1000;
vec2 resolution;
mat4 Projection;
GLuint MatProj, MatModel, MatProjS, MatModelS, vec_resS, loc_time;


bool show_bounding_boxes = false;
bool restart_game = false;

//----------------------------------------------------------------------------------------

//tutti gli elementi che compongono il gioco
vector<Figura> Scena;
Figura background = { }, star = { }, star2 = {};
Curva meteor1 = INIT_FORMA("meteor.txt", vec4(0.18, 0.004, 0.004,1.0), vec4(0.4, 0, 0, 1.0), METEORITE);
Curva meteor2 = INIT_FORMA("meteor.txt", vec4(0.22, 0, 0.137, 1.0), vec4(0.439, 0, 0.275, 1.0), METEORITE);
Curva meteor3 = INIT_FORMA("meteor.txt", vec4(0.322, 0.122, 0, 1.0), vec4(0.431, 0.165, 0, 1.0), METEORITE);
Curva player = INIT_FORMA("spaceship.txt", vec4(0.345, 0.522, 0.51, 1.0), vec4(1.0, 1.0, 1.0, 1.0), PLAYER);



// per ricominciare il gioco
void restart() {
    if (player.isalive == false) {
        restart_game = false;
        player.isalive = true;

        //ripristina le vite
        player.numLives = 3;

        //aggiorna i punti
        if (player.numPoints > player.pointsRecord) {
            player.pointsRecord = player.numPoints;
        }
        player.numPoints = 0;
        player.position.x = width / 5.0;
        player.position.y = height / 2.0;

   }
}

int main(void)
{
    GLFWwindow* window;
    
    if (!glfwInit())
        return -1;

    //Imposta le proprietà del contesto e del profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(height, width, "Space Explorer", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create the window !" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failde to load opengl function pointers !" << std::endl;
        glfwTerminate();
        return -1;
    }

    //inizializzazione degli shader
    INIT_SHADER();
    //Registrazione delle funzioni di callback 
    glfwSetKeyCallback(window, key_callback);
    //per visualizzare le dimensioni della finestra ridimensionata
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // localizzazione delle variabili di input degli shader
    Projection = ortho(0.0f, float(width), 0.0f, float(height));
    MatProj = glGetUniformLocation(programId, "Projection");
    MatModel = glGetUniformLocation(programId, "Model");
    MatProjS = glGetUniformLocation(programIdS, "Projection");
    MatModelS = glGetUniformLocation(programIdS, "Model");
    vec_resS = glGetUniformLocation(programIdS, "resolution");
    loc_time = glGetUniformLocation(programIdS, "time");

    resolution = vec2(float(height), float(width));
    Initialize_IMGUI(window);

    //Giocatore
    player.eltype = PLAYER;
    player.isalive = true;
    player.numLives = 3;
    player.numPoints = 0;
    player.programId = programId;
    player.position.x = width / 5.0;
    player.position.y = height / 2.0;
    player.scale = vec3(180.0, 180.0, 1.0);
    INIT_VAO_Curva(&player);
    

    //Sfondo
    background.nTriangles = 2;
    background.programId = programIdS;
    background.scale = vec3(2.0 * float(width), 2.0 * float(height), 1.0);
    INIT_PIANO(&background);
    INIT_VAO(&background);
    Scena.push_back(background);

    //Stella
    create_star(&star, programId);
    Scena.push_back(star);

    //Meteoriti
    create_meteor(&meteor1, programId);
    Scena.push_back(meteor1);
    create_meteor(&meteor2, programId);
    Scena.push_back(meteor2);
    create_meteor(&meteor3, programId);
    Scena.push_back(meteor3);

    // loopgame che termina solo alla chiusura della finestra di gioco
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;

        if (deltaTime > refreshTime) {
            lastFrame = currentFrame;
            frame++;

            /* Render here */
            my_interface();

            if (restart_game) {
                restart();
            }

            render(currentFrame, frame);

            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            /* Swap front and back buffers */
            glfwSwapBuffers(window);
            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    glDeleteProgram(programId);
    glDeleteProgram(programIdS);
    for (i = 0; i < Scena.size(); i++)
    {
        glDeleteBuffers(1, &Scena[i].VBO_vertices);
        glDeleteBuffers(1, &Scena[i].VBO_colors);
        glDeleteVertexArrays(1, &Scena[i].VAO);
    }

    glfwTerminate();

    return 0;
}





