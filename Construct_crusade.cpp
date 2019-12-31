#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "PlayerClass.hpp"
#include "EnemyClass.hpp"

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
    construct_tex.loadFromFile("assets/images/roboto_walk_idle_jump_2.png");
    Sprite construct_sprite(construct_tex);
    construct_sprite.setTextureRect(IntRect(131, 50, 11, 25));
    construct_sprite.getTextureRect();
    bool player_right, player_left, player_up, player_down;

    //plasma sprite
    Sprite plasma_booster_sprite(construct_tex);

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
    std::vector<PlatformClass> platforms;
    Texture platformTex;
    platformTex.loadFromFile("assets/images/tileset.png");
    Sprite platformSprite(platformTex);
    platformSprite.setTextureRect(IntRect(16, 16, 16, 16));

    Sprite platformSprite_middle(platformTex);
    platformSprite_middle.setTextureRect(IntRect(48, 16, 16, 16));

    Sprite platformSprite_left(platformTex);
    platformSprite_left.setTextureRect(IntRect(240, 224, 16, 16));

    Sprite platformSprite_right(platformTex);
    platformSprite_right.setTextureRect(IntRect(304, 224, 16, 16));

    //generate platforms
    for(int j = 0; j < 10; j++){

        platforms.push_back(PlatformClass(platformSprite_left, j*850, 500 - (j % 2)*50));

        for(int i = 1; i < 11; i++){
            platforms.push_back(PlatformClass(platformSprite_middle, 50*i + j*850, 500 - (j % 2)*50));
        }
        platforms.push_back(PlatformClass(platformSprite_right, 550 + j*850, 500 - (j % 2)*50));
    }

    Texture imp;
    imp.loadFromFile("assets/images/imp.png");

    Sprite impSprite(imp);
    Sprite fireballSprite(imp);
    impSprite.setTextureRect(IntRect(10, 211, 18, 15));

    EnemyClass imp1(impSprite, fireballSprite, 500, 441);

    sf::Thread thread(&EnemyClass::IdleAnimation, &imp1);

    thread.launch();

    sf::Thread threadIdlePlayer(&PlayerClass::IdleAnimation, &player);

    threadIdlePlayer.launch();

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
        player.update(player_up, player_down, player_right, player_left, platforms);

        //here we center the view on the player
        view.setCenter(Vector2f(player.sprite_.getPosition().x, player.sprite_.getPosition().y - window_height/8));
        window.setView(view);

        //draw construct based on the keys pressed - draw the corresponding animation
        if(player.jumping_ && player_left){
            player.sprite_.setTextureRect(IntRect(433, 0, 9, 25));
            player.plasma_sprite_.setTextureRect(player.rectangles_plasma_booster_[1]);
            player.plasma_sprite_.setScale(4, 4);
            player.plasma_sprite_.setPosition(player.sprite_.getPosition().x + 4, player.sprite_.getPosition().y + player.sprite_.getGlobalBounds().height - 4);
            window.draw(player.plasma_sprite_);
        }
        else if(player.jumping_ && player_right){
            player.plasma_sprite_.setTextureRect(player.rectangles_plasma_booster_[2]);
            player.plasma_sprite_.setScale(4, 4);
            player.plasma_sprite_.setPosition(player.sprite_.getPosition().x , player.sprite_.getPosition().y + player.sprite_.getGlobalBounds().height - 4);
            window.draw(player.plasma_sprite_);
            player.sprite_.setTextureRect(IntRect(483, 0, 9, 25));
        }
        else if(player.jumping_ && !player_left && !player_right){
            player.sprite_.setTextureRect(IntRect(477, 50, 21, 25));
            player.plasma_sprite_.setTextureRect(player.rectangles_plasma_booster_[0]);
            player.plasma_sprite_.setScale(4, 4);
            player.plasma_sprite_.setPosition(player.sprite_.getPosition().x + 24, player.sprite_.getPosition().y + player.sprite_.getGlobalBounds().height);
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
        window.draw(player.sprite_);


        //draw platforms
        for(auto plat : platforms){
            window.draw(plat.sprite_);
        }

        window.draw(imp1.sprite_);
        window.display();
    }

    return 0;
}


