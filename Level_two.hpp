#ifndef _LEVEL_TWO_HPP
#define _LEVEL_TWO_HPP

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

    cleopatra.sprite_.setTextureRect(enemy.rectangles_cleo_walk_left_[enemy.rectangles_index_walk_cleo_]);
    cleopatra.sprite_.setPosition(Vector2f(cleopatra.sprite_.getPosition().x-0.1f, cleopatra.sprite_.getPosition().y));

    window.draw(cleopatra.sprite_);

    //draw dino
    dino_sprite.setTextureRect(enemy.rectangles_dino_slam_[enemy.rectangles_index_dino_slam_]);
    dino_sprite.setScale(7,7);
    dino_sprite.setPosition(400, -575);
    window.draw(dino_sprite);


}

#endif // _LEVEL_TWO_HPP
