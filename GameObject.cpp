#include <utility>

#include "tge.hpp"
using namespace TGE;

GameObject::GameObject(Point position, std::vector<std::vector<Colors>> body) : position_(position), body_(std::move(body)) {

}

GameObject::~GameObject() = default;

Point GameObject::getPosition() const {
    return  position_;
}

std::vector<std::vector<Colors>> &GameObject::body() {
    return body_;
}

const std::vector<std::vector<Colors>> &GameObject::body() const {
    return body_;
}

void GameObject::setPosition(Point position) {
    position_ = position;
}

void GameObject::move(Point shift) {
    position_.x += shift.x;
    position_.y += shift.y;
    position_.z += shift.z;
}

bool GameObject::compareByZ(const GameObject * lhs, const GameObject * rhs) {
    return lhs->getPosition().z < rhs->getPosition().z;
}
