//
// Created by niklas on 31.01.25.
//

#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>
#include <vector>

#include "Shader.h"

typedef struct Vertex {
    float x, y, z;
    float tx, ty;
    float r = 1, g = 1, b = 1;
} Vertex;

class Texture {
public:
    Texture(
        const std::string &fileName,
        const std::vector<Vertex> &vertices,
        const std::vector<unsigned int> &indices,
        int format,
        float alpha_threshold = .01f
        );
    void draw() const;
    void set_matrix(const std::string &name, const glm::mat4 &matrix) const;
    Shader shader = Shader("resources/shaders/default_texture.vert", "resources/shaders/default_texture.frag");
    unsigned int texture;
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;
    int indexCount;
};

#endif //TEXTURE_H
