#ifndef _BATSY_ENEMY_CLASS_HPP
#define _BATSY_ENEMY_CLASS_HPP

using namespace sf;

class BatsyEnemyClass : public RealEnemyClass{
public:
    BatsyEnemyClass(Sprite sprite, Sprite sonic_sprite, Sprite gold_sprite, double x_pos, double y_pos, int plat_left, int plat_right)
     : RealEnemyClass(sprite, gold_sprite, x_pos, y_pos, plat_left, plat_right), sonic_sprite_(sonic_sprite){

        sonic_sprite_.setPosition(x_pos_, y_pos_);
        sonic_damage_ = 10;
        first_hit_sonic_ = true;
        phase_delta_ = 300;



     }

    int sonic_damage_;
    Sprite sonic_sprite_;
    bool first_hit_sonic_;

};
#endif // _BATSY_ENEMY_CLASS_HPP
