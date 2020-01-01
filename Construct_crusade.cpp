#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "PlayerClass.hpp"
#include "EnemyClass.hpp"
#include "BigPlatform.hpp"

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

    //the construct - our protagonist
    Texture construct_tex;
    construct_tex.loadFromFile("assets/images/roboto_walk_idle_jump_4.png");
    Sprite construct_sprite(construct_tex);
    construct_sprite.setTextureRect(IntRect(131, 50, 11, 25));
    bool player_right, player_left, player_up, player_down;

    //plasma sprite - for jumping
    Sprite plasma_booster_sprite(construct_tex);

    //making a player object
    PlayerClass player(plasma_booster_sprite, construct_sprite, 0, 400);

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
    int platform_distance = 750;
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
    if (!music.openFromFile("assets/music/bg_pop.ogg")){
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

        //detect an arrow key press - i might find a better way for this logic
        if(Keyboard::isKeyPressed(Keyboard::Right)){
            player_right = true;
        }

        if(Keyboard::isKeyPressed(Keyboard::Left)){
            player_left = true;
        }

        if(Keyboard::isKeyPressed(Keyboard::Up)){
            player_up = true;
        }

        if(Keyboard::isKeyPressed(Keyboard::Down))
            player_down = true;

        if(!Keyboard::isKeyPressed(Keyboard::Right))
            player_right = false;

        if(!Keyboard::isKeyPressed(Keyboard::Left))
            player_left = false;

        if(!Keyboard::isKeyPressed(Keyboard::Up))
            player_up = false;

        if(!Keyboard::isKeyPressed(Keyboard::Down))
            player_down = false;

        //let the player know if the key has been pressed
        player.update(player_up, player_down, player_right, player_left, big_platforms);

        //here we center the view on the player
        view.setCenter(Vector2f(player.sprite_.getPosition().x, player.sprite_.getPosition().y - window_height/8));
        window.setView(view);

        //draw construct based on the keys pressed - draw the corresponding animation
        if(player.jumping_ && player_left){
            //TODO refactor this part of the code
            player.sprite_.setTextureRect(IntRect(433, 0, 9, 25));
            player.plasma_sprite_.setTextureRect(player.rectangles_plasma_booster_[1]);
            player.plasma_sprite_.setScale(4, 4);
            player.plasma_sprite_.setPosition(player.sprite_.getPosition().x + 4, player.sprite_.getPosition().y + player.sprite_.getGlobalBounds().height - 4);
            window.draw(player.plasma_sprite_);


            player.plasma_sprite_.move(0, 4);
            player.plasma_sprite_.setTextureRect(player.rectangles_plasma_booster_[player.rectangles_index_jump_]);
            window.draw(player.plasma_sprite_);

            player.plasma_sprite_.move(4, 0);
            player.plasma_sprite_.setTextureRect(player.rectangles_plasma_booster_[player.rectangles_index_jump_+1]);
            window.draw(player.plasma_sprite_);

            player.plasma_sprite_.move(8, 0);
            player.plasma_sprite_.setTextureRect(player.rectangles_plasma_booster_[player.rectangles_index_jump_]);
            window.draw(player.plasma_sprite_);

            player.plasma_sprite_.move(8, 0);
            player.plasma_sprite_.setTextureRect(player.rectangles_plasma_booster_[player.rectangles_index_jump_]);
            window.draw(player.plasma_sprite_);

            player.plasma_sprite_.move(4, 0);
            player.plasma_sprite_.setTextureRect(player.rectangles_plasma_booster_[player.rectangles_index_jump_+2]);
            window.draw(player.plasma_sprite_);

            player.plasma_sprite_.move(4, 0);
            player.plasma_sprite_.setTextureRect(player.rectangles_plasma_booster_[player.rectangles_index_jump_+1]);
            window.draw(player.plasma_sprite_);

        }
        else if(player.jumping_ && player_right){
            player.sprite_.setTextureRect(IntRect(483, 0, 9, 25));

            player.plasma_sprite_.setTextureRect(player.rectangles_plasma_booster_[2]);
            player.plasma_sprite_.setScale(4, 4);
            player.plasma_sprite_.setPosition(player.sprite_.getPosition().x , player.sprite_.getPosition().y + player.sprite_.getGlobalBounds().height - 4);
            window.draw(player.plasma_sprite_);


            player.plasma_sprite_.move(0, 4);
            player.plasma_sprite_.setTextureRect(player.rectangles_plasma_booster_[player.rectangles_index_jump_]);
            window.draw(player.plasma_sprite_);

            player.plasma_sprite_.move(4, 0);
            player.plasma_sprite_.setTextureRect(player.rectangles_plasma_booster_[player.rectangles_index_jump_+1]);
            window.draw(player.plasma_sprite_);

            player.plasma_sprite_.move(8, 0);
            player.plasma_sprite_.setTextureRect(player.rectangles_plasma_booster_[player.rectangles_index_jump_]);
            window.draw(player.plasma_sprite_);

            player.plasma_sprite_.move(8, 0);
            player.plasma_sprite_.setTextureRect(player.rectangles_plasma_booster_[player.rectangles_index_jump_]);
            window.draw(player.plasma_sprite_);

            player.plasma_sprite_.move(4, 0);
            player.plasma_sprite_.setTextureRect(player.rectangles_plasma_booster_[player.rectangles_index_jump_+2]);
            window.draw(player.plasma_sprite_);

            player.plasma_sprite_.move(4, 0);
            player.plasma_sprite_.setTextureRect(player.rectangles_plasma_booster_[player.rectangles_index_jump_+1]);
            window.draw(player.plasma_sprite_);


        }
        else if(player.jumping_ && !player_left && !player_right){
            player.sprite_.setTextureRect(IntRect(477, 50, 21, 25));

            player.plasma_sprite_.setTextureRect(player.rectangles_plasma_booster_[0]);
            player.plasma_sprite_.setScale(4, 4);
            player.plasma_sprite_.setPosition(player.sprite_.getPosition().x + 24, player.sprite_.getPosition().y + player.sprite_.getGlobalBounds().height);
            window.draw(player.plasma_sprite_);

            player.plasma_sprite_.move(0, 4);
            player.plasma_sprite_.setTextureRect(player.rectangles_plasma_booster_[player.rectangles_index_jump_]);
            window.draw(player.plasma_sprite_);

            player.plasma_sprite_.move(4, 0);
            player.plasma_sprite_.setTextureRect(player.rectangles_plasma_booster_[player.rectangles_index_jump_+1]);
            window.draw(player.plasma_sprite_);

            player.plasma_sprite_.move(8, 0);
            player.plasma_sprite_.setTextureRect(player.rectangles_plasma_booster_[player.rectangles_index_jump_]);
            window.draw(player.plasma_sprite_);

            player.plasma_sprite_.move(8, 0);
            player.plasma_sprite_.setTextureRect(player.rectangles_plasma_booster_[player.rectangles_index_jump_]);
            window.draw(player.plasma_sprite_);

            player.plasma_sprite_.move(4, 0);
            player.plasma_sprite_.setTextureRect(player.rectangles_plasma_booster_[player.rectangles_index_jump_+2]);
            window.draw(player.plasma_sprite_);

            player.plasma_sprite_.move(8, 0);
            player.plasma_sprite_.setTextureRect(player.rectangles_plasma_booster_[player.rectangles_index_jump_+1]);
            window.draw(player.plasma_sprite_);
        }
        else if(player_right)
            player.sprite_.setTextureRect(player.rectanglesRight_[player.rectangles_index_]);
        else if(player_left){
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

        //TODO platforms and creatures are level specific they should be encapsulated
        if(level == 1){

        //draw platforms
        for(auto bp : big_platforms){
                for(auto plat : bp.platforms_)
                    window.draw(plat.sprite_);
        }

        //fireball collision
        if(imp_1.fireball_sprite_.getGlobalBounds().intersects(player.sprite_.getGlobalBounds())){
                    //std::cout << "Fire has collided: " << iz <<std::endl;
                    //iz++;
            }

        //draw the little imp bastard
        window.draw(imp_1.sprite_);
        //window.draw(imp_1.fireball_sprite_);
        }
        else if(level == 2){
            std::cout << "Comming soon! A whole new level! new enemies! new puzzles to solve! hazza!" << std::endl;
        }

        window.display();
    }//while loop

    return 0;
}



