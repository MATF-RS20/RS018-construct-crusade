#ifndef INIT_PLATFORMS_LEVEL_2_HPP
#define INIT_PLATFORMS_LEVEL_2_HPP

void init_platforms_level_2(std::vector<BigPlatform> &big_platforms, PlayerClass &player, Sprite &platform_sprite){

    int platform_distance = 800;
    int fixed_platform_height = -400;
    int platform_height_offset = 140;
    int coef = -1;

    big_platforms.push_back(BigPlatform(0, -400, 10, platform_sprite));
    player.num_of_platforms_++;

    //level 0 - height 500 - width from -4800 to 4000
    for(int j = -9; j < 9; j++){
        if(rand()%2 == 0)
            coef = 1;
        else coef = -1;
        platform_distance = platform_distance+(150+(rand()%100))*coef;
        fixed_platform_height = fixed_platform_height-(150+(rand()%100));
        big_platforms.push_back(BigPlatform(platform_distance, fixed_platform_height, 8 + rand() % 3, platform_sprite));
        player.num_of_platforms_++;
        std::cout << coef << std::endl;
    }


    std::cout << "plat num: " << player.num_of_platforms_ << std::endl;

}
#endif // INIT_PLATFORMS_HPP
