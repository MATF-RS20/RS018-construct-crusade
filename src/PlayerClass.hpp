#ifndef _PLAYER_CLASS_HPP
#define _PLAYER_CLASS_HPP

#include "BigPlatform.hpp"
#define VEL 400

using namespace sf;

extern bool shooting;

class PlayerClass : public GameObject{
public:

    PlayerClass(Sprite laser_sprite, Sprite plasma_sprite, Sprite sprite, double x_pos, double y_pos)
     : GameObject(x_pos, y_pos), sprite_(sprite), plasma_sprite_(plasma_sprite), laser_sprite_(laser_sprite){

        sprite_.setPosition(GameObject::x_pos_, GameObject::y_pos_);

        RIP_construct_ = false;
        shooting_ = false;

        construct_hp_ = 100.0;
        construct_mp_ = 100.0;
        laser_ = false;
        facing_left_ = false;
        scale_ = 4;
        sprite_.setScale(scale_, scale_);
        plasma_sprite.setScale(scale_, scale_);
        laser_sprite.setScale(scale_, scale_);
        on_ground_ = true;
        player_gold = 0;


        //these help us keep track of platforms that are closest to our construct
        platform_index_ = 37;
        platform_index_offset_ = 8;
        num_of_platforms_ = 0;

        x_vel_ = 0;
        y_vel_ = 0;

        init_rectangles();
     }

    //gain velocity if a button is pressed
    void update(int construct_move, std::vector<BigPlatform>& platforms, float uniform_time){
        int delta_time = 700;

        if(construct_move & 4 && on_ground_){
               on_ground_ = false;
               big_time_.restart();
        }

        y_vel_ = VEL*uniform_time;
        //this is here because when you move a window everything is paused on screen(but the clocks are working)
        //so the uniform_time because huge - and we get catapulted down - this is my fix
        if(y_vel_ > 3){
            y_vel_ = 1;
        }
        if(!(construct_move & 1 || construct_move & 2)){
            x_vel_ = 0;
        }
        if(construct_hp_ > 0 && construct_move & 1){
            x_vel_ = -VEL*uniform_time;
            facing_left_ = true;
        }
        if(construct_hp_ > 0 && construct_move & 2){
            x_vel_ = VEL*uniform_time;
            facing_left_ = false;
        }
        //std::cout << big_time_.getElapsedTime().asMilliseconds() << std::endl;
        if(!on_ground_ && construct_hp_ > 0 && big_time_.getElapsedTime().asMilliseconds() < delta_time){
            y_vel_ = -VEL*uniform_time;
        }
        else if(on_ground_){
            rectangles_index_jump_ = 3;
        }
        if(shooting_){
            x_vel_ = 0;
            on_ground_ = true;
        }

        //move the sprite
        if(!left_collide_)
            sprite_.move(Vector2f(x_vel_, 0));
        collision(x_vel_, 0, platforms);

        sprite_.move(Vector2f(0, y_vel_));
        collision(0, y_vel_, platforms);

        //std::cout << sprite_.getPosition().y << std::endl;

    }

