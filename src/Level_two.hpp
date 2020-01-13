#ifndef _LEVEL_TWO_HPP
#define _LEVEL_TWO_HPP
#include "EnemyHandler.hpp"
#include "CleopatraEnemyClass.hpp"

using namespace sf;

extern bool shaking;
extern bool gold_collected;
extern Clock shaking_clock;

void level_two(sf::RenderWindow &window,
               std::vector<BigPlatform> &big_platforms_2,
               PlayerClass &player,
               EnemyClass &enemy,
               Sprite &shooting_sprite,
               Sprite &hp_sprite,
               std::vector<CleopatraEnemyClass> &cleopatras,
               std::vector<DinoEnemyClass> &dinos,
               sf::Sound &cleo_sound)
{


    //draw platforms that are in the constructs area
    for(auto bp : big_platforms_2){
            for(const PlatformClass &plat : bp.platforms_)
                window.draw(plat.sprite_);
    }

    draw_player_hp_mp(window, player, hp_sprite);

        for(DinoEnemyClass &dino : dinos){

            if(!dino.enemy_dead_){
            //laser collision
                if(player.laser_){

                    if(dino.first_hit_laser_ && player.laser_sprite_.getGlobalBounds().intersects(dino.sprite_.getGlobalBounds())){
                            //if we hit the dino reduce his hp
                            dino.enemy_hp_ -= 30;
                            dino.first_hit_laser_ = false;
                    }
                }

                if(player.shooting_){
                    if(player.rectangles_index_shooting_ == 1){
                            dino.first_hit_shooting_ = true;
                    }

                    //check for collision with the dino
                    if(dino.first_hit_shooting_ && shooting_sprite.getGlobalBounds().intersects(dino.sprite_.getGlobalBounds())){
                            dino.enemy_hp_ -= 10*!(player.rectangles_index_shooting_ == 1);
                            dino.first_hit_shooting_ = false;
                    }
                }

            handle_dino(dino, enemy, player, window);
            dino.sprite_.setScale(7,7);
            handle_dino(dino, enemy, player, window);
            draw_dino_hp(window, dino, hp_sprite);
            window.draw(dino.sprite_);
            if(dino.attacking_)
            {
                window.draw(dino.stone_sprite_);
            }


            if(dino.enemy_hp_ <= 0)
            {
                dino.enemy_dead_ = true;
                dino.gold_collected_ = false;
                player.first_hit_gold = true;
                dino.phase_clock_.restart();
            }
        }
        else
        {
            if(dino.phase_clock_.getElapsedTime().asMilliseconds() < dino.phase_delta_){
            if(dino.facing_left_)
            {
                dino.sprite_.setTextureRect(IntRect(100,  0, 27, 25));
                window.draw(dino.sprite_);
            }
            else
            {

                dino.sprite_.setTextureRect(IntRect(100, 25, 27, 25));
                window.draw(dino.sprite_);
            }
            }

            dino.gold_sprite_.setScale(3,3);
            drop_gold(dino.gold_sprite_, dino);
            if(!dino.gold_collected_)
                window.draw(dino.gold_sprite_);

            if(player.first_hit_gold && player.sprite_.getGlobalBounds().intersects(dino.gold_sprite_.getGlobalBounds()))
            {
                dino.gold_collected_ = true;
                player.first_hit_gold = false;
                player.player_gold += 300;
                std::cout << player.player_gold << std::endl;

            }

        }
    }


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
                if(player.shooting_){
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
            handle_cleo(cleopatra, enemy, player, window, cleo_sound);
            draw_cleopatra_hp(window, cleopatra, hp_sprite);
            window.draw(cleopatra.sprite_);

            if(cleopatra.enemy_hp_ <= 0)
            {
                cleopatra.gold_collected_ = false;
                player.first_hit_gold = true;
            }
        }
        else
        {

            cleopatra.gold_sprite_.setScale(3,3);
            drop_gold(cleopatra.gold_sprite_, cleopatra);

            if(!cleopatra.gold_collected_){
                window.draw(cleopatra.gold_sprite_);
            }

            if(player.first_hit_gold && player.sprite_.getGlobalBounds().intersects(cleopatra.gold_sprite_.getGlobalBounds()))
            {
                cleopatra.gold_collected_ = true;
                player.first_hit_gold = false;
                player.player_gold += 100;
                std::cout << player.player_gold << std::endl;

            }

        }



    }


}

#endif // _LEVEL_TWO_HPP
