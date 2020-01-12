#ifndef _LEVEL_ONE_HPP
#define _LEVEL_ONE_HPP
#include "EnemyHandler.hpp"

extern bool RIP_construct;
//so the fireball hits only once
extern bool shooting;
float witch_uniform_move;
extern sf::Clock witch_uniform_clock;

void level_one(sf::RenderWindow &window,
               std::vector<BigPlatform> &big_platforms,
               EnemyClass &enemy,
               PlayerClass &player,
               Sprite &hp_sprite,
               std::vector<ImpEnemyClass> &imps,
               Sprite &shooting_sprite,
               std::vector<WitchEnemyClass> &witches,
               Sprite &minotaur_sprite
                 ){

    minotaur_sprite.setScale(4, 4);

    minotaur_sprite.setTextureRect(enemy.rectangles_minotaur_idle_[enemy.rectangles_index_minotaur_idle_]);
    //minotaur_sprite.setTextureRect(enemy.rectangles_minotaur_walk_right_[enemy.rectangles_index_minotaur_walk_]);
    minotaur_sprite.setPosition(0, 500 - 176);
    window.draw(minotaur_sprite);

    //draw platforms that are in the constructs area
    for(int i = player.platform_index_ - player.platform_index_offset_; i <= player.platform_index_ + player.platform_index_offset_; i++){
            for(const PlatformClass &plat : big_platforms[i].platforms_)
                window.draw(plat.sprite_);
    }

    for(ImpEnemyClass &imp : imps){
        if(!imp.enemy_dead_){
        //laser collision
        if(player.laser_){
                if(imp.first_hit_laser_ && player.laser_sprite_.getGlobalBounds().intersects(imp.sprite_.getGlobalBounds())){
                        //if we hit the imp reduce his hp
                        imp.enemy_hp_ -= 30;
                        enemy.rectangles_index_death_ = 0;
                        imp.first_hit_laser_ = false;
                }
            }
            if(shooting){
                if(player.rectangles_index_shooting_ == 1){
                        imp.first_hit_shooting_ = true;
                }

                //check for collision with the imp
                if(imp.first_hit_shooting_ && shooting_sprite.getGlobalBounds().intersects(imp.sprite_.getGlobalBounds())){
                        imp.enemy_hp_ -= 10*!(player.rectangles_index_shooting_ == 1);
                        enemy.rectangles_index_death_ = 0;
                        imp.first_hit_shooting_ = false;
                }
            }

            handle_imp(enemy, imp, player, window);

            //fireball collision - maybe optimize this at a later date
            if(enemy.rectangles_index_attack_ == 0)
                imp.first_hit_fireball_ = true;

            if(imp.enemy_hp_ <= 0){
                imp.first_hit_fireball_ = false;
                imp.attacking_ = false;
            }

            if(imp.first_hit_fireball_ && imp.fireball_sprite_.getGlobalBounds().intersects(player.sprite_.getGlobalBounds())){
                        imp.first_hit_fireball_ = false;
                        player.construct_hp_ -= 10*!(enemy.rectangles_index_attack_ == 0 && imp.attacking_);
                }

            draw_imp_hp(window, imp, hp_sprite);
            window.draw(imp.sprite_);
        }
    }//for imps
    witch_uniform_move = witch_uniform_clock.getElapsedTime().asSeconds();
    for(WitchEnemyClass &witch : witches){

        if(!witch.enemy_dead_){
            //laser collision
            if(player.laser_){

                    if(!witch.brooming_ && witch.first_hit_laser_ && player.laser_sprite_.getGlobalBounds().intersects(witch.sprite_.getGlobalBounds())){
                            //if we hit the witch reduce her hp
                            witch.enemy_hp_ -= 30;
                            enemy.rectangles_index_witch_death_ = 0;
                            witch.first_hit_laser_ = false;
                    }
                }
                if(shooting){
                    if(player.rectangles_index_shooting_ == 1){
                            witch.first_hit_shooting_ = true;
                    }

                    //check for collision with the witch
                    if(!witch.brooming_ && witch.first_hit_shooting_ && shooting_sprite.getGlobalBounds().intersects(witch.sprite_.getGlobalBounds())){
                            witch.enemy_hp_ -= 10*!(player.rectangles_index_shooting_ == 1);
                            enemy.rectangles_index_witch_death_ = 0;
                            witch.first_hit_shooting_ = false;
                    }
                }

            handle_witch(witch, enemy, player, window, witch_uniform_move);

        }


        draw_imp_hp(window, witch, hp_sprite);
        window.draw(witch.sprite_);
    }

    witch_uniform_clock.restart();

}
#endif // _LEVEL_ONE_HPP
