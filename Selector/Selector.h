#pragma once

#include "../Object/Object.h"
class Object;

class Selector {
public:
    Selector() = delete;
        
    static void DetectSelection(std::shared_ptr<Object> obj);
    static void performTransformation(glm::vec3 translate, glm::vec3 rotate, float scale);

    static void performTransformation(glm::mat4 model);
    static void changeObjectTag();
    //static void solidifyTransformation(glm::vec3 translate, glm::vec3 rotate, float scale);

private:
    static std::shared_ptr<Object> selectedObject;
    static glm::mat4 model;
    static glm::vec3 objectPos;
};