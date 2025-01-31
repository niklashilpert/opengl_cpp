//
// Created by niklas on 31.01.25.
//

#ifndef SHADER_H
#define SHADER_H
#include <string>

class Shader {
public:
    unsigned int id;

    Shader(const std::string& vertex_path, const std::string& fragment_path);
    void use() const;

    void setFloat3(const std::string& name, float value1, float value2, float value3) const;

    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
private:
};

#endif //SHADER_H
