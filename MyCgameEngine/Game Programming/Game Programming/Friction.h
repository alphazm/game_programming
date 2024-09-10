#pragma once
#include <d3dx9.h>
class Friction
{
public:
	D3DXVECTOR2 applayFriction(D3DXVECTOR2 velocity, D3DXVECTOR2 direction);
private :
	D3DXVECTOR2 velocity = D3DXVECTOR2(5.0,5.0);
};

