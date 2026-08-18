# OpenGL

A repository dedicated to learning modern OpenGL (Core Profile) and low-level graphics programming in C++. This serves as the learning ground for rendering techniques that will eventually be integrated into my custom game engine, **Vritra**.

# Progress

Following the [LearnOpenGL](https://learnopengl.com/) curriculum to build a strong systems foundation.

### Phase 1: OpenGL Core Foundations
- [x] **01. Hello Triangle:** Environment setup, GLAD/GLFW integration, VBOs/VAOs, and shader compilation.
- [x] **02. Shaders:** Uniforms, vertex/fragment shader data passing.
- [x] **03. Textures:** Loading 2D image data, texture wrapping, and filtering.
- [x] **04. Transformations:** Matrix math, translations, rotations, and scaling.
- [x] **05. Camera:** Model-View-Projection matrices and 3D space navigation.

### Phase 2: Lighting & Materials
- [x] **Colors & Lamp Source:** Separate Object and Light Source Shaders
- [ ] **Basic Lighting Model:**
  - Ambient Lighting
  - Diffuse Lighting (Normals, Normal Matrix transformations)
  - Specular Lighting (View Vector, Shininess)
- [ ] **Materials:**
  - Ambient, Diffuse, Specular color vectors
  - Material Shininess & Light Properties (`ambient`, `diffuse`, `specular`)
- [ ] **Lighting Maps:**
  - Diffuse Maps (Texture-based diffuse reflections)
  - Specular Maps (Shiny highlights on specific surface areas)
  - Emission Maps (Self-illuminating textures)
- [ ] **Light Casters:**
  - Directional Light (Sunlight model / Parallel rays)
  - Point Light (Attenuated point sources using constant, linear, quadratic terms)
  - Spotlight (Flashlight mechanism with inner/outer cutoff angles)
- [ ] **Multiple Lights:**
  - Combining Directional, Point, and Spotlights into single Fragment Shader structures

---

### Phase 3: Advanced OpenGL
- [ ] **Depth Testing:** `GL_DEPTH_TEST`, Depth Buffer Manipulation, Z-Fighting prevention
- [ ] **Stencil Testing:** Object Outlining / Selection highlights
- [ ] **Blending:** Alpha Cutout (discarding pixels) & Alpha Blending for transparent objects
- [ ] **Face Culling:** `GL_CULL_FACE`, Front/Back Face ordering optimizations
- [ ] **Framebuffers:** Offscreen Rendering, Post-Processing Effects (Inversion, Grayscale, Kernel Blurs)
- [ ] **Cubemaps & Skyboxes:** Environment Mapping, Reflection & Refraction Shaders
- [ ] **Advanced GLSL:** Uniform Buffer Objects (UBOs), Built-in variables (`gl_VertexID`, `gl_FragCoord`)
- [ ] **Geometry Shaders:** Dynamic primitive manipulation on the GPU
- [ ] **Instancing:** High-performance drawing of repetitive geometry (`glDrawArraysInstanced`)
- [ ] **Anti-Aliasing:** Multi-Sample Anti-Aliasing (MSAA) & Offscreen Framebuffer MSAA Resolving

---

# Tech Stack
* **Language:** C++17
* **Graphics API:** OpenGL 4.6
* **Windowing & Input:** GLFW
* **Function Pointers:** GLAD

# Controls
* **W / A / S / D:** Camera Movement (Forward / Left / Backward / Right)
* **E / C:** Camera Vertical Movement (Up / Down)
* **Mouse Movement:** Free-look / Pitch & Yaw
* **Mouse Scroll:** Zoom / Field of View adjustment
* **ESC:** Close Window

# How to Build

This project includes all necessary dependencies (GLFW, GLAD) directly in the repository. The Visual Studio solution is configured with relative paths, so no manual library installation is required.

1. Clone the repository: 
   ```bash
   git clone [https://github.com/Mohit-garage/learning-OpenGL.git](https://github.com/Mohit-garage/learning-OpenGL.git)