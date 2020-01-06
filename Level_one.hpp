#ifndef _LEVEL_ONE_HPP
#define _LEVEL_ONE_HPP

extern bool RIP_construct;
//so the fireball hits only once
extern bool fireball_attack_ind;
extern bool laser_hit_ind;
extern bool shooting;

void handle_imp(EnemyClass &imp_1, EnemyClass &imp, PlayerClass &player, sf::RenderWindow &window){

    //attack phase checker
    if(imp.imp_hp_ > 0 && player.sprite_.getPosition().x > imp.sprite_.getPosition().x - 400 && player.sprite_.getPosition().x < imp.sprite_.getPosition().x + 400){

        imp.facing_left_ = player.sprite_.getPosition().x < imp.sprite_.getPosition().x;
        imp.attacking_ = true;

    }else{
        imp.attacking_ = false;
        imp.fireball_sprite_.setPosition(imp.sprite_.getPosition().x, imp.sprite_.getPosition().y + 20);
    }

    if(!imp.attacking_ && imp.imp_hp_ > 0){
        if(imp.phase_clock_.getElapsedTime().asMilliseconds() > imp.phase_delta_){
                imp.phase_clock_.restart();
                imp.move_phase_++;
            }

            if(imp.move_phase_ == 4){
                imp.move_phase_ = 0;
            }

            //marching left then right
            if(imp.move_phase_ == 0 || imp.move_phase_ == 2){
                imp.sprite_.setTextureRect(imp_1.rectangles_imp_idle_[imp_1.rectangles_index_]);
                }
            else if(imp.move_phase_ == 1){
                imp.facing_left_ = true;
                imp.sprite_.setPosition(Vector2f(imp.sprite_.getPosition().x-0.4f, imp.sprite_.getPosition().y));
                imp.sprite_.setTextureRect(imp_1.rectangles_imp_walk_left_[imp_1.rectangles_index_walk_]);
            }else if(imp.move_phase_ == 3){
                imp.facing_left_ = false;
                imp.sprite_.setPosition(Vector2f(imp.sprite_.getPosition().x+0.4f, imp.sprite_.getPosition().y));
                imp.sprite_.setTextureRect(imp_1.rectangles_imp_walk_right_[imp_1.rectangles_index_walk_]);
            }
    }

            if(imp.attacking_){
                if(imp.facing_left_){
                    if(imp_1.rectangles_index_attack_ < 2)
                        imp.fireball_sprite_.setPosition(imp.sprite_.getPosition().x + 48, imp.sprite_.getPosition().y + 20);
                    else if(imp_1.rectangles_index_attack_ == 2)
                        imp.fireball_sprite_.setPosition(imp.sprite_.getPosition().x + -28, imp.sprite_.getPosition().y + 20);
                    else
                        imp.fireball_sprite_.move(Vector2f(-4, 0.0));


                    imp.sprite_.setTextureRect(imp_1.rectangles_imp_attack_left_[imp_1.rectangles_index_attack_]);
                    imp.fireball_sprite_.setTextureRect(imp_1.rectangles_imp_fireBall_left_[imp_1.rectangles_index_attack_]);
                }else{
                    if(imp_1.rectangles_index_attack_ < 2)
                        imp.fireball_sprite_.setPosition(imp.sprite_.getPosition().x, imp.sprite_.getPosition().y + 20);
                    else if(imp_1.rectangles_index_attack_ == 2)
                        imp.fireball_sprite_.setPosition(imp.sprite_.getPosition().x + 28, imp.sprite_.getPosition().y + 20);
                    else
                        imp.fireball_sprite_.move(Vector2f(4, 0.0));


                    imp.sprite_.setTextureRect(imp_1.rectangles_imp_attack_right_[imp_1.rectangles_index_attack_]);
                    imp.fireball_sprite_.setTextureRect(imp_1.rectangles_imp_fireBall_right_[imp_1.rectangles_index_attack_]);
                    }
                window.draw(imp.fireball_sprite_);
            }

            if(!imp.enemy_dead_ && imp.imp_hp_ <= 0){
                    imp.sprite_.setTextureRect(imp_1.rectangles_imp_death_[5*(imp.facing_left_) + imp_1.rectangles_index_death_]);

                if(imp_1.rectangles_index_death_ == 5){
                    imp.enemy_dead_ = true;
                }

            }


}

