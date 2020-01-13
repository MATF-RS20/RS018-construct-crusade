#ifndef INIT_PLATFORMS_HPP
#define INIT_PLATFORMS_HPP

void init_platforms_and_enemies(std::vector<BigPlatform> &big_platforms,
                    PlayerClass &player,
                    Sprite &platform_sprite,
                    std::vector<ImpEnemyClass> &imps,
                    std::vector<WitchEnemyClass> &witches,
                    std::vector<BatsyEnemyClass> &bats,
                    Sprite &imp_sprite,
                    Sprite &fireball_sprite,
                    Sprite &witch_sprite,
                    Sprite &poison_sprite,
                    Sprite &batsy_sprite,
                    Sprite &sonic_sprite,
                    Sprite &platform_sprite_level_1,
                    Sprite &gold_sprite
                    ){

    int platform_distance = 800;
    int fixed_platform_height = 500;
    int platform_height_offset = 140;

    //level 0 - height 500 - width from -4800 to 4000
    for(int j = -3; j < 6; j++){
        big_platforms.push_back(BigPlatform(platform_distance*j, fixed_platform_height, 8 + rand() % 3, platform_sprite_level_1, 2));
        player.num_of_platforms_++;

        if(rand() % 101 < 35 && j > 1)
            imps.push_back(ImpEnemyClass(fireball_sprite,
                                          imp_sprite,
                                          gold_sprite,
                                           big_platforms[player.num_of_platforms_-1].platform_right_ - 100,
                                            big_platforms[player.num_of_platforms_-1].platform_top_ - 60,
                                             big_platforms[player.num_of_platforms_-1].platform_left_,
                                              big_platforms[player.num_of_platforms_-1].platform_right_));
        else if(rand() % 101 < 35 && j > 1)
            bats.push_back(BatsyEnemyClass(batsy_sprite,
                                          sonic_sprite,
                                           big_platforms[player.num_of_platforms_-1].platform_right_ - 100,
                                            big_platforms[player.num_of_platforms_-1].platform_top_ - 76,
                                             big_platforms[player.num_of_platforms_-1].platform_left_,
                                              big_platforms[player.num_of_platforms_-1].platform_right_));

    }

    //stairs to level 1
    for(int j = 1; j < 6; j++){
        big_platforms.push_back(BigPlatform(6.3*platform_distance + platform_distance/2.5*(pow((-1),j)),
                                            fixed_platform_height - j*platform_height_offset , 7 + rand() % 3, platform_sprite_level_1, 2));
        player.num_of_platforms_++;

        if(rand() % 101 < 25)
            imps.push_back(ImpEnemyClass(fireball_sprite, imp_sprite, big_platforms[player.num_of_platforms_-1].platform_right_ - 100, big_platforms[player.num_of_platforms_-1].platform_top_ - 60, big_platforms[player.num_of_platforms_-1].platform_left_, big_platforms[player.num_of_platforms_-1].platform_right_));
        else if(rand() % 101 < 25 && j > 1)
            bats.push_back(BatsyEnemyClass(batsy_sprite,
                                          sonic_sprite,
                                           big_platforms[player.num_of_platforms_-1].platform_right_ - 100,
                                            big_platforms[player.num_of_platforms_-1].platform_top_ - 76,
                                             big_platforms[player.num_of_platforms_-1].platform_left_,
                                              big_platforms[player.num_of_platforms_-1].platform_right_));
    }

    //level 1 - height -200 - width from 4000 to 0
    int level_1_height = fixed_platform_height - 5*platform_height_offset;
    for(int j = 5; j > 0; j--){
        big_platforms.push_back(BigPlatform(platform_distance*j, level_1_height, 8 + rand() % 3, platform_sprite_level_1, 3));
        player.num_of_platforms_++;
        if(rand() % 101 < 25)
            imps.push_back(ImpEnemyClass(fireball_sprite, imp_sprite, big_platforms[player.num_of_platforms_-1].platform_right_ - 100, big_platforms[player.num_of_platforms_-1].platform_top_ - 60, big_platforms[player.num_of_platforms_-1].platform_left_, big_platforms[player.num_of_platforms_-1].platform_right_));
        else if(rand() % 101 < 25 && j > 1)
            bats.push_back(BatsyEnemyClass(batsy_sprite,
                                          sonic_sprite,
                                           big_platforms[player.num_of_platforms_-1].platform_right_ - 100,
                                            big_platforms[player.num_of_platforms_-1].platform_top_ - 76,
                                             big_platforms[player.num_of_platforms_-1].platform_left_,
                                              big_platforms[player.num_of_platforms_-1].platform_right_));
    }

    //stairs to level 0
    for(int j = 0 ; j > -6; j--){
        big_platforms.push_back(BigPlatform(platform_distance*j,level_1_height - j*platform_height_offset,
                                            8 + rand() % 3, platform_sprite_level_1, 2));
        player.num_of_platforms_++;
    }

    //level 0 again - height 500 - this is gonna be a special area at some point
    big_platforms.push_back(BigPlatform(platform_distance*(-7), fixed_platform_height, 25, platform_sprite_level_1, 2));
    player.num_of_platforms_++;

    witches.push_back(WitchEnemyClass(witch_sprite,
                                      poison_sprite,
                                      gold_sprite,
                                       big_platforms[player.num_of_platforms_-1].platform_right_ - 100,
                                        big_platforms[player.num_of_platforms_-1].platform_top_ - 108,
                                         big_platforms[player.num_of_platforms_-1].platform_left_,
                                          big_platforms[player.num_of_platforms_-1].platform_right_));


    //stairs to level 2
    for(int j = 0 ; j > -6; j--){
        big_platforms.push_back(BigPlatform(platform_distance*j,level_1_height + j*platform_height_offset,
                                            8 + rand() % 3, platform_sprite_level_1, 4));
        player.num_of_platforms_++;
    }

    for(int j = -4; j < 1; j++){
        big_platforms.push_back(BigPlatform(platform_distance*j,level_1_height + (-6)*platform_height_offset + -(j+4)*platform_height_offset,
                                            8 + rand() % 3, platform_sprite_level_1, 4));
        player.num_of_platforms_++;
    }

    //level 2 - height -1600
    int level_2_height = level_1_height - 10*platform_height_offset;
    big_platforms.push_back(BigPlatform(platform_distance, level_2_height, 25, platform_sprite_level_1, 4));
    player.num_of_platforms_++;

    witches.push_back(WitchEnemyClass(witch_sprite,
                                      poison_sprite,
                                      gold_sprite,
                                       big_platforms[player.num_of_platforms_-1].platform_right_ - 100,
                                        big_platforms[player.num_of_platforms_-1].platform_top_ - 108,
                                         big_platforms[player.num_of_platforms_-1].platform_left_,
                                          big_platforms[player.num_of_platforms_-1].platform_right_));

    //2050
    for(int j = 1; j < 6; j++){
        big_platforms.push_back(BigPlatform(2450 + platform_distance/2.5*(pow((-1),j)),
                                            -1600 - j*platform_height_offset , 7 + rand() % 3, platform_sprite_level_1, 5));
        player.num_of_platforms_++;
    }


    big_platforms.push_back(BigPlatform(-platform_distance, -1600 - 5*platform_height_offset, 50, platform_sprite_level_1, 5));
    player.num_of_platforms_++;

    std::cout << "plat num: " << player.num_of_platforms_ << std::endl;
    std::cout << "plat num: " << -1600 - 5*platform_height_offset << std::endl;

}
#endif // INIT_PLATFORMS_HPP
