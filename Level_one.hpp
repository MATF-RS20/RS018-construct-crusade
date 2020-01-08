#ifndef _LEVEL_ONE_HPP
#define _LEVEL_ONE_HPP

extern bool RIP_construct;
//so the fireball hits only once
extern bool shooting;

void patroling(RealEnemyClass &deviant,
               //EnemyClass &enemy,
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

    //marching left then right
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

void handle_witch(RealEnemyClass &witch, EnemyClass &enemy, PlayerClass &player, sf::RenderWindow &window){

    if(witch.enemy_hp_ > 0 && player.sprite_.getPosition().x > witch.sprite_.getPosition().x - 400 && player.sprite_.getPosition().x < witch.sprite_.getPosition().x + 400){
        //facing left can only be updated on te first frame of the animation
        if(enemy.rectangles_index_attack_ == 0)
            witch.facing_left_ = player.sprite_.getPosition().x < witch.sprite_.getPosition().x;
        witch.attacking_ = true;

    }else{
        witch.attacking_ = false;
    }

    if(!witch.attacking_ && witch.enemy_hp_ > 0)
        patroling(witch, enemy.rectangles_witch_idle_, enemy.rectangles_witch_walk_left_, enemy.rectangles_witch_walk_right_,
                  enemy.rectangles_index_witch_idle_, enemy.rectangles_index_witch_walk_);

    if(witch.attacking_){
        witch.sprite_.setTextureRect(enemy.rectangles_witch_attack_[8*witch.facing_left_ + enemy.rectangles_index_witch_attack_]);
    }

    if(witch.enemy_hp_ <= 0){
        witch.sprite_.setTextureRect(enemy.rectangles_witch_death_[10*witch.facing_left_ + enemy.rectangles_index_witch_death_]);
        if(enemy.rectangles_index_witch_death_ == 9){
            witch.enemy_dead_ = true;
        }
    }


}

void handle_imp(EnemyClass &enemy, RealEnemyClass &imp, PlayerClass &player, sf::RenderWindow &window){

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
        patroling(imp, enemy.rectangles_imp_idle_, enemy.rectangles_imp_walk_left_, enemy.rectangles_imp_walk_right_,
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

void level_one(sf::RenderWindow &window,
               std::vector<BigPlatform> &big_platforms,
               EnemyClass &enemy,
               PlayerClass &player,
               Sprite &hp_sprite,
               std::vector<RealEnemyClass> &imps,
               Sprite &shooting_sprite,
               std::vector<RealEnemyClass> &witches
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
                        imp.enemy_hp_ -= 10;
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
                        if(player.construct_hp_ < 0)
                            player.construct_hp_ = 0;
                }

            draw_imp_hp(window, imp, hp_sprite);
            window.draw(imp.sprite_);
        }
    }//for imps

    for(RealEnemyClass &witch : witches){

        if(!witch.enemy_dead_){
            //laser collision
            if(player.laser_){

                    if(witch.first_hit_laser_ && player.laser_sprite_.getGlobalBounds().intersects(witch.sprite_.getGlobalBounds())){
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
                    if(witch.first_hit_shooting_ && shooting_sprite.getGlobalBounds().intersects(witch.sprite_.getGlobalBounds())){
                            witch.enemy_hp_ -= 10;
                            enemy.rectangles_index_witch_death_ = 0;
                            witch.first_hit_shooting_ = false;
                    }
                }
            handle_witch(witch, enemy, player, window);
        }


        draw_imp_hp(window, witch, hp_sprite);
        window.draw(witch.sprite_);
    }

}
#endif // _LEVEL_ONE_HPP
