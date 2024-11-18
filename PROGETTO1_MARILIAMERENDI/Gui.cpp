#pragma once 
#include "ImGui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imGui/imgui_impl_opengl3.h"
#include "strutture.h"
#include <math.h>

//extern bool dead;
extern int width, height;
extern Curva player;
extern bool show_bounding_boxes;

void Initialize_IMGUI(GLFWwindow* window) {

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
}

void my_interface()
{
    ImGuiIO& io = ImGui::GetIO();
    io.FontGlobalScale = 1.5f;
    ImGui_ImplGlfw_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    // Crea una finestra per le informazioni sul giocatore: vite, punti e record di punti
    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(200,110), ImGuiCond_Always);
    ImGui::Begin("Player info:");
    switch (player.numLives) {
        case(3):
            ImGui::Text("Lives: X X X");
            break;
        case(2):
            ImGui::Text("Lives: X X");
            break;
        case(1):
            ImGui::Text("Lives: X");
            break;
        default:
            ImGui::Text("Lives: -");
            break;
    }
    ImGui::Text("Points: %d", player.numPoints);
    ImGui::Text("Record: %d", player.pointsRecord);
    ImGui::End();

    // Crea una finestra per i comandi del giocatore
    ImGui::SetNextWindowPos(ImVec2(680,620), ImGuiCond_Always); 
    ImGui::SetNextWindowSize(ImVec2(300,90), ImGuiCond_Always);
    ImGui::Begin("Controls");
    ImGui::Text("Press or hold A to go up");
    ImGui::Text("Press or hold Z to go down");
    ImGui::End();

    // Crea una finestra per il game over
    if (player.isalive == false) { //questa finestra compare solo quando il giocatore non ha più vite
        ImGui::SetNextWindowPos(ImVec2(250,150), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(500, 500), ImGuiCond_Always);
        ImGui::Begin("Game Over");
        ImGui::Text("GAME OVER");
        ImGui::Text("press R to restart");
        ImGui::End();
    }

    ImGui::Render();

}

void close_GUI() {

    ImGui_ImplOpenGL3_Shutdown(); 
    ImGui_ImplGlfw_Shutdown(); 
    ImGui::DestroyContext();
}
