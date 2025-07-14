#include "Node.h"

//Node::Node() {
//	
//}

Node::~Node() {

}

Node* Node::parent() const {
	// just a simple parentNode getter.
	return parentNode;
}

// reparents exisiting node to another Parent Node

/*First of all checks whether the Node we are trying to reparent already has a parent or not,
	if YES -> we need to remove the Node itself from the ACTIVE PARENT's childrenNodes list(vector).
	std::find(m_parent->m_children.begin(), m_parent->m_children.end(), this)
	this removes "this" specified node we are calling the method from, from the parents child list.

	Afterwards we reassign the parentNode of the Node we are working with to newParentNode given in args.
	Then finally we add this Node to the newParentNode's childrenNodes vector
	newParentNode->childrenNodes.push_back(this), this as in the Node we are trying to reparent.


	EXPLANATION ABOVE IS A LITTLE OUTDATED, SINCE I DETECTED THAT IF WE REPARENT CHILD NODE TO NULLPTR,
		IT IS LIKELY TO CAUSE CRASH THE WHOLE ENGINE!*/
void Node::reparent(Node* newParentNode) {
	if (parentNode) {
		auto it = std::find(parentNode->childrenNodes.begin(),
							parentNode->childrenNodes.end(), this);
		// only erase if the iterator points to a real child, not .end() not found
		if (it != parentNode->childrenNodes.end()) {
			parentNode->childrenNodes.erase(it);
		}
		//parentNode->childrenNodes.erase(std::find(parentNode->childrenNodes.begin(),
		//								parentNode->childrenNodes.end(), this));
	}

	parentNode = newParentNode;
	if(newParentNode) {
		newParentNode->childrenNodes.push_back(this);
	}
}	
//void Node::reparent(Node* newParentNode) {
//	// Prevent cycles
//	Node* current = newParentNode;
//	while (current) {
//		if (current == this) {
//			std::cout << "CYCLE DETECTED: Can't reparent to one of its descendants.\n";
//			return;
//		}
//		current = current->parent();
//	}
//
//	// Detach from current parent
//	if (parentNode) {
//		auto it = std::find(parentNode->childrenNodes.begin(), parentNode->childrenNodes.end(), this);
//		if (it != parentNode->childrenNodes.end()) {
//			parentNode->childrenNodes.erase(it);
//		}
//	}
//
//	parentNode = newParentNode;
//
//	if (newParentNode) {
//		newParentNode->childrenNodes.push_back(this);
//	}
//}


void Node::addChild(Node* childNode) {
	// so we are basically going to be calling reparent in order to add a parent to the Node,
	// just to make sure that node doesn't already have a parent, and just efficient.
	childNode->reparent(this);
}

void Node::removeChild(Node* childNodeToBeRemoved) {
	/*It will check if the childNode's parent exist(which it should since we are removing a child!)
		Then it should erase itself from the parentNode's children list.
		Since the new parentNode = nullptr; What happens is that the child is now assigned to nullptr.*/
	childNodeToBeRemoved->reparent(nullptr);
}

//void Node::drawNodeTesting() {
//	for (auto child : childrenNodes) {
//		child->drawNodeTesting();
//	}
//}


/* A BIG ASS PARAGRAPH EXPLAINING THE YEEPIEST CODE I'VE EVER WITNESSED :
	CREDITS TO DUMMREN;
		Returns the world transformation matrix of the given node(pos, rot, scale) based on its own
		transform + the transform of the parent.
		
	First of all we declare basic mat4 identity matrix 1.0f.*/
//glm::mat4 Node::transform() const {
//	glm::mat4 out{ 1.0f }; 
//	if (parentNode) {
//		out = glm::translate(out, parentNode->globalPos());
//		out = glm::eulerAngleYXZ(parentNode->globalRot().x, 
//			parentNode->globalRot().y, parentNode->globalRot().z) * out;
//	}
//	out = glm::translate(out, globalPosition);
//	out = glm::eulerAngleYXZ(globalRotation.x, globalRotation.y, globalRotation.z) * out;
//	out = glm::scale(out, globalScale);
//	
//	return out;
//}
// 
//glm::mat4 Node::transform() const {
//	glm::mat4 localTransform = glm::translate(glm::mat4(1.0f), globalPosition) *
//		glm::eulerAngleYXZ(globalRotation.y, globalRotation.x, globalRotation.z) *
//		glm::scale(glm::mat4(1.0f), globalScale);
//
//	if (parentNode)
//		return parentNode->transform() * localTransform;
//
//	//std::cout << this << glm::to_string(localTransform) << "\n";
//	return localTransform;
//}

glm::mat4 Node::transform() const {
	glm::mat4 localTransform = glm::translate(glm::mat4(1.0f), this->globalPosition)
		* glm::eulerAngleYXZ(globalRotation.y, globalRotation.x, globalRotation.z) *
		glm::scale(glm::mat4(1.f), globalScale);
	// scale is applied directly in shape object constructor xD
	return localTransform;
}



glm::mat4 Node::view() const {
	glm::mat4 out{ 1.0f };

	if (parentNode) {
		out = glm::translate(out,-parentNode->globalPos());
		out = glm::eulerAngleYXZ(-parentNode->globalRot().y,
								 -parentNode->globalRot().x,
								 -parentNode->globalRot().z) * out;
		// out = glm::translate(out, m_parent->globalPos());
	}

	out = glm::translate(out, -globalPosition);
	out = glm::eulerAngleYXZ(-globalRotation.y, -globalRotation.x, -globalRotation.z) * out;
	out = glm::scale(out, globalScale);

	return out;
}

glm::vec3 Node::globalPos() const {
	return globalPosition + (parentNode ? parentNode->globalPosition : glm::vec3(0.0f));
}

glm::vec3 Node::globalRot() const {
	return globalRotation + (parentNode ? parentNode->globalRotation : glm::vec3(0.0f));
}