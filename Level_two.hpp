#ifndef _LEVEL_TWO_HPP
#define _LEVEL_TWO_HPP
#include "EnemyHandler.hpp"

void level_two(sf::RenderWindow &window,
               std::vector<BigPlatform> &big_platforms_2,
               PlayerClass &player,
               EnemyClass &enemy,
               RealEnemyClass &cleopatra,
               RealEnemyClass &dino)
{

    //iscrtaj platforme za nivo 2
    for(auto bp : big_platforms_2)
        for(auto plat : bp.platforms_)
            window.draw(plat.sprite_);

    //cleopatra.sprite_.setTextureRect(enemy.rectangles_cleo_death_[enemy.rectangles_index_cleo_death_]);
    handle_cleo(cleopatra, enemy, player, window);
    window.draw(cleopatra.sprite_);

    //draw dino
    dino.sprite_.setTextureRect(enemy.rectangles_dino_walk_left_[enemy.rectangles_index_dino_walk_]);
    dino.sprite_.setScale(7,7);
    dino.sprite_.setPosition(400, -575);
    window.draw(dino.sprite_);


}

#endif // _LEVEL_TWO_HPP
