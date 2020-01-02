#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "PlayerClass.hpp"
#include "EnemyClass.hpp"
#include "BigPlatform.hpp"
#include "DrawTrails.hpp"


using namespace sf;
double window_height = 600;
double window_width = 1200;
Clock bigTime;

int main(){

    //create the main window
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Construct Crusade!");

    //define a view
    sf::View view(sf::FloatRect(0.0, 0.0, window_width, window_height));

    //activate it
    window.setView(view);

    srand (time(NULL));
    //generate secret number between 0 and 99: rand() % 100

    //the construct - our protagonist
    Texture construct_tex;
    construct_tex.loadFromFile("assets/images/roboto_walk_idle_jump_laser_5.png");
    Sprite construct_sprite(construct_tex);
    construct_sprite.setTextureRect(IntRect(131, 50, 11, 25));
    // 1 - move left, 2 - move right, 4 - move up, 8 - move down
    int construct_move = 0;

    //plasma sprite - for jumping
    Sprite plasma_booster_sprite(construct_tex);

    //laser sprite - for disintegrating
    Sprite laser_sprite(construct_tex);

    //making a player object
    PlayerClass player(laser_sprite, plasma_booster_sprite, construct_sprite, 0, 400);

    //background element
    Texture background;
    background.loadFromFile("assets/images/sky.png");

    Texture background_2;
    background_2.loadFromFile("assets/images/skyReverse.png");

    Sprite backgroundSprite(background);
    backgroundSprite.getTextureRect();
    backgroundSprite.scale(1, window_height/backgroundSprite.getLocalBounds().height);

    Sprite backgroundSprite_2(background_2);
    backgroundSprite_2.getTextureRect();
    backgroundSprite_2.scale(1, window_height/backgroundSprite.getLocalBounds().height);

    //platform initialization
    std::vector<BigPlatform> big_platforms;
    int platform_distance = 800;
    int fixed_platform_height = 500;
    int platform_height_offset = 50;

    Texture platform_tex;
    platform_tex.loadFromFile("assets/images/tileset.png");

    Sprite platform_sprite(platform_tex);

    for(int j = 0; j < 10; j++){
        big_platforms.push_back(BigPlatform(platform_distance*j, fixed_platform_height - (j%3)*platform_height_offset, 10, platform_sprite));
    }

    //imp initialization
    Texture imp;
    imp.loadFromFile("assets/images/imp.png");

    Sprite imp_sprite(imp);
    Sprite fireball_sprite(imp);

    fireball_sprite.setTextureRect(IntRect(10, 211, 18, 15));
    imp_sprite.setTextureRect(IntRect(23, 377, 1, 1));

    EnemyClass imp_1(imp_sprite, fireball_sprite, 500, 441);

    //these threads do all the animation calculations - yes i said THREADS... IM A REAL PROGRAMMER!
    //create a thread asign a function and an object to the thread
    sf::Thread imp_thread(&EnemyClass::Animation, &imp_1);
    //start the thread
    imp_thread.launch();

    sf::Thread cunstruct_thread(&PlayerClass::Animation, &player);
    cunstruct_thread.launch();

    //a little audio for out little game
    sf::Music music;
    if (!music.openFromFile("assets/music/bg_fa.ogg")){
        std::cout << "we have failed at music" << std::endl; // error
    }
    music.setVolume(0.3f);
    music.setLoop(true);
    music.play();

    //soon there will be another
    int level = 1;

    //start the main loop
    while (window.isOpen())
    {

        //react to an event
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed){

                    if(event.key.code == sf::Keyboard::Escape){
                        window.close();
                    }
                    if(event.key.code == sf::Keyboard::A){
                        construct_move |= 1;
                    }
                    if(event.key.code == sf::Keyboard::D){
                        construct_move |= 2;
                    }
                    if(event.key.code == sf::Keyboard::W){
                        construct_move |= 4;
                    }
                    if(event.key.code == sf::Keyboard::S){
                        construct_move |= 8;
                    }
            }//key pressed
            if (event.type == sf::Event::KeyReleased){

                    if(event.key.code == sf::Keyboard::A){
                        construct_move ^= 1;
                    }
                    if(event.key.code == sf::Keyboard::D){
                        construct_move ^= 2;
                    }
                    if(event.key.code == sf::Keyboard::W){
                        construct_move ^= 4;
                    }
                    if(event.key.code == sf::Keyboard::S){
                        construct_move ^= 8;
                    }
            }//key released

            if (event.type == sf::Event::Resized)
                {
                // update the view to the new size of the window
                sf::FloatRect visibleArea(0.0, 0.0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
                }

        }
        window.clear(Color(161, 242, 236));

        //drawing the background
        for(int i = 0; i < window_width/backgroundSprite.getGlobalBounds().width; i++){
                backgroundSprite.setPosition(i*backgroundSprite.getGlobalBounds().width + (player.sprite_.getPosition().x - window_width/2), 0);
                window.draw(backgroundSprite);
        }
        for(int i = 0; i < window_width/backgroundSprite.getGlobalBounds().width; i++){
                backgroundSprite_2.setPosition(i*backgroundSprite_2.getGlobalBounds().width + (player.sprite_.getPosition().x - window_width/2), window_height);
                window.draw(backgroundSprite_2);
        }

        //let the player know if the key has been pressed
        player.update(construct_move, big_platforms);

        //here we center the view on the player
        view.setCenter(Vector2f(player.sprite_.getPosition().x, player.sprite_.getPosition().y - window_height/8));
        window.setView(view);

        //draw construct based on the keys pressed - draw the corresponding animation
        if(!player.on_ground_ && (construct_move & 1)){

            player.sprite_.setTextureRect(IntRect(433, 0, 9, 25));
            //this functions draws the little animated trail when the robot is jumping
            //dont look at this function implementation - its sickening
            draw_left_trail(player, window);

        }
        else if(!player.on_ground_ && (construct_move & 2)){

            player.sprite_.setTextureRect(IntRect(483, 0, 9, 25));
            draw_right_trail(player, window);

        }
        else if(!player.on_ground_ && !((construct_move & 1) || (construct_move & 2))){

            player.sprite_.setTextureRect(IntRect(477, 50, 21, 25));
            draw_middle_trail(player, window);

        }
        else if(construct_move & 2)
            player.sprite_.setTextureRect(player.rectanglesRight_[player.rectangles_index_]);
        else if(construct_move & 1){
            player.sprite_.setTextureRect(player.rectanglesLeft_[player.rectangles_index_]);
        }
        else{
            player.sprite_.setTextureRect(player.rectanglesIdle_[player.rectangles_index_idle_]);
        }

        if(player.sprite_.getPosition().y > 750){
            std::cout << "Congratulations! you died!" << std::endl;
            player.sprite_.setPosition(0, 400);
        }

        window.draw(player.sprite_);
        player.laser_sprite_.setTextureRect(player.rectangles_laser_[player.rectangles_index_laser_]);
        player.laser_sprite_.setPosition(player.sprite_.getPosition().x + 100, player.sprite_.getPosition().y + 50);
        player.laser_sprite_.setScale(4, 4);
        //window.draw(player.laser_sprite_);


        //TODO platforms and creatures are level specific they should be encapsulated
        if(level == 1){
        //draw platforms
        for(auto bp : big_platforms){
                for(auto plat : bp.platforms_)
                    window.draw(plat.sprite_);
        }

        //fireball collision
        if(imp_1.fireball_sprite_.getGlobalBounds().intersects(player.sprite_.getGlobalBounds())){
                //TODO actual collision
            }

        //draw the little imp bastard
        window.draw(imp_1.sprite_);
        //window.draw(imp_1.fireball_sprite_);

        }//first level end
        else if(level == 2){
            std::cout << "Comming soon! A whole new level! new enemies! new puzzles to solve! hazza!" << std::endl;
        }

        window.display();
    }//while loop

    return 0;
}



