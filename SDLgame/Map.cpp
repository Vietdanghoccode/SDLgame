#include "Map.h"

Tile::Tile(Vector2f vt, int tileType)
{
    //Get the offsets
    mBox.x = vt.x;
    mBox.y = vt.y;

    //Set the collision box
    mBox.w = TILE_WIDTH;
    mBox.h = TILE_HEIGHT;

    //Get the tile type
    mType = tileType;
}
/*
void Tile::render(SDL_Rect& camera)
{
    //If the tile is on screen
    if (checkCollision(camera, mBox))
    {
        //Show the tile
        gTileTexture.render(mBox.x - camera.x, mBox.y - camera.y, &gTileClips[mType]);
    }
}
*/
int Tile::getType()
{
    return mType;
}

SDL_Rect Tile::getBox()
{
    return mBox;
}
