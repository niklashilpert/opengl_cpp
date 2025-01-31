//
// Created by niklas on 31.01.25.
//
#include <glad/glad.h>
#include <iostream>

#include "Texture.h"
#include "Shader.h"

#define STB_IMAGE_IMPLEMENTATION

#include "../io/stb_image.h"


unsigned int prepare_texture(const std::string &path, const int format = GL_RGB) {
  unsigned int texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  int desired_channels;
  switch (format) {
    case GL_RGB:
      desired_channels = STBI_rgb;
      break;
    case GL_RGBA:
      desired_channels = STBI_rgb_alpha;
      break;
    default:
      desired_channels = 0;
      break;
  }

  int width, height, nrChannels;
  stbi_set_flip_vertically_on_load(true);
  unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, desired_channels);

  if (data)
  {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
    std::cout << "Failed to load texture " << path << std::endl;
  }
  stbi_image_free(data);

  return texture;
}

Texture::Texture(
  const std::string &fileName,
  const std::vector<Vertex> &vertices,
  const std::vector<unsigned int> &indices,
  const int format,
  const float alpha_threshold
  ) {
    VBO = 0;
    VAO = 0;
    EBO = 0;

    indexCount = static_cast<int>(indices.size());

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, static_cast<long>(vertices.size() * sizeof(Vertex)), vertices.data(), GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<void *>(nullptr));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    const long size = static_cast<long>(indices.size() * sizeof(unsigned int));
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices.data(), GL_STATIC_DRAW);

    texture = prepare_texture(fileName, format);
    glActiveTexture(GL_TEXTURE0);

    shader.use();
    shader.setInt("texture0", 0);
    shader.setFloat("alpha_threshold", alpha_threshold);
}

void Texture::draw() const {
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBindTexture(GL_TEXTURE_2D, texture);
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    shader.use();
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
}

void Texture::set_offset(float x, float y) const {
  shader.setFloat3("offset", x, y, 0);
}
