#ifndef INIT_PLATFORMS_LEVEL_2_HPP
#define INIT_PLATFORMS_LEVEL_2_HPP

void init_platforms_level_2(std::vector<BigPlatform> &big_platforms, PlayerClass &player, Sprite &platform_sprite){

    int platform_distance = 1000;
    int platform_height = -400;
    //int platform_height_offset = 140;


    big_platforms.push_back(BigPlatform(0, platform_height, 10, platform_sprite));
    player.num_of_platforms_++;

    //heights = -1200, -1800
    platform_height -= 800;
    for(int i = 1; i < 3; i++){
        big_platforms.push_back(BigPlatform(300, platform_height, 7, platform_sprite));
        platform_height -= 600;
        player.num_of_platforms_++;
    }

    //heights -400, -800, .. , -1600
    platform_height = -400;
    for(int i = 1; i < 5; i++){
        big_platforms.push_back(BigPlatform(platform_distance, platform_height*i, 9, platform_sprite));
        player.num_of_platforms_++;
        //width = 2400, hight = -1200
        if(i == 3)
        {
            big_platforms.push_back(BigPlatform(platform_distance*2.4, platform_height*i, 6, platform_sprite));
            player.num_of_platforms_++;
        }
    }

    //heights = -600, -1000, -1400
    //width = 1800
    for(int i = 1; i < 4; i++){
        platform_height -= 200;
        big_platforms.push_back(BigPlatform(platform_distance*1.8, platform_height, 7, platform_sprite));
        platform_height -= 200;
        player.num_of_platforms_++;
    }

    //middle platform
    //width = 1000
    //height = -2000
    big_platforms.push_back(BigPlatform(platform_distance, platform_height-400, 10, platform_sprite));
    player.num_of_platforms_++;


    platform_height = -2200;
    //width = 500, 1500
    for(int i = 0; i < 2; i++)
    {
        big_platforms.push_back(BigPlatform(platform_distance*(i+0.6), platform_height, 7, platform_sprite));
        player.num_of_platforms_++;
    }

    platform_height = -2420;
    big_platforms.push_back(BigPlatform(platform_distance*2.1, platform_height, 7, platform_sprite));
    player.num_of_platforms_++;
    for(int i = 0; i < 2; i++)
    {
        big_platforms.push_back(BigPlatform(platform_distance+100, platform_height, 6, platform_sprite));
        platform_height -= 400;
        player.num_of_platforms_++;
    }


    platform_height = -2650;
    for(int i = 0; i < 2; i++)
    {
        big_platforms.push_back(BigPlatform(platform_distance*(i+0.6), platform_height, 7, platform_sprite));
        player.num_of_platforms_++;
    }

    big_platforms.push_back(BigPlatform(platform_distance*2.3, platform_height-130, 7, platform_sprite));
    player.num_of_platforms_++;

    //Special path that leads to the gate
    big_platforms.push_back(BigPlatform(700, -3000 , 4, platform_sprite));
    player.num_of_platforms_++;

    big_platforms.push_back(BigPlatform(200, -3150, 5, platform_sprite));
    player.num_of_platforms_++;

    big_platforms.push_back(BigPlatform(750, -3300, 15, platform_sprite));
    player.num_of_platforms_++;

    //Another part of level 2

    platform_height = -3300;
    for(int i = 0; i < 2; i++)
    {
        big_platforms.push_back(BigPlatform((platform_distance-550)+(i*1040), platform_height-200, 5, platform_sprite));
        player.num_of_platforms_++;
    }

    platform_height = -3500;
    for(int i = 0; i < 2; i++)
    {
        big_platforms.push_back(BigPlatform(250+(i*1400), platform_height-200, 5, platform_sprite));
        player.num_of_platforms_++;
    }

    platform_height = -3700;
    for(int i = 0; i < 2; i++)
    {
        big_platforms.push_back(BigPlatform(0+(i*1950), platform_height-200, 4, platform_sprite));
        player.num_of_platforms_++;
    }

    platform_height = -3900;
    for(int i = 0; i < 2; i++)
    {
        big_platforms.push_back(BigPlatform(350+(i*1000), platform_height-200, 8, platform_sprite));
        player.num_of_platforms_++;
    }

    big_platforms.push_back(BigPlatform(920, -4300, 4, platform_sprite));
    player.num_of_platforms_++;





    std::cout << "plat num: " << player.num_of_platforms_ << std::endl;

}
#endif // INIT_PLATFORMS_HPP
