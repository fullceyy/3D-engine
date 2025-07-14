#pragma once
#include "GLFW/glfw3.h"
#include <vector>
#include <iostream>

class InputSystem {
public:
	//InputSystem(GLFWwindow* currentWindow);
	InputSystem();
	void initializeInputSystem(GLFWwindow* currentWindow);

	bool isKeyPressed(int key);
	bool isKeyHeld(int key);
	bool isKeyReleased(int key);
	bool isMouseButtonPressed(int button);
	bool isMouseButtonHeld(int button);
	bool isMouseButtonReleased(int button);

	double getMouseDeltaX() const;
	double getMouseDeltaY() const;

	void clearReleasedKeys(); // Optional, if you want to clear every frame
	void key_callback(GLFWwindow*, int key, int scancode, int action, int mods);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

	inline GLFWwindow* getActiveWindowPointer() const { return activeWindowPointer; }
private:
	GLFWwindow* activeWindowPointer;
	std::vector<int> keysPressed; // ints?
	std::vector<int> keysReleased;
	std::vector<int> keysHolding;
	std::vector<int> mouseButtonsPressed;
	std::vector<int> mouseButtonsReleased;
	std::vector<int> mouseButtonsHeld;

	double mouseX = 0.0, mouseY = 0.0;
	double mouseDeltaX = 0.0, mouseDeltaY = 0.0;
	bool firstMouse = true;
};

