#include "AssetManager.hpp"

#include <OpenGL/glu.h>

void AssetManager::LoadResources() {
    auto resPath = ResourcePath();
    LoadTexture(resPath + "textures/wingTexture.png", TextureId::Wing);
    LoadTexture(resPath + "textures/engineTexture.png", TextureId::Engine);
    LoadTexture(resPath + "textures/fuselage.png", TextureId::Fuselage);
    LoadTexture(resPath + "textures/strut.png", TextureId::Strut);
    LoadModel(resPath + "models/wing.obj", ModelId::RWing);
    LoadModel(resPath + "models/leftWing.obj", ModelId::LWing);
    LoadModel(resPath + "models/engine.obj", ModelId::Engine);
    LoadModel(resPath + "models/fuselage.obj", ModelId::Fuselage);
    LoadModel(resPath + "models/strut.obj", ModelId::Strut);
    LoadModel(resPath + "models/mtn.obj", ModelId::Mountain);
    CreateProgram(SetupShader(resPath + "shaders/depth.vert", GL_VERTEX_SHADER),
		  SetupShader(resPath + "shaders/depth.frag", GL_FRAGMENT_SHADER),
		  ShaderProgramId::Shadow);
    CreateProgram(SetupShader(resPath + "shaders/terrain.vert", GL_VERTEX_SHADER),
		  SetupShader(resPath + "shaders/terrain.frag", GL_FRAGMENT_SHADER),
		  ShaderProgramId::Terrain);
    CreateProgram(SetupShader(resPath + "shaders/base.vert", GL_VERTEX_SHADER),
		  SetupShader(resPath + "shaders/base.frag", GL_FRAGMENT_SHADER),
		  ShaderProgramId::Base);
    LoadFont(resPath + "fonts/MuseoSlab900.ttf", FontId::MuseoSlab900);
    LoadFont(resPath + "fonts/MuseoSlab700.ttf", FontId::MuseoSlab700);
    LoadFont(resPath + "fonts/MuseoSlab500.ttf", FontId::MuseoSlab500);
    SetMaterial<MaterialId::Shellac>({0.8, 0.84, 64});
    SetMaterial<MaterialId::Metal>({0.8, 0.5, 84});
}

void AssetManager::CreateProgram(const GLuint vert, const GLuint frag, ShaderProgramId id) {
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vert);
    glAttachShader(shaderProgram, frag);
    glDeleteShader(vert);
    glDeleteShader(frag);
    glLinkProgram(shaderProgram);
    char buffer[1024];
    GLsizei len;
    glGetProgramInfoLog(shaderProgram, 1024, &len, buffer);
    printf("%s", buffer);
    glUseProgram(shaderProgram);
    m_shaderPrograms[static_cast<int>(id)] = shaderProgram;
}

GLuint AssetManager::SetupShader(const std::string & path, GLenum shaderType) {
    std::ifstream ifs(path);
    std::stringstream buffer;
    buffer << ifs.rdbuf();
    GLuint shader = glCreateShader(shaderType);
    auto content = buffer.str();
    const auto src = content.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    GLint test;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &test);
    if (!test) {
	std::vector<char> compilationLog(1024);
	glGetShaderInfoLog(shader, compilationLog.size(), nullptr,
			   compilationLog.data());
	std::cerr << compilationLog.data() << std::endl;
	exit(1);
    }
    return shader;
}

AssetManager assetManager;

AssetManager & GetAssets() {
    return ::assetManager;
}
