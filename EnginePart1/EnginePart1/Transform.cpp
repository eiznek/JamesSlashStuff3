#include "Transform.h"

Transform::Transform() {
	position = new VECTOR2;
}

Transform::~Transform() {
	delete(position);
	position = NULL;

}

void Transform::Translate(VECTOR2 translation) {
	*position += translation;

}

VECTOR2 Transform::GetPosition() {
	return *position;

}
