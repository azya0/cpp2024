#include <SFML/Graphics.hpp>
#include <map>


enum class Color {
    RED = 0,
    GREEN,
    BLUE,
    YELLOW,
    CYAN,
    UNSELECTED,
    BOMB,
    COLORCHANGER,
};

class BaseGEM {
public:
    sf::CircleShape draw;
    static const int size = 20;
    int pos_x, pos_y;

    virtual ~BaseGEM() {};
};

class GEM : public BaseGEM {
public:
    Color color;

    GEM();
    GEM(Color _color);
    void selectColor(Color _color);
    void setPosition(int x, int y);

    virtual ~GEM() {};
};

class Bomb : public GEM {
public:
    Bomb();

    virtual ~Bomb() {};
};


class ColorChanger: public GEM {
public:
    ColorChanger();

    virtual ~ColorChanger() {};
};