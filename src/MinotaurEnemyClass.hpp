
#ifndef _MINOTAUR_ENEMY_CLASS_HPP
#define _MINOTAUR_ENEMY_CLASS_HPP

using namespace sf;

class MinotaurEnemyClass : public RealEnemyClass{
public:
    MinotaurEnemyClass(Sprite sprite, Sprite gold_sprite, double x_pos, double y_pos, int plat_left, int plat_right)
     : RealEnemyClass(sprite, gold_sprite, x_pos, y_pos, plat_left, plat_right){

        attack_mode_ = 0;
        delta_attack_ = 3000;
        attack_in_progress_ = false;
     }

     int attack_mode_;
     int delta_attack_;
     Clock attack_clock_;
     bool attack_in_progress_;
};
#endif // _MINOTAUR_ENEMY_CLASS_HPP