void level_one(sf::RenderWindow &window,
               std::vector<BigPlatform> &big_platforms,
               EnemyClass &imp_1,
               PlayerClass &player,
               Sprite &hp_sprite,
               std::vector<EnemyClass> &imps,
               Sprite &shooting_sprite
                 ){

    //draw platforms that are in the constructs area
    for(int i = player.platform_index_ - player.platform_index_offset_; i <= player.platform_index_ + player.platform_index_offset_; i++){
            for(const PlatformClass &plat : big_platforms[i].platforms_)
                window.draw(plat.sprite_);
    }

    draw_imp_hp(window, imp_1, hp_sprite);

    //attack phase checker
    if(imp_1.imp_hp_ > 0 && player.sprite_.getPosition().x > imp_1.sprite_.getPosition().x - 400 && player.sprite_.getPosition().x < imp_1.sprite_.getPosition().x + 400){

        imp_1.facing_left_ = player.sprite_.getPosition().x < imp_1.sprite_.getPosition().x;
        imp_1.attacking_ = true;

    }else{
        imp_1.attacking_ = false;
        imp_1.fireball_sprite_.setPosition(imp_1.sprite_.getPosition().x, imp_1.sprite_.getPosition().y + 20);
    }
    //imp_1 -> imp
    //fireball collision - maybe optimize this at a later date
    if(imp_1.rectangles_index_attack_ == 0)
        imp_1.fireball_attack_ind_ = true;

    if(imp_1.imp_hp_ <= 0){
        imp_1.fireball_attack_ind_ = false;
        imp_1.attacking_ = false;
    }

    if(imp_1.fireball_attack_ind_ && imp_1.fireball_sprite_.getGlobalBounds().intersects(player.sprite_.getGlobalBounds())){
                imp_1.fireball_attack_ind_ = false;
                player.construct_hp_ -= 10*!(imp_1.rectangles_index_attack_ == 0);
                if(player.construct_hp_ < 0)
                    player.construct_hp_ = 0;
        }

    //laser collision
    if(player.laser_){
        if(laser_hit_ind && player.laser_sprite_.getGlobalBounds().intersects(imp_1.sprite_.getGlobalBounds())){
                //if we hit the imp reduce his hp
                    imp_1.imp_hp_ -= 30;
                    laser_hit_ind = false;
        }
    }

    //draw the little imp bastard
    window.draw(imp_1.sprite_);

    for(EnemyClass &imp : imps){

        //laser collision //TODO fix this for laser hits
        if(player.laser_){
            if(imp.laser_hit_ind_ && player.laser_sprite_.getGlobalBounds().intersects(imp.sprite_.getGlobalBounds())){
                    //if we hit the imp reduce his hp
                        imp.imp_hp_ -= 100;
                        imp_1.rectangles_index_death_ = 0;
                        imp.laser_hit_ind_ = false;
            }
        }
        if(shooting){
            if(player.rectangles_index_shooting_ == 1){
                    imp.first_hit_shooting_ = true;
            }

            //check for collision with the imp
            if(imp.first_hit_shooting_ && shooting_sprite.getGlobalBounds().intersects(imp.sprite_.getGlobalBounds())){
                    imp.imp_hp_ -= 10;
                    imp.first_hit_shooting_ = false;
            }
        }

        handle_imp(imp_1, imp, player, window);

        //fireball collision - maybe optimize this at a later date
        if(imp_1.rectangles_index_attack_ == 0)
            imp.fireball_attack_ind_ = true;

        if(imp.imp_hp_ <= 0){
            imp.fireball_attack_ind_ = false;
            imp.attacking_ = false;
        }

        if(imp.fireball_attack_ind_ && imp.fireball_sprite_.getGlobalBounds().intersects(player.sprite_.getGlobalBounds())){
                    imp.fireball_attack_ind_ = false;
                    player.construct_hp_ -= 10*!(imp_1.rectangles_index_attack_ == 0);
                    if(player.construct_hp_ < 0)
                        player.construct_hp_ = 0;
            }

        draw_imp_hp(window, imp, hp_sprite);
        window.draw(imp.sprite_);
    }

    if(imp_1.attacking_){
        window.draw(imp_1.fireball_sprite_);
    }

}
#endif // _LEVEL_ONE_HPP
