#ifndef _REAL_ENEMY_CLASS_HPP
#define _REAL_ENEMY_CLASS_HPP

#include "GameObject.hpp"

using namespace sf;

//Real Enemy class where we store all the relevant information on enemies
class RealEnemyClass : public GameObject{
public:
    RealEnemyClass(Sprite sprite, Sprite gold_sprite, double x_pos, double y_pos, int plat_left, int plat_right)
     : GameObject(x_pos, y_pos), sprite_(sprite), gold_sprite_(gold_sprite), platform_left_(plat_left), platform_right_(plat_right){

        sprite_.setPosition(x_pos_, y_pos_);
        scale_ = 4;
        sprite_.setScale(scale_, scale_);

        gold_collected_ = false;

        enemy_hp_ = 100;
        facing_left_ = true;
        attacking_ = false;

        //we use these to patrol the enemy
        phase_clock_.restart();
        move_phase_ = 0;
        phase_delta_ = 3000;

        //when two sprites intersect that connection lasts - so one hit can deal -80 damage witch we dont want
        first_hit_laser_ = true;
        first_hit_shooting_ = true;

        enemy_dead_ = false;
     }

    Sprite sprite_;
    Sprite gold_sprite_;
    bool gold_collected_;
    double scale_;
    double x_vel_;
    double y_vel_;
    int platform_left_;
    int platform_right_;

    double enemy_hp_;
    bool facing_left_;
    bool attacking_;
    Clock phase_clock_;
    int move_phase_;
    int phase_delta_;
    bool first_hit_laser_;
    bool first_hit_shooting_;
    bool enemy_dead_;

};

#endif // _REAL_ENEMY_CLASS_HPP

