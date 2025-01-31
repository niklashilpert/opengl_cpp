//
// Created by niklas on 31.01.25.
//

#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>
#include <vector>

#include "Shader.h"

struct Vertex {
  float x, y, z;
  float r, g, b;
  float tx, ty;
};

class Texture {
public:
    Texture(
        const std::string &fileName,
        const std::vector<Vertex> &vertices,
        const std::vector<unsigned int> &indices,
        int format,
        float alpha_threshold = .1f
        );
    void draw() const;
    void set_offset(float x, float y) const;
private:
    Shader shader = Shader("resources/shaders/default_texture.vert", "resources/shaders/default_texture.frag");
	unsigned int texture;
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;
    int indexCount;
};

#endif //TEXTURE_H
