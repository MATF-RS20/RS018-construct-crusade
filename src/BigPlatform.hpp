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

        //grass platform - basic
        if(kind == 0){
            //left platform
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

        }//cupcake
        else if(kind == 1){
            sprite_.setTextureRect(rectangles_[3]);
            platforms_.push_back(PlatformClass(sprite_, x_pos_, y_pos_));
            platforms_[0].sprite_.setScale(2.7, 2.7);
            double platform_width = platforms_[0].sprite_.getGlobalBounds().width;

            //middle platforms
            sprite_.setTextureRect(rectangles_[4]);
            for(int i = 1; i < platform_length - 1; i++){
                platforms_.push_back(PlatformClass(sprite_, x_pos_ + platform_width * i, y_pos_));
                platforms_[i].sprite_.setScale(2.7, 2.7);
            }

            //right platform
            sprite_.setTextureRect(rectangles_[5]);
            platforms_.push_back(PlatformClass(sprite_, x_pos_ + (platform_length_ - 1)* platform_width, y_pos_));
            platforms_[platform_length_ - 1].sprite_.setScale(2.7, 2.7);
            //set bounding parameters
            platform_top_ = y_pos_;
            platform_bot_ = y_pos_ + platforms_[0].sprite_.getGlobalBounds().height;
            platform_left_ = x_pos_;
            platform_right_ = x_pos_ + platform_length_* platform_width;

        }//grass #2
        else if(kind_ == 2){

            //sprite_.setScale(0.73529411764, 0.73529411764);

            sprite_.setTextureRect(rectangles_[6]);
            platforms_.push_back(PlatformClass(sprite_, x_pos_, y_pos_));
            platforms_[0].sprite_.setScale(0.71428571428, 0.71428571428);
            double platform_width = platforms_[0].sprite_.getGlobalBounds().width;

            //middle platforms
            sprite_.setTextureRect(rectangles_[7]);
            for(int i = 1; i < platform_length - 1; i++){
                platforms_.push_back(PlatformClass(sprite_, x_pos_ + platform_width * i, y_pos_));
                platforms_[i].sprite_.setScale(0.71428571428, 0.71428571428);
            }

            //right platform
            sprite_.setTextureRect(rectangles_[8]);
            platforms_.push_back(PlatformClass(sprite_, x_pos_ + (platform_length_ - 1)* platform_width, y_pos_));
            platforms_[platform_length_-1].sprite_.setScale(0.71428571428, 0.71428571428);
            //set bounding parameters
            platform_top_ = y_pos_;
            platform_bot_ = y_pos_ + platforms_[0].sprite_.getGlobalBounds().height;
            platform_left_ = x_pos_;
            platform_right_ = x_pos_ + platform_length_* platform_width;

        }//snow
        else if(kind_ == 3){

            sprite_.setTextureRect(rectangles_[9]);
            platforms_.push_back(PlatformClass(sprite_, x_pos_, y_pos_));
            platforms_[0].sprite_.setScale(0.71428571428, 0.71428571428);
            double platform_width = platforms_[0].sprite_.getGlobalBounds().width;

            //middle platforms
            sprite_.setTextureRect(rectangles_[10]);
            for(int i = 1; i < platform_length - 1; i++){
                platforms_.push_back(PlatformClass(sprite_, x_pos_ + platform_width * i, y_pos_));
                platforms_[i].sprite_.setScale(0.71428571428, 0.71428571428);
            }

            //right platform
            sprite_.setTextureRect(rectangles_[11]);
            platforms_.push_back(PlatformClass(sprite_, x_pos_ + (platform_length_ - 1)* platform_width, y_pos_));
            platforms_[platform_length_-1].sprite_.setScale(0.71428571428, 0.71428571428);
            //set bounding parameters
            platform_top_ = y_pos_;
            platform_bot_ = y_pos_ + platforms_[0].sprite_.getGlobalBounds().height;
            platform_left_ = x_pos_;
            platform_right_ = x_pos_ + platform_length_* platform_width;

        }//ice
        else if(kind_ == 4){

            sprite_.setTextureRect(rectangles_[12]);
            platforms_.push_back(PlatformClass(sprite_, x_pos_, y_pos_));
            platforms_[0].sprite_.setScale(0.71428571428, 0.71428571428);
            double platform_width = platforms_[0].sprite_.getGlobalBounds().width;

            //middle platforms
            sprite_.setTextureRect(rectangles_[13]);
            for(int i = 1; i < platform_length - 1; i++){
                platforms_.push_back(PlatformClass(sprite_, x_pos_ + platform_width * i, y_pos_));
                platforms_[i].sprite_.setScale(0.71428571428, 0.71428571428);
            }

            //right platform
            sprite_.setTextureRect(rectangles_[14]);
            platforms_.push_back(PlatformClass(sprite_, x_pos_ + (platform_length_ - 1)* platform_width, y_pos_));
            platforms_[platform_length_-1].sprite_.setScale(0.71428571428, 0.71428571428);
            //set bounding parameters
            platform_top_ = y_pos_;
            platform_bot_ = y_pos_ + platforms_[0].sprite_.getGlobalBounds().height;
            platform_left_ = x_pos_;
            platform_right_ = x_pos_ + platform_length_* platform_width;

        }//castle
        else if(kind_ == 5){

            sprite_.setTextureRect(rectangles_[15]);
            platforms_.push_back(PlatformClass(sprite_, x_pos_, y_pos_));
            platforms_[0].sprite_.setScale(0.71428571428, 0.71428571428);
            double platform_width = platforms_[0].sprite_.getGlobalBounds().width;

            //middle platforms
            sprite_.setTextureRect(rectangles_[16]);
            for(int i = 1; i < platform_length - 1; i++){
                platforms_.push_back(PlatformClass(sprite_, x_pos_ + platform_width * i, y_pos_));
                platforms_[i].sprite_.setScale(0.71428571428, 0.71428571428);
            }

            //right platform
            sprite_.setTextureRect(rectangles_[17]);
            platforms_.push_back(PlatformClass(sprite_, x_pos_ + (platform_length_ - 1)* platform_width, y_pos_));
            platforms_[platform_length_-1].sprite_.setScale(0.71428571428, 0.71428571428);
            //set bounding parameters
            platform_top_ = y_pos_;
            platform_bot_ = y_pos_ + platforms_[0].sprite_.getGlobalBounds().height;
            platform_left_ = x_pos_;
            platform_right_ = x_pos_ + platform_length_* platform_width;

        }



    }

    //number of little platforms encapsulated in it - 2
    int platform_length_;
    Sprite sprite_;
    double platform_top_ = 0;
    double platform_bot_ = 0;

    double platform_left_ = 0;
    double platform_right_ = 0;

    std::vector<IntRect> rectangles_;

    std::vector<PlatformClass> platforms_;

    int kind_;

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

    //grassy platforms
    //left end platform - index 6
    rectangles_.push_back(IntRect(215, 1, 70, 70));

    //middle platform - index 7
    rectangles_.push_back(IntRect(283, 1, 70, 70));

    //right end platform - index 8
    rectangles_.push_back(IntRect(351, 1, 70, 70));

    //snowy platforms
    //left end platform - index 9
    rectangles_.push_back(IntRect(0, 0, 70, 70));

    //middle platform - index 10
    rectangles_.push_back(IntRect(70, 0, 70, 70));

    //right end platform - index 11
    rectangles_.push_back(IntRect(138, 0, 70, 70));

    //icy platforms
    //left end platform - index 12
    rectangles_.push_back(IntRect(354, 306, 70, 70));

    //middle platform - index 13
    rectangles_.push_back(IntRect(214, 306, 70, 70));

    //right end platform - index 14
    rectangles_.push_back(IntRect(354, 376, 70, 70));

    //castle platforms
    //left end platform - index 15
    rectangles_.push_back(IntRect(434, 0, 70, 70));

    //middle platform - index 16
    rectangles_.push_back(IntRect(512, 0, 70, 70));

    //right end platform - index 17
    rectangles_.push_back(IntRect(589, 0, 70, 70));

    }

};

#endif // _BIG_PLATFORM_HPP
