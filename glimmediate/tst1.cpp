#include <GLFW/glfw3.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

static GLFWwindow* window = nullptr;
static void (*display)() = nullptr;

void display1() {
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0f, 1.0f, 0.0f); // green
  glBegin(GL_TRIANGLES);
  glVertex3f(-0.5f, -0.5f, 0.0f);
  glVertex3f( 0.5f, -0.5f, 0.0f);
  glVertex3f( 0.0f,  0.5f, 0.0f);
  glEnd();
  glFlush();
}

void display2() {
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_TRIANGLES);
  glColor3f(1.0f, 0.0f, 0.0f); // red
  glVertex3f(-0.5f, -0.5f, 0.0f);
  glVertex3f( 0.5f, -0.5f, 0.0f);
  glVertex3f( 0.0f,  0.5f, 0.0f);
  glEnd();
  glFlush();
}

void display3() {
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_TRIANGLES);
  glColor3f(1.0f, 0.0f, 0.0f);
  glVertex3f(-0.5f, -0.5f, 0.0f);
  glColor3f(0.0f, 1.0f, 0.0f);
  glVertex3f( 0.5f, -0.5f, 0.0f);
  glColor3f(0.0f, 0.0f, 1.0f);
  glVertex3f( 0.0f,  0.5f, 0.0f);
  glEnd();
  glFlush();
}

void display4() {
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_TRIANGLES);
  glColor3f(1.0f, 0.0f, 0.0f);
  glVertex3f(-0.5f, -0.5f, 0.0f);
  glVertex3f( 0.0f, -0.1f, 0.0f);
  glVertex3f( 0.0f,  0.5f, 0.0f);
  glColor3f(0.0f, 1.0f, 0.0f);
  glVertex3f(-0.5f, -0.5f, 0.0f);
  glVertex3f( 0.5f, -0.5f, 0.0f);
  glVertex3f( 0.0f, -0.1f, 0.0f);
  glColor3f(0.0f, 0.0f, 1.0f);
  glVertex3f( 0.5f, -0.5f, 0.0f);
  glVertex3f( 0.0f,  0.5f, 0.0f);
  glVertex3f( 0.0f, -0.1f, 0.0f);
  glEnd();
  glFlush();
}

void frame() {
  glfwPollEvents();
  if (display) {
    display();
  }
  glfwSwapBuffers(window);
}

void keyboard(int key) {
  switch (key) {
    case GLFW_KEY_1: display = display1; break;
    case GLFW_KEY_2: display = display2; break;
    case GLFW_KEY_3: display = display3; break;
    case GLFW_KEY_4: display = display4; break;
    default: break;
  }
}

void reshape(int w, int h) {
  glViewport(0, 0, w, h);
}

int main() {
  if (!glfwInit()) {
    return -1;
  }
  window = glfwCreateWindow(
      400, 400,
      "GLImmediate test",
      nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    return -2;
  }
  glfwSetKeyCallback(window,
    [](GLFWwindow*, int key, int, int, int) {
      keyboard(key);
    });
  glfwSetWindowSizeCallback(window,
    [](GLFWwindow*, int w, int h) {
      reshape(w, h);
    });
  glfwMakeContextCurrent(window);
#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(frame, 0, 1);
#else
  while (!glfwWindowShouldClose(window)) {
    frame();
  }
#endif
  glfwTerminate();
  return 0;
}

// vim: sw=2 ts=2 et:
