#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <filesystem>
#include "Shader.h"
#include"stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"


/***************************funciton prototypes*******************************/
// function for get relative paths.
static std::string getRelativePath(const std::string& relativePath);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processCursorInput(GLFWwindow* window, double xpos, double ypos);
void processScrollInput(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void Check_Window_Close(GLFWwindow* window);
void contrastControl(GLFWwindow*, float&);
/******************************************************************************/

const unsigned int ScrWidth = 800;
const unsigned int ScrHeight = 600;

//Setting up Camera
camera ourCamera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = ScrWidth / 2.0f;
float lastY = ScrHeight / 2.0f;
bool firstMouse = true;

//timing
float deltaTime = 0.0f;
float lastTime = 0.0f;

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(ScrWidth, ScrHeight, "Camera", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    //callback functions
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, processCursorInput);
    glfwSetScrollCallback(window, processScrollInput);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    glm::vec3 cubePositions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    
    /***************************Shader & Textures*********************************************/
    Shader ourShader("Shader.vert", "Shader.frag");
    //Defining Triangle Coordinates

    // created buffer and array and allocated memory on gpu
    unsigned int VAO1, VBO1;
    glGenVertexArrays(1, &VAO1);
    glGenBuffers(1, &VBO1);

    glBindVertexArray(VAO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

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
        std::cout << "Failed to load Texture : " << texture1Path << ":\n" << stbi_failure_reason() << "\n";
    }

    stbi_image_free(data);
    stbi_image_free(data1);

    //assigning uniforms values
    ourShader.use();
    ourShader.setint("texture1", 0);
    ourShader.setint("texture2", 1);
    float value = 0.2f;

    //Enabling depth testing
    glEnable(GL_DEPTH_TEST);
    /******************************************************************************/


    /* Loop until the user closes the window */
    /**********************************************************Game Loop******************************************************************************/
    while (!glfwWindowShouldClose(window))
    {
        //Delta Time
        float currentTime = static_cast<float>(glfwGetTime());
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        processInput(window);
        contrastControl(window, value);

        /* Render here */
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ourShader.use();;

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture1);
        ourShader.setfloat("contrast", value);

        // all Matrices
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(ourCamera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);
        ourShader.setMat4("projection", projection);

        glm::mat4 view = ourCamera.getViewMatrix();
        ourShader.setMat4("view", view);

        glBindVertexArray(VAO1);
        for (int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            ourShader.setMat4("model", model);
            if (!(i % 3))
            {
                float angle = 20.0f * (i + 1);
                model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(0.5f, 1.0f, 0.0f));
                ourShader.setMat4("model", model);
            }
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glBindVertexArray(0);


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
/*********************************************************************************************************************************************************/

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// for texture contrast control
void contrastControl(GLFWwindow* window, float& value)
{
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && value < 1)
    {
        value = value + 0.0001f;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && value > 0)
    {
        value = value - 0.0001f;
    }
}

//Keyboard Input
void processInput(GLFWwindow* window)
{
    if ((glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS))
    {
        glfwSetWindowShouldClose(window, true);
    }
    if ((glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS))
    {
        ourCamera.processKeyboardInput(Forward, deltaTime);
    }
    if ((glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS))
    {
        ourCamera.processKeyboardInput(Backward, deltaTime);
    }
    if ((glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS))
    {
        ourCamera.processKeyboardInput(Left, deltaTime);
    }
    if ((glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS))
    {
        ourCamera.processKeyboardInput(Right, deltaTime);
    }
    if ((glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS))
    {
        ourCamera.processKeyboardInput(Up, deltaTime);
    }
    if ((glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS))
    {
        ourCamera.processKeyboardInput(Down, deltaTime);
    }
}

//Cursor Position Input
void processCursorInput(GLFWwindow* window, double xpos, double ypos)
{
    float curX = static_cast<float>(xpos);
    float curY = static_cast<float>(ypos);

    if (firstMouse)
    {
        lastX = curX;
        lastY = curY;
        firstMouse = false;
    }

    float xoffset = curX - lastX;
    float yoffset = lastY - curY;

    ourCamera.processMouseInput(xoffset, yoffset);

    lastX = curX;
    lastY = curY;
}
void processScrollInput(GLFWwindow* window, double xoffset, double yoffset)
{
    ourCamera.processMouseScrollInput(static_cast<float>(yoffset));
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