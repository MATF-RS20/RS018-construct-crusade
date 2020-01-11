#ifndef _ENEMY_HANDLER_HPP
#define _ENEMY_HANDLER_HPP

#include "WitchEnemyClass.hpp"
#include "ImpEnemyClass.hpp"
#include "DinoEnemyClass.hpp"

using namespace sf;

int scale_1 = 1;
int scale_2 = 1;
int scale_3 = 1;
int scale_4 = 1;
int scale_5 = 1;
int scale_6 = 1;
int scale_7 = 1;
int scale_8 = 1;

int offset_x = 0;

int offset_y_2 = 0;
int offset_y_3 = 0;
int offset_y_4 = 0;
int offset_y_5 = 0;
int offset_y_6 = 0;
int offset_y_7 = 0;
int offset_y_8 = 0;

void poison_drop(WitchEnemyClass &witch, PlayerClass &player, sf::RenderWindow &window, int scale, int offset_x, int offset_y, bool &first_hit){

        witch.poison_sprite_.setScale(scale, scale);
        witch.poison_sprite_.move(offset_x, -offset_y);
        window.draw(witch.poison_sprite_);

        if(first_hit && player.sprite_.getGlobalBounds().intersects(witch.poison_sprite_.getGlobalBounds())){
            player.construct_hp_ -= witch.poison_damage_;
            if(witch.enemy_hp_ <= (100 - witch.poison_damage_))
            witch.enemy_hp_ += witch.poison_damage_;
            first_hit = false;
        }

        witch.poison_sprite_.move(-offset_x, offset_y);
}

