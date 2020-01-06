#ifndef _LEVEL_ONE_HPP
#define _LEVEL_ONE_HPP

extern bool RIP_construct;
//so the fireball hits only once
extern bool shooting;

void handle_imp(EnemyClass &enemy, RealEnemyClass &imp, PlayerClass &player, sf::RenderWindow &window){

    //attack phase checker
    if(imp.enemy_hp_ > 0 && player.sprite_.getPosition().x > imp.sprite_.getPosition().x - 400 && player.sprite_.getPosition().x < imp.sprite_.getPosition().x + 400){

        imp.facing_left_ = player.sprite_.getPosition().x < imp.sprite_.getPosition().x;
        imp.attacking_ = true;

    }else{
        imp.attacking_ = false;
        imp.fireball_sprite_.setPosition(imp.sprite_.getPosition().x, imp.sprite_.getPosition().y + 20);
    }

    if(!imp.attacking_ && imp.enemy_hp_ > 0){
        if(imp.phase_clock_.getElapsedTime().asMilliseconds() > imp.phase_delta_){
                imp.phase_clock_.restart();
                imp.move_phase_++;
            }

            if(imp.move_phase_ == 4){
                imp.move_phase_ = 0;
            }

            //marching left then right
            if(imp.move_phase_ == 0 || imp.move_phase_ == 2){
                imp.sprite_.setTextureRect(enemy.rectangles_imp_idle_[enemy.rectangles_index_]);
                }
            else if(imp.move_phase_ == 1){
                imp.facing_left_ = true;
                imp.sprite_.setPosition(Vector2f(imp.sprite_.getPosition().x-0.4f, imp.sprite_.getPosition().y));
                imp.sprite_.setTextureRect(enemy.rectangles_imp_walk_left_[enemy.rectangles_index_walk_]);
                if(imp.sprite_.getPosition().x < imp.platform_left_)
                    imp.sprite_.setPosition(Vector2f(imp.platform_left_, imp.sprite_.getPosition().y));
            }else if(imp.move_phase_ == 3){
                imp.facing_left_ = false;
                imp.sprite_.setPosition(Vector2f(imp.sprite_.getPosition().x+0.4f, imp.sprite_.getPosition().y));
                imp.sprite_.setTextureRect(enemy.rectangles_imp_walk_right_[enemy.rectangles_index_walk_]);
                if(imp.sprite_.getPosition().x + imp.sprite_.getGlobalBounds().width > imp.platform_right_)
                    imp.sprite_.setPosition(Vector2f(imp.platform_right_ - imp.sprite_.getGlobalBounds().width, imp.sprite_.getPosition().y));
            }
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

void level_one(sf::RenderWindow &window,
               std::vector<BigPlatform> &big_platforms,
               EnemyClass &enemy,
               PlayerClass &player,
               Sprite &hp_sprite,
               std::vector<RealEnemyClass> &imps,
               Sprite &shooting_sprite
                 ){

    //draw platforms that are in the constructs area
    for(int i = player.platform_index_ - player.platform_index_offset_; i <= player.platform_index_ + player.platform_index_offset_; i++){
            for(const PlatformClass &plat : big_platforms[i].platforms_)
                window.draw(plat.sprite_);
    }

    for(RealEnemyClass &imp : imps){
        if(!imp.enemy_dead_){
        //laser collision
        if(player.laser_){
                if(imp.first_hit_laser_ && player.laser_sprite_.getGlobalBounds().intersects(imp.sprite_.getGlobalBounds())){
                        //if we hit the imp reduce his hp
                        imp.enemy_hp_ -= 100;
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
                        imp.enemy_hp_ -= 10;
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
                        player.construct_hp_ -= 10*!(enemy.rectangles_index_attack_ == 0);
                        if(player.construct_hp_ < 0)
                            player.construct_hp_ = 0;
                }

            draw_imp_hp(window, imp, hp_sprite);
            window.draw(imp.sprite_);
        }
    }

}
#endif // _LEVEL_ONE_HPP
