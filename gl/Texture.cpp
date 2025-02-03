//
// Created by niklas on 03.02.25.
//


#include "Texture.h"

#include <iostream>
#include <glad/glad.h>

unsigned int Texture::instance_count = 0;
Shader *Texture::shader = nullptr;

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

unsigned int create_vertex_buffer(const std::vector<Vertex> &vertices, const glm::mat4 &transform) {
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
        std::cout << "Failed to load texture " << path << std::endl;
    }
    stbi_image_free(data);

    return texture;
}

/* ###### STATIC ###### */
void Texture::init_shader() {
    std::cout << "Initializing texture shader..." << std::endl;
    shader = new Shader(
        "resources/shaders/default_texture.vert",
        "resources/shaders/default_texture.frag"
    );
}

void Texture::destroy_shader() {
    std::cout << "Destroying texture shader..." << std::endl;
    delete shader;
}


/* ######  MEMBERS ###### */
Texture::Texture(
    const TextureInfo &texture_info,
    const glm::mat4 &transform,
    const int gl_format,
    const int channel_count
) : original_vertices(texture_info.vertices),
    transform(transform) {
    instance_count++;
    if (shader == nullptr) {
        init_shader();
    }

    this->VBO = create_vertex_buffer(texture_info.vertices, transform);
    this->VAO = create_vertex_array();
    this->EBO = create_element_buffer(texture_info.indices);

    this->indexCount = static_cast<int>(texture_info.indices.size());

    this->texture = prepare_texture(texture_info.file_path, gl_format, channel_count);
}

Texture::~Texture() {
    instance_count--;
    if (instance_count == 0 && shader != nullptr) {
        destroy_shader();
        shader = nullptr;
    }

    glDeleteTextures(1, &texture);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &EBO);
}

void Texture::transform_texture(const glm::mat4 &transform, const bool relative) {
    if (relative) {
        this->transform = transform * this->transform;
    } else {
        this->transform = transform;
    }

    set_vertex_buffer(VBO, original_vertices);
}

void Texture::draw() const {
    shader->use();
    shader->setMat4("model", transform);

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBindTexture(GL_TEXTURE_2D, this->texture);
    glActiveTexture(GL_TEXTURE0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDrawElements(GL_TRIANGLES, this->indexCount, GL_UNSIGNED_INT, nullptr);

    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
}

