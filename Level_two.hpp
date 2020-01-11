#ifndef _LEVEL_TWO_HPP
#define _LEVEL_TWO_HPP
#include "EnemyHandler.hpp"
using namespace sf;

extern bool shaking;
extern Clock shaking_clock;

void level_two(sf::RenderWindow &window,
               std::vector<BigPlatform> &big_platforms_2,
               PlayerClass &player,
               EnemyClass &enemy,
               RealEnemyClass &cleopatra,
               std::vector<DinoEnemyClass> &dinos,
               DinoEnemyClass &dino)
{

    //iscrtaj platforme za nivo 2
    for(auto bp : big_platforms_2)
        for(auto plat : bp.platforms_)
            window.draw(plat.sprite_);

    //cleopatra.sprite_.setTextureRect(enemy.rectangles_cleo_death_[enemy.rectangles_index_cleo_death_]);
    handle_cleo(cleopatra, enemy, player, window);
    window.draw(cleopatra.sprite_);

    //draw dino
//    dino.sprite_.setTextureRect(enemy.rectangles_dino_walk_left_[enemy.rectangles_index_dino_walk_]);
//    dino.sprite_.setScale(7,7);
//    dino.sprite_.setPosition(400, -575);
//    window.draw(dino.sprite_);

    handle_dino(dino, enemy, player, window);
    if(shaking_clock.getElapsedTime().asMilliseconds() > 3000)
    {
        shaking_clock.restart();
        shaking = !shaking;
    }

        for(DinoEnemyClass &dino : dinos){

            dino.sprite_.setScale(7,7);
            handle_dino(dino, enemy, player, window);
            window.draw(dino.sprite_);
    }



    dino.sprite_.setScale(7,7);
    window.draw(dino.sprite_);


}

#endif // _LEVEL_TWO_HPP
