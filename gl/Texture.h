//
// Created by niklas on 31.01.25.
//

#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../io/stb_image.h"
#include "Shader.h"

typedef struct Vertex {
    glm::vec3 position;
    glm::vec2 texCoord;
    glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
} Vertex;

typedef struct TextureInfo {
    std::string file_path;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
} TextureInfo;

class Texture {
public:
    static Shader *shader;


    explicit Texture(
        const TextureInfo& texture_info,
        const glm::mat4 &transform = glm::mat4(1.0f),
        int gl_format = GL_RGB,
        int channel_count = STBI_rgb
        );
    ~Texture();
    void transform_texture(const glm::mat4 &transform, bool relative);
    void draw() const;
private:
    static unsigned int instance_count;
    static void init_shader();
    static void destroy_shader();

    std::vector<Vertex> original_vertices;
    glm::mat4 transform{};

    unsigned int texture;
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;
    int indexCount;
};

#endif //TEXTURE_H
