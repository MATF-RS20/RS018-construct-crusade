#ifndef _LEVEL_TWO_HPP
#define _LEVEL_TWO_HPP

void patroling2(RealEnemyClass &deviant,
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

void handle_cleo(RealEnemyClass &cleo, EnemyClass &enemy, PlayerClass &player, sf::RenderWindow &window){


        patroling2(cleo, enemy.rectangles_cleo_idle_, enemy.rectangles_cleo_walk_left_, enemy.rectangles_cleo_walk_right_,
                   enemy.rectangles_index_cleo_idle_, enemy.rectangles_index_cleo_walk_);

}



void level_two(sf::RenderWindow &window,
               std::vector<BigPlatform> &big_platforms_2,
               PlayerClass &player,
               EnemyClass &enemy,
               RealEnemyClass &cleopatra,
               Sprite &dino_sprite)
{

    //iscrtaj platforme za nivo 2
    for(auto bp : big_platforms_2)
        for(auto plat : bp.platforms_)
            window.draw(plat.sprite_);

    //cleopatra.sprite_.setTextureRect(enemy.rectangles_cleo_death_[enemy.rectangles_index_cleo_death_]);
    handle_cleo(cleopatra, enemy, player, window);
    window.draw(cleopatra.sprite_);

    //draw dino
    dino_sprite.setTextureRect(enemy.rectangles_dino_slam_[enemy.rectangles_index_dino_slam_]);
    dino_sprite.setScale(7,7);
    dino_sprite.setPosition(400, -575);
    window.draw(dino_sprite);


}

#endif // _LEVEL_TWO_HPP
