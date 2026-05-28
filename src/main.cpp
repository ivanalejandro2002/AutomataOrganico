#include <iostream>
#include <vector>
#include <array>

#include <glad/gl.h>
#include <SDL3/SDL.h>

#include <CG/CG.h>
#include <math.h>

const char* vertexShaderSource = R"(
#version 420 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 vertexColor;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    vertexColor = aColor;
}
)";

const char* fragmentShaderSource = R"(
#version 420 core

in vec3 vertexColor;

out vec4 FragColor;

void main()
{
    FragColor = vec4(vertexColor, 1.0);
}
)";

GLuint createShader(GLenum type, const char* source)
{
    GLuint shader = glCreateShader(type);

    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        char infoLog[512];

        glGetShaderInfoLog(shader, 512, nullptr, infoLog);

        std::cerr << infoLog << std::endl;
    }

    return shader;
}

GLuint createShaderProgram()
{
    GLuint vertexShader =
        createShader(GL_VERTEX_SHADER, vertexShaderSource);

    GLuint fragmentShader =
        createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    GLuint shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    GLint success;

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if(!success)
    {
        char infoLog[512];

        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);

        std::cerr << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

int main(int argc, char *argv[])
{
    CG::CG cg;

    cg.createPolygon(15);
    cg.normalize();

    cg.convexHull();
    std::vector<CG::Polygon::Point> points = cg.getPoints();

    std::vector<std::array<float,3>> colors;

    for(size_t i = 0; i < points.size(); ++i)
    {
        float t = static_cast<float>(i) / points.size();

        colors.push_back(
        {
            0.5f + 0.5f * sin(t * 6.28f),
            0.5f + 0.5f * sin(t * 6.28f + 2.0f),
            0.5f + 0.5f * sin(t * 6.28f + 4.0f)
        });
    }

    // x y z r g b
    std::vector<float> vertices;

    for(size_t i = 0; i < points.size(); ++i)
    {
        vertices.push_back((float)points[i].getX());
        vertices.push_back((float)points[i].getY());
        vertices.push_back(0.0f);

        vertices.push_back(colors[i][0]);
        vertices.push_back(colors[i][1]);
        vertices.push_back(colors[i][2]);
    }

    if(!SDL_Init(SDL_INIT_VIDEO))
    {
        return -1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_PROFILE_MASK,
        SDL_GL_CONTEXT_PROFILE_CORE
    );

    SDL_Window* window = SDL_CreateWindow(
        "Polygon",
        1280,
        720,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );

    SDL_GLContext glContext =
        SDL_GL_CreateContext(window);

    gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);

    GLuint shaderProgram = createShaderProgram();

    GLuint VAO;
    GLuint VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        vertices.size() * sizeof(float),
        vertices.data(),
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*)(3 * sizeof(float))
    );

    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    bool running = true;

    while(running)
    {
        SDL_Event event;

        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_EVENT_QUIT)
            {
                running = false;
            }
        }

        int width;
        int height;

        SDL_GetWindowSize(window, &width, &height);

        glViewport(0, 0, width, height);

        glClearColor(0.1f, 0.1f, 0.12f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glBindVertexArray(VAO);

        glDrawArrays(
            GL_TRIANGLE_FAN,
            0,
            static_cast<GLsizei>(points.size())
        );

        SDL_GL_SwapWindow(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glDeleteProgram(shaderProgram);

    SDL_GL_DestroyContext(glContext);

    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}