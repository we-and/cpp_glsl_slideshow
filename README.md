# Compiling

g++ -o ShaderSwitcher main.cpp -std=c++11 -I/opt/homebrew/opt/glew/include -I/opt/homebrew/opt/glfw/include -L/opt/homebrew/lib -lGLEW -lglfw -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo