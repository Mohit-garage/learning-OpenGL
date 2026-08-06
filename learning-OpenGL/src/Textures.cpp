#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <filesystem>
#include "Shader.h"
#include"Dependenies/stb_image.h"

// function for get relative paths.
static std::string getRelativePath(const std::string& relativePath);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void Check_Window_Close(GLFWwindow* window);
void contrastControl(GLFWwindow*, float&);

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Textures", NULL, NULL);
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

    Shader ourShader("Shader.vert", "Shader.frag");
    //Defining Triangle Coordinates
    float Vertex[] =
    {
        //Square
        //coordinates            //color            //texture
        -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,   0.0f, 0.0f,     // first point
        0.5f, -0.5f, 0.0f,      0.0f, 1.0f, 0.0f,   2.0f, 0.0f,     // second point
        -0.5f, 0.5f, 0.0f,      0.0f, 0.0f, 1.0f,   0.0f, 2.0f,     // third point
        0.5f, 0.5f, 0.0f,       1.0f, 1.0f, 0.0f,   2.0f, 2.0f      // fourth point
    };

    unsigned int indices[] =
    {
        0, 1, 2,
        3, 1, 2
    };

    // created buffer and array and allocated memory on gpu
    unsigned int VAO1, VBO1, EBO1;
    glGenVertexArrays(1, &VAO1);
    glGenBuffers(1, &VBO1);
    glGenBuffers(1, &EBO1);

    glBindVertexArray(VAO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex), Vertex, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //Creting and Applying texture
    stbi_set_flip_vertically_on_load(true);
    unsigned int texture, texture1;
    glCreateTextures(GL_TEXTURE_2D, 1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    std::string texturePath = getRelativePath("resources/textures/container.jpg");
    unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load Texture : " << texturePath << ":\n" << stbi_failure_reason() << "\n";
    }
    //  second texture
    glCreateTextures(GL_TEXTURE_2D, 1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    int width1, height1, nrChannels1;
    std::string texture1Path = getRelativePath("resources/textures/awesomeface.png");
    unsigned char* data1 = stbi_load(texture1Path.c_str(), &width1, &height1, &nrChannels1, 0);
    if (data1)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGBA, GL_UNSIGNED_BYTE, data1);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load Texture : " << texture1Path << ":\n" <<stbi_failure_reason() << "\n";
    }

    stbi_image_free(data);
    stbi_image_free(data1);

    //assigning uniforms values
    ourShader.use();
    ourShader.setint("texture1", 0);
    ourShader.setint("texture2", 1);
    float value = 0.5;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        Check_Window_Close(window);
        contrastControl(window, value);

        /* Render here */
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ourShader.use();;

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture1);
        ourShader.setfloat("contrast", value);

        glBindVertexArray(VAO1);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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

// for texture contrast control
void contrastControl(GLFWwindow* window, float& value)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && value < 1)
    {
        value = value + 0.0001f;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && value > 0)
    {
        value = value - 0.0001f;
    }
}
void Check_Window_Close(GLFWwindow* window)
{
    if ((glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) && (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS))
    {
        glfwSetWindowShouldClose(window, true);
    }
}

//creating a relative path finder upto 3 folder back to current working directory
static std::string getRelativePath(const std::string& relativePath) {
    // 1. Get the Current Working Directory (CWD)
    std::filesystem::path currentPath = std::filesystem::current_path();

    // 2. Loop to check the current folder and up to 3 parent folders
    for (int i = 0; i < 4; ++i) {

        // 3. Construct the full path we want to check
        std::filesystem::path checkPath = currentPath / relativePath;

        // 4. Query the OS to see if the file actually exists here
        if (std::filesystem::exists(checkPath)) {
            return checkPath.string(); // 5. Found it! Return as std::string
        }

        currentPath = currentPath.parent_path();
    }

    return relativePath; // 7. Fallback if not found
}