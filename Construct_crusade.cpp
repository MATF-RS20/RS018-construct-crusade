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

//TODO maybe seporate this into a hpp file
void draw_player_hp_mp(RenderWindow &window, PlayerClass &player, Sprite hp_sprite){

        //we draw the hp bar propartionally to the amount of hp left
        hp_sprite.setTextureRect(IntRect(8, 14, 64*player.construct_hp_/100.0, 9));
        hp_sprite.setScale(2, 2);
        hp_sprite.setPosition(player.sprite_.getPosition().x - window_width/2 + 16, player.sprite_.getPosition().y - 0.62*window_height);
        window.draw(hp_sprite);

        hp_sprite.setTextureRect(IntRect(8, 0, 64*player.construct_mp_/100.0, 9));
        hp_sprite.setScale(2, 2);
        hp_sprite.setPosition(player.sprite_.getPosition().x - window_width/2 + 16, player.sprite_.getPosition().y - 0.58*window_height);
        window.draw(hp_sprite);

        hp_sprite.setTextureRect(IntRect(0, 42, 80, 9));
        hp_sprite.setScale(2, 2);
        hp_sprite.setPosition(player.sprite_.getPosition().x - window_width/2, player.sprite_.getPosition().y - 0.62*window_height);
        window.draw(hp_sprite);

        hp_sprite.setTextureRect(IntRect(0, 54, 80, 9));
        hp_sprite.setScale(2, 2);
        hp_sprite.setPosition(player.sprite_.getPosition().x - window_width/2, player.sprite_.getPosition().y - 0.58*window_height);
        window.draw(hp_sprite);
}

void draw_imp_hp(RenderWindow &window,EnemyClass &imp_1,Sprite hp_sprite){

        if(imp_1.imp_hp_ > 0){
            hp_sprite.setTextureRect(IntRect(0, 65, 1 + 110*imp_1.imp_hp_/100.0, 8));
            hp_sprite.setScale(0.6, 1);
            hp_sprite.setPosition(imp_1.sprite_.getPosition().x, imp_1.sprite_.getPosition().y - 20);
            window.draw(hp_sprite);
        }
        hp_sprite.setTextureRect(IntRect(0, 81, 112, 8));
        hp_sprite.setScale(0.6, 1);
        hp_sprite.setPosition(imp_1.sprite_.getPosition().x, imp_1.sprite_.getPosition().y - 20);
        window.draw(hp_sprite);

}

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
    construct_tex.loadFromFile("assets/images/roboto_walk_idle_jump_laser_RIP_2.png");
    Sprite construct_sprite(construct_tex);
    construct_sprite.setTextureRect(IntRect(131, 50, 11, 25));
    // 1 - move left, 2 - move right, 4 - move up, 8 - move down
    int construct_move = 0;
    bool RIP_construct = false;

    //plasma sprite - for jumping
    Sprite plasma_booster_sprite(construct_tex);

    //laser sprite - for disintegrating
    Sprite laser_sprite(construct_tex);

    bool laser_hit_ind = false;

    //making a player object
    PlayerClass player(laser_sprite, plasma_booster_sprite, construct_sprite, 0, 400);

    //health and mana bars
    Texture hp_tex;
    hp_tex.loadFromFile("assets/images/hp_mp_bars.png");
    Sprite hp_sprite(hp_tex);

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

    EnemyClass imp_1(imp_sprite, fireball_sprite, 1000, 391);

    //so the fireball hits only once
    bool fireball_attack_ind = true;

    //these threads do all the animation calculations - yes i said THREADS... IM A REAL PROGRAMMER!
    //create a thread asign a function and an object to the thread
    sf::Thread imp_thread(&EnemyClass::Animation, &imp_1);
    //start the thread
    imp_thread.launch();

    sf::Thread cunstruct_thread(&PlayerClass::Animation, &player);
    cunstruct_thread.launch();

    //for recovering mana
    sf::Thread mana_thread(&PlayerClass::mana_recovery, &player);

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
                    }if(event.key.code == sf::Keyboard::E){
                        if(player.construct_mp_ == 100){
                            player.laser_ = true;
                            laser_hit_ind = true;
                            player.construct_mp_ = 0;
                            mana_thread.launch();
                        }

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



        //draw construct based on the keys pressed - draw the corresponding animation
        if(!RIP_construct){

            //let the player know if the key has been pressed
            player.update(construct_move, big_platforms);

            //here we center the view on the player
            view.setCenter(Vector2f(player.sprite_.getPosition().x, player.sprite_.getPosition().y - window_height/8));
            window.setView(view);

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

            if(player.laser_){
                player.sprite_.setTextureRect(player.rectangles_laser_[7 + player.rectangles_index_laser_ % 2]);
            }

            if(player.construct_hp_ <= 0){
             player.sprite_.setTextureRect(player.rectangles_death_[player.rectangles_index_death_]);

             if(player.rectangles_index_death_ == 10){
                RIP_construct = true;
                player.construct_mp_ = 0.0;
             }
        }
            window.draw(player.sprite_);
        }


        draw_player_hp_mp(window, player, hp_sprite);

        if(player.laser_){
            player.laser_sprite_.setTextureRect(player.rectangles_laser_[player.rectangles_index_laser_]);
            player.laser_sprite_.setPosition(player.sprite_.getPosition().x + 56, player.sprite_.getPosition().y + 36);
            player.laser_sprite_.setScale(2.5, 4);
            window.draw(player.laser_sprite_);

        }


        //TODO platforms and creatures are level specific they should be encapsulated
        if(level == 1){
        //draw platforms
        for(auto bp : big_platforms){
                for(auto plat : bp.platforms_)
                    window.draw(plat.sprite_);
        }


        //draw the little imp bastard
        window.draw(imp_1.sprite_);

        draw_imp_hp(window, imp_1, hp_sprite);

        //attack phase checker
        if(player.sprite_.getPosition().x > imp_1.sprite_.getPosition().x - 400 && player.sprite_.getPosition().x < imp_1.sprite_.getPosition().x + 400 && imp_1.move_phase_ != 8){
            if(player.sprite_.getPosition().x < imp_1.sprite_.getPosition().x){
                imp_1.facing_left_ = true;
        }
            else{
                imp_1.facing_left_ = false;
                }
            imp_1.attacking_ = true;

        }else{
            imp_1.attacking_ = false;
        }

        if(imp_1.attacking_){
            window.draw(imp_1.fireball_sprite_);
        }


        //fireball collision
        if(imp_1.rectangles_index_attack_ == 0){
                    fireball_attack_ind = true;
                }

        //patching until i implementa a destructor
        if(imp_1.move_phase_ == 8){
            fireball_attack_ind = false;
        }

        if(imp_1.fireball_sprite_.getGlobalBounds().intersects(player.sprite_.getGlobalBounds())){
            if(fireball_attack_ind && !RIP_construct){
                    fireball_attack_ind = false;
                    player.construct_hp_ -= 10;
                    if(player.construct_hp_ < 0)
                        player.construct_hp_ = 0;
                }
            }

        //laser collision
        if(player.laser_){
            if(player.laser_sprite_.getGlobalBounds().intersects(imp_1.sprite_.getGlobalBounds())){
                    //if we hit the imp reduce his hp
                    if(laser_hit_ind){
                        imp_1.imp_hp_ -= 10;
                        laser_hit_ind = false;
                    }
            }
        }



        }//first level end
        else if(level == 2){
            std::cout << "Comming soon! A whole new level! new enemies! new puzzles to solve! hazza!" << std::endl;
        }

        window.display();
    }//while loop

    return 0;
}



