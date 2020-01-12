#ifndef _BIG_PLATFORM_HPP
#define _BIG_PLATFORM_HPP

#include "PlatformClass.hpp"

using namespace sf;

//kind = 0 -> grass
//kind = 1 -> cupcake
class BigPlatform : public GameObject{
public:
    BigPlatform(double x_pos, double y_pos, double platform_length, Sprite sprite, int kind)
    : GameObject(x_pos, y_pos), platform_length_(platform_length), sprite_(sprite), kind_(kind){

        init_rectangles();

        //generate platforms

        //left platform
        if(kind == 0){
            sprite_.setTextureRect(rectangles_[0]);
            platforms_.push_back(PlatformClass(sprite_, x_pos_, y_pos_));
            double platform_width = platforms_[0].sprite_.getGlobalBounds().width;

            //middle platforms
            sprite_.setTextureRect(rectangles_[1]);
            for(int i = 1; i < platform_length - 1; i++){
                platforms_.push_back(PlatformClass(sprite_, x_pos_ + platform_width * i, y_pos_));
            }

            //right platform
            sprite_.setTextureRect(rectangles_[2]);
            platforms_.push_back(PlatformClass(sprite_, x_pos_ + (platform_length_ - 1)* platform_width, y_pos_));

            //set bounding parameters
            platform_top_ = y_pos_;
            platform_bot_ = y_pos_ + platforms_[0].sprite_.getGlobalBounds().height;
            platform_left_ = x_pos_;
            platform_right_ = x_pos_ + platform_length_* platform_width;
        }
        else if(kind == 1){
            sprite_.setTextureRect(rectangles_[3]);
            platforms_.push_back(PlatformClass(sprite_, x_pos_, y_pos_));
            double platform_width = platforms_[0].sprite_.getGlobalBounds().width;

            //middle platforms
            sprite_.setTextureRect(rectangles_[4]);
            for(int i = 1; i < platform_length - 1; i++){
                platforms_.push_back(PlatformClass(sprite_, x_pos_ + platform_width * i, y_pos_));
            }

            //right platform
            sprite_.setTextureRect(rectangles_[5]);
            platforms_.push_back(PlatformClass(sprite_, x_pos_ + (platform_length_ - 1)* platform_width, y_pos_));

            //set bounding parameters
            platform_top_ = y_pos_;
            platform_bot_ = y_pos_ + platforms_[0].sprite_.getGlobalBounds().height;
            platform_left_ = x_pos_;
            platform_right_ = x_pos_ + platform_length_* platform_width;
        }
    }

    //number of little platforms encapsulated in it - 2
    int kind_;
    int platform_length_;
    Sprite sprite_;
    double platform_top_ = 0;
    double platform_bot_ = 0;

    double platform_left_ = 0;
    double platform_right_ = 0;

    std::vector<IntRect> rectangles_;

    std::vector<PlatformClass> platforms_;

private:
    void init_rectangles(){

    //left end platform - index 0
    rectangles_.push_back(IntRect(240, 224, 16, 16));

    //middle platform - index 1
    rectangles_.push_back(IntRect(48, 16, 16, 16));

    //right end platform - index 2
    rectangles_.push_back(IntRect(304, 224, 16, 16));

    //cupcake platforms
    //left end platform - index 3
    rectangles_.push_back(IntRect(439, 370, 21, 21));

    //middle platform - index 4
    rectangles_.push_back(IntRect(393, 370, 21, 21));

    //right end platform - index 5
    rectangles_.push_back(IntRect(439, 393, 21, 21));

    }

};

#endif // _BIG_PLATFORM_HPP
