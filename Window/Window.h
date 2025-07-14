#pragma once
#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include <iostream>

class Window {
	public:
		Window(unsigned int, unsigned int, bool, bool);

		inline void pollEvents() { glfwPollEvents(); }
		inline void swapBuffers() { glfwSwapBuffers(this->window); }
		
		void enablevsync();

		inline GLFWwindow* getNativePointer() { return window; }
		inline unsigned int getWidth()  const { return width;  }
		inline unsigned int getHeight() const { return height; }

	private:
		bool initializeWindow();
		void setStartPos(const GLFWvidmode*);
		void makeContextCurrent();
		void setGLVP(const GLFWvidmode*) const;
		void resizeCallback();


		GLFWwindow* window;
		unsigned int width = 800;
		unsigned int height = 600;
		bool resizable = false;
		bool fullscreen = false;
		const char* title = "Tagshare";
};

#endif