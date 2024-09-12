#include "Sprite.h"

Sprite::Sprite() : texture(nullptr), position(0, 0, 0)
{
}

Sprite::~Sprite()
{
    if (texture) texture->Release();
}

void Sprite::setTexture(LPDIRECT3DTEXTURE9 tex)
{
    texture = tex;
}

void Sprite::setPosition(float x, float y)
{
    position.x = x;
    position.y = y;
}

void Sprite::update()
{
    
}

void Sprite::render(IDirect3DDevice9* d3dDevice)
{
    if (texture && d3dDevice) {
        LPD3DXSPRITE sprite;
        D3DXCreateSprite(d3dDevice, &sprite);
        sprite->Begin(D3DXSPRITE_ALPHABLEND);
        sprite->Draw(texture, &spriteRect, NULL, &position, D3DCOLOR_XRGB(255, 255, 255));
        sprite->End();
        sprite->Release();
    }
}
