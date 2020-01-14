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

        //minotaur
        Clock minotaur_idle_clock;
        Clock minotaur_taunt_clock;
        Clock minotaur_walk_clock;
        Clock minotaur_attack_1_clock;
        Clock minotaur_attack_2_clock;
        Clock minotaur_attack_3_clock;
        Clock minotaur_attack_4_clock;
        Clock minotaur_death_clock;

        //batsy
        Clock batsy_fly_clock;
        Clock batsy_attack_clock;
        Clock batsy_death_clock;


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
            index_update(delta_time, dino_slam_clock, 4, rectangles_index_dino_slam_);
            index_update(delta_time, dino_walk_clock, 6, rectangles_index_dino_walk_);

            //witch
            index_update(delta_time, witch_idle_clock, 4, rectangles_index_witch_idle_);
            index_update(delta_time, witch_walk_clock, 8, rectangles_index_witch_walk_);
            index_update(delta_time, witch_attack_clock, 8, rectangles_index_witch_attack_);
            index_update(delta_time, witch_death_clock, 10, rectangles_index_witch_death_);
            index_update(delta_time, witch_broom_clock, 4, rectangles_index_witch_broom_);

            //minotaur
            index_update(delta_time, minotaur_idle_clock, 5, rectangles_index_minotaur_idle_);
            index_update(delta_time, minotaur_walk_clock, 8, rectangles_index_minotaur_walk_);
            index_update(delta_time, minotaur_taunt_clock, 5, rectangles_index_minotaur_taunt_);
            index_update(delta_time, minotaur_attack_1_clock, 9, rectangles_index_minotaur_attack_1_);
            index_update(delta_time, minotaur_attack_2_clock, 5, rectangles_index_minotaur_attack_2_);
            index_update(delta_time, minotaur_attack_3_clock, 6, rectangles_index_minotaur_attack_3_);
            index_update(75, minotaur_attack_4_clock, 6, rectangles_index_minotaur_attack_4_);
            index_update(delta_time, minotaur_death_clock, 6, rectangles_index_minotaur_death_);

            //batsy
            index_update(delta_time, batsy_fly_clock, 5, rectangles_index_batsy_fly_);
            index_update(25, batsy_attack_clock, 3, rectangles_index_batsy_attack_);
            index_update(delta_time, batsy_death_clock, 6, rectangles_index_batsy_death_);

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
    std::vector<IntRect> rectangles_dino_slam_left;
    std::vector<IntRect> rectangles_dino_slam_right;
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

    //minotaur parameters
    std::vector<IntRect> rectangles_minotaur_idle_;
    std::vector<IntRect> rectangles_minotaur_walk_left_;
    std::vector<IntRect> rectangles_minotaur_walk_right_;
    std::vector<IntRect> rectangles_minotaur_taunt_;
    std::vector<IntRect> rectangles_minotaur_attack_1_;
    std::vector<IntRect> rectangles_minotaur_attack_2_;
    std::vector<IntRect> rectangles_minotaur_attack_3_;
    std::vector<IntRect> rectangles_minotaur_attack_4_;
    std::vector<IntRect> rectangles_minotaur_death_;


    int rectangles_index_minotaur_idle_;
    int rectangles_index_minotaur_walk_;
    int rectangles_index_minotaur_taunt_;
    int rectangles_index_minotaur_attack_1_;
    int rectangles_index_minotaur_attack_2_;
    int rectangles_index_minotaur_attack_3_;
    int rectangles_index_minotaur_attack_4_;
    int rectangles_index_minotaur_death_;

    //batsy parameters
    std::vector<IntRect> rectangles_batsy_fly_;
    std::vector<IntRect> rectangles_sonic_attack_;
    std::vector<IntRect> rectangles_batsy_death_;

    int rectangles_index_batsy_fly_;
    int rectangles_index_batsy_attack_;
    int rectangles_index_batsy_death_;


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

        //minotaur indices
        rectangles_index_minotaur_idle_ = 0;
        rectangles_index_minotaur_walk_ = 0;
        rectangles_index_minotaur_taunt_ = 0;
        rectangles_index_minotaur_attack_1_ = 0;
        rectangles_index_minotaur_attack_2_ = 0;
        rectangles_index_minotaur_attack_3_ = 0;
        rectangles_index_minotaur_attack_4_ = 0;
        rectangles_index_minotaur_death_ = 0;

        //batsy indices
        rectangles_index_batsy_fly_ = 0;
        rectangles_index_batsy_attack_ = 0;
        rectangles_index_batsy_death_ = 0;

        for (int i = 0; i < 4; i++){
            rectangles_dino_slam_left.push_back(IntRect(150 , 25*i, 33, 25));
        }

        for (int i = 0; i < 4; i++){
            rectangles_dino_slam_right.push_back(IntRect(200 , 25*i, 33, 25));
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
        for (int i = 5; i >= 0; i--){
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

        //MINOTAUR

        //Minotaur idle
        for (int i = 0; i < 5; i++){
            rectangles_minotaur_idle_.push_back(IntRect(27 + i*96, 5, 53, 59));
        }

        //Minotaur walk right
        for (int i = 0; i < 8; i++){
            rectangles_minotaur_walk_right_.push_back(IntRect(25 + i*96, 101, 56, 59));
        }

        //Minotaur walk left
        for (int i = 0; i < 8; i++){
            rectangles_minotaur_walk_left_.push_back(IntRect(14 + i*96, 1061, 60, 59)); //1076
        }

        //Minotaur taunt right
        for (int i = 0; i < 5; i++){
            rectangles_minotaur_taunt_.push_back(IntRect(28 + i*96, 197, 56, 59));
        }

        //Minotaur taunt left
        for (int i = 0; i < 5; i++){
            rectangles_minotaur_taunt_.push_back(IntRect(16 + i*96, 1157, 60, 59));
        }

        //Minotaur attack 1 right
        for (int i = 0; i < 9; i++){
            rectangles_minotaur_attack_1_.push_back(IntRect(5 + i*96, 293, 83, 65));
        }

        //Minotaur attack 1 left
        for (int i = 0; i < 9; i++){
            rectangles_minotaur_attack_1_.push_back(IntRect(8 + i*96, 1253, 83, 65));
        }

        //Minotaur attack 2 right
        for (int i = 0; i < 5; i++){
            rectangles_minotaur_attack_2_.push_back(IntRect(28 + i*96, 389, 65, 61));
        }

        //Minotaur attack 2 left
        for (int i = 0; i < 5; i++){
            rectangles_minotaur_attack_2_.push_back(IntRect(6 + i*96, 1349, 65, 67));
        }

        //Minotaur attack 3 right
        for (int i = 0; i < 6; i++){
            rectangles_minotaur_attack_3_.push_back(IntRect(23 + i*96, 485, 38, 66));
        }

        //Minotaur attack 3 left
        for (int i = 0; i < 6; i++){
            rectangles_minotaur_attack_3_.push_back(IntRect(34 + i*96, 1445, 38, 62));
        }

         //Minotaur attack 4 right
        for (int i = 3; i < 9; i++){
            rectangles_minotaur_attack_4_.push_back(IntRect(2 + i*96, 581, 94, 63));
        }

        //Minotaur attack 4 left
        for (int i = 3; i < 9; i++){
            rectangles_minotaur_attack_4_.push_back(IntRect(6 + i*96, 1541, 90, 63));
        }

        //Minotaur death right
        for (int i = 0; i < 6; i++){
            rectangles_minotaur_death_.push_back(IntRect(28 + i*96, 869, 60, 69));
        }

        //Minotaur death left
        for (int i = 0; i < 6; i++){
            rectangles_minotaur_death_.push_back(IntRect(8 + i*96, 1829, 60, 69));
        }



        //batsy

        //right
        for(int i = 0; i < 5; i++)
            rectangles_batsy_fly_.push_back(IntRect(1 + i*16, 27, 15, 11));

        //left
        for(int i = 0; i < 5; i++)
            rectangles_batsy_fly_.push_back(IntRect(64 - i*16, 244, 16, 11));

        //right
        for(int i = 0; i < 5; i++)
            rectangles_batsy_death_.push_back(IntRect(0 + i*16, 53, 15, 19));
        rectangles_batsy_death_.push_back(IntRect(0 + 4*16, 53, 15, 19));
        //left
        for(int i = 0; i < 5; i++)
            rectangles_batsy_death_.push_back(IntRect(64 - i*16, 269, 15, 19));
        rectangles_batsy_death_.push_back(IntRect(64 - 4*16, 53, 15, 19));

        //sonic attack
        //right
        rectangles_sonic_attack_.push_back(IntRect(45, 91, 35, 43));
        rectangles_sonic_attack_.push_back(IntRect(45, 135, 35, 43));
        rectangles_sonic_attack_.push_back(IntRect(45, 177, 35, 43));

        //left
        rectangles_sonic_attack_.push_back(IntRect(0, 91, 35, 43));
        rectangles_sonic_attack_.push_back(IntRect(0, 135, 35, 43));
        rectangles_sonic_attack_.push_back(IntRect(0, 177, 35, 43));


    }
};
#endif // _ENEMY_CLASS_HPP