void patrolling(RealEnemyClass &deviant,
               std::vector<IntRect> &rectangles_deviant_idle_,
               std::vector<IntRect> &rectangles_deviant_walk_left_,
               std::vector<IntRect> &rectangles_deviant_walk_right_,
               int rectangles_index_deviant_idle_,
               int rectangles_index_deviant_walk_
               ){

    if(deviant.phase_clock_.getElapsedTime().asMilliseconds() > deviant.phase_delta_){
                deviant.phase_clock_.restart();
                deviant.move_phase_++;
    }

    if(deviant.move_phase_ == 4){
        deviant.move_phase_ = 0;
    }

    //marching left then right - phase 0 and 2 are idle - phase 1 walk left - phase 2 walk right
    if(deviant.move_phase_ == 0 || deviant.move_phase_ == 2){

        deviant.sprite_.setTextureRect(rectangles_deviant_idle_[rectangles_index_deviant_idle_]);

        }
    else if(deviant.move_phase_ == 1){

        deviant.facing_left_ = true;
        deviant.sprite_.setPosition(Vector2f(deviant.sprite_.getPosition().x-0.4f, deviant.sprite_.getPosition().y));
        deviant.sprite_.setTextureRect(rectangles_deviant_walk_left_[rectangles_index_deviant_walk_]);

        if(deviant.sprite_.getPosition().x < deviant.platform_left_)
            deviant.sprite_.setPosition(Vector2f(deviant.platform_left_, deviant.sprite_.getPosition().y));

    }else if(deviant.move_phase_ == 3){

        deviant.facing_left_ = false;
        deviant.sprite_.setPosition(Vector2f(deviant.sprite_.getPosition().x+0.4f, deviant.sprite_.getPosition().y));
        deviant.sprite_.setTextureRect(rectangles_deviant_walk_right_[rectangles_index_deviant_walk_]);

        if(deviant.sprite_.getPosition().x + deviant.sprite_.getGlobalBounds().width > deviant.platform_right_)
            deviant.sprite_.setPosition(Vector2f(deviant.platform_right_ - deviant.sprite_.getGlobalBounds().width, deviant.sprite_.getPosition().y));

    }
}
//WITCH
void handle_witch(WitchEnemyClass &witch, EnemyClass &enemy, PlayerClass &player, sf::RenderWindow &window, float witch_uniform_move){
    //detect if the construct is near
    if(witch.enemy_hp_ > 0 && player.sprite_.getPosition().x > witch.sprite_.getPosition().x - 400
                           && player.sprite_.getPosition().x < witch.sprite_.getPosition().x + 400){
        //if(enemy.rectangles_index_attack_ == 0)
        witch.facing_left_ = player.sprite_.getPosition().x < witch.sprite_.getPosition().x;
        witch.attacking_ = true;

    }else if(witch.brooming_ || witch.hexing_){
        witch.attacking_ = true;
        witch.facing_left_ = player.sprite_.getPosition().x < witch.sprite_.getPosition().x;
    }else
        witch.attacking_ = false;

    //if the ghost is clear - patrol
    if(!witch.attacking_ && witch.enemy_hp_ > 0)
        patrolling(witch, enemy.rectangles_witch_idle_, enemy.rectangles_witch_walk_left_, enemy.rectangles_witch_walk_right_,
                  enemy.rectangles_index_witch_idle_, enemy.rectangles_index_witch_walk_);

    if(witch.attacking_){
        if(!witch.brooming_ && !witch.hexing_){
        if(rand() % 2 == 1){
            witch.brooming_ = true;
            witch.first_hit_brooming_ = true;
            witch.brooming_phase_ = 0;

        }else{
            witch.hexing_ = true;
            witch.brooming_clock_.restart();
        }
    }
    if(witch.brooming_){

        if(witch.brooming_phase_ == 0 && witch.sprite_.getPosition().x < (witch.platform_left_ - abs(witch.platform_left_))){
            witch.brooming_phase_++;
            witch.first_hit_brooming_ = true;
        }

        if(witch.brooming_phase_ == 1 && witch.sprite_.getPosition().x > (witch.platform_right_ + abs(witch.platform_right_))){
            witch.brooming_phase_++;
            witch.first_hit_brooming_ = true;
        }

        if(witch.brooming_phase_ == 2 && witch.sprite_.getPosition().x < witch.platform_right_ - 100){
            witch.brooming_ = false;
        }

        if(witch.brooming_phase_ == 0 || witch.brooming_phase_ == 2){

            witch.sprite_.setTextureRect(enemy.rectangles_witch_broom_[4 + enemy.rectangles_index_witch_broom_]);
            witch.sprite_.setPosition(witch.sprite_.getPosition().x -witch_uniform_move*1200.0f, witch.sprite_.getPosition().y);

        }else if(witch.brooming_phase_ == 1){

            witch.sprite_.setTextureRect(enemy.rectangles_witch_broom_[enemy.rectangles_index_witch_broom_]);
            witch.sprite_.setPosition(witch.sprite_.getPosition().x + witch_uniform_move*1200.0f, witch.sprite_.getPosition().y);

        }


        if(witch.first_hit_brooming_ && player.sprite_.getGlobalBounds().intersects(witch.sprite_.getGlobalBounds())){
            player.construct_hp_ -= 10;
            witch.first_hit_brooming_ = false;
        }
    }
    else if(witch.hexing_){
            witch.sprite_.setTextureRect(enemy.rectangles_witch_attack_[8*witch.facing_left_ + enemy.rectangles_index_witch_attack_]);

            if(witch.poison_clock_.getElapsedTime().asMilliseconds() > witch.poison_wave_delta_){
                witch.poison_clock_.restart();

                //1300 duzina platforme
                scale_1 = 1 + rand()%4;
                scale_2 = 1 + rand()%4;
                scale_3 = 1 + rand()%4;
                scale_4 = 1 + rand()%4;
                scale_5 = 1 + rand()%4;
                scale_6 = 1 + rand()%4;
                scale_7 = 1 + rand()%4;
                scale_8 = 1 + rand()%4;

                offset_x = rand() % 200;

                offset_y_2 = rand() % 200;
                offset_y_3 = rand() % 200;
                offset_y_4 = rand() % 200;
                offset_y_5 = rand() % 200;
                offset_y_6 = rand() % 200;
                offset_y_7 = rand() % 200;
                offset_y_8 = rand() % 200;

                witch.poison_sprite_.setPosition(witch.platform_left_ + 50, witch.sprite_.getPosition().y + 500);
                witch.first_hit_hexing_1_ = true;
                witch.first_hit_hexing_2_ = true;
                witch.first_hit_hexing_3_ = true;
                witch.first_hit_hexing_4_ = true;
                witch.first_hit_hexing_5_ = true;
                witch.first_hit_hexing_6_ = true;
                witch.first_hit_hexing_7_ = true;
                witch.first_hit_hexing_8_ = true;

            }
            witch.poison_sprite_.setScale(scale_1, scale_1);
            witch.poison_sprite_.move(0, -witch_uniform_move*500);
            window.draw(witch.poison_sprite_);

            if(witch.first_hit_hexing_1_ && player.sprite_.getGlobalBounds().intersects(witch.poison_sprite_.getGlobalBounds())){
                player.construct_hp_ -= witch.poison_damage_;
                if(witch.enemy_hp_ <= (100 - witch.poison_damage_))
                witch.enemy_hp_ += witch.poison_damage_;
                witch.first_hit_hexing_1_ = false;
            }

            poison_drop(witch, player, window, scale_2, 200 + offset_x, offset_y_2, witch.first_hit_hexing_2_);
            poison_drop(witch, player, window, scale_3, 400 + offset_x, offset_y_3, witch.first_hit_hexing_3_);
            poison_drop(witch, player, window, scale_4, 600 + offset_x, offset_y_4, witch.first_hit_hexing_4_);
            poison_drop(witch, player, window, scale_5, 800 + offset_x, offset_y_5, witch.first_hit_hexing_5_);
            poison_drop(witch, player, window, scale_6, 1000 + offset_x, offset_y_6, witch.first_hit_hexing_6_);
            poison_drop(witch, player, window, scale_7, 1200 + offset_x, offset_y_7, witch.first_hit_hexing_7_);
            poison_drop(witch, player, window, scale_8, 1400 - offset_x, offset_y_8, witch.first_hit_hexing_8_);

            if(witch.brooming_clock_.getElapsedTime().asMilliseconds() > witch.brooming_phase_delta_){
                witch.hexing_ = false;
            }
            if(witch.enemy_hp_ <= 0){
                witch.hexing_ = false;
            }
    }
    }

    if(witch.enemy_hp_ <= 0){
        witch.sprite_.setTextureRect(enemy.rectangles_witch_death_[10*witch.facing_left_ + enemy.rectangles_index_witch_death_]);
        if(enemy.rectangles_index_witch_death_ == 9){
            witch.enemy_dead_ = true;
        }
    }


}
//IMP
void handle_imp(EnemyClass &enemy, ImpEnemyClass &imp, PlayerClass &player, sf::RenderWindow &window){

    //attack phase checker - if the construct is near enough we switch to attack phase
    if(imp.enemy_hp_ > 0 && player.sprite_.getPosition().x > imp.sprite_.getPosition().x - 400 && player.sprite_.getPosition().x < imp.sprite_.getPosition().x + 400){
        //facing left can only be updated on te first frame of the animation
        if(enemy.rectangles_index_attack_ == 0)
            imp.facing_left_ = player.sprite_.getPosition().x < imp.sprite_.getPosition().x;
        imp.attacking_ = true;

    }else{
        imp.attacking_ = false;
    }

    if(!imp.attacking_ && imp.enemy_hp_ > 0){
        patrolling(imp, enemy.rectangles_imp_idle_, enemy.rectangles_imp_walk_left_, enemy.rectangles_imp_walk_right_,
                      enemy.rectangles_index_, enemy.rectangles_index_walk_);
    }

    if(imp.attacking_){
        if(imp.facing_left_){
            if(enemy.rectangles_index_attack_ < 2)
                imp.fireball_sprite_.setPosition(imp.sprite_.getPosition().x + 48, imp.sprite_.getPosition().y + 20);
            else if(enemy.rectangles_index_attack_ == 2)
                imp.fireball_sprite_.setPosition(imp.sprite_.getPosition().x + -28, imp.sprite_.getPosition().y + 20);
            else
                imp.fireball_sprite_.move(Vector2f(-4, 0.0));


            imp.sprite_.setTextureRect(enemy.rectangles_imp_attack_left_[enemy.rectangles_index_attack_]);
            imp.fireball_sprite_.setTextureRect(enemy.rectangles_imp_fireBall_left_[enemy.rectangles_index_attack_]);
        }else{
            if(enemy.rectangles_index_attack_ < 2)
                imp.fireball_sprite_.setPosition(imp.sprite_.getPosition().x, imp.sprite_.getPosition().y + 20);
            else if(enemy.rectangles_index_attack_ == 2)
                imp.fireball_sprite_.setPosition(imp.sprite_.getPosition().x + 28, imp.sprite_.getPosition().y + 20);
            else
                imp.fireball_sprite_.move(Vector2f(4, 0.0));


            imp.sprite_.setTextureRect(enemy.rectangles_imp_attack_right_[enemy.rectangles_index_attack_]);
            imp.fireball_sprite_.setTextureRect(enemy.rectangles_imp_fireBall_right_[enemy.rectangles_index_attack_]);
            }
        window.draw(imp.fireball_sprite_);
    }
    //TODO make this animation last longer
    if(!imp.enemy_dead_ && imp.enemy_hp_ <= 0){
            imp.sprite_.setTextureRect(enemy.rectangles_imp_death_[5*(imp.facing_left_) + enemy.rectangles_index_death_]);

        if(enemy.rectangles_index_death_ == 5){
            imp.enemy_dead_ = true;
        }

    }
}
//MIMI MERCEDEZ
void handle_cleo(RealEnemyClass &cleo, EnemyClass &enemy, PlayerClass &player, sf::RenderWindow &window){


        patrolling(cleo, enemy.rectangles_cleo_idle_, enemy.rectangles_cleo_walk_left_, enemy.rectangles_cleo_walk_right_,
                   enemy.rectangles_index_cleo_idle_, enemy.rectangles_index_cleo_walk_);

}

//DINO BAMBINO
void handle_dino(DinoEnemyClass &dino, EnemyClass &enemy, PlayerClass &player, sf::RenderWindow &window){


        patrolling(dino, enemy.rectangles_dino_slam_left, enemy.rectangles_dino_walk_left_, enemy.rectangles_dino_walk_right_,
                   enemy.rectangles_index_dino_slam_, enemy.rectangles_index_dino_walk_);


}



#endif // _ENEMY_HANDLER_HPP
