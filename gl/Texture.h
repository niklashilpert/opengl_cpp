//
// Created by niklas on 31.01.25.
//

#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <unordered_map>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../io/stb_image.h"
#include "Shader.h"

namespace gl {
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
        explicit Texture(
            const Shader *shader,
            const TextureInfo& texture_info,
            int gl_format = GL_RGB,
            int channel_count = STBI_rgb
            );
        ~Texture();

        void bind();
        bool is_bound() const;

    private:
        static Texture *current;

        const Shader *shader;
        const unsigned int texture;
        const unsigned int VBO;
        const unsigned int VAO;
        const unsigned int EBO;
        const int indexCount;

        friend class TextureInstance;
    };

    Texture *load_block(const Shader *shader, const std::string& file_path);
    Texture *load_grass_block(const Shader *shader);
    Texture *load_debug_block(const Shader *shader);
    Texture *load_brick_block(const Shader *shader);

}

#endif //TEXTURE_H
