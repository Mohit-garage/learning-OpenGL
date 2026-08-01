#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void Check_Window_Close(GLFWwindow* window);

//Vertex Shader
const char* vertexShaderSource = "#version 460 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aCol;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"   ourColor = aCol;\n"
"}\0";

//Fragment Shader
const char* fragShaderSource = "#version 460 core\n"
"in vec3 ourColor;\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(ourColor, 1.0f);\n"
"}\0";

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // creating and compiling vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // creating and compiling fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragShaderSource, NULL);
    glCompileShader(fragmentShader);

    // checking success of compilation
    int successVertex;
    int successFragment;

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &successVertex);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successFragment);

    if (!successVertex)
    {
        char infoLogVertex[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLogVertex);
        std::cout << "ERROR: Shader::Vertex::Compilation_Failed :\n\t" << infoLogVertex << "\n";
    }
    if (!successFragment)
    {
        char infoLogFragment[512];
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLogFragment);
        std::cout << "Error: Shader::Fragment::Compilation Failed :\n\t" << infoLogFragment << "\n";
    }

    // Creating Shader Program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Checking for linking errors
    int successShaderProgram;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &successShaderProgram);
    if (!successShaderProgram)
    {
        char infoLogShaderProgram[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLogShaderProgram);
        std::cout << "Error: Program::ShaderProgram::Linking Failed :\n\t" << infoLogShaderProgram << "\n";
    }

    // Deleting the linked shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);



    //Defining Triangle Coordinates
    float Vertex[] =
    {
        //Triangle
        //coordinates            //color
        -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,  // first point
        0.5f, -0.5f, 0.0f,      0.0f, 1.0f, 0.0f,  // second point
        0.0f, 0.5f, 0.0f,       0.0f, 0.0f, 1.0f  // third point
    };

    // created buffer and array and allocated memory on gpu
    unsigned int VAO1, VBO1;
    glGenVertexArrays(1, &VAO1);
    glGenBuffers(1, &VBO1);

    glBindVertexArray(VAO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex), Vertex, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);



    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        Check_Window_Close(window);

        /* Render here */
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);

        //Uniform Variable (removed from shader: reedit if running)
        /*int current_time = glfwGetTime();
        float gradiant_value = sin(current_time) / 2.0f + 0.5f;
        int uniform_location = glGetUniformLocation(shaderProgram, "FragmentColor");
        glUniform4f(uniform_location, 0.0f, 0.0f, gradiant_value, 1.0f);*/

        glBindVertexArray(VAO1);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Check_Window_Close(GLFWwindow* window)
{
    if ((glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) && (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS))
    {
        glfwSetWindowShouldClose(window, true);
    }
}