    //check if you are intersecting with a platform
    void collision(float delta_x, float delta_y, std::vector<BigPlatform>& platforms){

        int ind = 0;
        int index = 0;
        if(delta_x < 0 || delta_y != 0){
            left_collide_ = false;
        }
        //platform index has the value of the current platform we are standing on in the grand scheme of things
        //platform index offset makes a range of platforms that are closest to our current platform
        //we check for collision within this range
        for(int i = platform_index_ - platform_index_offset_; i <= platform_index_ + platform_index_offset_; i++){
            if(sprite_.getPosition().x + sprite_.getGlobalBounds().width > platforms[i].platform_left_ &&
               sprite_.getPosition().x < platforms[i].platform_right_ &&
               sprite_.getPosition().y + sprite_.getGlobalBounds().height > platforms[i].platform_top_ &&
               sprite_.getPosition().y < platforms[i].platform_bot_
               ){
                if(delta_y > 0){
                    //we have collided with a platform - ind marks that - index tells us witch platform was it
                    ind = 1;
                    index = i;
                    sprite_.setPosition(Vector2f(sprite_.getPosition().x, platforms[i].platform_top_ - sprite_.getGlobalBounds().height));
                }
                if(delta_y < 0){
                    sprite_.setPosition(Vector2f(sprite_.getPosition().x, platforms[i].platform_bot_));
                }
                if(delta_x > 0){
                    sprite_.setPosition(Vector2f(platforms[i].platform_left_ - sprite_.getGlobalBounds().width - 36, sprite_.getPosition().y));
                    left_collide_ = true;
                }
                if(delta_x < 0){
                    sprite_.setPosition(Vector2f(platforms[i].platform_right_ + 5, sprite_.getPosition().y));
                }

            }

            }//platforms-for

            if(ind == 1){
                //here we make sure that our index wont lead us out of bounds (of platforms vector)
                if(index < platform_index_offset_)
                    index = platform_index_offset_;
                if(index > num_of_platforms_ - platform_index_offset_)
                    index = num_of_platforms_ - platform_index_offset_;
                platform_index_ = index;
                //there was a collision with a topside of a platform
                on_ground_ = true;
            }else
                on_ground_ = false;
    }
    //this is a thread called function - im abusing threads at this point
    void mana_recovery(){

        Clock mana_clock;
        int mana_time = 0;
        int mana_tmp_time = 0;
        int mana_delta_time = 500;

        while(true){
            mana_time = mana_clock.getElapsedTime().asMilliseconds();

            if(mana_tmp_time + mana_delta_time < mana_time){
                mana_tmp_time = mana_time;
                construct_mp_ += 5;
                if(construct_mp_ >= 100){
                    construct_mp_ = 100;
                    break;
                }
            }
        }

    }

    void Animation(){

        //delt_time - duration of a frame
        int delta_time = 200;

        Clock game_clock_idle;
        Clock game_clock;
        Clock jump_anime_clock;
        Clock laser_clock;
        Clock death_clock;
        Clock shooting_clock;


        while(true){

            index_update(delta_time, game_clock_idle, 5, rectangles_index_idle_, 0);
            index_update(delta_time, game_clock, 6, rectangles_index_, 0);
            index_update(100, shooting_clock, 4, rectangles_index_shooting_, 0);

            if(construct_hp_ <= 0){
                index_update(delta_time, death_clock, 14, rectangles_index_death_, 0);
            }

            if(!on_ground_){
                index_update(75, jump_anime_clock, 9, rectangles_index_jump_, 3);
            }
            if(laser_){
                index_update(105, laser_clock, 8, rectangles_index_laser_, 0);
                if(rectangles_index_laser_ == 7){
                    laser_ = false;
                }
            }

        }//while

    }//Animation

    std::vector<IntRect> rectanglesIdle_;
    std::vector<IntRect> rectanglesRight_;
    std::vector<IntRect> rectanglesLeft_;
    std::vector<IntRect> rectangles_plasma_booster_;
    std::vector<IntRect> rectangles_laser_;
    std::vector<IntRect> rectangles_laser_trails_;
    std::vector<IntRect> rectangles_death_;
    std::vector<IntRect> rectangles_shooting_;
    bool on_ground_;
    int rectangles_index_idle_;
    int rectangles_index_;
    int rectangles_index_jump_;
    int rectangles_index_laser_;
    int rectangles_index_laser_trails_;
    int rectangles_index_death_;
    int rectangles_index_shooting_;
    Sprite sprite_;
    Sprite plasma_sprite_;
    Sprite laser_sprite_;
    double scale_;
    double x_vel_;
    double y_vel_;
    bool laser_;
    bool left_collide_ = false;
    bool facing_left_;
    bool RIP_construct_;
    bool shooting_;
    bool first_hit_gold;

