#include "SpriteRender.h"
#include <Windows.h>
#include <d3dx9.h>

void SpriteRender::setRectSize() {
	height = totalHeight / row;
	width = totalLength / col;
	updateRect();
}

void SpriteRender::updateRect() {
	rect.top = FrameCount / col * height;
	rect.left = FrameCount % col * width;
	rect.bottom = rect.top + height;
	rect.right = rect.left + width;
}

SpriteRender::SpriteRender() {
}

SpriteRender::SpriteRender(int height, int length, int col, int row) {
	this->totalHeight = height;
	this->totalLength = length;
	this->col = col;
	this->row = row;
	setRectSize();
}
SpriteRender::~SpriteRender() {
	texture = NULL;
}

void SpriteRender::initi(int height, int length, int col, int row) {
	this->totalHeight = height;
	this->totalLength = length;
	this->col = col;
	this->row = row;
	setRectSize();
}

void SpriteRender::setMaxCount(int maximumCount)
{
	this->maximunFrameCount = maximumCount - 1;
}

void SpriteRender::setMinCount(int minimumCount)
{
	this->minimumFrameCount = minimumCount - 1;
}

void SpriteRender::setTransformation(D3DXVECTOR2* scaling, D3DXVECTOR2* centerPoint, float rotation, D3DXVECTOR2* position)
{
	D3DXMatrixTransformation2D(&mat,NULL,0.0,scaling,centerPoint,rotation,position);
}

void SpriteRender::updateTransformation()
{
	centerPoint = D3DXVECTOR2(width / 2.0f, height / 2.0f);
	D3DXMatrixTransformation2D(&mat, &centerPoint, 0.0, &scaling, &centerPoint, rotateValue, &translation);
}

void SpriteRender::setRotateValue(float value)
{
	rotateValue = value;
}

void SpriteRender::updateRotateValue(float rotationspeed)
{
	rotateValue += rotationspeed;
	updateTransformation();
}

void SpriteRender::setScaling(D3DXVECTOR2 scaling)
{
	this->scaling = scaling;
}

void SpriteRender::setCenterPoint(D3DXVECTOR2 centerPoint)
{
	this->centerPoint = centerPoint;
}

void SpriteRender::settranslation(D3DXVECTOR2 position)
{
	translation = position;
}

float SpriteRender::getRotateValue()
{
	return rotateValue;
}

D3DXMATRIX* SpriteRender::getMat()
{
	updateTransformation();
	return &mat;
}

void SpriteRender::FrameUpdate() {
	this->FrameCount++;
	if (FrameCount > maximunFrameCount)
		FrameCount = minimumFrameCount;
	if (FrameCount < minimumFrameCount)
		FrameCount = minimumFrameCount;
	updateRect();
}
int SpriteRender::getFrameCount() {
	return FrameCount;
}
int SpriteRender::getHeight() {
	return height;
}
int SpriteRender::getLength() {
	return width;
}
int SpriteRender::getTop() {
	return top;
}
int SpriteRender::getLeft() {
	return left;
}
int SpriteRender::getBottom() {
	return bottom;
}
int SpriteRender::getright() {
	return right;
}
RECT* SpriteRender::GetRect() {
	return &rect;
}

void SpriteRender::Render(LPD3DXSPRITE sprite,int r,int g,int b)
{
	sprite->Draw(texture, GetRect(), NULL, NULL, D3DCOLOR_XRGB(r, g, b));
}

void SpriteRender::Render(LPD3DXSPRITE sprite)
{
	sprite->Draw(texture, GetRect(), NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
}

bool SpriteRender::loadTexture(LPDIRECT3DDEVICE9 d3dDevice, const char* filePath) {
	HRESULT hr = D3DXCreateTextureFromFile(d3dDevice, filePath, &texture);
	return SUCCEEDED(hr);
}
bool SpriteRender::loadTextureEx(LPDIRECT3DDEVICE9 d3dDevice, const char* filePath, int r, int g, int b) {
	HRESULT hr = D3DXCreateTextureFromFileEx(d3dDevice, filePath, D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(r, g, b),
		NULL, NULL, &texture);
	return SUCCEEDED(hr);
}

LPDIRECT3DTEXTURE9 SpriteRender::getTexture() const {
	return texture;
}