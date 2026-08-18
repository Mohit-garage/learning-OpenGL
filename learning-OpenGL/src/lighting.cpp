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
    window = glfwCreateWindow(ScrWidth, ScrHeight, "lighting", NULL, NULL);
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

    float lightObject[] = {
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,

    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,

     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,

    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f
    };

    /***************************Shader & Textures*********************************************/
    Shader ourShader("Shader.vert", "Shader.frag");
    Shader lightShader("lightShader.vert", "lightShader.frag");

    //creating light object
    unsigned int lightVAO, lightVBO;
    glGenVertexArrays(1, &lightVAO);
    glGenBuffers(1, &lightVBO);

    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lightObject), lightObject, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

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
    unsigned int texture;
    glCreateTextures(GL_TEXTURE_2D, 1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    std::string texturePath = getRelativePath("resources/textures/wall.jpg");
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
    stbi_image_free(data);

    //setting up light object pos and color
    lightShader.use();
    glm::vec3 lightColor(1.0f, 0.5f, 1.0f);
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
    lightShader.setvec3("lightColor", lightColor);

    //assigning uniforms values
    ourShader.use();
    ourShader.setint("texture1", 0);
    ourShader.setvec3("lightColor", lightColor);

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

        /* Render here */
        //glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        // all Matrices
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(ourCamera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);
        glm::mat4 view = ourCamera.getViewMatrix();

        // setting up light model matrix
        lightShader.use();
        lightShader.setMat4("projection", projection);
        lightShader.setMat4("view", view);
        glBindVertexArray(lightVAO);
        glm::mat4 lightmodel = glm::mat4(1.0f);
        lightmodel = glm::translate(lightmodel, lightPos);
        lightShader.setMat4("model", lightmodel);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //Object Shader
        ourShader.use();
        ourShader.setMat4("projection", projection);
        glBindVertexArray(VAO1);
        ourShader.setMat4("view", view);
        glm::mat4 model = glm::mat4(1.0f);
        ourShader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

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