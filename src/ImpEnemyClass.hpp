#ifndef _IMP_ENEMY_CLASS_HPP
#define _IMP_ENEMY_CLASS_HPP

#include "RealEnemyClass.hpp"

class ImpEnemyClass : public RealEnemyClass{
public:
    ImpEnemyClass(Sprite fireball_sprite, Sprite sprite, Sprite gold_sprite, double x_pos, double y_pos, int plat_left, int plat_right)
     : RealEnemyClass(sprite, gold_sprite, x_pos, y_pos, plat_left, plat_right), fireball_sprite_(fireball_sprite){

        scale_ = 4;
        fireball_sprite_.setScale(scale_, scale_);

        first_hit_fireball_ = true;
     }

    Sprite fireball_sprite_;
    double scale_;
    bool first_hit_fireball_;

};
#endif // _IMP_ENEMY_CLASS_HPP

