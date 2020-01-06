#ifndef _CLEOPATRA_CLASS_HPP
#define _CLEOPATRA_CLASS_HPP

#include "GameObject.hpp"

using namespace sf;

//Enemy class
class CleopatraClass : public GameObject{
public:
    CleopatraClass(Sprite sprite, double x_pos, double y_pos)
     : GameObject(x_pos, y_pos), sprite_(sprite){
        sprite_.setPosition(x_pos_, y_pos_);
        scale_ = 4;
        sprite_.setScale(scale_, scale_);
        init_rectangles();
     }

     void Animation(){

        int delta_time = 100;
        Clock cleo_idle_clock;
        Clock cleo_walk_clock;
        Clock attack_clock;
        Clock death_clock;
        Clock heart_clock;

        while(true){
            //index_update(delta_time, cleo_idle_clock, 4, rectangles_index_idle_);
            //sprite_.setTextureRect(rectangles_cleopatra_idle_[rectangles_index_idle_]);

            index_update(delta_time, cleo_walk_clock, 4, rectangles_index_walk_);
            sprite_.setPosition(Vector2f(sprite_.getPosition().x-0.00001f, sprite_.getPosition().y));
            sprite_.setTextureRect(rectangles_cleo_walk_left_[rectangles_index_walk_]);

            //index_update(delta_time, cleo_walk_clock, 4, rectangles_index_walk_);
            //sprite_.setPosition(Vector2f(sprite_.getPosition().x+0.00001f, sprite_.getPosition().y));
            //sprite_.setTextureRect(rectangles_cleo_walk_right_[rectangles_index_walk_]);

        }
    }

    std::vector<IntRect> rectangles_cleopatra_idle_;
    int rectangles_index_idle_;

    std::vector<IntRect> rectangles_cleo_walk_right_;
     std::vector<IntRect> rectangles_cleo_walk_left_;
    int rectangles_index_walk_;

    std::vector<IntRect> rectangles_cleo_attack_left_;
    std::vector<IntRect> rectangles_cleo_attack_right_;
    int rectangles_index_attack_;

    std::vector<IntRect> rectangles_cleo_death_;
    int rectangles_index_death_;

    std::vector<IntRect> rectangles_cleo_heart_left_;
    std::vector<IntRect> rectangles_cleo_heart_right_;
    int rectangles_index_heart_;

    Sprite sprite_;
    double scale_;
    double x_vel_;
    double y_vel_;
    double cleo_hp_;
    bool facing_left_;
    bool attacking_;
    int move_phase_;


private:
     void index_update(int delta_time, Clock &clock, int iters, int &index){

        if(clock.getElapsedTime().asMilliseconds() > delta_time){
            index++;
            if(index == iters)
                index = 0;
            clock.restart();
        }
    }

    void init_rectangles(){
        rectangles_index_idle_ = 0;
        for (int i = 0; i < 3; i++){
            rectangles_cleopatra_idle_.push_back(IntRect(i*25, 0, 25, 25));
        }
        rectangles_cleopatra_idle_.push_back(IntRect(25, 0, 25, 25));

        for (int i = 0; i < 4; i++){
            rectangles_cleo_walk_left_.push_back(IntRect(i*25, 75, 25, 25));
        }

        for (int i = 0; i < 4; i++){
            rectangles_cleo_walk_right_.push_back(IntRect(i*25, 50, 25, 25));
        }
    }
};

#endif // _CLEOPATRA_CLASS_HPP
