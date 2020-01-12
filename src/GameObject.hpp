#ifndef _GAME_OBJECT_HPP
#define _GAME_OBJECT_HPP

class GameObject{
public:
    GameObject(double x_pos, double y_pos) : x_pos_(x_pos), y_pos_(y_pos)
    {}

protected:
    //default player position
    double x_pos_;
    double y_pos_;
};

#endif // _GAME_OBJECT_HPP
