//
// Created by niklas on 04.02.25.
//

#include "TextureInstance.h"

namespace gl {
    TextureInstance::TextureInstance(Texture *texture, const glm::mat4 &transform)
        : texture(texture), transform(transform) {
    }

    void TextureInstance::draw() const {
        if (!texture->is_bound()) {
            texture->bind();
        }

        texture->shader->setMat4("model", transform);
        glDrawElements(GL_TRIANGLES, texture->indexCount, GL_UNSIGNED_INT, nullptr);
    }
}

