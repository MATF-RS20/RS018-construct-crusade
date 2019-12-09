#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
double VEL = 1;

//the robots class
class PlayerClass{
public:

    PlayerClass(Sprite sprite, double x_pos, double y_pos){
        this->sprite_ = sprite;

        //default player position
        x_pos_ = x_pos;
        y_pos_ = y_pos;
    }
    //gain velocity if a button is pressed
    void update(bool player_up,bool player_down,bool player_right,bool player_left){
        if(player_up){
            y_vel_ = -VEL;
        }
        if(player_down){
            y_vel_ = VEL;
        }
        if(!player_up && !player_down){
            y_vel_ = 0;
        }
        if(player_left){
            x_vel_ = -VEL;
        }
        if(player_right){
            x_vel_ = VEL;
        }
        if(!player_left && !player_right){
            x_vel_ = 0;
        }
    }
Sprite sprite_;
double x_vel_;
double y_vel_;
double x_pos_;
double y_pos_;
};

int main(){
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1200, 600), "SFML window");
    Texture constructTex;
    constructTex.loadFromFile("assets/images/roboto100x100.png");
    Sprite constructSprite(constructTex);
    constructSprite.getTextureRect();
    bool player_right, player_left, player_up, player_down;

    PlayerClass player(constructSprite, 0, 0);

   //Zapocni glavnu petlju
    while (window.isOpen())
    {

        //Reaguj na dogadjaje
        sf::Event event;
        while (window.pollEvent(event))
        {
            // ako zatvoris prozor izadji
            if (event.type == sf::Event::Closed)
                window.close();

        }
        //detect an arrow key press
        if(Keyboard::isKeyPressed(Keyboard::Right))
            player_right = true;

        if(Keyboard::isKeyPressed(Keyboard::Left))
            player_left = true;

        if(Keyboard::isKeyPressed(Keyboard::Up))
            player_up = true;

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
        player.update(player_up, player_down, player_right, player_left);

        //Clear a window with a certain color
        window.clear(Color(45, 145, 223));


        //move the sprite
        player.sprite_.move(Vector2f(player.x_vel_, player.y_vel_));


        // Nacrtaj igraca
        window.draw(player.sprite_);

        // Azuriraj prikaz prozora
        window.display();
    }

    return 0;
}
