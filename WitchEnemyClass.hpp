#ifndef _WITCH_ENEMY_CLASS_HPP
#define _WITCH_ENEMY_CLASS_HPP

#include "RealEnemyClass.hpp"

using namespace sf;

class WitchEnemyClass : public RealEnemyClass{
public:
    WitchEnemyClass(Sprite sprite, Sprite poison_sprite, double x_pos, double y_pos, int plat_left, int plat_right)
     : RealEnemyClass(sprite, x_pos, y_pos, plat_left, plat_right), poison_sprite_(poison_sprite){

        brooming_ = false;
        hexing_ = false;
        brooming_phase_ = 0;
        brooming_phase_delta_ = 5000;
        first_hit_brooming_ = true;
        first_hit_hexing_1_ = true;
        first_hit_hexing_2_ = true;
        first_hit_hexing_3_ = true;
        first_hit_hexing_4_ = true;
        first_hit_hexing_5_ = true;
        first_hit_hexing_6_ = true;
        first_hit_hexing_7_ = true;
        first_hit_hexing_8_ = true;

        brooming_damage_ = 20;
        poison_damage_ = 10;

        poison_sprite_.setRotation(180.0f);
        poison_wave_delta_ = 1000;

     }

    bool brooming_;
    bool first_hit_brooming_;
    Clock brooming_clock_;
    int brooming_phase_;
    int brooming_phase_delta_;
    int brooming_damage_;

    bool hexing_;
    bool first_hit_hexing_1_;
    bool first_hit_hexing_2_;
    bool first_hit_hexing_3_;
    bool first_hit_hexing_4_;
    bool first_hit_hexing_5_;
    bool first_hit_hexing_6_;
    bool first_hit_hexing_7_;
    bool first_hit_hexing_8_;
    int poison_wave_delta_;
    int poison_damage_;
    Clock poison_clock_;
    Sprite poison_sprite_;

};
#endif // _WITCH_ENEMY_CLASS_HPP
