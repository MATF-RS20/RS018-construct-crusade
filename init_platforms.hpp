#ifndef INIT_PLATFORMS_HPP
#define INIT_PLATFORMS_HPP

void init_platforms(std::vector<BigPlatform> &big_platforms, PlayerClass &player, Sprite &platform_sprite, std::vector<EnemyClass> &imps, Sprite imp_sprite, Sprite fireball_sprite){

    int platform_distance = 800;
    int fixed_platform_height = 500;
    int platform_height_offset = 140;

    //imp initialization
    imps.push_back(EnemyClass(imp_sprite, fireball_sprite, 0, 440));
    imps.push_back(EnemyClass(imp_sprite, fireball_sprite, 50, 440));

    //level 0 - height 500 - width from -4800 to 4000
    for(int j = -6; j < 6; j++){
        big_platforms.push_back(BigPlatform(platform_distance*j, fixed_platform_height, 8 + rand() % 3, platform_sprite));
        player.num_of_platforms_++;
    }

    //stairs to level 1
    for(int j = 1; j < 6; j++){
        big_platforms.push_back(BigPlatform(6.3*platform_distance + platform_distance/2.5*(pow((-1),j)), fixed_platform_height - j*platform_height_offset , 7 + rand() % 3, platform_sprite));
        player.num_of_platforms_++;
    }

    //level 1 - height -200 - width from 4000 to 0
    int level_1_height = fixed_platform_height - 5*platform_height_offset;
    for(int j = 5; j > 0; j--){
        big_platforms.push_back(BigPlatform(platform_distance*j, level_1_height, 8 + rand() % 3, platform_sprite));
        player.num_of_platforms_++;
    }

    //stairs to level 0
    for(int j = 0 ; j > -6; j--){
        big_platforms.push_back(BigPlatform(platform_distance*j,level_1_height - j*platform_height_offset, 8 + rand() % 3, platform_sprite));
        player.num_of_platforms_++;
    }

    //level 0 again - height 500 - this is gonna be a special area at some point
    big_platforms.push_back(BigPlatform(platform_distance*(-7), fixed_platform_height, 25, platform_sprite));
    player.num_of_platforms_++;

    //stairs to level 2
    for(int j = 0 ; j > -6; j--){
        big_platforms.push_back(BigPlatform(platform_distance*j,level_1_height + j*platform_height_offset, 8 + rand() % 3, platform_sprite));
        player.num_of_platforms_++;
    }

    for(int j = -4; j < 1; j++){
        big_platforms.push_back(BigPlatform(platform_distance*j,level_1_height + (-6)*platform_height_offset + -(j+4)*platform_height_offset, 8 + rand() % 3, platform_sprite));
        player.num_of_platforms_++;
    }

    //level 2 - height -1600
    int level_2_height = level_1_height - 10*platform_height_offset;
    big_platforms.push_back(BigPlatform(platform_distance, level_2_height, 25, platform_sprite));
    player.num_of_platforms_++;

    //TODO finis making platforms

    std::cout << "plat num: " << player.num_of_platforms_ << std::endl;

}
#endif // INIT_PLATFORMS_HPP
