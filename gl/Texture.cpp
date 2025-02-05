//
// Created by niklas on 03.02.25.
//

#include "Texture.h"

#include <iostream>
#include <glad/glad.h>

namespace gl {

    Texture *Texture::current = nullptr;

    /* ###### HELPERS ###### */

    void set_vertex_buffer(const unsigned int VBO, const std::vector<Vertex> &vertices) {
        std::vector<float> data_vec = {};
        for (auto [position, texCoord, color]: vertices) {
            data_vec.push_back(position.x);
            data_vec.push_back(position.y);
            data_vec.push_back(position.z);
            data_vec.push_back(texCoord.x);
            data_vec.push_back(texCoord.y);
            data_vec.push_back(color.r);
            data_vec.push_back(color.g);
            data_vec.push_back(color.b);
            data_vec.push_back(color.a);
        }

        const long size = static_cast<long>(data_vec.size() * sizeof(float));
        const float *data = data_vec.data();
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    unsigned int create_vertex_buffer(const std::vector<Vertex> &vertices) {
        unsigned int VBO = 0;
        glGenBuffers(1, &VBO);
        set_vertex_buffer(VBO, vertices);
        return VBO;
    }

    unsigned int create_vertex_array() {
        unsigned int VAO = 0;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), nullptr);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void *>(3 * sizeof(float)));
        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void *>(5 * sizeof(float)));

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        return VAO;
    }

    unsigned int create_element_buffer(const std::vector<unsigned int> &indices) {
        unsigned int EBO = 0;
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        const long size = static_cast<long>(indices.size() * sizeof(unsigned int));
        const unsigned int *data = indices.data();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

        return EBO;
    }

    unsigned int prepare_texture(const std::string &path, const int gl_format, const int channel_count) {
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, channel_count);
        if (data) {
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glTexImage2D(GL_TEXTURE_2D, 0, gl_format, width, height, 0, gl_format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cout << "Failed to load texture" << path << std::endl;
        }
        stbi_image_free(data);

        return texture;
    }

    /* ######  MEMBERS ###### */

    Texture::Texture(
        const Shader *shader,
        const TextureInfo &texture_info,
        const int gl_format,
        const int channel_count
    ) : shader(shader),
        texture(prepare_texture(texture_info.file_path, gl_format, channel_count)),
        VBO(create_vertex_buffer(texture_info.vertices)),
        VAO(create_vertex_array()),
        EBO(create_element_buffer(texture_info.indices)),
        indexCount(static_cast<int>(texture_info.indices.size())) {
    }

    Texture::~Texture() {
        glDeleteTextures(1, &this->texture);
        glDeleteBuffers(1, &this->EBO);
        glDeleteVertexArrays(1, &this->VAO);
        glDeleteBuffers(1, &this->VBO);
    }

    void Texture::bind() {
        current = this;

        shader->use();
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE0);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glDrawElements(GL_TRIANGLES, this->indexCount, GL_UNSIGNED_INT, nullptr);
    }

    bool Texture::is_bound() const {
        return current == this;
    }



    constexpr float F_1_4 = 1.0f / 4.0f;
    constexpr float F_2_4 = 2 * F_1_4;
    constexpr float F_3_4 = 3 * F_1_4;

    constexpr float F_1_3 = 1.0f / 3.0f;
    constexpr float F_2_3 = 2.0f / 3.0f;

    const std::vector vertices{
        // front
        Vertex{glm::vec3(.5f, .5f, .5f), glm::vec2(F_2_3, F_2_4)},
        Vertex{glm::vec3(-.5f, .5f, .5f), glm::vec2(F_1_3, F_2_4)},
        Vertex{glm::vec3(.5f, -.5f, .5f), glm::vec2(F_2_3, F_1_4)},
        Vertex{glm::vec3(-.5f, -.5f, .5f), glm::vec2(F_1_3, F_1_4)},

        // back
        Vertex{glm::vec3(.5f, .5f, -.5f), glm::vec2(F_2_3, F_3_4)},
        Vertex{glm::vec3(-.5f, .5f, -.5f), glm::vec2(F_1_3, F_3_4)},
        Vertex{glm::vec3(.5f, -.5f, -.5f), glm::vec2(F_2_3, 1)},
        Vertex{glm::vec3(-.5f, -.5f, -.5f), glm::vec2(F_1_3, 1)},

        // left
        Vertex{glm::vec3(-.5f, .5f, .5f), glm::vec2(F_1_3, F_2_4)},
        Vertex{glm::vec3(-.5f, .5f, -.5f), glm::vec2(F_1_3, F_3_4)},
        Vertex{glm::vec3(-.5f, -.5f, .5f), glm::vec2(0, F_2_4)},
        Vertex{glm::vec3(-.5f, -.5f, -.5f), glm::vec2(0, F_3_4)},

        // right
        Vertex{glm::vec3(.5f, .5f, .5f), glm::vec2(F_2_3, F_2_4)},
        Vertex{glm::vec3(.5f, .5f, -.5f), glm::vec2(F_2_3, F_3_4)},
        Vertex{glm::vec3(.5f, -.5f, .5f), glm::vec2(1, F_2_4)},
        Vertex{glm::vec3(.5f, -.5f, -.5f), glm::vec2(1, F_3_4)},

        // top
        Vertex{glm::vec3(.5f, .5f, .5f), glm::vec2(F_2_3, F_2_4)},
        Vertex{glm::vec3(.5f, .5f, -.5f), glm::vec2(F_2_3, F_3_4)},
        Vertex{glm::vec3(-.5f, .5f, .5f), glm::vec2(F_1_3, F_2_4)},
        Vertex{glm::vec3(-.5f, .5f, -.5f), glm::vec2(F_1_3, F_3_4)},

        // bottom
        Vertex{glm::vec3(.5f, -.5f, .5f), glm::vec2(F_2_3, F_1_4)},
        Vertex{glm::vec3(.5f, -.5f, -.5f), glm::vec2(F_2_3, 0)},
        Vertex{glm::vec3(-.5f, -.5f, .5f), glm::vec2(F_1_3, F_1_4)},
        Vertex{glm::vec3(-.5f, -.5f, -.5f), glm::vec2(F_1_3, 0)},
    };

    const std::vector<unsigned int> indices = {
        0, 1, 3,
        0, 3, 2,
        4, 7, 5,
        4, 6, 7,
        8, 9, 11,
        8, 11, 10,
        12, 15, 13,
        12, 14, 15,
        16, 17, 19,
        16, 19, 18,
        20, 23, 21,
        20, 22, 23
    };

    Texture *load_block(const Shader *shader, const std::string& file_path) {
        const TextureInfo texture_info(file_path, vertices, indices);
        return new Texture(shader, texture_info, GL_RGBA, STBI_rgb_alpha);
    }

    Texture *load_grass_block(const Shader *shader) {
        return load_block(shader, "resources/textures/grass/grass.png");
    }

    Texture *load_debug_block(const Shader *shader) {
        return load_block(shader, "resources/textures/debug.png");
    }

    Texture *load_brick_block(const Shader *shader) {
        const TextureInfo texture_info("resources/textures/wall.png", vertices, indices);

        return new Texture(shader, texture_info,GL_RGBA, STBI_rgb_alpha);
    }

}
