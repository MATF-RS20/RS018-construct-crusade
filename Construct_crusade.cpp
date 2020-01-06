#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "PlayerClass.hpp"
#include "EnemyClass.hpp"
#include "BigPlatform.hpp"
#include "DrawTrails.hpp"
#include "Bars.hpp"
#include "Level_one.hpp"
#include "Level_two.hpp"
#include "init_platforms.hpp"
#include "CleopatraClass.hpp"
#include "init_platforms_level_2.hpp"

using namespace sf;
double window_height = 600;
double window_width = 1200;
bool RIP_construct = false;
bool shooting = false;
//so the laser hits only once
bool laser_hit_ind = false;
int level = 1;
//Clock random_clock;

int main(){
    //create the main window
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Construct Crusade!");

    //define a view
    sf::View view(sf::FloatRect(0.0, 0.0, window_width, window_height));

    //activate it
    window.setView(view);

    srand (time(NULL));
    //generate secret number between 0 and 99: rand() % 100

    //so our construct always moves the same - even on a slower/faster computer
    Clock uniform_move_clock;

    //the construct - our protagonist
    Texture construct_tex;
    construct_tex.loadFromFile("assets/images/roboto_walk_idle_jump_laser_RIP_shooting_5.png");
    Sprite construct_sprite(construct_tex);
    construct_sprite.setTextureRect(IntRect(131, 50, 11, 25));
    // 1 - move left, 2 - move right, 4 - move up, 8 - move down
    int construct_move = 0;

    //plasma sprite - for jumping
    Sprite plasma_booster_sprite(construct_tex);

    //laser sprite - for disintegrating
    Sprite laser_sprite(construct_tex);

    //construct shooting parameters
    Clock shooting_clock_main;
    float shooting_scaler = 0;
    Sprite shooting_sprite(construct_tex, IntRect(26, 152, 4, 4));

    //making a player object
    PlayerClass player(laser_sprite, plasma_booster_sprite, construct_sprite, 0, 400);

    //health and mana bars
    Texture hp_tex;
    hp_tex.loadFromFile("assets/images/hp_mp_bars.png");
    Sprite hp_sprite(hp_tex);

    sf::Thread cunstruct_thread(&PlayerClass::Animation, &player);
    cunstruct_thread.launch();

    //for recovering mana
    sf::Thread mana_thread(&PlayerClass::mana_recovery, &player);

    //background element
    Texture background;
    background.loadFromFile("assets/images/sky.png");

    Texture background_2;
    background_2.loadFromFile("assets/images/skyReverse.png");

    Sprite backgroundSprite(background);
    backgroundSprite.setScale(1, window_height/backgroundSprite.getLocalBounds().height);

    Sprite backgroundSprite_2(background_2);
    backgroundSprite_2.setScale(1, window_height/backgroundSprite.getLocalBounds().height);

    //platform initialization
    Texture platform_tex;
    platform_tex.loadFromFile("assets/images/tileset.png");
    Sprite platform_sprite(platform_tex);

    std::vector<BigPlatform> big_platforms;

    //imp initialization
    Texture imp;
    imp.loadFromFile("assets/images/imp.png");

    Sprite imp_sprite(imp, IntRect(23, 377, 1, 1));
    Sprite fireball_sprite(imp, IntRect(10, 211, 18, 15));

    std::vector<EnemyClass> imps;

    init_platforms(big_platforms, player, platform_sprite, imps, imp_sprite, fireball_sprite);

    EnemyClass imp_1(imp_sprite, fireball_sprite, 1000, 440);
    //these threads do all the animation calculations - yes i said THREADS... IM A REAL PROGRAMMER!
    //create a thread asign a function and an object to the thread
    sf::Thread imp_thread(&EnemyClass::Animation, &imp_1);
    //start the thread
    imp_thread.launch();

    //a little audio for our little game
    sf::Music music;
    if (!music.openFromFile("assets/music/bg_fa.ogg")){
        std::cout << "we have failed at music" << std::endl; // error
    }
    music.setVolume(0.3f);
    music.setLoop(true);
    music.play();

    //inicijalizacije za NIVO 2

    //Cleopatra initialization
    Texture cleo;
    cleo.loadFromFile("assets/images/cleopatra.png");
    Sprite cleo_sprite(cleo, IntRect(0,0,25,25));

    CleopatraClass cleopatra(cleo_sprite, 200, -500);

    sf::Thread cleo_thread(&CleopatraClass::Animation, &cleopatra);
    //start the thread
    cleo_thread.launch();

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
                    //we do a binery or to add 1 to our code
                    if(event.key.code == sf::Keyboard::A){
                        construct_move |= 1;
                    }
                    //here we add 2 if D is pressed - this works for multiple keys pressed
                    if(event.key.code == sf::Keyboard::D){
                        construct_move |= 2;
                    }
                    if(event.key.code == sf::Keyboard::W){
                        construct_move |= 4;
                    }
                    if(event.key.code == sf::Keyboard::S){
                        construct_move |= 8;
                    }if(event.key.code == sf::Keyboard::E){
                        if(player.construct_mp_ == 100 && player.on_ground_){
                            player.laser_ = true;
                            laser_hit_ind = true;
                            for(auto imp : imps){
                                imp.laser_hit_ind_ = true;
                            }
                            player.construct_mp_ = 0;
                            mana_thread.launch();
                        }

                    }if(event.key.code == sf::Keyboard::Q){
                        shooting = true;
                    }
            }//key pressed
            if (event.type == sf::Event::KeyReleased){
                    //with xor we want to remove 1 from our movement code
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
                    }if(event.key.code == sf::Keyboard::Q){
                        shooting = false;
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

        //drawing the background - if follows the player
        for(int i = 0; i < window_width/backgroundSprite.getGlobalBounds().width; i++){
                backgroundSprite.setPosition(i*backgroundSprite.getGlobalBounds().width + (player.sprite_.getPosition().x - window_width/2), player.sprite_.getPosition().y - window_height/2);
                window.draw(backgroundSprite);
        }
        for(int i = 0; i < window_width/backgroundSprite.getGlobalBounds().width; i++){
                backgroundSprite_2.setPosition(i*backgroundSprite_2.getGlobalBounds().width + (player.sprite_.getPosition().x - window_width/2), player.sprite_.getPosition().y + window_height/2);
                window.draw(backgroundSprite_2);
        }



        //draw construct based on the keys pressed - draw the corresponding animation
        if(!RIP_construct){

            //if we needed more time to call update function the unifomr time is bigger and so we walk faster
            //slow computers benefit the most from this, but fast computers slow down a bit - so its uniform
            float uniform_time = uniform_move_clock.getElapsedTime().asSeconds();
            //let the player know if the key has been pressed
            player.update(construct_move, big_platforms, uniform_time);
            uniform_move_clock.restart();

            //here we center the view on the player - when we animate the raptor we might add the sin when he slams the ground
            view.setCenter(Vector2f(player.sprite_.getPosition().x, player.sprite_.getPosition().y /*+ 4*sin(random_clock.getElapsedTime().asMilliseconds())*/));
            window.setView(view);

            //jumping animation
            if(!player.on_ground_ && (construct_move & 1) && !shooting){

                player.sprite_.setTextureRect(IntRect(433, 0, 9, 25));
                //this functions draws the little animated trail when the robot is jumping
                //dont look at this function implementation - its sickening
                draw_left_trail(player, window);

            }
            else if(!player.on_ground_ && (construct_move & 2) && !shooting){

                player.sprite_.setTextureRect(IntRect(483, 0, 9, 25));
                draw_right_trail(player, window);

            }
            else if(!player.on_ground_ && !((construct_move & 1) || (construct_move & 2)) && !shooting){

                player.sprite_.setTextureRect(IntRect(477, 50, 21, 25));
                draw_middle_trail(player, window);

            }
            //movement animation left - right - idle
            else if(construct_move & 2)
                player.sprite_.setTextureRect(player.rectanglesRight_[player.rectangles_index_]);
            else if(construct_move & 1){
                player.sprite_.setTextureRect(player.rectanglesLeft_[player.rectangles_index_]);
            }
            else{
                player.sprite_.setTextureRect(player.rectanglesIdle_[player.rectangles_index_idle_]);
            }

            //falling to your death
            if(player.sprite_.getPosition().y > 1750){
                player.construct_hp_ = 0;
            }
            //costruct animation while the laser is firing rectangles_laser_ index 7 and 8 represent the construct
            if(player.laser_){
                player.sprite_.setTextureRect(player.rectangles_laser_[9*(player.facing_left_) + 7 + player.rectangles_index_laser_ % 2]);
            }

            //death animation
            if(player.construct_hp_ <= 0){

                player.sprite_.setTextureRect(player.rectangles_death_[13*(player.facing_left_) + player.rectangles_index_death_]);
             //after the animation is done stop everything
                if(player.rectangles_index_death_ == 13){
                    RIP_construct = true;
                    player.construct_mp_ = 0.0;
                }
            }

            if(shooting){
                //draw the cunstruct while shooting - specail case left or right
                player.sprite_.setTextureRect(player.rectangles_shooting_[4*(player.facing_left_) + player.rectangles_index_shooting_]);
                //draw and move the plasma bullet
                shooting_scaler = shooting_clock_main.getElapsedTime().asSeconds();
                shooting_sprite.move(pow(-1, player.facing_left_)*1500*shooting_scaler, 0);
                shooting_clock_main.restart();
                if(player.rectangles_index_shooting_ == 1){
                    shooting_sprite.setPosition(player.sprite_.getPosition().x + 52 -(player.facing_left_)*60, player.sprite_.getPosition().y + 48);
                }
                shooting_sprite.setScale(4, 4);
                window.draw(shooting_sprite);

                for(auto imp : imps){
                    //check for collision with the imp
                    if(imp.first_hit_shooting_ && shooting_sprite.getGlobalBounds().intersects(imp.sprite_.getGlobalBounds())){
                            imp.imp_hp_ -= 10;
                            imp.first_hit_shooting_ = false;
                    }
                }
            }

            window.draw(player.sprite_);
        }

        //health and mana bars
        draw_player_hp_mp(window, player, hp_sprite);
        //laser animation
        if(player.laser_){
            player.laser_sprite_.setTextureRect(player.rectangles_laser_[9*(player.facing_left_) + player.rectangles_index_laser_]);
            player.laser_sprite_.setPosition(player.sprite_.getPosition().x + 56 - 685*(player.facing_left_), player.sprite_.getPosition().y + 36);
            player.laser_sprite_.setScale(2.5, 4);
            window.draw(player.laser_sprite_);
        }

    //deo specifican za svaki nivo
    if(level == 1){
        level_one(window, big_platforms, imp_1, player, hp_sprite, imps, shooting_sprite);

        //prelaz iz nivoa 1 u nivo 2
//        level = 2;
//        player.sprite_.setPosition(0, -500);
//        big_platforms.clear();
//
//        player.num_of_platforms_ = 0;
//        init_platforms_level_2(big_platforms, player, platform_sprite);
//
//        player.platform_index_ = 6;
//        player.platform_index_offset_ = 6;


    }
    else if(level == 2){

        level_two(window, big_platforms, player);

        window.draw(cleopatra.sprite_);
    }

    window.display();

    }//while loop

    return 0;
}



