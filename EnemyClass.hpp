#ifndef _ENEMY_CLASS_HPP
#define _ENEMY_CLASS_HPP

#include "GameObject.hpp"

using namespace sf;

//Enemy class
class EnemyClass : public GameObject{
public:

    EnemyClass(Sprite sprite, Sprite fireball_sprite, double x_pos, double y_pos) : GameObject(x_pos, y_pos), sprite_(sprite), fireball_sprite_(fireball_sprite){
        sprite_.setPosition(GameObject::x_pos_, GameObject::y_pos_);
        scale_ = 4;
        sprite_.setScale(scale_, scale_);

        init_rectangles();
    }

    void IdleAnimation(){

        //delt_time - duration of a frame
        int delta_time = 150;

        //Idle parameters
        Clock imp_clock;
        int time = 0;
        //helps us determin if our frame should be changed - it marks the time when a frame is first used
        int current_frame_time = 0;

        //walk parameters
        Clock imp_walk_clock;
        int time_walk = 0;
        int current_walk_frame_time = 0;

        //attack parameters
        Clock attack_clock;
        int attack_time = 0;
        int attack_tmp_time = 0;

        //take damage parameters
        Clock damage_clock;
        int damage_time = 0;
        int damage_tmp_time = 0;

        //death parameters
        Clock death_clock;
        int death_time = 0;
        int death_tmp_time = 0;

        /*//fireball parameters
        Clock fireball_clock;
        int fireball_time = 0;
        int fireball_tmp_time = 0;*/

        //phase change paramaters
        Clock phase_clock;
        //movement animations: 0 - idle, 1 - walk left, 2 - walk right, 4 - attack left, 5 - attack right,
        int move_phase = 0;
        int phase_time = 0;
        int phase_time_tmp = 0;
        int phase_delta = 3000;

        while(true){

            index_update(time, current_frame_time, delta_time, imp_clock, 6, rectangles_index_);

            index_update(time_walk, current_walk_frame_time, delta_time, imp_walk_clock, 7, rectangles_index_walk_);

            index_update(attack_time, attack_tmp_time, delta_time, attack_clock, 5, rectangles_index_attack_);

            index_update(damage_time, damage_tmp_time, delta_time, damage_clock, 3, rectangles_index_damage_);

            index_update(death_time, death_tmp_time, delta_time, death_clock, 5, rectangles_index_death_);

            //index_update(fireball_time, fireball_tmp_time, delta_time, fireball_clock, 5, rectangles_index_fireball_);

            phase_time = phase_clock.getElapsedTime().asMilliseconds();

            if(phase_time > phase_time_tmp + phase_delta){
                phase_time_tmp = phase_time;
                move_phase++;
            }

            if(move_phase == 4){
                phase_time_tmp = 0;
                phase_clock.restart();
                move_phase = 0;
            }

            if(move_phase == 0 || move_phase == 2){
                sprite_.setTextureRect(rectangles_imp_idle_[rectangles_index_]);
                }
            else if(move_phase == 1){
                sprite_.setPosition(Vector2f(sprite_.getPosition().x-0.00009f, sprite_.getPosition().y));
                sprite_.setTextureRect(rectangles_imp_walk_left_[rectangles_index_walk_]);
            }else if(move_phase == 3){
                sprite_.setPosition(Vector2f(sprite_.getPosition().x+0.00009f, sprite_.getPosition().y));
                sprite_.setTextureRect(rectangles_imp_walk_right_[rectangles_index_walk_]);
            }

        }//while

    }//IdleAnimation

    Sprite sprite_;
    Sprite fireball_sprite_;
    std::vector<IntRect> rectangles_imp_idle_;
    std::vector<IntRect> rectangles_imp_walk_right_;
    std::vector<IntRect> rectangles_imp_walk_left_;
    std::vector<IntRect> rectangles_imp_attack_left_;
    std::vector<IntRect> rectangles_imp_attack_right_;
    std::vector<IntRect> rectangles_imp_take_damage_left_;
    std::vector<IntRect> rectangles_imp_take_damage_right_;
    std::vector<IntRect> rectangles_imp_death_left_;
    std::vector<IntRect> rectangles_imp_death_right_;
    //std::vector<IntRect> rectangles_imp_fireBall_left_;
    //std::vector<IntRect> rectangles_imp_fireBall_right_;
    int rectangles_index_;
    int rectangles_index_walk_;
    int rectangles_index_attack_;
    int rectangles_index_damage_;
    int rectangles_index_death_;
    //int rectangles_index_fireball_;
    double scale_;
    double x_vel_;
    double y_vel_;

private:
    void index_update(int time, int &tmp_time, int delta_time, Clock &clock, int iters, int &index){
        time = clock.getElapsedTime().asMilliseconds();

        if(tmp_time + delta_time < time){
            tmp_time = time;
            if(index == iters){
                index = 0;
                tmp_time = 0;
                index--;
                clock.restart();
            }
            index++;
        }
    }

    void init_rectangles(){

        rectangles_index_ = 0;
        rectangles_index_walk_ = 0;
        rectangles_index_attack_ = 0;
        rectangles_index_damage_ = 0;
        rectangles_index_death_ = 0;
        //rectangles_index_fireball_ = 0;

        for (int i = 0; i < 7; i++){
            rectangles_imp_idle_.push_back(IntRect(10 + i*32, 209, 15, 15));
        }

        for (int i = 0; i < 8; i++){
            rectangles_imp_walk_left_.push_back(IntRect(10 + i*32, 241, 15, 15));
        }

        for (int i = 0; i < 8; i++){
            rectangles_imp_walk_right_.push_back(IntRect(7 + i*32, 49, 15, 15));
        }
        for (int i = 0; i < 6; i++){
            rectangles_imp_attack_left_.push_back(IntRect(169 - i*32, 273, 17, 15));
        }

        for (int i = 0; i < 6; i++){
            rectangles_imp_attack_right_.push_back(IntRect(7 + i*32, 81, 17, 15));
        }

        for (int i = 0; i < 4; i++){
            rectangles_imp_take_damage_left_.push_back(IntRect(9 + i*32, 305, 15, 15));
        }
        for (int i = 0; i < 4; i++){
            rectangles_imp_take_damage_right_.push_back(IntRect(8 + i*32, 113, 15, 15));
        }

        for (int i = 0; i < 6; i++){
            rectangles_imp_death_left_.push_back(IntRect(7 + i*32, 145, 16, 15));
        }
        for (int i = 0; i < 6; i++){
            rectangles_imp_death_right_.push_back(IntRect(9 + i*32, 337, 16, 15));
        }
        //TODO fireball init

    }
};


#endif // _ENEMY_CLASS_HPP
