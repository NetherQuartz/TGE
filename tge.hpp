#ifndef TGE_HPP
#define TGE_HPP

#include <vector>
#include <string>

namespace TGE {

    struct Point final {
        unsigned x;
        unsigned y;
    };

    enum class Colors {
        Black, Red, Green, Yellow, Blue, Magenta, Cyan, White, Transparent
    };

    class GameObject {
    public:

        explicit GameObject(Point);
        GameObject(unsigned, unsigned);

        virtual ~GameObject();

        Point position() const;

    protected:
        
        Point position_;
    };

    class Grid {
    public:

        Grid(unsigned width, unsigned height);
        ~Grid();

        void Print() const;

        void Place(unsigned x, unsigned y, Colors color);
        void Place(Point position, Colors color);
        void Place(const GameObject & gameObject);

        unsigned width() const;
        unsigned height() const;

    private:

        std::vector<std::vector<Colors>> grid_;
        unsigned width_;
        unsigned height_;
    };

    class Game {
    public:

        Game(unsigned, unsigned);
        virtual ~Game();
    
    protected:

        Grid grid_;

    private:

        Game();
        Game operator=(const Game &);

    };

    void ColoredOutput(std::string text, Colors foreground, Colors background = Colors::Transparent);
};

//#if defined(_WIN32) || defined(WIN32)
//#include "tge_win.hpp"
//#elif defined(__unix__)
//#include "tge_unix.hpp"
//#else
//#error Unknown operating system! This code has been tested only on Windows and *nix systems!
//#endif

#endif