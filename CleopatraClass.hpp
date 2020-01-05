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

        int delta_time = 300;
        Clock cleo_idle_clock;

        while(true){
            index_update(delta_time, cleo_idle_clock, 4, rectangles_index_idle_);
            sprite_.setTextureRect(rectangles_cleopatra_idle_[rectangles_index_idle_]);
        }
    }

    Sprite sprite_;
    double scale_;
    std::vector<IntRect> rectangles_cleopatra_idle_;
    int rectangles_index_idle_;

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
    }
};

#endif // _CLEOPATRA_CLASS_HPP
