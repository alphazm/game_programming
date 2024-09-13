#include "collider.h"
#include <iostream>
using namespace std;


collider::collider()
{
}

bool collider::isCollide(RECT* button, RECT* cursor)
{
	// Check if cursor is completely to the left of button
	if (cursor->right < button->left) {
		return false;
	}
	// Check if cursor is completely to the right of button
	if (cursor->left > button->right) {
		return false;
	}
	// Check if cursor is completely above button
	if (cursor->bottom < button->top) {
		return false;
	}
	// Check if cursor is completely below button
	if (cursor->top > button->bottom) {
		return false;
	}
	// If none of the above conditions are true, rectangles must be colliding
	return true;

}

bool collider::isCollide(SpaceShip* spaceShip)
{
	//D3DXVECTOR2 v1 = spaceShip->velocity;
	//D3DXVECTOR2 v2 = OtherSpaceShip->velocity;
	//D3DXVECTOR2 distanceVector = spaceShip->position - OtherSpaceShip->position;
	//if (spaceShip->spriteWidth / 2 + OtherSpaceShip->spriteWidth / 2 > D3DXVec2Length(&distanceVector)) {
	// return true;
	//}
	//return false
}

void collider::inside(SpaceShip* spaceShip, RECT* field, D3DXVECTOR3* Fposition)
{
	D3DXVECTOR2 position = spaceShip->position;
	D3DXVECTOR2 velocity = spaceShip->velocity;
	if (position.x < field->left + Fposition->x) {

		velocity.x *= -1;
	}
	if (position.x > field->right + Fposition->x - spaceShip->spriteWidth) {

		velocity.x *= -1;
	}
	if (position.y < field->top + Fposition->y) {

		velocity.y *= -1;
	}
	if (position.y > field->bottom + Fposition->y - spaceShip->spriteHeight) {

		velocity.y *= -1;
	}
	spaceShip->velocity = velocity;
}

void collider::inside(Ball* ball, RECT* field, D3DXVECTOR3* Fposition)
{
	D3DXVECTOR2 position = ball->position;
	D3DXVECTOR2 velocity = ball->velocity;
	if (position.x < field->left + Fposition->x) {

		velocity.x *= -1;
	}
	if (position.x > field->right + Fposition->x - ball->spriteWidth) {

		velocity.x *= -1;
	}
	if (position.y < field->top + Fposition->y) {

		velocity.y *= -1;
	}
	if (position.y > field->bottom + Fposition->y - ball->spriteHeight) {

		velocity.y *= -1;
	}
	ball->velocity=velocity;
}

bool collider::leftGoal(Ball* ball, RECT* goal, RECT* field, D3DXVECTOR3* position)
{
	// Check left goal area
	if (ball->position.x < field->left && ball->position.y >((field->bottom - field->top) - (goal->bottom - goal->top)) / 2 &&
		ball->position.y < ((field->bottom - field->top) + (goal->bottom - goal->top)) / 2) {
		return true;
	}
	return false;
}
bool collider::rightGoal(Ball* ball, RECT* goal, RECT* field, D3DXVECTOR3* position)
{
	// Check right goal area
	if (ball->position.x > field->right && ball->position.y > ((field->bottom - field->top) - (goal->bottom - goal->top)) / 2 &&
		ball->position.y < ((field->bottom - field->top) + (goal->bottom - goal->top)) / 2) {
		return true;
	}
	return false;
}

void collider::Circle(SpaceShip* spaceShip, SpaceShip* OtherSpaceShip)
{
	D3DXVECTOR2 v1 = spaceShip->velocity;
	D3DXVECTOR2 v2 = OtherSpaceShip->velocity;
	D3DXVECTOR2 distanceVector = spaceShip->position - OtherSpaceShip->position;
	if (spaceShip->spriteWidth / 2 + OtherSpaceShip->spriteWidth / 2 > D3DXVec2Length(&distanceVector)) {
		float distance = D3DXVec2Length(&distanceVector);
		D3DXVECTOR2 normal = distanceVector / distance;
		D3DXVECTOR2 relativeVelocity = spaceShip->velocity - OtherSpaceShip->velocity;
		float velocityAlongNormal = D3DXVec2Dot(&relativeVelocity, &normal);
		if (velocityAlongNormal > 0.0f) return;
		float restitution = 1.0f;
		float impulse = -(1.0f + restitution) * velocityAlongNormal;
		impulse /= (1.0f / spaceShip->mass + 1.0f / OtherSpaceShip->mass);
		D3DXVECTOR2 impulseVector = impulse * normal;
		spaceShip->velocity += (impulseVector / spaceShip->mass);
		OtherSpaceShip->velocity -= (impulseVector / OtherSpaceShip->mass);
	}
}

void collider::Circle(SpaceShip* spaceShip, Ball* ball)
{
	D3DXVECTOR2 v1 = spaceShip->velocity;
	D3DXVECTOR2 v2 = ball->velocity;
	D3DXVECTOR2 distanceVector = spaceShip->position - ball->position;
	if (spaceShip->spriteWidth / 2 + ball->spriteWidth / 2 > D3DXVec2Length(&distanceVector)) {
		float distance = D3DXVec2Length(&distanceVector);
		D3DXVECTOR2 normal = distanceVector / distance;
		D3DXVECTOR2 relativeVelocity = spaceShip->velocity - ball->velocity;
		float velocityAlongNormal = D3DXVec2Dot(&relativeVelocity, &normal);
		if (velocityAlongNormal > 0.0f) return;
		float restitution = 1.0f;
		float impulse = -(1.0f + restitution) * velocityAlongNormal;
		impulse /= (1.0f / spaceShip->mass + 1.0f / ball->mass);
		D3DXVECTOR2 impulseVector = impulse * normal;
		spaceShip->velocity -= (impulseVector / spaceShip->mass);
		ball->velocity += -(impulseVector / ball->mass);
	}
}


