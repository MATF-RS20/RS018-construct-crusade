#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
double VEL = 1;
double window_height = 600;
double window_width = 1200;

class GameObject{
public:
    GameObject(double x_pos, double y_pos) : x_pos_(x_pos), y_pos_(y_pos)
    {}

protected:
    //default player position
    double x_pos_;
    double y_pos_;
};

class PlatformClass : public GameObject{
public:
    PlatformClass(Sprite sprite, double x_pos, double y_pos) : GameObject(x_pos, y_pos), sprite_(sprite)
    {
        sprite_.setPosition(GameObject::x_pos_, GameObject::y_pos_);
        scale_ = 2.7777778;
        sprite_.setScale(scale_*2, scale_);
    }

    float scale_;
    Sprite sprite_;
};


//the constructs class
class PlayerClass : public GameObject{
public:

    PlayerClass(Sprite sprite, double x_pos, double y_pos) : GameObject(x_pos, y_pos), sprite_(sprite){
        sprite_.setPosition(GameObject::x_pos_, GameObject::y_pos_);
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
    //check if you are intersecting with a platform - update position if you are and then move
    void collision(std::vector<PlatformClass>& platforms){
        for(PlatformClass const& plat : platforms){
            if(plat.sprite_.getGlobalBounds().intersects(sprite_.getGlobalBounds())){
                sprite_.setPosition(sprite_.getPosition().x, plat.sprite_.getGlobalBounds().top - sprite_.getGlobalBounds().height);
            }

            }
            //move the sprite
            sprite_.move(Vector2f(x_vel_, y_vel_));
    }


    Sprite sprite_;
    double x_vel_;
    double y_vel_;
};

int main(){

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "SFML window");

    //the construct - our protagonist
    Texture constructTex;
    constructTex.loadFromFile("assets/images/roboto100x100.png");
    Sprite constructSprite(constructTex);
    constructSprite.setTextureRect(IntRect(16, 0, 75, 99));
    bool player_right, player_left, player_up, player_down;

    PlayerClass player(constructSprite, 0, 0);

    //background element
    Texture background;
    background.loadFromFile("assets/images/background.png");

    Sprite backgroundSprite(background);
    backgroundSprite.getTextureRect();
    backgroundSprite.scale(window_width/backgroundSprite.getLocalBounds().width, window_height/backgroundSprite.getLocalBounds().height);

    //platform initialization
    std::vector<PlatformClass> platforms;

    Texture platformTex;
    platformTex.loadFromFile("assets/images/tileset.png");

    Sprite platformSprite(platformTex);
    platformSprite.setTextureRect(IntRect(14, 14, 18, 17));

    PlatformClass platform_1(platformSprite, 200, 500);

    platforms.push_back(platform_1);

    Sprite platformSprite_2(platformTex);
    platformSprite_2.setTextureRect(IntRect(14, 14, 18, 17));

    PlatformClass platform_2(platformSprite_2, 300, 500);

    platforms.push_back(platform_2);

    Sprite platformSprite_3(platformTex);
    platformSprite_3.setTextureRect(IntRect(14, 14, 18, 17));

    PlatformClass platform_3(platformSprite_3, 400, 500);

    platforms.push_back(platform_3);


   //start the main loop
    while (window.isOpen())
    {

        //react to an event
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }

        window.clear();

        window.draw(backgroundSprite);

        //detect an arrow key press - i might find a better way for this logic
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

        //check for collision and move
        player.collision(platforms);

        //draw construct
        window.draw(player.sprite_);

        //draw platforms
        window.draw(platform_1.sprite_);
        window.draw(platform_2.sprite_);
        window.draw(platform_3.sprite_);

        window.display();
    }

    return 0;
}
