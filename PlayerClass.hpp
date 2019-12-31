#ifndef _PLAYER_CLASS_HPP
#define _PLAYER_CLASS_HPP

#include "PlatformClass.hpp"

double VEL = 1;

using namespace sf;
extern Clock bigTime;

//the constructs class
class PlayerClass : public GameObject{
public:

    PlayerClass(Sprite plasma_sprite, Sprite sprite, double x_pos, double y_pos) : GameObject(x_pos, y_pos), sprite_(sprite), plasma_sprite_(plasma_sprite){
        sprite_.setPosition(GameObject::x_pos_, GameObject::y_pos_);
        jumping_ = false;
        jump_time_ = 0;
        scale_ = 4;
        sprite_.setScale(scale_, scale_);
        plasma_sprite.setScale(scale_, scale_);
        rectangles_index_idle_ = 0;
        rectangles_index_ = 0;
        on_ground_ = true;

        init_rectangles();

    }

    //gain velocity if a button is pressed
    void update(bool player_up,bool player_down,bool player_right,bool player_left, std::vector<PlatformClass>& platforms){
        int time;
        int delta_time = 500;
        if(player_up){
            if(!jumping_){
                jumping_ = true;
                jump_time_ = bigTime.getElapsedTime().asMilliseconds();
                on_ground_ = false;
            }
        }
        if(!jumping_){
            y_vel_ = VEL;
        }
        if(player_up && player_down){
            y_vel_ = 0;
        }
        if(!player_up && !player_down){
            y_vel_ = VEL;
        }
        if(player_left){
            x_vel_ = -VEL;
        }
        if(player_right){
            x_vel_ = VEL;
        }
        if(player_left && player_right){
            x_vel_ = 0;
        }
        if(!player_left && !player_right){
            x_vel_ = 0;
        }
        if(player_left && player_up){
            x_vel_ = 0;
            y_vel_ = 0;
        }
        if(player_left && player_down){
            x_vel_ = 0;
            y_vel_ = 0;
        }
        if(player_up && player_right){
            x_vel_ = 0;
            y_vel_ = 0;
        }
        if(player_down && player_right){
            x_vel_ = 0;
            y_vel_ = 0;
        }

        //move the sprite
        collision(x_vel_, 0, platforms);
            if(!left_collide_)
                sprite_.move(Vector2f(x_vel_, 0));

        time = bigTime.getElapsedTime().asMilliseconds();
        if(jumping_ && jump_time_ + delta_time > time){
            y_vel_ = -VEL;
        }
        else if(jumping_ && !on_ground_){
            y_vel_ = VEL;
        }else if(jumping_  && on_ground_){
            jumping_ = false;
        }

        sprite_.move(Vector2f(0, y_vel_));
        collision(0, y_vel_, platforms);

    }

    //check if you are intersecting with a platform
    void collision(float delta_x, float delta_y, std::vector<PlatformClass>& platforms){
        if(delta_x < 0 || delta_y != 0){
            left_collide_ = false;
        }
        for(PlatformClass const& plat : platforms){
            if(plat.sprite_.getGlobalBounds().intersects(sprite_.getGlobalBounds())){
                if(delta_x > 0){
                    sprite_.setPosition(Vector2f(plat.sprite_.getGlobalBounds().left - sprite_.getGlobalBounds().width - 36, sprite_.getPosition().y));
                    left_collide_ = true;
                }
                if(delta_x < 0){
                    sprite_.setPosition(Vector2f(plat.sprite_.getGlobalBounds().left + plat.sprite_.getGlobalBounds().width + 5, sprite_.getPosition().y));
                }
                if(delta_y > 0){
                    on_ground_ = true;
                    sprite_.setPosition(Vector2f(sprite_.getPosition().x, plat.sprite_.getGlobalBounds().top - sprite_.getGlobalBounds().height));
                }
                if(delta_y < 0){
                    sprite_.setPosition(Vector2f(sprite_.getPosition().x, plat.sprite_.getGlobalBounds().top + plat.sprite_.getGlobalBounds().height));
                }
            }

            }
    }

    void IdleAnimation(){

        int time_idle;
        //delt_time - duration of a frame
        int delta_time = 200;
        //helps us determin if our frame should be changed - it marks the time when a frame is first used
        int current_frame_time_idle = 0;

        Clock gameClockIdle;

        int time;
        //helps us determin if our frame should be changed - it marks the time when a frame is first used
        int current_frame_time = 0;

        Clock gameClock;

        while(true){
            time_idle = gameClockIdle.getElapsedTime().asMilliseconds();

            //update rectangle_index if its time for the next frame
            if(current_frame_time_idle+delta_time < time_idle){
                current_frame_time_idle = time_idle;
                if(rectangles_index_idle_ == 4){
                    rectangles_index_idle_ = 0;
                    current_frame_time_idle = 0;
                    rectangles_index_idle_--;
                    gameClockIdle.restart();
                }
                rectangles_index_idle_++;
            }

            time = gameClock.getElapsedTime().asMilliseconds();

            //update rectangle_index if its time for the next frame
            if(current_frame_time+delta_time < time){
                current_frame_time = time;
                if(rectangles_index_ == 5){
                    rectangles_index_ = 0;
                    current_frame_time = 0;
                    rectangles_index_--;
                    gameClock.restart();
                }
                rectangles_index_++;
            }


        }//while

    }//IdleAnimation

    std::vector<IntRect> rectanglesIdle_;
    std::vector<IntRect> rectanglesRight_;
    std::vector<IntRect> rectanglesLeft_;
    std::vector<IntRect> rectangles_plasma_booster_;
    bool on_ground_;
    int rectangles_index_idle_;
    int rectangles_index_;
    Sprite sprite_;
    Sprite plasma_sprite_;
    double scale_;
    double x_vel_;
    double y_vel_;
    int jump_time_;
    bool jumping_;
    bool left_collide_ = false;

    void init_rectangles(){

        for (int i = 0; i < 6; i++){
            rectanglesRight_.push_back(IntRect(131 + i*25, 50, 12, 25));
        }

        for (int i = 0; i < 6; i++){
            rectanglesLeft_.push_back(IntRect(131 + i*25, 25, 12, 25));
        }

        for (int i = 0; i < 5; i++){
            rectanglesIdle_.push_back(IntRect(152 + i*25, 0, 21, 25));
        }

        //middle
        rectangles_plasma_booster_.push_back(IntRect(483, 75, 9, 7));
        //left
        rectangles_plasma_booster_.push_back(IntRect(434, 24, 8, 8));
        //right
        rectangles_plasma_booster_.push_back(IntRect(483, 24, 8, 8));
    }
};



#endif // _PLAYER_CLASS_HPP
