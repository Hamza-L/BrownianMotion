//
// Created by Hamza Lahmimsi on 2021-02-17.
//

#ifndef VULKANTESTING_POINT_H
#define VULKANTESTING_POINT_H

#include "Node.h"

class Point : public Node {
public:
    Point(glm::vec2 center){
        
        Vertex v0;
        v0.position = glm::vec3(center,0.0f); //center of the circle
        v0.texCoord = {0,1};
        v0.colour = {1.0f, 1.0f, 1.0f, 1.0f};
        v0.norm = {0.0f, 0.0f, 1.0f};
        v0.up = {0.0f, 1.0f, 0.0f};
        vertices.push_back(v0);
        
        int subdivisions = 30;
        float size = 0.01f;

        std::vector<glm::vec3> circumference = getSpherePoints(subdivisions, size, glm::vec2(center));

        for(int i=0; i<subdivisions-1; i++){
            Vertex v1;
            v1.position = circumference[i];
            v1.texCoord = {0,0};
            v1.colour = {1.0f, 1.0f, 1.0f, 1.0f};
            v1.norm = {0.0f, 0.0f, 1.0f};
            v1.up = {0.0f, 1.0f, 0.0f};

            indices.push_back(0);
            indices.push_back(i+2);
            indices.push_back(i+1);

            vertices.push_back(v1);
        }

        Vertex v_last;
        v_last.position = circumference[subdivisions-1];
        v_last.texCoord = {0,0};
        v_last.colour = {1.0f, 1.0f, 1.0f, 1.0f};
        v_last.norm = {0.0f, 0.0f, 1.0f};
        v_last.up = {0.0f, 1.0f, 0.0f};

        indices.push_back(0);
        indices.push_back(1);
        indices.push_back(subdivisions);

        vertices.push_back(v_last);

    }

    Point(glm::mat4 M){
        glm::mat4 MinvT = glm::transpose(glm::inverse(M));
        Vertex v0,v1,v2,v3;
        glm::vec4 t0,t1,t2,t3;
        t0 = M * glm::vec4(0.5f, -0.5f, 0.0f,1.0f);
        t1 = M * glm::vec4(-0.5f, -0.5f, 0.0f,1.0f);
        t2 = M * glm::vec4(-0.5f, 0.5f, 0.0f,1.0f);
        t3 = M * glm::vec4(0.5f, 0.5f, 0.0f,1.0f);

        v0.position = glm::vec3(t0.x,t0.y,t0.z);
        v1.position = glm::vec3(t1.x,t1.y,t1.z);
        v2.position = glm::vec3(t2.x,t2.y,t2.z);
        v3.position = glm::vec3(t3.x,t3.y,t3.z);

        v0.texCoord = {0,1};
        v1.texCoord = {0,0};
        v2.texCoord = {1,0};
        v3.texCoord = {1,1};

        v0.colour = {0.1f, 0.1f, 0.1f, 1.0f};
        v1.colour = {0.1f, 0.1f, 0.1f, 1.0f};
        v2.colour = {0.1f, 0.1f, 0.1f, 1.0f};
        v3.colour = {0.1f, 0.1f, 0.1f, 1.0f};

        t0 = MinvT * glm::vec4(0.0f, 0.0f, 1.0f,0.0f);
        t1 = MinvT * glm::vec4(0.0f, 0.0f, 1.0f,0.0f);
        t2 = MinvT * glm::vec4(0.0f, 0.0f, 1.0f,0.0f);
        t3 = MinvT * glm::vec4(0.0f, 0.0f, 1.0f,0.0f);

        v0.norm = glm::normalize(glm::vec3(t0.x,t0.y,t0.z));
        v1.norm = glm::normalize(glm::vec3(t1.x,t1.y,t1.z));
        v2.norm = glm::normalize(glm::vec3(t2.x,t2.y,t2.z));
        v3.norm = glm::normalize(glm::vec3(t3.x,t3.y,t3.z));

        t0 = MinvT * glm::vec4(0.0f, 1.0f, 0.0f,0.0f);
        t1 = MinvT * glm::vec4(0.0f, 1.0f, 0.0f,0.0f);
        t2 = MinvT * glm::vec4(0.0f, 1.0f, 0.0f,0.0f);
        t3 = MinvT * glm::vec4(0.0f, 1.0f, 0.0f,0.0f);

        v0.up = glm::normalize(glm::vec3(t0.x,t0.y,t0.z));
        v1.up = glm::normalize(glm::vec3(t1.x,t1.y,t1.z));
        v2.up = glm::normalize(glm::vec3(t2.x,t2.y,t2.z));
        v3.up = glm::normalize(glm::vec3(t3.x,t3.y,t3.z));

        //indices = {0, 1, 2, 0, 2, 3};
        indices.push_back(0);
        indices.push_back(1);
        indices.push_back(2);
        indices.push_back(0);
        indices.push_back(2);
        indices.push_back(3);

        vertices.push_back(v0);
        vertices.push_back(v1);
        vertices.push_back(v2);
        vertices.push_back(v3);
        //vertices.push_back(v2);
        //vertices.push_back(v3);
    }

