#ifndef _PLAYER_CLASS_HPP
#define _PLAYER_CLASS_HPP

#include "BigPlatform.hpp"

//TODO this shoud coralate to fps somehow
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
        on_ground_ = true;

        init_rectangles();

    }

    //gain velocity if a button is pressed
    void update(bool player_up,bool player_down,bool player_right,bool player_left, std::vector<BigPlatform>& platforms){
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
        time = bigTime.getElapsedTime().asMilliseconds();
        if(jumping_ && jump_time_ + delta_time > time){
            y_vel_ = -VEL;
        }
        else if(jumping_ && !on_ground_){
            y_vel_ = VEL;
        }else if(jumping_  && on_ground_){
            jumping_ = false;
            rectangles_index_jump_ = 3;
        }
        sprite_.move(Vector2f(0, y_vel_));
        collision(0, y_vel_, platforms);


        if(!left_collide_)
            sprite_.move(Vector2f(x_vel_, 0));
        collision(x_vel_, 0, platforms);



    }

    //check if you are intersecting with a platform
    void collision(float delta_x, float delta_y, std::vector<BigPlatform>& platforms){
        if(delta_x < 0 || delta_y != 0){
            left_collide_ = false;
        }
        /*for(PlatformClass const& plat : platforms){
            if(plat.sprite_.getGlobalBounds().intersects(sprite_.getGlobalBounds())){*/

        for(const BigPlatform& bp : platforms){
            if(sprite_.getPosition().x + sprite_.getGlobalBounds().width > bp.platform_left_ &&
               sprite_.getPosition().x < bp.platform_right_ &&
               sprite_.getPosition().y + sprite_.getGlobalBounds().height > bp.platform_top_ &&
               sprite_.getPosition().y < bp.platform_bot_
               ){
                if(delta_y > 0){
                    on_ground_ = true;
                    sprite_.setPosition(Vector2f(sprite_.getPosition().x, bp.platform_top_ - sprite_.getGlobalBounds().height));
                }
                if(delta_y < 0){
                    sprite_.setPosition(Vector2f(sprite_.getPosition().x, bp.platform_bot_));
                }
                if(delta_x > 0){
                    sprite_.setPosition(Vector2f(bp.platform_left_ - sprite_.getGlobalBounds().width - 36, sprite_.getPosition().y));
                    left_collide_ = true;
                }
                if(delta_x < 0){
                    sprite_.setPosition(Vector2f(bp.platform_right_ + 5, sprite_.getPosition().y));
                }

            }

            }//platforms-for
    }

    void Animation(){

        //delt_time - duration of a frame
        int delta_time = 200;

        Clock game_clock_idle;
        int time_idle = 0;
        //helps us determin if our frame should be changed - it marks the time when a frame is first used
        int current_frame_time_idle = 0;

        Clock game_clock;
        int time = 0;
        int current_frame_time = 0;

        Clock jump_anime_clock;
        int jump_animation_time = 0;
        int current_jump_animation_time = 0;

        while(true){

            index_update(time_idle, current_frame_time_idle, delta_time, game_clock_idle, 4, rectangles_index_idle_, 0);
            index_update(time, current_frame_time, delta_time, game_clock, 5, rectangles_index_, 0);

            if(jumping_){
                index_update(jump_animation_time, current_jump_animation_time, 100, jump_anime_clock, 7, rectangles_index_jump_, 3);
            }

        }//while

    }//Animation

    std::vector<IntRect> rectanglesIdle_;
    std::vector<IntRect> rectanglesRight_;
    std::vector<IntRect> rectanglesLeft_;
    std::vector<IntRect> rectangles_plasma_booster_;
    bool on_ground_;
    int rectangles_index_idle_;
    int rectangles_index_;
    int rectangles_index_jump_;
    Sprite sprite_;
    Sprite plasma_sprite_;
    double scale_;
    double x_vel_;
    double y_vel_;
    int jump_time_;
    bool jumping_;
    bool left_collide_ = false;
private:
    void index_update(int time, int &tmp_time, int delta_time, Clock &clock, int iters, int &index, int start_index){
        time = clock.getElapsedTime().asMilliseconds();

        if(tmp_time + delta_time < time){
            tmp_time = time;
            if(index == iters){
                index = start_index;
                tmp_time = 0;
                index--;
                clock.restart();
            }
            index++;
        }
    }
    void init_rectangles(){

        rectangles_index_idle_ = 0;
        rectangles_index_ = 0;
        rectangles_index_jump_ = 3;

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
        rectangles_plasma_booster_.push_back(IntRect(483, 75, 9, 2));
        //left
        rectangles_plasma_booster_.push_back(IntRect(434, 24, 8, 3));
        //right
        rectangles_plasma_booster_.push_back(IntRect(483, 24, 8, 3));

        for(int i = 0; i < 7; i++)
            rectangles_plasma_booster_.push_back(IntRect(503 + i, 51, 1, 1 + i));
    }
};



#endif // _PLAYER_CLASS_HPP
