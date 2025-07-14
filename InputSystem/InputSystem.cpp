#include "InputSystem.h"


InputSystem::InputSystem() {
	std::cout << "INPUTSYSTEM::CREATED!\n";
}

/*BOOL PART OF THE SYSTEM*/
bool InputSystem::isKeyPressed(int key) {
	return std::find(keysPressed.begin(), keysPressed.end(), key) != keysPressed.end();
}

bool InputSystem::isKeyHeld(int key) {
	return std::find(keysHolding.begin(), keysHolding.end(), key) != keysHolding.end();
}

bool InputSystem::isKeyReleased(int key) {
	return std::find(keysReleased.begin(), keysReleased.end(), key) != keysReleased.end();
}

bool InputSystem::isMouseButtonPressed(int button) {
	return std::find(mouseButtonsPressed.begin(), mouseButtonsPressed.end(), button) != mouseButtonsPressed.end();
}

bool InputSystem::isMouseButtonHeld(int button) {
	return std::find(mouseButtonsHeld.begin(), mouseButtonsHeld.end(), button) != mouseButtonsHeld.end();
}

bool InputSystem::isMouseButtonReleased(int button) {
	return std::find(mouseButtonsReleased.begin(), mouseButtonsReleased.end(), button) != mouseButtonsReleased.end();
}
/*BOOL PART OF THE SYSTEM ENDS*/

void InputSystem::initializeInputSystem(GLFWwindow* currentWindow) {
	activeWindowPointer = currentWindow;
	glfwSetWindowUserPointer(currentWindow, this);

	glfwSetKeyCallback(currentWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		auto* inputSystem = static_cast<InputSystem*>(glfwGetWindowUserPointer(window));
		if (inputSystem) {
			inputSystem->key_callback(window, key, scancode, action, mods);
		}
		});

	glfwSetMouseButtonCallback(currentWindow, [](GLFWwindow* window, int button, int action, int mods) {
		auto* inputSystem = static_cast<InputSystem*>(glfwGetWindowUserPointer(window));
		if (inputSystem) {
			inputSystem->mouse_button_callback(window, button, action, mods);
		}
		});

	glfwSetCursorPosCallback(currentWindow, [](GLFWwindow* window, double xpos, double ypos) {
		auto* inputSystem = static_cast<InputSystem*>(glfwGetWindowUserPointer(window));
		if (inputSystem) {
			inputSystem->cursor_position_callback(window, xpos, ypos);
		}
		});
}

void InputSystem::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	//if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
	//	glfwSetWindowShouldClose(window, GLFW_TRUE);
	//}
	if(action == GLFW_PRESS) {
		if(std::find(keysPressed.begin(), keysPressed.end(), key) != keysPressed.end()) {
			std::cout << "KEY ALREADY IN THE VECTOR" << "\n";
		} else {
			keysPressed.emplace_back(key);
			keysHolding.emplace_back(key);
		}
	}

	if(action == GLFW_RELEASE) {
		for(std::vector<int>::iterator it = keysHolding.begin(); it != keysHolding.end(); it++) {
			if(*it == key) {
				keysHolding.erase(it);
				break;
			}
		}
		keysReleased.emplace_back(key);
	}
}

void InputSystem::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (std::find(mouseButtonsHeld.begin(), mouseButtonsHeld.end(), button) == mouseButtonsHeld.end()) {
			mouseButtonsPressed.emplace_back(button);
			mouseButtonsHeld.emplace_back(button);
		}
	}
	if (action == GLFW_RELEASE) {
		mouseButtonsReleased.emplace_back(button);
		mouseButtonsHeld.erase(std::remove(mouseButtonsHeld.begin(), mouseButtonsHeld.end(), button), mouseButtonsHeld.end());
	}
}

void InputSystem::cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) {
		mouseX = xpos;
		mouseY = ypos;
		firstMouse = false;
	}

	mouseDeltaX = xpos - mouseX;
	mouseDeltaY = mouseY - ypos; // Invert Y if needed
	mouseX = xpos;
	mouseY = ypos;
}

double InputSystem::getMouseDeltaX() const { return mouseDeltaX; }
double InputSystem::getMouseDeltaY() const { return mouseDeltaY; }


//Call this at the end of your game loop
void InputSystem::clearReleasedKeys() {
	keysPressed.clear();
	keysReleased.clear();

	mouseButtonsPressed.clear();
	mouseButtonsReleased.clear();

	mouseDeltaX = 0.0;
	mouseDeltaY = 0.0;
}
