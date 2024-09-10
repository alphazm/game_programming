#include "Friction.h"

D3DXVECTOR2 Friction::applayFriction(D3DXVECTOR2 velocity, D3DXVECTOR2 direction)
{
	if (velocity.x != 0.0)
	{
		this->velocity.x *= -direction.x;
	}
	if (velocity.y != 0.0)
	{
		this->velocity.y *= -direction.y;
	}
    return this->velocity;
}
