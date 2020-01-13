
#ifndef _MINOTAUR_ENEMY_CLASS_HPP
#define _MINOTAUR_ENEMY_CLASS_HPP

using namespace sf;

class MinotaurEnemyClass : public RealEnemyClass{
public:
    MinotaurEnemyClass(Sprite sprite, double x_pos, double y_pos, int plat_left, int plat_right)
     : RealEnemyClass(sprite, x_pos, y_pos, plat_left, plat_right){

        attack_mode_ = 3;
        choose_attack_ = true;
     }

     int attack_mode_;
     bool choose_attack_;
};
#endif // _MINOTAUR_ENEMY_CLASS_HPP
