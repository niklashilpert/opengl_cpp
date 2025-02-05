//
// Created by niklas on 31.01.25.
//

#ifndef SHADER_H
#define SHADER_H
#include <string>
#include <glm/glm.hpp>

namespace gl {
    const std::string TEXTURE_VERTEX_SHADER_FILE = "resources/shaders/default_texture.vert";
    const std::string TEXTURE_FRAGMENT_SHADER_FILE = "resources/shaders/default_texture.frag";

    class Shader {
    public:
        Shader(const std::string& vertex_path, const std::string& fragment_path);
        ~Shader();
        void use() const;

        void setFloat3(const std::string& name, float value1, float value2, float value3) const;
        void setBool(const std::string& name, bool value) const;
        void setInt(const std::string& name, int value) const;
        void setFloat(const std::string& name, float value) const;
        void setMat4(const std::string& name, const glm::mat4& value) const;

    private:
        unsigned int id;
    };

    Shader *load_texture_shader();

}


#endif //SHADER_H
