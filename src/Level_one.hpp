#ifndef _LEVEL_ONE_HPP
#define _LEVEL_ONE_HPP
#include "EnemyHandler.hpp"
#include "BatsyEnemyClass.hpp"
#include "MinotaurEnemyClass.hpp"

using namespace sf;

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
               std::vector<BatsyEnemyClass> &bats,
               MinotaurEnemyClass &minos,
               Sprite &gold_sprite,
               sf::Sound &coin_sound,
               sf::Sound &mino_sound
               ){



    //draw platforms that are in the constructs area
    for(int i = player.platform_index_ - player.platform_index_offset_; i <= player.platform_index_ + player.platform_index_offset_; i++){
            for(const PlatformClass &plat : big_platforms[i].platforms_)
                window.draw(plat.sprite_);
    }

    if(!minos.enemy_dead_ && minos.enemy_hp_ > 0){
        //laser collision
        if(player.laser_){
                if(minos.first_hit_laser_ && player.laser_sprite_.getGlobalBounds().intersects(minos.sprite_.getGlobalBounds())){
                        //if we hit the minos reduce his hp
                        minos.enemy_hp_ -= 30;
                        enemy.rectangles_index_death_ = 0;
                        minos.first_hit_laser_ = false;
                }
            }
            if(player.shooting_){
                if(player.rectangles_index_shooting_ == 1){
                        minos.first_hit_shooting_ = true;
                }

                //check for collision with the minos
                if(minos.first_hit_shooting_ && shooting_sprite.getGlobalBounds().intersects(minos.sprite_.getGlobalBounds())){
                        minos.enemy_hp_ -= 10*!(player.rectangles_index_shooting_ == 1);
                        enemy.rectangles_index_death_ = 0;
                        minos.first_hit_shooting_ = false;
                }
            }


        handle_minos(minos, enemy, player, window);
        minos.sprite_.setScale(4, 4);
        window.draw(minos.sprite_);
        draw_minos_hp(window, minos, hp_sprite);
    }else if(!minos.enemy_dead_ && minos.enemy_hp_ <= 0){
        minos.sprite_.setTextureRect(enemy.rectangles_minotaur_death_[6*minos.facing_left_ + enemy.rectangles_index_minotaur_death_]);
        window.draw(minos.sprite_);

        if(minos.enemy_hp_ <= 0){
                    minos.gold_collected_ = false;
                    player.first_hit_gold = true;
        }

        if(enemy.rectangles_index_minotaur_death_ == 5){
            mino_sound.play();
            minos.enemy_dead_ = true;
        }
    }
    else if(minos.enemy_dead_)
    {
            minos.gold_sprite_.setScale(3,3);
            drop_gold(minos.gold_sprite_, minos);

            if(!minos.gold_collected_){
                window.draw(minos.gold_sprite_);

            }

            if(player.first_hit_gold && player.sprite_.getGlobalBounds().intersects(minos.gold_sprite_.getGlobalBounds()))
            {
                minos.gold_collected_ = true;
                player.first_hit_gold = false;
                player.player_gold += 300;
                std::cout << player.player_gold << std::endl;

            }
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
            if(player.shooting_){
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
                imp.gold_collected_ = false;
                player.first_hit_gold = true;
            }

            if(imp.first_hit_fireball_ && imp.fireball_sprite_.getGlobalBounds().intersects(player.sprite_.getGlobalBounds())){
                        imp.first_hit_fireball_ = false;
                        player.construct_hp_ -= 10*!(enemy.rectangles_index_attack_ == 0 && imp.attacking_);
                }

            draw_imp_hp(window, imp, hp_sprite);
            window.draw(imp.sprite_);
        }
        else
        {

            imp.gold_sprite_.setScale(3,3);
            drop_gold(imp.gold_sprite_, imp);

            if(!imp.gold_collected_){
                window.draw(imp.gold_sprite_);

            }

            if(player.first_hit_gold && player.sprite_.getGlobalBounds().intersects(imp.gold_sprite_.getGlobalBounds()))
            {
                imp.gold_collected_ = true;
                player.first_hit_gold = false;
                player.player_gold += 100;
                coin_sound.play();
                std::cout << player.player_gold << std::endl;

            }

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
                if(player.shooting_){
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

                if(witch.enemy_hp_ <= 0){
                    witch.gold_collected_ = false;
                    player.first_hit_gold = true;
                }

            handle_witch(witch, enemy, player, window, witch_uniform_move);

        }
        else
        {

            witch.gold_sprite_.setScale(3,3);
            drop_gold(witch.gold_sprite_, witch);

            if(!witch.gold_collected_){
                window.draw(witch.gold_sprite_);

            }

            if(player.first_hit_gold && player.sprite_.getGlobalBounds().intersects(witch.gold_sprite_.getGlobalBounds()))
            {
                witch.gold_collected_ = true;
                player.first_hit_gold = false;
                player.player_gold += 300;
                coin_sound.play();
                std::cout << player.player_gold << std::endl;

            }

        }


        draw_imp_hp(window, witch, hp_sprite);
        window.draw(witch.sprite_);
    }

    witch_uniform_clock.restart();

    //BATS
    for(BatsyEnemyClass &batsy : bats){

    if(!batsy.enemy_dead_ && batsy.enemy_hp_ > 0){

        if(player.laser_){

            if(batsy.first_hit_laser_ && player.laser_sprite_.getGlobalBounds().intersects(batsy.sprite_.getGlobalBounds())){
                    batsy.enemy_hp_ -= 30;
                    enemy.rectangles_index_batsy_death_ = 0;
                    batsy.first_hit_laser_ = false;
            }
        }
        if(player.shooting_){
            if(player.rectangles_index_shooting_ == 1){
                    batsy.first_hit_shooting_ = true;
            }

        //check for collision with the batsy
        if(batsy.first_hit_shooting_ && shooting_sprite.getGlobalBounds().intersects(batsy.sprite_.getGlobalBounds())){
                batsy.enemy_hp_ -= 10*!(player.rectangles_index_shooting_ == 1);
                enemy.rectangles_index_batsy_death_ = 0;
                batsy.first_hit_shooting_ = false;
        }
        }


        //PATROLLING
        if(batsy.sprite_.getPosition().x < batsy.platform_left_){
                batsy.move_phase_++;
        }

        if(batsy.move_phase_ == 1 && batsy.sprite_.getPosition().x > batsy.platform_right_){
                batsy.move_phase_++;
        }

        if(batsy.move_phase_ == 2){
            batsy.move_phase_ = 0;
        }

        else if(batsy.move_phase_ == 0){
            batsy.facing_left_ = true;
            batsy.sprite_.setPosition(Vector2f(batsy.sprite_.getPosition().x-0.6f, batsy.sprite_.getPosition().y));
            batsy.sprite_.setTextureRect(enemy.rectangles_batsy_fly_[5 + enemy.rectangles_index_batsy_fly_]);

            batsy.sonic_sprite_.setPosition(Vector2f(batsy.sprite_.getPosition().x-0.6f - 140, batsy.sprite_.getPosition().y - 68));
            batsy.sonic_sprite_.setTextureRect(enemy.rectangles_sonic_attack_[3 + enemy.rectangles_index_batsy_attack_]);

        }else if(batsy.move_phase_ == 1){
            batsy.facing_left_ = false;
            batsy.sprite_.setPosition(Vector2f(batsy.sprite_.getPosition().x+0.6f, batsy.sprite_.getPosition().y));
            batsy.sprite_.setTextureRect(enemy.rectangles_batsy_fly_[enemy.rectangles_index_batsy_fly_]);

            batsy.sonic_sprite_.setPosition(Vector2f(batsy.sprite_.getPosition().x+0.6f + 56, batsy.sprite_.getPosition().y - 68));
            batsy.sonic_sprite_.setTextureRect(enemy.rectangles_sonic_attack_[enemy.rectangles_index_batsy_attack_]);

        }

        if(!batsy.first_hit_sonic_ && batsy.phase_clock_.getElapsedTime().asMilliseconds() > batsy.phase_delta_){
                batsy.first_hit_sonic_ = true;
        }


        if(batsy.first_hit_sonic_ && batsy.sonic_sprite_.getGlobalBounds().intersects(player.sprite_.getGlobalBounds())){
                player.construct_hp_ -= batsy.sonic_damage_;
                batsy.first_hit_sonic_ = false;
                batsy.phase_clock_.restart();

        }

        draw_batsy_hp(window, batsy, hp_sprite);

        batsy.sprite_.setScale(4, 4);
        window.draw(batsy.sprite_);

        batsy.sonic_sprite_.setScale(4, 4);
        window.draw(batsy.sonic_sprite_);


    }else if(!batsy.enemy_dead_ && batsy.enemy_hp_ <= 0){

        batsy.sprite_.setTextureRect(enemy.rectangles_batsy_death_[6*(batsy.facing_left_) + enemy.rectangles_index_batsy_death_]);
        batsy.sprite_.setScale(4, 4);
        window.draw(batsy.sprite_);

        if(enemy.rectangles_index_batsy_death_ == 5){
            batsy.enemy_dead_ = true;
        }

    }

    }

}
#endif // _LEVEL_ONE_HPP