    double construct_hp_;
    double construct_mp_;
    int platform_index_;
    int num_of_platforms_;
    int platform_index_offset_;
    Clock big_time_;
    int player_gold;


private:
    void index_update(int delta_time, Clock &clock, int iters, int &index, int start_index){

        if(clock.getElapsedTime().asMilliseconds() > delta_time){
            index++;
            if(index == iters)
                index = start_index;
            clock.restart();
        }
    }
    void init_rectangles(){

        rectangles_index_idle_ = 0;
        rectangles_index_ = 0;
        rectangles_index_jump_ = 3;
        rectangles_index_laser_ = 0;
        rectangles_index_laser_trails_ = 0;
        rectangles_index_death_ = 0;
        rectangles_index_shooting_ = 0;

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

        //plasma trail blue
        for(int i = 0; i < 9; i++)
            rectangles_plasma_booster_.push_back(IntRect(500 + i, 50, 1, 1 + i));

        //plasma trail white
        for(int i = 0; i < 9; i++)
            rectangles_plasma_booster_.push_back(IntRect(509 + i, 50, 1, 1 + i));

        //laser right
        //laser ball index 0
        rectangles_laser_.push_back(IntRect(569, 0, 8, 8));
        //laser beam small index 1
        rectangles_laser_.push_back(IntRect(549, 17, 251, 6));
        //laser beam big index 2
        rectangles_laser_.push_back(IntRect(549, 9, 251, 8));
        //laser beam big color change index 3
        rectangles_laser_.push_back(IntRect(549, 34, 251, 8));
        //darker finishing trace for the laser index 4
        rectangles_laser_.push_back(IntRect(549, 42, 251, 6));
        //energy ball after trace index 5
        rectangles_laser_.push_back(IntRect(549, 0, 8, 8));
        //energy ball after trace scatter index 6
        rectangles_laser_.push_back(IntRect(559, 0, 9, 9));
        //robot sprite while lasering index 7
        rectangles_laser_.push_back(IntRect(533, 0, 15, 25));
        //robot sprite while lasering #2 index 8
        rectangles_laser_.push_back(IntRect(533, 25, 15, 25));

        //laser trails white
        for(int i = 0; i < 9; i++)
            rectangles_laser_trails_.push_back(IntRect(550 + i, 25, 1, 9 - i));
        //blue
        for(int i = 0; i < 9; i++)
            rectangles_laser_trails_.push_back(IntRect(559 + i, 25, 1, 9 - i));

        //laser left
        //laser ball index 9
        rectangles_laser_.push_back(IntRect(525, 108, 251, 8));
        //laser beam small index 10
        rectangles_laser_.push_back(IntRect(525, 67, 251, 6));
        //laser beam big index 11
        rectangles_laser_.push_back(IntRect(525, 59, 251, 8));
        //laser beam big color change index 12
        rectangles_laser_.push_back(IntRect(525, 84, 251, 8));
        //darker finishing trace for the laser index 13
        rectangles_laser_.push_back(IntRect(525, 92, 251, 6));
        //energy ball after trace index 14
        rectangles_laser_.push_back(IntRect(525, 100, 251, 8));
        //energy ball after trace scatter index 15
        rectangles_laser_.push_back(IntRect(525, 125, 251, 9));
        //robot sprite while lasering index 16
        rectangles_laser_.push_back(IntRect(778, 50, 14, 25));
        //robot sprite while lasering #2 index 17
        rectangles_laser_.push_back(IntRect(778, 75, 14, 25));

        //right
        for(int i = 0; i < 7; i++)
            rectangles_death_.push_back(IntRect(0 + 25*i, 75, 25, 25));

        rectangles_death_.push_back(IntRect(175, 75, 29, 25));

        rectangles_death_.push_back(IntRect(204, 75, 35, 25));

        rectangles_death_.push_back(IntRect(239, 75, 35, 25));

        rectangles_death_.push_back(IntRect(274, 75, 35, 25));

        rectangles_death_.push_back(IntRect(274, 75, 35, 25));

        rectangles_death_.push_back(IntRect(274, 75, 35, 25));

        //left
        for(int i = 0; i < 7; i++)
            rectangles_death_.push_back(IntRect(300 - 25*i, 100, 25, 25));

        rectangles_death_.push_back(IntRect(121, 100, 29, 25));

        rectangles_death_.push_back(IntRect(86, 100, 35, 25));

        rectangles_death_.push_back(IntRect(51, 100, 35, 25));

        rectangles_death_.push_back(IntRect(16, 100, 35, 25));

        rectangles_death_.push_back(IntRect(16, 100, 35, 25));

        rectangles_death_.push_back(IntRect(16, 100, 35, 25));

        for(int i = 0; i < 4; i++)
            rectangles_shooting_.push_back(IntRect(4 + 25*i, 125, 20, 25));

        for(int i = 0; i < 4; i++)
            rectangles_shooting_.push_back(IntRect(80 - 25*i, 175, 20, 25));

    }
};
#endif // _PLAYER_CLASS_HPP
