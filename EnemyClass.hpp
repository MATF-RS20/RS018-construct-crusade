#ifndef _ENEMY_CLASS_HPP
#define _ENEMY_CLASS_HPP

using namespace sf;

//Enemy class - this is used to animate everything - and storage for our rectangle frames
class EnemyClass{
public:

    EnemyClass(int value_that_has_no_value_you_are_here_because_i_desire_you_to_be){

        init_rectangles();
    }

    void Animation(){

        //duration of a frame
        int delta_time = 200;

        Clock imp_idle_clock;
        Clock imp_walk_clock;
        Clock attack_clock;
        Clock death_clock;
        Clock fireball_clock;
        Clock dino_slam_clock;

        //cleo
        Clock cleo_idle_clock;
        Clock cleo_walk_clock;

        while(true){
            index_update(delta_time, cleo_walk_clock, 4, rectangles_index_walk_cleo_);

            index_update(delta_time, imp_idle_clock, 7, rectangles_index_);

            index_update(delta_time, imp_walk_clock, 8, rectangles_index_walk_);

            index_update(delta_time, attack_clock, 6, rectangles_index_attack_);

            index_update(140, dino_slam_clock, 4, rectangles_index_dino_slam_);


            index_update(delta_time, death_clock, 6, rectangles_index_death_);

            index_update(delta_time + 200, fireball_clock, 6, rectangles_index_fireball_);

        }//while

    }//IdleAnimation

    std::vector<IntRect> rectangles_imp_idle_;
    std::vector<IntRect> rectangles_imp_walk_right_;
    std::vector<IntRect> rectangles_imp_walk_left_;
    std::vector<IntRect> rectangles_imp_attack_left_;
    std::vector<IntRect> rectangles_imp_attack_right_;
    std::vector<IntRect> rectangles_imp_death_;
    std::vector<IntRect> rectangles_imp_fireBall_left_;
    std::vector<IntRect> rectangles_imp_fireBall_right_;
    std::vector<IntRect> rectangles_dino_slam_;
    int rectangles_index_;
    int rectangles_index_walk_;
    int rectangles_index_attack_;
    int rectangles_index_death_;
    int rectangles_index_fireball_;
    int rectangles_index_dino_slam_;

    //cleo parameters
    std::vector<IntRect> rectangles_cleo_idle_;
    int rectangles_index_idle_cleo_;

    std::vector<IntRect> rectangles_cleo_walk_right_;
    std::vector<IntRect> rectangles_cleo_walk_left_;
    int rectangles_index_walk_cleo_;

//    std::vector<IntRect> rectangles_cleo_attack_left_;
//    std::vector<IntRect> rectangles_cleo_attack_right_;
//    int rectangles_index_attack_cleo_;

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
        //Cleopatra indices
        rectangles_index_idle_cleo_ = 0;
        rectangles_index_walk_cleo_ = 0;

        //imp indices
        rectangles_index_ = 0;
        rectangles_index_walk_ = 0;
        rectangles_index_attack_ = 0;
        rectangles_index_death_ = 0;
        rectangles_index_fireball_ = 0;

        rectangles_index_dino_slam_ = 0;

        for (int i = 0; i < 4; i++){
            rectangles_dino_slam_.push_back(IntRect(0 , 0+25*i, 33, 25));
        }


        //Cleopatra rectangles
        for (int i = 0; i < 4; i++){
            rectangles_cleo_walk_left_.push_back(IntRect(i*25, 75, 25, 25));
        }

        for (int i = 0; i < 3; i++){
            rectangles_cleo_idle_.push_back(IntRect(i*25, 0, 25, 25));
        }
        rectangles_cleo_idle_.push_back(IntRect(25, 0, 25, 25));

        for (int i = 0; i < 4; i++){
            rectangles_cleo_walk_left_.push_back(IntRect(i*25, 75, 25, 25));
        }

        for (int i = 0; i < 4; i++){
            rectangles_cleo_walk_right_.push_back(IntRect(i*25, 50, 25, 25));
        }

        //Imp rectangles
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
            rectangles_imp_attack_left_.push_back(IntRect(9 + i*32, 273, 17, 15));
        }

        for (int i = 0; i < 6; i++){
            rectangles_imp_attack_right_.push_back(IntRect(7 + i*32, 81, 17, 15));
        }

        for (int i = 0; i < 6; i++){
            rectangles_imp_death_.push_back(IntRect(7 + i*32, 145, 16, 15));
        }
        for (int i = 0; i < 6; i++){
            rectangles_imp_death_.push_back(IntRect(9 + i*32, 337, 16, 15));
        }
        //no pattern with fireballs :(
        rectangles_imp_fireBall_left_.push_back(IntRect(23, 377, 1, 1));
        rectangles_imp_fireBall_left_.push_back(IntRect(54, 376, 3, 4));
        rectangles_imp_fireBall_left_.push_back(IntRect(66, 376, 19, 3));
        rectangles_imp_fireBall_left_.push_back(IntRect(98, 376, 9, 3));
        rectangles_imp_fireBall_left_.push_back(IntRect(130, 376, 5, 3));
        rectangles_imp_fireBall_left_.push_back(IntRect(162, 372, 4, 8));
        rectangles_imp_fireBall_left_.push_back(IntRect(194, 375, 4, 8));

        rectangles_imp_fireBall_right_.push_back(IntRect(8, 185, 1, 1));
        rectangles_imp_fireBall_right_.push_back(IntRect(39, 184, 3, 4));
        rectangles_imp_fireBall_right_.push_back(IntRect(75, 184, 19, 3));
        rectangles_imp_fireBall_right_.push_back(IntRect(117, 184, 9, 3));
        rectangles_imp_fireBall_right_.push_back(IntRect(153, 184, 5, 3));
        rectangles_imp_fireBall_right_.push_back(IntRect(186, 181, 4, 8));
        rectangles_imp_fireBall_right_.push_back(IntRect(218, 183, 4, 8));

    }
};
#endif // _ENEMY_CLASS_HPP
