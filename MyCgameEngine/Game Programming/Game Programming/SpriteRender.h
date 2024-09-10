#pragma once
#include <Windows.h>
#include <d3dx9.h>
class SpriteRender
{
public:
	int totalHeight;
	int totalLength;
	int col;
	int row;
	SpriteRender();
	~SpriteRender();
	SpriteRender(int height, int length, int col, int row);
	bool loadTexture(LPDIRECT3DDEVICE9 d3dDevice, const char* filePath);
	bool loadTextureEx(LPDIRECT3DDEVICE9 d3dDevice, const char* filePath, int r, int g, int b);
	LPDIRECT3DTEXTURE9 getTexture() const;
	void initi(int height, int length, int col, int row);
	void setMaxCount(int maximumCount);
	void FrameUpdate();
	void setMinCount(int minimumCount);
	void setTransformation(D3DXVECTOR2* scaling, D3DXVECTOR2* centerPoint, float rotation, D3DXVECTOR2* position);
	void updateTransformation();
	void setRotateValue(float value);
	void updateRotateValue(float rotationspeed);
	void setScaling(D3DXVECTOR2 scaling);
	void setCenterPoint(D3DXVECTOR2 centerPoint);
	void settranslation(D3DXVECTOR2 position);
	float getRotateValue();
	D3DXMATRIX* getMat();
	int getFrameCount();
	int getHeight();
	int getLength();
	int getTop();
	int getLeft();
	int getBottom();
	int getright();
	RECT* GetRect();
	void Render(LPD3DXSPRITE sprite, int r, int g, int b);
	void Render(LPD3DXSPRITE sprite);
private:
	D3DXVECTOR2 scaling= D3DXVECTOR2(1.0,1.0);
	D3DXVECTOR2 centerPoint;
	D3DXVECTOR2 translation= D3DXVECTOR2(0.0, 0.0);
	RECT rect;
	D3DXMATRIX mat;
	LPDIRECT3DTEXTURE9 texture;
	float rotateValue;
	int FrameCount = 0;
	int maximunFrameCount = 0;
	int minimumFrameCount = 0;
	void updateRect();
	void setRectSize();
	int height;
	int width;
	int top;
	int left;
	int bottom;
	int right;
};

