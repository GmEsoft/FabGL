/*
  Created by Fabrizio Di Vittorio (fdivitto2013@gmail.com) - <http://www.fabgl.com>
  Copyright (c) 2019-2021 Fabrizio Di Vittorio.
  All rights reserved.

  This library and related software is available under GPL v3 or commercial license. It is always free for students, hobbyists, professors and researchers.
  It is not-free if embedded as firmware in commercial boards.


* Contact for commercial license: fdivitto2013@gmail.com


* GPL license version 3, for non-commercial use:

  FabGL is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  FabGL is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with FabGL.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "fabutils.h"


using fabgl::twrap;


const uint8_t spaceship_data[] = {
  0x00, 0x00, 0xd5, 0xd5, 0xd9, 0xd9, 0xd9, 0xd9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xe9, 0xea, 0xc0, 0x00, 0x00, 0xd4, 0xd4, 0xd4, 0x00, 0x00, 0x00,
  0xd5, 0xd5, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0xc0, 0xd4, 0xd5, 0xd9, 0xd9, 0xd9, 0xd5, 0x00,
  0xd9, 0xd9, 0xd9, 0xd9, 0xd9, 0xd9, 0xc0, 0xc0, 0xd4, 0xd5, 0xd9, 0xe9, 0xe9, 0xe9, 0xd9, 0xd5,
  0x00, 0xd4, 0xe9, 0xe9, 0xea, 0xea, 0xc0, 0xd4, 0xd5, 0xe9, 0xe9, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd4, 0xd5, 0xd5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xe9, 0xe9, 0xc0, 0xe9, 0xc0, 0xe9, 0xe9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xea, 0xea, 0xea, 0xc0, 0xea, 0xc0, 0xea, 0xea, 0xd9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xd9, 0xd9, 0xd9, 0xc0, 0xd9, 0xc0, 0xd9, 0xd9, 0xd5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xd5, 0xd5, 0xc0, 0xd5, 0xc0, 0xd5, 0xd5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd4, 0xd5, 0xd5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xd4, 0xd9, 0xd9, 0xe9, 0xe9, 0xc0, 0xd4, 0xd5, 0xe9, 0xe9, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xd5, 0xd5, 0xd5, 0xd5, 0xd5, 0xd5, 0xc0, 0xc0, 0xd4, 0xd5, 0xd9, 0xe9, 0xe9, 0xe9, 0xd9, 0xd5,
  0xd4, 0xd4, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0xc0, 0xd4, 0xd5, 0xd9, 0xd9, 0xd5, 0xd5, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xd9, 0xe9, 0xc0, 0x00, 0x00, 0xd4, 0xd5, 0xd5, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xd4, 0xd4, 0xd5, 0xd5, 0xd5, 0xd5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
Bitmap spaceship = Bitmap(16, 16, &spaceship_data[0], PixelFormat::RGBA2222);


struct MySprite : Sprite {
  double fx;
  double fy;
  double dir; // radians
};





class SpritesTest : public Test {
public:

  SpritesTest()
  {
    sprites_ = new MySprite[MAXSPRITES];
  }

  virtual ~SpritesTest()
  {
    DisplayController.removeSprites();
    delete [] sprites_;
  }

  void update()
  {
    canvas.setBrushColor(Color::Black);
    canvas.clear();

    for (int i = 0; i < spritesCount_; ++i) {
      MySprite * sprite = &sprites_[i];
      sprite->fx = twrap<double>(sprite->fx + 3 * cos(sprite->dir), 0, canvas.getWidth());
      sprite->fy = twrap<double>(sprite->fy + 3 * sin(sprite->dir), 0, canvas.getHeight());
      sprite->moveTo(ceil(sprite->fx), ceil(sprite->fy));
    }
    DisplayController.refreshSprites();
  }

  bool nextState()
  {
    if (spritesCount_ == MAXSPRITES)
      return false;
    if (counter_ % 40 == 0) {
      // create a new sprite
      MySprite * newSprite = &sprites_[spritesCount_++];
      newSprite->addBitmap(&spaceship);
      newSprite->dir = random(0, 360) * PI / 180.0;
      newSprite->fx = canvas.getWidth() / 2.0;
      newSprite->fy = canvas.getHeight() / 2.0;
      newSprite->moveTo(ceil(newSprite->fx), ceil(newSprite->fy));
      DisplayController.setSprites(sprites_, spritesCount_);
    }
    ++counter_;
    return true;
  }

  int testState()
  {
    return spritesCount_;
  }

  char const * name() { return "Sprites"; }

private:

  static const int MAXSPRITES = 20;

  MySprite * sprites_ = nullptr;

  int spritesCount_ = 0;

  int counter_ = 0;

};
