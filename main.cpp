#include "src/Shader/Shader.h"
#include "src/Window/Window.h"
#include "src/Camera/Camera.h"
#include "src/Texture/Texture.h"
#include "src/Shapes/Cube.h"
#include "src/Shapes/Plane.h"
#include "src/Shapes/Sphere.h"
#include "src/Player/PlayableCharacter.h"
#include "src/Scenegraph/Scenegraph.h"
#include "src/Object/Spawner.h"

#include <chrono>
#include <thread>
#include <random>
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

int main(void) {
    if (!glfwInit())
        return -1;

    Window* window = new Window(1600, 900, true, false);

    // Important to call it before IMGUI, so that I don't overwrite IMGUI INPUT callbacks
    InputSystem* IS = new InputSystem();
    IS->initializeInputSystem(window->getNativePointer());

    Scenegraph* sg = new Scenegraph();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window->getNativePointer(), true);
    ImGui_ImplOpenGL3_Init("#version 130");

    std::shared_ptr<Shader> shader =
        std::make_shared<Shader>("src/shader_text/basiclight.vert", "src/shader_text/basiclight.frag");
    shader->CACShaders(GL_VERTEX_SHADER);
    shader->CACShaders(GL_FRAGMENT_SHADER);

    std::shared_ptr<Shader> lightShader = std::make_shared<Shader>("src/shader_text/Light.vert", "src/shader_text/Light.frag");
    lightShader->CACShaders(GL_VERTEX_SHADER);
    lightShader->CACShaders(GL_FRAGMENT_SHADER);


    std::shared_ptr<Texture> ptd =
        std::make_shared<Texture>("src/Img/plane.jpg", "texture_diffuse");
    std::shared_ptr<Texture> pts =
        std::make_shared<Texture>("src/Img/planespec.png", "texture_specular");

    std::shared_ptr<Texture> ctd =
        std::make_shared<Texture>("src/Img/container2.png", "texture_diffuse");
    std::shared_ptr<Texture> cts =
        std::make_shared<Texture>("src/Img/container2_specular.png", "texture_specular");

    std::shared_ptr<Texture> c2td =
        std::make_shared<Texture>("src/Img/crate512.png", "texture_diffuse");
    std::shared_ptr<Texture> c2ts =
        std::make_shared<Texture>("src/Img/container2_specular.png", "texture_specular");

    std::shared_ptr<Texture> c3td =
        std::make_shared<Texture>("src/Img/a1.png", "texture_diffuse");
    std::shared_ptr<Texture> c3ts =
        std::make_shared<Texture>("src/Img/a1.png", "texture_specular");


    glm::vec3 pointLightPos[] = {
        glm::vec3(4.5f, 6.0f, 0.0f),
        glm::vec3(0.f, 6.0f, 3.0f),
        glm::vec3(1.5f, 3.0f, -3.0f),
        glm::vec3(-4.5f, 4.0f, 1.0f),
    };

    for (int q = 0; q < 4; q++) {
        auto lightSource = std::make_shared<Cube>(0.1f, Tag::NonCollidable);
        lightSource->globalPosition = pointLightPos[q];
        std::cout << "LightSource " + std::to_string(q) << " is set to : " << pointLightPos[q] << '\n';
        lightSource->setObjectShader(lightShader);
        sg->attachObject(lightSource);
    }
    auto pln = std::make_shared<Plane>(0.5f, Tag::Collidable);

    pln->setObjectShader(shader);
    pln->setTexture(ptd);
    pln->setTexture(pts);

    std::shared_ptr<PlayableCharacter> p = std::make_shared<PlayableCharacter>(glm::vec3(0.f, 0.f, 0.f));
    p->cameraRef().get()->cameraCurrentWorkingWindow(window->getNativePointer());

    std::cout << "player spawn pos : " << p->globalPosition << "\n";
    std::cout << "player camera pos : " << p->cameraRef().get()->Pos << "\n";
    pln->globalPosition = glm::vec3(p->globalPosition.x, -0.5f, p->globalPosition.z);
    sg->attachObject(pln);
    sg->attachObject(p);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distX(-5.0f, 5.0f);
    std::uniform_real_distribution<float> distZ(-5.0f, 5.0f);
    std::uniform_real_distribution<float> distFloatY(0.5f, 1.5f);

    // 10 collidable cubes at y = 0
    float exclusionRadius = 1.0f;

    // Collidable cubes on ground
    for (int i = 0; i < 10; ++i) {
        auto cube = std::make_shared<Cube>(0.3f, Tag::Collidable);
        glm::vec3 randomPos;
        glm::vec3 busyPos[10];
        int q = 0;
        do {
            randomPos = glm::vec3(distX(gen), -0.2f, distZ(gen));
        } while (glm::length(randomPos) < exclusionRadius && randomPos + cube->globalScale != busyPos[q]);
        busyPos[q] = randomPos;
        cube->globalPosition = randomPos;
        cube->setObjectShader(shader);
        cube->setTexture(ctd);
        cube->setTexture(cts);
        sg->attachObject(cube);
        q++;
    }

    for (int i = 0; i < 10; ++i) {
        auto sphere = std::make_shared<Sphere>(0.15f, Tag::Breakable);
        glm::vec3 randomPos;

        do {
            randomPos = glm::vec3(distX(gen), distFloatY(gen), distZ(gen));
        } while (glm::length(glm::vec3(randomPos.x, 0.0f, randomPos.z)) < exclusionRadius);
        sphere->globalPosition = randomPos;
        sphere->setObjectShader(shader);
        sphere->setTexture(c3td);
        sphere->setTexture(c3ts);
        sg->attachObject(sphere);
    }

    double previousTime = glfwGetTime();
    glEnable(GL_DEPTH_TEST);

    float sensitivity = 0.2f;

    float temp_x = 0.0f;
    float temp_y = 0.0f;
    float temp_z = 0.0f;

    float temp_yRot = 0.0f;
    float temp_xRot = 0.0f;
    float temp_zRot = 0.0f;

    float scale = 1.0f;

    bool uiMode = false;
    bool admin = false;
    bool parentMode = false;

    while (!glfwWindowShouldClose(window->getNativePointer())) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        double currentTime = glfwGetTime();
        double deltaTime = currentTime - previousTime;
        previousTime = currentTime;

        ImGui::Begin("Settings", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("Admin Mode: %s", admin ? "ON" : "OFF");
        ImGui::SliderFloat("Camera Sensitivity", &sensitivity, 0.01f, 1.0f);
        if (ImGui::Button("Add 5 Spheres")) {
            Spawner::SpawnSpheres(5, sg, shader, c3td, c3ts);
        }
        ImGui::SliderFloat("X", &temp_x, -10.f, 10.0f);
        ImGui::SliderFloat("Y", &temp_y, -10.f, 10.0f);
        ImGui::SliderFloat("Z", &temp_z, -10.f, 10.0f);

        ImGui::SliderFloat("X ROT", &temp_xRot, -1.f, 1.0f);
        ImGui::SliderFloat("Y ROT", &temp_yRot, -1.f, 1.0f);
        ImGui::SliderFloat("Z ROT", &temp_zRot, -1.f, 1.0f);

        ImGui::SliderFloat("SCALE", &scale, 0.f, 10.0f);
        Selector::performTransformation(
            glm::vec3(temp_x, temp_y, temp_z), glm::vec3(temp_yRot, temp_xRot, temp_zRot), scale);
        //if (ImGui::Button("Apply Transformation")) {
        //    Selector::performTransformation(
        //        glm::vec3(temp_x, temp_y, temp_z), glm::vec3(temp_yRot, temp_xRot, temp_zRot));
        //}

        if(ImGui::Button("Reset Transformation values")) {
            temp_x = 0.0f;
            temp_y = 0.0f;
            temp_z = 0.0f;
            temp_xRot = 0.0f;
            temp_yRot = 0.0f;
            temp_zRot = 0.0f;
            scale = 1.f;
        }
        if(ImGui::Button("Change State to Breakable")) {
            Selector::changeObjectTag();
        }
        if (ImGui::Button("Quit")) {
            glfwSetWindowShouldClose(window->getNativePointer(), true);
        }
        ImGui::End();

        p->cameraRef()->sens = sensitivity;

        if (IS->isKeyPressed(GLFW_KEY_T)) {
            uiMode = !uiMode;
            glfwSetInputMode(window->getNativePointer(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        if (IS->isKeyPressed(GLFW_KEY_Q)) {
            admin = !admin;
            p->setAdminMode(admin);
        }
        if(IS->isKeyPressed(GLFW_KEY_E)) {
            parentMode = !parentMode;
            p->setParentMode(parentMode);
        }

        if (uiMode == false) {
            glfwSetInputMode(window->getNativePointer(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            p->processPlayerInput(static_cast<float>(deltaTime), IS);
            p->update(static_cast<float>(deltaTime));
        }

        shader->bind();
        shader->SUvec3("viewPos", p->cameraRef().get()->Pos);
        glm::mat4 projection =
            glm::perspective(glm::radians(45.0f), (float)window->getWidth() / (float)window->getHeight(), 0.1f, 100.0f);
        shader->SUmat4("projection", projection);
        shader->SUmat4("view", p->cameraRef().get()->getViewMatrix());
        shader->SUvec3("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
        shader->SUvec3("dirLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
        shader->SUvec3("light.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
        shader->SUvec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        shader->SUvec3("light.ambient", glm::vec3(0.5f, 0.5f, 0.5f));
        shader->SUvec3("light.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
        shader->SUvec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        shader->SUfloat("light.constant", 1.0f);
        shader->SUfloat("light.linear", 0.045f);
        shader->SUfloat("light.quadratic", 0.0075f);
        shader->SUfloat("material.shininess", 64.0f);

        shader->SUvec3("lights[0].position", pointLightPos[0]);
        shader->SUvec3("lights[0].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
        shader->SUvec3("lights[0].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
        shader->SUvec3("lights[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));
        shader->SUfloat("lights[0].constant", 1.0f);
        shader->SUfloat("lights[0].linear", 0.09f);
        shader->SUfloat("lights[0].quadratic", 0.032f);
        // point light 2
        shader->SUvec3("lights[1].position", pointLightPos[1]);
        shader->SUvec3("lights[1].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
        shader->SUvec3("lights[1].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
        shader->SUvec3("lights[1].specular", glm::vec3(1.0f, 1.0f, 1.0f));
        shader->SUfloat("lights[1].constant", 1.0f);
        shader->SUfloat("lights[1].linear", 0.09f);
        shader->SUfloat("lights[1].quadratic", 0.032f);
        // point light 3
        shader->SUvec3("lights[2].position", pointLightPos[2]);
        shader->SUvec3("lights[2].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
        shader->SUvec3("lights[2].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
        shader->SUvec3("lights[2].specular", glm::vec3(1.0f, 1.0f, 1.0f));
        shader->SUfloat("lights[2].constant", 1.0f);
        shader->SUfloat("lights[2].linear", 0.09f);
        shader->SUfloat("lights[2].quadratic", 0.032f);
        // point light 4
        shader->SUvec3("lights[3].position", pointLightPos[3]);
        shader->SUvec3("lights[3].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
        shader->SUvec3("lights[3].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
        shader->SUvec3("lights[3].specular", glm::vec3(1.0f, 1.0f, 1.0f));
        shader->SUfloat("lights[3].constant", 1.0f);
        shader->SUfloat("lights[3].linear", 0.09f);
        shader->SUfloat("lights[3].quadratic", 0.032f);
        // spotLight
        shader->SUvec3("spotLight.position", p->cameraRef().get()->Pos);
        shader->SUvec3("spotLight.direction", p->cameraRef().get()->Front);
        shader->SUvec3("spotLight.ambient", glm::vec3(0.0f, 0.0f, 0.0f));
        shader->SUvec3("spotLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
        shader->SUvec3("spotLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        shader->SUfloat("spotLight.constant", 1.0f);
        shader->SUfloat("spotLight.linear", 0.09f);
        shader->SUfloat("spotLight.quadratic", 0.032f);
        shader->SUfloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        shader->SUfloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

        lightShader->bind();
        lightShader->SUmat4("view", p->cameraRef().get()->getViewMatrix());
        lightShader->SUmat4("projection", projection);

        sg->render(p->cameraRef().get()->getViewMatrix(), projection);
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        IS->clearReleasedKeys();
        window->swapBuffers();
        window->pollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window->getNativePointer());
    glfwTerminate();
    return 0;
}
