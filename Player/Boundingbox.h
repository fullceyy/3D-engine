#pragma once
#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "glm/glm.hpp"

struct Bounding_Box {
	glm::vec3 minObjectVal;
	glm::vec3 maxObjectVal;


    glm::vec3 getCenter() const {
        return (minObjectVal + maxObjectVal) * 0.5f;
    }

    // Calculate dimensions (width, height, depth)
    glm::vec3 getSize() const {
        return maxObjectVal - minObjectVal;
    }

    static bool rayIntersectsAABB(const glm::vec3& rayOrigin, const glm::vec3& rayDir, const Bounding_Box& box, float& outDistance) {
        float tMin = 0.0f;
        float tMax = FLT_MAX;

        for (int i = 0; i < 3; ++i) {
            if (std::abs(rayDir[i]) < 1e-6f) {
                // Ray is parallel to slab. No hit if origin not within slab
                if (rayOrigin[i] < box.minObjectVal[i] || rayOrigin[i] > box.maxObjectVal[i]) return false;
            } else {
                float invD = 1.0f / rayDir[i];
                float t0 = (box.minObjectVal[i] - rayOrigin[i]) * invD;
                float t1 = (box.maxObjectVal[i] - rayOrigin[i]) * invD;
                if (t0 > t1) std::swap(t0, t1);
                tMin = std::max(tMin, t0);
                tMax = std::min(tMax, t1);
                if (tMax < tMin) return false;
            }
        }

        outDistance = tMin;
        return true;
    }

    static bool checkColl(const Bounding_Box& a, const Bounding_Box& b) {
        return (a.minObjectVal.x <= b.maxObjectVal.x && a.maxObjectVal.x >= b.minObjectVal.x) &&
            (a.minObjectVal.y <= b.maxObjectVal.y && a.maxObjectVal.y >= b.minObjectVal.y) &&
            (a.minObjectVal.z <= b.maxObjectVal.z && a.maxObjectVal.z >= b.minObjectVal.z);
    }
};


#endif