#ifndef _LEVEL_ONE_HPP
#define _LEVEL_ONE_HPP

extern bool RIP_construct;
//so the fireball hits only once
extern bool fireball_attack_ind;
extern bool laser_hit_ind;

void level_one(sf::RenderWindow &window,
               std::vector<BigPlatform> &big_platforms,
               EnemyClass &imp_1,
               PlayerClass &player,
               Sprite &hp_sprite
                 ){

        //draw platforms
        for(auto bp : big_platforms){
                for(auto plat : bp.platforms_)
                    window.draw(plat.sprite_);
        }


        //draw the little imp bastard
        window.draw(imp_1.sprite_);

        draw_imp_hp(window, imp_1, hp_sprite);

        //attack phase checker
        if(player.sprite_.getPosition().x > imp_1.sprite_.getPosition().x - 400 && player.sprite_.getPosition().x < imp_1.sprite_.getPosition().x + 400 && imp_1.move_phase_ != 8){
            if(player.sprite_.getPosition().x < imp_1.sprite_.getPosition().x){
                imp_1.facing_left_ = true;
        }
            else{
                imp_1.facing_left_ = false;
                }
            imp_1.attacking_ = true;

        }else{
            imp_1.attacking_ = false;
        }

        if(imp_1.attacking_){
            window.draw(imp_1.fireball_sprite_);
        }


        //fireball collision
        if(imp_1.rectangles_index_attack_ == 0){
                    fireball_attack_ind = true;
                }

        //patching until i implementa a destructor
        if(imp_1.move_phase_ == 8){
            fireball_attack_ind = false;
        }

        if(imp_1.fireball_sprite_.getGlobalBounds().intersects(player.sprite_.getGlobalBounds())){
            if(fireball_attack_ind && !RIP_construct){
                    fireball_attack_ind = false;
                    player.construct_hp_ -= 10;
                    if(player.construct_hp_ < 0)
                        player.construct_hp_ = 0;
                }
            }

        //laser collision
        if(player.laser_){
            if(player.laser_sprite_.getGlobalBounds().intersects(imp_1.sprite_.getGlobalBounds())){
                    //if we hit the imp reduce his hp
                    if(laser_hit_ind){
                        imp_1.imp_hp_ -= 10;
                        laser_hit_ind = false;
                    }
            }
        }





}


#endif // _LEVEL_ONE_HPP
