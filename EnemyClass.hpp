#ifndef _ENEMY_CLASS_HPP
#define _ENEMY_CLASS_HPP

using namespace sf;

//Enemy class - this is used to animate everything - and storage for our rectangle frames
class EnemyClass{
public:

    EnemyClass(){

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

        //dino
        Clock dino_slam_clock;
        Clock dino_walk_clock;

        //cleo
        Clock cleo_idle_clock;
        Clock cleo_walk_clock;
        Clock cleo_attack_clock;
        Clock cleo_death_clock;

        //witch
        Clock witch_idle_clock;
        Clock witch_walk_clock;
        Clock witch_attack_clock;
        Clock witch_death_clock;
        Clock witch_broom_clock;

        while(true){

            //imp
            index_update(delta_time, imp_idle_clock, 7, rectangles_index_);

            index_update(delta_time, imp_walk_clock, 8, rectangles_index_walk_);

            index_update(delta_time, attack_clock, 6, rectangles_index_attack_);

            index_update(delta_time, death_clock, 6, rectangles_index_death_);

            index_update(delta_time + 200, fireball_clock, 6, rectangles_index_heart_);

            //cleopatra
            index_update(delta_time, cleo_idle_clock, 4, rectangles_index_cleo_idle_);

            index_update(delta_time, cleo_walk_clock, 4, rectangles_index_cleo_walk_);

            index_update(delta_time + 200, cleo_attack_clock, 2, rectangles_index_cleo_attack_);

            index_update(delta_time, cleo_death_clock, 6, rectangles_index_cleo_death_);


            //dino
            index_update(140, dino_slam_clock, 4, rectangles_index_dino_slam_);
            index_update(delta_time, dino_walk_clock, 6, rectangles_index_dino_walk_);

            //witch
            index_update(delta_time, witch_idle_clock, 4, rectangles_index_witch_idle_);
            index_update(delta_time, witch_walk_clock, 8, rectangles_index_witch_walk_);
            index_update(delta_time, witch_attack_clock, 8, rectangles_index_witch_attack_);
            index_update(delta_time, witch_death_clock, 10, rectangles_index_witch_death_);
            index_update(delta_time, witch_broom_clock, 4, rectangles_index_witch_broom_);

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

    int rectangles_index_;
    int rectangles_index_walk_;
    int rectangles_index_attack_;
    int rectangles_index_death_;
    int rectangles_index_fireball_;

    //dino parameters
    std::vector<IntRect> rectangles_dino_slam_;
    std::vector<IntRect> rectangles_dino_walk_left_;
    std::vector<IntRect> rectangles_dino_walk_right_;


    int rectangles_index_dino_slam_;
    int rectangles_index_dino_walk_;


    //cleo parameters
    std::vector<IntRect> rectangles_cleo_idle_;
    std::vector<IntRect> rectangles_cleo_walk_right_;
    std::vector<IntRect> rectangles_cleo_walk_left_;
    std::vector<IntRect> rectangles_cleo_attack_;
    std::vector<IntRect> rectangles_cleo_death_;
    int rectangles_index_cleo_idle_;
    int rectangles_index_cleo_walk_;
    int rectangles_index_cleo_attack_;
    int rectangles_index_heart_;
    int rectangles_index_cleo_death_;

    //witch parameters
    std::vector<IntRect> rectangles_witch_idle_;
    std::vector<IntRect> rectangles_witch_walk_left_;
    std::vector<IntRect> rectangles_witch_walk_right_;
    std::vector<IntRect> rectangles_witch_attack_;
    std::vector<IntRect> rectangles_witch_death_;
    std::vector<IntRect> rectangles_witch_broom_;

    int rectangles_index_witch_idle_;
    int rectangles_index_witch_walk_;
    int rectangles_index_witch_attack_;
    int rectangles_index_witch_death_;
    int rectangles_index_witch_broom_;

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
        rectangles_index_cleo_idle_ = 0;
        rectangles_index_cleo_walk_ = 0;
        rectangles_index_cleo_attack_ = 0;
        rectangles_index_cleo_death_ = 0;

        //imp indices
        rectangles_index_ = 0;
        rectangles_index_walk_ = 0;
        rectangles_index_attack_ = 0;
        rectangles_index_death_ = 0;
        rectangles_index_fireball_ = 0;

        //dino indices
        rectangles_index_dino_slam_ = 0;
        rectangles_index_dino_walk_ = 0;

        //witch indices
        rectangles_index_witch_idle_ = 0;
        rectangles_index_witch_walk_ = 0;
        rectangles_index_witch_attack_ = 0;
        rectangles_index_witch_death_ = 0;
        rectangles_index_witch_broom_ = 0;

        for (int i = 0; i < 4; i++){
            rectangles_dino_slam_.push_back(IntRect(0 , 25*i, 33, 25));
        }

        for (int i = 0; i < 6; i++){
            rectangles_dino_walk_left_.push_back(IntRect(0 , 25*i, 33, 25));
        }

        for (int i = 0; i < 6; i++){
            rectangles_dino_walk_right_.push_back(IntRect(50 , 25*i, 33, 25));
        }

        //Cleopatra rectangles
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

        //attack
        for (int i = 0; i < 4; i++){
            rectangles_cleo_attack_.push_back(IntRect(i*25, 25, 25, 25));
        }

        rectangles_cleo_attack_.push_back(IntRect(106, 10, 38, 38));
        rectangles_cleo_attack_.push_back(IntRect(156, 10, 38, 38));


        //death
        for (int i = 0; i < 6; i++){
            rectangles_cleo_death_.push_back(IntRect(i*25, 150, 25, 25));
        }
        for (int i = 5; i >= 1; i--){
            rectangles_cleo_death_.push_back(IntRect(i*25, 175, 25, 25));
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

        //witch rectangles
        //idle
        for (int i = 0; i < 4; i++){
            rectangles_witch_idle_.push_back(IntRect(4 + i*32, 4, 22, 27));
        }

        //walk
        //right
        for (int i = 0; i < 8; i++){
            rectangles_witch_walk_right_.push_back(IntRect(4 + i*32, 37, 22, 27));
        }

        //left
        for (int i = 0; i < 8; i++){
            rectangles_witch_walk_left_.push_back(IntRect(291 - i*32, 229, 25, 27));
        }

        //attack
        //right
        for (int i = 0; i < 8; i++){
            rectangles_witch_attack_.push_back(IntRect(1 + i*32, 68, 28, 27));
        }

        //left
        for (int i = 0; i < 8; i++){
            rectangles_witch_attack_.push_back(IntRect(291 - i*32, 261, 28, 27));
        }

        //death
        //right
        for (int i = 0; i < 10; i++){
            rectangles_witch_death_.push_back(IntRect(4 + i*32, 133, 25, 27));
        }

        //left
        for (int i = 0; i < 10; i++){
            rectangles_witch_death_.push_back(IntRect(293 - i*32, 325, 25, 27));
        }

        //broom
        //right
        for (int i = 0; i < 4; i++){
            rectangles_witch_broom_.push_back(IntRect(1 + i*32, 163, 28, 27));
        }

        //left
        for (int i = 0; i < 4; i++){
            rectangles_witch_broom_.push_back(IntRect(291 - i*32, 354, 28, 27));
        }


    }
};
#endif // _ENEMY_CLASS_HPP
