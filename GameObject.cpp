#include "tge.hpp"
using namespace TGE;

GameObject::GameObject(unsigned x, unsigned y) : position_({x, y}) {

}

GameObject::GameObject(Point position) : position_(position) {

}

GameObject::~GameObject() {

}

Point GameObject::position() const {
    return  position_;
}