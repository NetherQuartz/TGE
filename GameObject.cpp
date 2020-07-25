#include "tge.hpp"
using namespace TGE;

GameObject::GameObject(int x, int y) : position_({x, y, 0}) {

}

GameObject::GameObject(Point position) : position_(position) {

}

GameObject::~GameObject() {

}

Point GameObject::position() const {
    return  position_;
}