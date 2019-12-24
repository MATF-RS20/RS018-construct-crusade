#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

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
        scale_ = 4;
        sprite_.setScale(scale_, scale_);
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
    double scale_;
    double x_vel_;
    double y_vel_;
};

int main(){

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "SFML window");

    //define a view
    sf::View view(sf::FloatRect(0.0, 0.0, window_width, window_height));

    //activate it
    window.setView(view);

    //the construct - our protagonist
    Texture constructTex;
    constructTex.loadFromFile("assets/images/walkingAnimation10.png");
    Sprite constructSprite(constructTex);
    constructSprite.setTextureRect(IntRect(125, 50, 25, 25));
    bool player_right, player_left, player_up, player_down;

    PlayerClass player(constructSprite, 0, 0);

    //background element
    Texture background;
    background.loadFromFile("assets/images/background.png");

    Sprite backgroundSprite(background);
    backgroundSprite.getTextureRect();
    backgroundSprite.scale(window_width/backgroundSprite.getLocalBounds().width, window_height/backgroundSprite.getLocalBounds().height);

    //make a vector that contains rectangle information that corelates to picture frames we want to animate
    std::vector<IntRect> rectangles;
    rectangles.push_back(IntRect(125, 50, 25, 25));
    rectangles.push_back(IntRect(150, 50, 25, 25));
    rectangles.push_back(IntRect(175, 50, 25, 25));
    rectangles.push_back(IntRect(200, 50, 25, 25));
    rectangles.push_back(IntRect(225, 50, 25, 25));
    rectangles.push_back(IntRect(250, 50, 25, 25));
    int rectangles_index = 0;
    int time;
    //delt_time - duration of a frame
    int delta_time = 200;
    //helps us determin if our frame should be changed - it marks the time when a frame is first used
    int current_frame_time = 0;

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

    Clock gameClock;


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
        window.clear();

        window.draw(backgroundSprite);

        //detect an arrow key press - i might find a better way for this logic
        if(Keyboard::isKeyPressed(Keyboard::Right)){
            player_right = true;
            //move the view with the player
            view.move(1.f, 0.f);
            window.setView(view);
        }

        if(Keyboard::isKeyPressed(Keyboard::Left)){
            player_left = true;
            view.move(-1.f, 0.f);
            window.setView(view);
        }

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

        time = gameClock.getElapsedTime().asMilliseconds();

        //update rectangle_index if its time for the next frame
        if(current_frame_time+delta_time < time){
            current_frame_time = time;
            if(rectangles_index == 5){
                rectangles_index = 0;
                current_frame_time = 0;
                rectangles_index--;
                gameClock.restart();
            }
            rectangles_index++;
        }

        //draw construct
        player.sprite_.setTextureRect(rectangles[rectangles_index]);
        window.draw(player.sprite_);

        //draw platforms
        window.draw(platform_1.sprite_);
        window.draw(platform_2.sprite_);
        window.draw(platform_3.sprite_);

        window.display();
    }

    return 0;
}
