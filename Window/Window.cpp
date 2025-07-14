#include "Window.h"

Window::Window(unsigned int w, unsigned int h, bool rs, bool fs) {
	this->width = w;
	this->height = h;
	this->resizable = rs;
	this->fullscreen = fs;

	if (!initializeWindow()) {
		std::cout << "WINDOW-CLASS::WINDOW::Window initialization failed!\n";
		return;
	} else {
		std::cout << "WINDOW-CLASS::WINDOW::Window initialization success!\n";
	}
}

void Window::setStartPos(const GLFWvidmode* glvm) {
	int xPosToCenterWindow = (glvm->width / 2) - (width / 2);
	int yPosToCenterWindow = (glvm->height / 2) - (height / 2);
	glfwSetWindowPos(window, xPosToCenterWindow, yPosToCenterWindow);
}

void Window::makeContextCurrent() {
	glfwMakeContextCurrent(this->window);
}

void Window::enablevsync() {
		glfwSwapInterval(1);
}

bool Window::initializeWindow() {
	GLFWmonitor* glmonitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* glvm = glfwGetVideoMode(glmonitor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, (resizable == true ? GLFW_TRUE : GLFW_FALSE));
	if (fullscreen) {
		glfwWindowHint(GLFW_RED_BITS, glvm->redBits);
		glfwWindowHint(GLFW_BLUE_BITS, glvm->blueBits);
		glfwWindowHint(GLFW_GREEN_BITS, glvm->greenBits);
		glfwWindowHint(GLFW_REFRESH_RATE, glvm->refreshRate);
		window = glfwCreateWindow(glvm->width, glvm->height, title, glmonitor, NULL);
	} else {
		window = glfwCreateWindow(width, height, title, NULL, NULL);
	}
	if (window == NULL) {
		std::cout << "WINDOW-CLASS::INITIALIZEWINDOW::Window creation failed! : "
			<< width, height, title;
		return false;
	} else {
		std::cout << "Window created!\n";
	}
	Window::makeContextCurrent();
	Window::setStartPos(glvm);
	glfwSetWindowUserPointer(getNativePointer(), this);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "WINDOW-CLASS::INITIALIZEWINDOW::GLAD failed!\n";
		return false;
	}
	Window::setGLVP(glvm);
	Window::resizeCallback();
	return true;
}

void Window::setGLVP(const GLFWvidmode* glvm) const {
	if(this->fullscreen) {
		glViewport(0, 0, glvm->width, glvm->height);
	} else {
		glViewport(0, 0, this->width, this->height);
	}
}

void Window::resizeCallback() {
	glfwSetFramebufferSizeCallback(this->window, [](GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
		});
}