# OpenGL Study Project

This repository contains a small OpenGL rendering engine developed as a study project.  
The objective is to practice and understand the fundamentals of modern OpenGL (Core Profile 3.3), including shaders, lighting, meshes, model loading, and camera movement.  
Code quality is intentionally flexible since the purpose is exploration and learning.

The project is configured so that after cloning the repository, it can be compiled and executed with no additional setup.  

>**Target build configuration is Release x86, so please use this**.

Building the solution in **Release x86** automatically copies all required DLLs and asset folders into the output directory.

<img width="802" height="832" alt="image" src="https://github.com/user-attachments/assets/455ed31a-6a0b-4363-884d-b36fa5036ac2" />


---

## Project Overview

The project implements a basic rendering engine featuring:

- A windowing and input system (GLFW + GLEW)
- A movable free-look camera (WASD + mouse)
- A shader system supporting uniforms, structs, and arrays
- Directional, point and spot lighting using the Phong model
- Materials with specular intensity and shininess
- Mesh class managing VAO, VBO and IBO
- Texture loading via stb_image
- Model loading via Assimp (OBJ + textures)
- A simple scene with primitives and imported models

---

## Topics Covered

This project touches on the following concepts:

**Rendering Pipeline**
- Vertex and fragment shaders  
- Attribute layouts (position, UVs, normals)  
- Model, view and projection matrices  
- Normal transformation using inverse-transpose  
- Texture sampling  

**Lighting**
- Ambient, diffuse and specular components  
- Directional lights  
- Point lights with attenuation  
- Spotlights with soft edges  
- Per-fragment Phong lighting  

**Engine Components**
- Mesh creation from raw vertex data  
- Shader compilation and linking  
- Uniform handling (matrices, vectors, struct arrays)  
- Material system  
- Texture system  
- Camera movement and look direction  
- Window creation, input callbacks and mouse deltas  

**Model Loading**
- Assimp scene traversal  
- Mesh extraction  
- UVs, normals and index loading  
- Texture lookup and fallback textures  

---

## Folder Structure

OpenGLProject/  
│  
├── Models/ # Imported OBJ models  
├── Shaders/ # GLSL vertex & fragment shaders  
├── Textures/ # PNG textures (diffuse maps)  
├── *.cpp, *.h # Engine and rendering code  
└── DLLs # assimp / glew DLLs (copied on build)  

---

## Build Instructions (Visual Studio)

1. Clone the repository.
2. Open the solution in **Visual Studio**.
3. Select **Release x86**.
4. Build the project.
5. The Post-Build step copies:
   - `assimp-vc143-mt.dll`  
   - `glew32.dll`  
   - `Models/`  
   - `Shaders/`  
   - `Textures/`  
   into the output folder automatically.

Run the executable from:

OpenGLProject/Release/