    Point(glm::mat4 M, glm::vec4 colour){
        glm::mat4 MinvT = glm::transpose(glm::inverse(M));
        Vertex v0,v1,v2,v3;
        glm::vec4 t0,t1,t2,t3;
        t0 = M * glm::vec4(0.5f, -0.5f, 0.0f,1.0f);
        t1 = M * glm::vec4(-0.5f, -0.5f, 0.0f,1.0f);
        t2 = M * glm::vec4(-0.5f, 0.5f, 0.0f,1.0f);
        t3 = M * glm::vec4(0.5f, 0.5f, 0.0f,1.0f);

        v0.position = glm::vec3(t0.x,t0.y,t0.z);
        v1.position = glm::vec3(t1.x,t1.y,t1.z);
        v2.position = glm::vec3(t2.x,t2.y,t2.z);
        v3.position = glm::vec3(t3.x,t3.y,t3.z);

        v0.texCoord = {1,1};
        v1.texCoord = {0,1};
        v2.texCoord = {0,0};
        v3.texCoord = {1,0};

        v0.colour = colour;
        v1.colour = colour;
        v2.colour = colour;
        v3.colour = colour;

        t0 = MinvT * glm::vec4(0.0f, 0.0f, 1.0f,0.0f);
        t1 = MinvT * glm::vec4(0.0f, 0.0f, 1.0f,0.0f);
        t2 = MinvT * glm::vec4(0.0f, 0.0f, 1.0f,0.0f);
        t3 = MinvT * glm::vec4(0.0f, 0.0f, 1.0f,0.0f);

        v0.norm = glm::normalize(glm::vec3(t0.x,t0.y,t0.z));
        v1.norm = glm::normalize(glm::vec3(t1.x,t1.y,t1.z));
        v2.norm = glm::normalize(glm::vec3(t2.x,t2.y,t2.z));
        v3.norm = glm::normalize(glm::vec3(t3.x,t3.y,t3.z));

        t0 = MinvT * glm::vec4(0.0f, 1.0f, 0.0f,0.0f);
        t1 = MinvT * glm::vec4(0.0f, 1.0f, 0.0f,0.0f);
        t2 = MinvT * glm::vec4(0.0f, 1.0f, 0.0f,0.0f);
        t3 = MinvT * glm::vec4(0.0f, 1.0f, 0.0f,0.0f);

        v0.up = glm::normalize(glm::vec3(t0.x,t0.y,t0.z));
        v1.up = glm::normalize(glm::vec3(t1.x,t1.y,t1.z));
        v2.up = glm::normalize(glm::vec3(t2.x,t2.y,t2.z));
        v3.up = glm::normalize(glm::vec3(t3.x,t3.y,t3.z));

        //indices = {0, 1, 2, 0, 2, 3};
        indices.push_back(0);
        indices.push_back(1);
        indices.push_back(2);
        indices.push_back(0);
        indices.push_back(2);
        indices.push_back(3);

        vertices.push_back(v0);
        vertices.push_back(v1);
        vertices.push_back(v2);
        vertices.push_back(v3);
    }

private:
    std::vector<glm::vec3> getSpherePoints(int subdivisions, float size, glm::vec2 center){
        
        std::vector<glm::vec3> circumference;
        
        float increment = (2.0f*M_PI) / float(subdivisions);

        for(int i=0; i<subdivisions; i++){
            circumference.push_back(glm::vec3(size * cos(float(i)*increment) + center.x, size * sin(float(i)*increment) + center.y ,0.0f));
        }

        return circumference;
    }
};

#endif //VULKANTESTING_POINT_H
