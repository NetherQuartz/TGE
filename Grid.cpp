#include "tge.hpp"
using namespace TGE;

Grid::Grid(unsigned width, unsigned height) : width_(width), height_(height) {
    grid_ = std::vector<std::vector<Colors>>(width, std::vector<Colors>(height));
}

Grid::~Grid() = default;

unsigned int Grid::height() const {
    return height_;
}

unsigned int Grid::width() const {
    return width_;
}

void Grid::Place(const GameObject &gameObject) {
    throw "Not implemented yet!";
}

void Grid::Place(unsigned int x, unsigned int y, Colors color) {
    grid_[x][y] = color;
}

void Grid::Place(Point position, Colors color) {}

void Grid::Print() const {
    std::cout << grid_.size() << 'x' << grid_[0].size() << std::endl;
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            ColoredOutput("  ", Colors::Transparent, grid_[x][y]);
        }
        std::cout << '\n';
    }
}