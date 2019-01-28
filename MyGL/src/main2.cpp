#include <unistd.h>
#include <GLFW/glfw3.h>
#include <iostream>
void b_callback(GLFWwindow* window, int width, int height);

void b_callback(GLFWwindow* window, int width, int height) {
  std::cout << "View";
  glViewport(0,0, width, height);
}
int main(void) {
  GLFWwindow* window;
  if (!glfwInit()) return -1;
  window = glfwCreateWindow(640, 480, "HElo", NULL, NULL);
  if(!window) {
    glfwTerminate();
    return -1;
  }
  int count = 0;
  glfwSetFramebufferSizeCallback(window, b_callback);
  while(!glfwWindowShouldClose(window) and count < 10) {
    glfwSwapBuffers(window);
    glfwPollEvents();
    glViewport(0, 0, 320, 240);
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) break;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        glClearColor(1.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        count += 1;
    }
    sleep(0.2);
  }
  std::cout << count;
  glfwTerminate();
  std::cout << "Bye";
  return 0;
}
