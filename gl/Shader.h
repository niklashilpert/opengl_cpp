//
// Created by niklas on 31.01.25.
//

#ifndef SHADER_H
#define SHADER_H
#include <string>
#include <vector>
#include <glm/glm.hpp>

namespace gl {
    const std::string TEXTURE_VERTEX_SHADER_FILE = "resources/shaders/default_texture.vert";
    const std::string TEXTURE_FRAGMENT_SHADER_FILE = "resources/shaders/default_texture.frag";

    const std::string CIRCLE_VERTEX_SHADER_FILE = "resources/shaders/circle/shader.vert";
    const std::string CIRCLE_GEOMETRY_SHADER_FILE = "resources/shaders/circle/shader.geom";
    const std::string CIRCLE_FRAGMENT_SHADER_FILE = "resources/shaders/circle/shader.frag";

    const std::string LINE_VERTEX_SHADER_FILE = "resources/shaders/line/shader.vert";
    const std::string LINE_GEOMETRY_SHADER_FILE = "resources/shaders/line/shader.geom";
    const std::string LINE_FRAGMENT_SHADER_FILE = "resources/shaders/line/shader.frag";

    class Shader {
    public:
        Shader(const std::vector<std::string> &paths);
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

    Shader *loadTextureShader();

    Shader *loadCircleShader();

    Shader *loadLineShader();
}


#endif //SHADER_H
