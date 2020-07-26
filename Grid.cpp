#include "tge.hpp"
#include <iostream>

using namespace TGE;

Grid::Grid(unsigned width, unsigned height, Colors fill) : width_(width), height_(height), fill_(fill) {
    grid_ = std::vector<std::vector<Colors>>(width, std::vector<Colors>(height, fill));
    gameObjects_ = std::set<const GameObject*, decltype(GameObject::compareByZ)*>(GameObject::compareByZ);
}

Grid::~Grid() = default;

unsigned int Grid::height() const {
    return height_;
}

unsigned int Grid::width() const {
    return width_;
}

void Grid::Place(const GameObject &gameObject) {
    gameObjects_.emplace(&gameObject);
}

void Grid::Draw() {
    for (size_t j = 0; j < height_; ++j) {
        for (size_t i = 0; i < width_; ++i) {
            grid_[i][j] = fill_;
        }
    }
    for (const GameObject * obj : gameObjects_) {
        for (size_t i = 0; i < obj->body().size(); ++i) {
            for (size_t j = 0; j < obj->body()[i].size(); ++j) {
                size_t x = i + obj->getPosition().x;
                size_t y = j + obj->getPosition().y;
                if (x >= 0 && x < width_ && y >= 0 && y < height_ && obj->body()[i][j] != Colors::Transparent) {
                    grid_[x][y] = obj->body()[i][j];
                }
            }
        }
    }
    for (size_t j = 0; j < height_; ++j) {
        for (size_t i = 0; i < width_; ++i) {
            ColoredOutput("  ", Colors::Transparent, grid_[i][j]);
        }
        std::cout << '\n';
    }
}