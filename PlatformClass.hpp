#ifndef _PLATFORM_CLASS_HPP
#define _PLATFORM_CLASS_HPP

#include "GameObject.hpp"

class PlatformClass : public GameObject{
public:
    PlatformClass(sf::Sprite sprite, double x_pos, double y_pos) : GameObject(x_pos, y_pos), sprite_(sprite)
    {
        sprite_.setPosition(GameObject::x_pos_, GameObject::y_pos_);
        scale_ = 3.125;
        sprite_.setScale(scale_, scale_);
    }

    float scale_;
    sf::Sprite sprite_;
};

#endif
