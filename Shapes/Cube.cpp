#include "Cube.h"

void Cube::setup() {


        std::vector<Vertex> cubeVertices = {
            // TEST SCALE
    {{-1.0f * scaleSize, -1.0f * scaleSize, -1.0f * scaleSize}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
    {{ 1.0f * scaleSize, -1.0f * scaleSize, -1.0f * scaleSize}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},
    {{ 1.0f * scaleSize,  1.0f * scaleSize, -1.0f * scaleSize}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},
    {{-1.0f * scaleSize,  1.0f * scaleSize, -1.0f * scaleSize}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},
    // Back Face
    {{-1.0f * scaleSize, -1.0f * scaleSize,  1.0f * scaleSize}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
    {{ 1.0f * scaleSize, -1.0f * scaleSize,  1.0f * scaleSize}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
    {{ 1.0f * scaleSize,  1.0f * scaleSize,  1.0f * scaleSize}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
    {{-1.0f * scaleSize,  1.0f * scaleSize,  1.0f * scaleSize}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
    // Left Face
    {{-1.0f * scaleSize,  1.0f * scaleSize, -1.0f * scaleSize}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
    {{-1.0f * scaleSize, -1.0f * scaleSize, -1.0f * scaleSize}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
    {{-1.0f * scaleSize, -1.0f * scaleSize,  1.0f * scaleSize}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
    {{-1.0f * scaleSize,  1.0f * scaleSize,  1.0f * scaleSize}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
    // Right Face
    {{ 1.0f * scaleSize, -1.0f * scaleSize, -1.0f * scaleSize}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
    {{ 1.0f * scaleSize,  1.0f * scaleSize, -1.0f * scaleSize}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
    {{ 1.0f * scaleSize,  1.0f * scaleSize,  1.0f * scaleSize}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
    {{ 1.0f * scaleSize, -1.0f * scaleSize,  1.0f * scaleSize}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
    // Bottom Face
    {{-1.0f * scaleSize, -1.0f * scaleSize, -1.0f * scaleSize}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},
    {{ 1.0f * scaleSize, -1.0f * scaleSize, -1.0f * scaleSize}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},
    {{ 1.0f * scaleSize, -1.0f * scaleSize,  1.0f * scaleSize}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}},
    {{-1.0f * scaleSize, -1.0f * scaleSize,  1.0f * scaleSize}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}},
    // Top Face
    {{ 1.0f * scaleSize,  1.0f * scaleSize, -1.0f * scaleSize}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
    {{-1.0f * scaleSize,  1.0f * scaleSize, -1.0f * scaleSize}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
    {{-1.0f * scaleSize,  1.0f * scaleSize,  1.0f * scaleSize}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
    {{ 1.0f * scaleSize,  1.0f * scaleSize,  1.0f * scaleSize}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
    };

    this->vertices = cubeVertices;

    std::vector<uint32_t> cubeIndices = {
        0,  3,  2,
        2,  1,  0,
        4,  5,  6,
        6,  7,  4,
        // left and right
        11, 8,  9,
        9,  10, 11,
        12, 13, 14,
        14, 15, 12,
        // bottom and top
        16, 17, 18,
        18, 19, 16,
        20, 21, 22,
        22, 23, 20
    };

    this->indices = cubeIndices;

    mesh = std::make_shared<Mesh>(vertices, indices);
    
    auto tag = getObjTag();
    if(tag == Tag::Collidable || tag == Tag::Breakable) {
        auto xyz = mesh->getVerts();
        min = xyz[0];
        max = xyz[0];
        for (int q = 0; q < xyz.size(); q++) {
            min = glm::min(xyz[q], min);
            max = glm::max(xyz[q], max);
        }
        std::cout << "Collision Box for " << this << ": "
            << min << " to " << max << "\n";
        this->setObjBB(min, max);
    }
}

//if (getObjTag() == Tag::Collidable || Tag::Player) {
//    // Calculate based on actual intended collision size
//    float collisionSize = scaleSize * 0.25f; // Half of vertex range
//    min = glm::vec3(-collisionSize);
//    max = glm::vec3(collisionSize);

//    this->setObjBB(min, max);

//    std::cout << "Collision Box for " << this << ": "
//        << min << " to " << max << "\n";
//}
// if the object is non collidable, there is no point in calculating the bb