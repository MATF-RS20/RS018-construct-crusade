#ifndef _CLEOPATRA_ENEMY_CLASS_HPP
#define _CLEOPATRA_ENEMY_CLASS_HPP

using namespace sf;

class CleopatraEnemyClass : public RealEnemyClass{
public:
    CleopatraEnemyClass(Sprite sprite, Sprite heart_sprite, Sprite gold_sprite, double x_pos, double y_pos, int plat_left, int plat_right)
     : RealEnemyClass(sprite, gold_sprite, x_pos, y_pos, plat_left, plat_right), heart_sprite_(heart_sprite){
        heart_sprite_.setPosition(x_pos_, y_pos_);
        scale_ = 4;
        //heart_sprite_.setScale(scale_, scale_);

        first_hit_pulsing_ = true;

        pulsing_ = false;
        pulsing_phase_ = 0;
        //pulsing_phase_delta_ = 5000;

        pulsing_damage_ = 20;

     }

    double scale_;
    bool pulsing_;
    bool first_hit_pulsing_;
    Clock pulsing_clock_;
    int pulsing_phase_;
    int pulsing_phase_delta_;
    int pulsing_damage_;

    Sprite heart_sprite_;


};
#endif // _CLEOPATRA_ENEMY_CLASS_HPP
