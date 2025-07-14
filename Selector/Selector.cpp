#include "Selector.h"

std::shared_ptr<Object> Selector::selectedObject = nullptr;

glm::mat4 Selector::model = glm::mat4(1.f);
//glm::vec3 Selector::objectPos = glm::vec3(0.f);


void Selector::DetectSelection(std::shared_ptr<Object> object) {
    if(object) {
        selectedObject = object;
    }
}

void Selector::performTransformation(glm::mat4 model) {
    if (selectedObject == nullptr) { return; }
    std::shared_ptr<Shader> temp_s = selectedObject->getShader();

    temp_s->SUmat4("model", model);
}


void Selector::performTransformation(glm::vec3 translate, glm::vec3 rotate, float scale) {
    if (selectedObject == nullptr) { return; }
    auto& temp_s = selectedObject->getShader();

    static glm::vec3 prevTranslate = glm::vec3(0.f);
    static glm::vec3 prevRotate = glm::vec3(0.f);
    static float prevScale = 1.f;

    // Compute deltas
    glm::vec3 deltaTranslate = translate - prevTranslate;
    glm::vec3 deltaRotate = rotate - prevRotate;
    float deltaScale = scale - prevScale;

    if (deltaTranslate != glm::vec3(0.f)) {
        selectedObject->globalPosition += deltaTranslate;
    }
    if (deltaRotate != glm::vec3(0.f)) {
        selectedObject->globalRotation += deltaRotate;
    }

    if (deltaScale != 1.f) {
        selectedObject->globalScale += deltaScale;
    }

    // Save current state for next frame
    prevTranslate = translate;
    prevRotate = rotate;
    prevScale = scale;

    temp_s->SUmat4("model", selectedObject->transform());
}

void Selector::changeObjectTag() {
    if (selectedObject == nullptr) { return; }
    selectedObject->setObjTag(Tag::Breakable);
}
