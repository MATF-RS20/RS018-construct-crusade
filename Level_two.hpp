#ifndef _LEVEL_TWO_HPP
#define _LEVEL_TWO_HPP
#include "EnemyHandler.hpp"
#include "CleopatraEnemyClass.hpp"

using namespace sf;

extern bool shaking;
extern Clock shaking_clock;

void level_two(sf::RenderWindow &window,
               std::vector<BigPlatform> &big_platforms_2,
               PlayerClass &player,
               EnemyClass &enemy,
               Sprite &shooting_sprite,
               Sprite &hp_sprite,
               std::vector<CleopatraEnemyClass> &cleopatras,
               std::vector<DinoEnemyClass> &dinos)
{

    //iscrtaj platforme za nivo 2
    for(auto bp : big_platforms_2)
        for(auto plat : bp.platforms_)
            window.draw(plat.sprite_);

    //cleopatra.sprite_.setTextureRect(enemy.rectangles_cleo_death_[enemy.rectangles_index_cleo_death_]);
//    handle_cleo(cleopatra, enemy, player, window);
//    window.draw(cleopatra.sprite_);
//    cleopatra.heart_sprite_.move(-1, 0);
//    cleopatra.heart_sprite_.setTextureRect(enemy.rectangles_cleo_attack_[4 + enemy.rectangles_index_cleo_attack_]);
//    window.draw(cleopatra.heart_sprite_);
//    cleopatra.sprite_.setTextureRect(enemy.rectangles_cleo_attack_[2 + enemy.rectangles_index_cleo_attack_]);
//    window.draw(cleopatra.sprite_);


    //draw dino
//    dino.sprite_.setTextureRect(enemy.rectangles_dino_walk_left_[enemy.rectangles_index_dino_walk_]);
//    dino.sprite_.setScale(7,7);
//    dino.sprite_.setPosition(400, -575);
//    window.draw(dino.sprite_);

    handle_dino(dino, enemy, player, window);
    if(shaking_clock.getElapsedTime().asMilliseconds() > 3000)
    {
        shaking_clock.restart();
        shaking = !shaking;
    }

        for(DinoEnemyClass &dino : dinos){

            dino.sprite_.setScale(7,7);
            handle_dino(dino, enemy, player, window);
            window.draw(dino.sprite_);
    }



    dino.sprite_.setScale(7,7);
    window.draw(dino.sprite_);

    for(CleopatraEnemyClass &cleopatra : cleopatras){

        if(!cleopatra.enemy_dead_){
            //laser collision
            if(player.laser_){

                    if(cleopatra.first_hit_laser_ && player.laser_sprite_.getGlobalBounds().intersects(cleopatra.sprite_.getGlobalBounds())){
                            //if we hit the cleopatra reduce her hp
                            cleopatra.enemy_hp_ -= 30;
                            enemy.rectangles_index_cleo_death_ = 0;
                            cleopatra.first_hit_laser_ = false;
                    }
                }
                if(shooting){
                    if(player.rectangles_index_shooting_ == 1){
                            cleopatra.first_hit_shooting_ = true;
                    }

                    //check for collision with the cleopatra
                    if(cleopatra.first_hit_shooting_ && shooting_sprite.getGlobalBounds().intersects(cleopatra.sprite_.getGlobalBounds())){
                            cleopatra.enemy_hp_ -= 10*!(player.rectangles_index_shooting_ == 1);
                            enemy.rectangles_index_cleo_death_ = 0;
                            cleopatra.first_hit_shooting_ = false;
                    }
                }
            handle_cleo(cleopatra, enemy, player, window);
        }


        //draw_cleo_hp(window, cleopatra, hp_sprite);
        window.draw(cleopatra.sprite_);
    }


}

#endif // _LEVEL_TWO_HPP
