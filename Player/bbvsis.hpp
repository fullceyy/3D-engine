#include "../Mesh/Mesh.h"
#include "../Object/Object.h"
#include "../Player/Boundingbox.h"


//class BoundingBoxVisualizer {
//public:
//    BoundingBoxVisualizer(Bounding_Box bb, std::shared_ptr<Object> object) {
//        this->bbvismax = bb.maxObjectVal;
//        this->bbvismin = bb.minObjectVal;
//
//        mesh = object->getMeshRef();
//
//    }
//    void draw(GLenum type) { 
//        mesh->draw(type);
//    }
//private:
//    std::shared_ptr<Mesh> mesh;
//    glm::vec3 bbvismin;
//    glm::vec3 bbvismax;
//};


class BoundingBoxVisualizer {
public:
    BoundingBoxVisualizer(std::shared_ptr<Object> object) {
        // Create wireframe-specific mesh
        Bounding_Box bb = object->getObjBB();

        // Create vertices for the 8 corners of the AABB
        //std::vector<Vertex> vertices = {
        //    {{bb.minObjectVal.x, bb.minObjectVal.y, bb.minObjectVal.z}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}, // 0
        //    {{bb.maxObjectVal.x, bb.minObjectVal.y, bb.minObjectVal.z}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}, // 1
        //    {{bb.maxObjectVal.x, bb.minObjectVal.y, bb.maxObjectVal.z}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}, // 2
        //    {{bb.minObjectVal.x, bb.minObjectVal.y, bb.maxObjectVal.z}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}, // 3
        //    {{bb.minObjectVal.x, bb.maxObjectVal.y, bb.minObjectVal.z}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}, // 4
        //    {{bb.maxObjectVal.x, bb.maxObjectVal.y, bb.minObjectVal.z}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}, // 5
        //    {{bb.maxObjectVal.x, bb.maxObjectVal.y, bb.maxObjectVal.z}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}, // 6
        //    {{bb.minObjectVal.x, bb.maxObjectVal.y, bb.maxObjectVal.z}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}  // 7
        //};

        // was just wfVertex before with 1.0fvec3 at the end as color layout
        std::vector<Vertex> vertices = {
    {{bb.minObjectVal.x, bb.minObjectVal.y, bb.minObjectVal.z}, {}, {}},
    {{bb.maxObjectVal.x, bb.minObjectVal.y, bb.minObjectVal.z}, {}, {}},
    {{bb.maxObjectVal.x, bb.minObjectVal.y, bb.maxObjectVal.z}, {}, {}},
    {{bb.minObjectVal.x, bb.minObjectVal.y, bb.maxObjectVal.z}, {}, {}},
    {{bb.minObjectVal.x, bb.maxObjectVal.y, bb.minObjectVal.z}, {}, {}},
    {{bb.maxObjectVal.x, bb.maxObjectVal.y, bb.minObjectVal.z}, {}, {}},
    {{bb.maxObjectVal.x, bb.maxObjectVal.y, bb.maxObjectVal.z}, {}, {}},
    {{bb.minObjectVal.x, bb.maxObjectVal.y, bb.maxObjectVal.z}, {}, {}}
        };


        // Indices for wireframe (12 edges)
        std::vector<uint32_t> indices = {
            // Bottom face
            0, 1,  1, 2,  2, 3,  3, 0,
            // Top face
            4, 5,  5, 6,  6, 7,  7, 4,
            // Vertical edges
            0, 4,  1, 5,  2, 6,  3, 7
        };

        wireframeMesh = std::make_shared<Mesh>(vertices, indices);
    }


    void draw() {
        if (!wireframeMesh) return;

        // Save current state
        GLint prevPolygonMode[2];
        glGetIntegerv(GL_POLYGON_MODE, prevPolygonMode);
        GLfloat prevLineWidth;
        glGetFloatv(GL_LINE_WIDTH, &prevLineWidth);

        // Set wireframe mode
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glLineWidth(2.0f);

        // Draw the wireframe
        wireframeMesh->draw(GL_LINES);
        // Restore state
        glPolygonMode(GL_FRONT_AND_BACK, prevPolygonMode[0]);
        glLineWidth(prevLineWidth);
    }

private:
    std::shared_ptr<Mesh> wireframeMesh;
};