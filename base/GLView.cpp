//
//  GLView.cpp
//  gl
//
//  Created by huangkun on 15/11/2017.
//  Copyright © 2017 kk. All rights reserved.
//

#include "GLView.h"
#include <stdio.h>
#include <stdlib.h>
#include "Application.h"
#include "Render.h"

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    printf("key_callback: key(%d), action(%d),mods(%d)", key, action, mods);
    if (action != GLFW_PRESS)
        return;

    switch (key) {
        case GLFW_KEY_LEFT: {
            break;
        }
        case GLFW_KEY_RIGHT: {
            break;
        }
        case GLFW_KEY_ESCAPE: {
            Application::getInstance()->release();
            break;
        }
        default:
            break;
    }
}

static void error_callback(int error, const char *description) {
    fprintf(stderr, "Error: %s\n", description);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    printf("framebuffer_size_callback: %d, %d", width, height);
    glViewport(0, 0, width, height);
}

void window_size_callback(GLFWwindow *window, int width, int height) {
    printf("window_size_callback: %d, %d", width, height);
}

GLView::GLView() {
}

GLView::~GLView() {
    glfwTerminate();
}

GLView *GLView::createWithRect(int x, int y, int width, int height) {
    auto ret = new GLView();
    if (ret->initWithRect(x, y, width, height)) {
        return ret;
    }
    return nullptr;
}

bool GLView::initWithRect(int x, int y, int width, int height) {
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        printf("Failed to initialize GLFW");
        return false;
    }
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_FLOATING, GL_TRUE);
    GLFWwindow *window = glfwCreateWindow(width, height, "GL", NULL, NULL);
    if (!window) {
        printf("Failed to create GLFW window");
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        printf("Failed to initialize GLAD");
        glfwTerminate();
        return false;
    }
    glfwSetKeyCallback(window, key_callback);
    glfwSetWindowPos(window, x, y);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);
    glfwShowWindow(window);
    _window = window;
    int realW = 0, realH = 0;
    glfwGetWindowSize(window, &realW, &realH);
    printf("GLView::initWithRect(%d,%d,%d,%d), realSize=(%d,%d)", x, y, width, height, realW, realH);

    return true;
}

void GLView::pollEvents() {
    glfwPollEvents();
}

void GLView::swapBuffers() {
    glfwSwapBuffers(_window);
}

bool GLView::windowShouldClose() {
    return glfwWindowShouldClose(_window);
}

void GLView::release() {
    printf("GLView::release");
    glfwTerminate();
}