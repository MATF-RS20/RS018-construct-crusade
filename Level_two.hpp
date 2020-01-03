#ifndef _LEVEL_TWO_HPP
#define _LEVEL_TWO_HPP

void level_two(sf::RenderWindow &window, std::vector<BigPlatform> &big_platforms_2, PlayerClass &player)
{

    //iscrtaj platforme za nivo 2
    for(auto bp : big_platforms_2)
        for(auto plat : bp.platforms_)
            window.draw(plat.sprite_);


}

#endif // _LEVEL_TWO_HPP
