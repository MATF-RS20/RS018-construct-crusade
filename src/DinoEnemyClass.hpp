#ifndef _DINO_ENEMY_CLASS_HPP
#define _DINO_ENEMY_CLASS_HPP

#include "RealEnemyClass.hpp"

class DinoEnemyClass : public RealEnemyClass{
public:
    DinoEnemyClass(Sprite sprite, double x_pos, double y_pos, int plat_left, int plat_right)
     : RealEnemyClass(sprite, x_pos, y_pos, plat_left, plat_right){

     }


};
#endif // _DINO_ENEMY_CLASS_HPP
