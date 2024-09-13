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

void collider::inside(SpaceShip* spaceShip, RECT* field)
{
	D3DXVECTOR2 position = spaceShip->position;
	D3DXVECTOR2 velocity = spaceShip->velocity;
	if (position.x < field->left) {

		velocity.x *= -1;
	}
	if (position.x > field->right - spaceShip->spriteWidth) {

		velocity.x *= -1;
	}
	if (position.y < field->top) {

		velocity.y *= -1;
	}
	if (position.y > field->bottom - spaceShip->spriteHeight) {

		velocity.y *= -1;
	}
	spaceShip->velocity = velocity;
}

void collider::inside(Ball* ball, RECT* field)
{
	D3DXVECTOR2 position = ball->position;
	D3DXVECTOR2 velocity = ball->velocity;
	if (position.x < field->left) {

		velocity.x *= -1;
	}
	if (position.x > field->right - ball->spriteWidth) {

		velocity.x *= -1;
	}
	if (position.y < field->top) {

		velocity.y *= -1;
	}
	if (position.y > field->bottom - ball->spriteHeight) {

		velocity.y *= -1;
	}
	ball->velocity=velocity;
}

bool collider::leftGoal(Ball* ball, RECT* goal, RECT* field)
{
	// Check left goal area
	if (ball->position.x < field->left && ball->position.y >((field->bottom - field->top) - (goal->bottom - goal->top)) / 2 &&
		ball->position.y < ((field->bottom - field->top) + (goal->bottom - goal->top)) / 2) {
		return true;
	}
	return false;
}
bool collider::rightGoal(Ball* ball, RECT* goal, RECT* field)
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
	if (spaceShip->spriteWidth / 2.1 + OtherSpaceShip->spriteWidth / 2.1 > D3DXVec2Length(&distanceVector)) {
		D3DXVec2Normalize(&distanceVector, &distanceVector); //normalize distance vector 
		D3DXVECTOR2 v1n = distanceVector * D3DXVec2Dot(&v1, &distanceVector); //vector 1 . n * n; normal component before collision 
		D3DXVECTOR2 v2n = distanceVector * D3DXVec2Dot(&v2, &distanceVector);
		D3DXVECTOR2 v1t = v1 - v1n; // tangent component 
		D3DXVECTOR2 v2t = v2 - v2n;
		D3DXVECTOR2 newV1n = (((spaceShip->mass - OtherSpaceShip->mass) * v1n) + (2 * OtherSpaceShip->mass * v2n)) / (spaceShip->mass + OtherSpaceShip->mass); //after collision change the normal; find the new normal with mass; refer wiki 
		D3DXVECTOR2 newV2n = (((OtherSpaceShip->mass - spaceShip->mass) * v2n) + (2 * spaceShip->mass * v1n)) / (spaceShip->mass + OtherSpaceShip->mass);
		D3DXVECTOR2 newV1 = newV1n + v1t;//form the new vactor 
		D3DXVECTOR2 newV2 = newV2n + v2t;
		spaceShip->velocity = (newV1);
		OtherSpaceShip->velocity = (newV2);
	}
}

void collider::Circle(SpaceShip* spaceShip, Ball* ball)
{
	D3DXVECTOR2 v1 = spaceShip->velocity;
	D3DXVECTOR2 v2 = ball->velocity;
	D3DXVECTOR2 distanceVector = spaceShip->position - ball->position;
	if (spaceShip->spriteWidth / 2.1 + ball->spriteWidth / 2.1 > D3DXVec2Length(&distanceVector)) {
		D3DXVec2Normalize(&distanceVector, &distanceVector); //normalize distance vector 
		D3DXVECTOR2 v1n = distanceVector * D3DXVec2Dot(&v1, &distanceVector); //vector 1 . n * n; normal component before collision 
		D3DXVECTOR2 v2n = distanceVector * D3DXVec2Dot(&v2, &distanceVector);
		D3DXVECTOR2 v1t = v1 - v1n; // tangent component 
		D3DXVECTOR2 v2t = v2 - v2n;
		D3DXVECTOR2 newV1n = (((spaceShip->mass - ball->mass) * v1n) + (2 * ball->mass * v2n)) / (spaceShip->mass + ball->mass); //after collision change the normal; find the new normal with mass; refer wiki 
		D3DXVECTOR2 newV2n = (((ball->mass - spaceShip->mass) * v2n) + (2 * spaceShip->mass * v1n)) / (spaceShip->mass + ball->mass);
		D3DXVECTOR2 newV1 = newV1n + v1t;//form the new vactor 
		D3DXVECTOR2 newV2 = newV2n + v2t;
		spaceShip->velocity = (newV1);
		ball->velocity = (newV2);
	}
}


