#ifndef DRAW_TRAILS_HPP
#define DRAW_TRAILS_HPP

void draw_left_trail(PlayerClass player, RenderWindow &window){

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


void draw_middle_trail(PlayerClass player, RenderWindow &window){

            player.plasma_sprite_.setTextureRect(player.rectangles_plasma_booster_[0]);
            player.plasma_sprite_.setScale(4, 4);
            player.plasma_sprite_.setPosition(player.sprite_.getPosition().x + 24, player.sprite_.getPosition().y + player.sprite_.getGlobalBounds().height);
            window.draw(player.plasma_sprite_);

            player.plasma_sprite_.move(0, 4);
            player.plasma_sprite_.setTextureRect(player.rectangles_plasma_booster_[player.rectangles_index_jump_ + 5]);
            window.draw(player.plasma_sprite_);

            player.plasma_sprite_.move(0, 4);
            player.plasma_sprite_.setTextureRect(player.rectangles_plasma_booster_[player.rectangles_index_jump_]);
            window.draw(player.plasma_sprite_);

            player.plasma_sprite_.move(4, 0);
            player.plasma_sprite_.setTextureRect(player.rectangles_plasma_booster_[player.rectangles_index_jump_+2]);
            window.draw(player.plasma_sprite_);

            player.plasma_sprite_.move(8, 0);
            player.plasma_sprite_.setTextureRect(player.rectangles_plasma_booster_[player.rectangles_index_jump_+2]);
            window.draw(player.plasma_sprite_);

            player.plasma_sprite_.move(8, 0);
            player.plasma_sprite_.setTextureRect(player.rectangles_plasma_booster_[player.rectangles_index_jump_+9]);
            window.draw(player.plasma_sprite_);

            player.plasma_sprite_.move(4, 0);
            player.plasma_sprite_.setTextureRect(player.rectangles_plasma_booster_[player.rectangles_index_jump_+3]);
            window.draw(player.plasma_sprite_);

            player.plasma_sprite_.move(8, 0);
            player.plasma_sprite_.setTextureRect(player.rectangles_plasma_booster_[player.rectangles_index_jump_+1]);
            window.draw(player.plasma_sprite_);
}


void draw_right_trail(PlayerClass player, RenderWindow &window){
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

#endif // DRAW_TRAILS_HPP
