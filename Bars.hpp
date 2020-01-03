#ifndef BARS_HPP
#define BARS_HPP

extern double window_height;
extern double window_width;

//TODO maybe seporate this into a hpp file
void draw_player_hp_mp(RenderWindow &window, PlayerClass &player, Sprite hp_sprite){

        //we draw the hp bar propartionally to the amount of hp left
        hp_sprite.setTextureRect(IntRect(8, 14, 64*player.construct_hp_/100.0, 9));
        hp_sprite.setScale(2, 2);
        hp_sprite.setPosition(player.sprite_.getPosition().x - window_width/2 + 16, player.sprite_.getPosition().y - 0.495*window_height);
        window.draw(hp_sprite);

        hp_sprite.setTextureRect(IntRect(8, 0, 64*player.construct_mp_/100.0, 9));
        hp_sprite.setScale(2, 2);
        hp_sprite.setPosition(player.sprite_.getPosition().x - window_width/2 + 16, player.sprite_.getPosition().y - 0.455*window_height);
        window.draw(hp_sprite);

        hp_sprite.setTextureRect(IntRect(0, 42, 80, 9));
        hp_sprite.setScale(2, 2);
        hp_sprite.setPosition(player.sprite_.getPosition().x - window_width/2, player.sprite_.getPosition().y - 0.495*window_height);
        window.draw(hp_sprite);

        hp_sprite.setTextureRect(IntRect(0, 54, 80, 9));
        hp_sprite.setScale(2, 2);
        hp_sprite.setPosition(player.sprite_.getPosition().x - window_width/2, player.sprite_.getPosition().y - 0.455*window_height);
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

#endif // BARS_HPP
