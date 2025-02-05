//
// Created by niklas on 04.02.25.
//

#ifndef TEXTUREINSTANCE_H
#define TEXTUREINSTANCE_H

#include "Texture.h"

namespace gl {
    class TextureInstance {
    public:
        Texture *texture;

        TextureInstance(Texture *texture, const glm::mat4 &transform);

        void draw() const;
        void set_transform(glm::mat4 transform);
        glm::mat4 get_transform();

    private:
        glm::mat4 transform;
    };
}

#endif //TEXTUREINSTANCE_H
