#include "collider.h"
#include <iostream>
using namespace std;


collider::collider()
{
}

bool collider::isCollide(RECT button, RECT cursor)
{
	// Check if cursor is completely to the left of button
	if (cursor.right < button.left) {
		return false;
	}
	// Check if cursor is completely to the right of button
	if (cursor.left > button.right) {
		return false;
	}
	// Check if cursor is completely above button
	if (cursor.bottom < button.top) {
		return false;
	}
	// Check if cursor is completely below button
	if (cursor.top > button.bottom) {
		return false;
	}
	// If none of the above conditions are true, rectangles must be colliding
	return true;

}

void collider::inside(SpaceShip spaceShip, RECT field)
{
	D3DXVECTOR2 position = spaceShip.getPosition();
	D3DXVECTOR2 velocity = spaceShip.getVector();
	if (position.x < field.left) {

		velocity.x *= -1;
	}
	if (position.x > field.right - spaceShip.getLength()) {

		velocity.x *= -1;
	}
	if (position.y < field.top) {

		velocity.y *= -1;
	}
	if (position.y > field.bottom - spaceShip.getHeight()) {

		velocity.y *= -1;
	}
	spaceShip.setVector(velocity);
}

void collider::inside(Ball ball, RECT field)
{
	D3DXVECTOR2 position = ball.getPosition();
	D3DXVECTOR2 velocity = ball.getVector();
	if (position.x < field.left) {

		velocity.x *= -1;
	}
	if (position.x > field.right - ball.getLength()) {

		velocity.x *= -1;
	}
	if (position.y < field.top) {

		velocity.y *= -1;
	}
	if (position.y > field.bottom - ball.getHeight()) {

		velocity.y *= -1;
	}
	ball.setVector(velocity);
}

void collider::inGoal(Ball ball, Goal goal, RECT field, bool* left, bool* right)
{
	// Check left goal area
	if (ball.getPosition().x < field.left && ball.getPosition().y >((field.bottom-field.top) - (goal.GetRect()->bottom- goal.GetRect()->top)) / 2 &&
		ball.getPosition().y < ((field.bottom - field.top) + (goal.GetRect()->bottom - goal.GetRect()->top)) / 2) {
		*left = true;
	}
	// Check right goal area
	if (ball.getPosition().x > field.right && ball.getPosition().y > ((field.bottom - field.top) - (goal.GetRect()->bottom - goal.GetRect()->top)) / 2 &&
		ball.getPosition().y < ((field.bottom - field.top) + (goal.GetRect()->bottom - goal.GetRect()->top)) / 2) {
		*right = true;
	}
}

void collider::Circle(SpaceShip* spaceShip, SpaceShip* OtherSpaceShip)
{
	D3DXVECTOR2 v1 = spaceShip->getVector();
	D3DXVECTOR2 v2 = OtherSpaceShip->getVector();
	D3DXVECTOR2 distanceVector = spaceShip->getPosition() - OtherSpaceShip->getPosition();
	if (spaceShip->getLength() / 2.1 + OtherSpaceShip->getLength() / 2.1 > D3DXVec2Length(&distanceVector)) {
		D3DXVec2Normalize(&distanceVector, &distanceVector); //normalize distance vector 
		D3DXVECTOR2 v1n = distanceVector * D3DXVec2Dot(&v1, &distanceVector); //vector 1 . n * n; normal component before collision 
		D3DXVECTOR2 v2n = distanceVector * D3DXVec2Dot(&v2, &distanceVector);
		D3DXVECTOR2 v1t = v1 - v1n; // tangent component 
		D3DXVECTOR2 v2t = v2 - v2n;
		D3DXVECTOR2 newV1n = (((spaceShip->getMass() - OtherSpaceShip->getMass()) * v1n) + (2 * OtherSpaceShip->getMass() * v2n)) / (spaceShip->getMass() + OtherSpaceShip->getMass()); //after collision change the normal; find the new normal with mass; refer wiki 
		D3DXVECTOR2 newV2n = (((OtherSpaceShip->getMass() - spaceShip->getMass()) * v2n) + (2 * spaceShip->getMass() * v1n)) / (spaceShip->getMass() + OtherSpaceShip->getMass());
		D3DXVECTOR2 newV1 = newV1n + v1t;//form the new vactor 
		D3DXVECTOR2 newV2 = newV2n + v2t;
		spaceShip->setVector(newV1);
		OtherSpaceShip->setVector(newV2);
	}
}

void collider::Circle(SpaceShip* spaceShip, Ball* ball)
{
	D3DXVECTOR2 v1 = spaceShip->getVector();
	D3DXVECTOR2 v2 = ball->getVector();
	D3DXVECTOR2 distanceVector = spaceShip->getPosition() - ball->getPosition();
	if (spaceShip->getLength() / 2.1 + ball->getLength() / 2.1 > D3DXVec2Length(&distanceVector)) {
		D3DXVec2Normalize(&distanceVector, &distanceVector); //normalize distance vector 
		D3DXVECTOR2 v1n = distanceVector * D3DXVec2Dot(&v1, &distanceVector); //vector 1 . n * n; normal component before collision 
		D3DXVECTOR2 v2n = distanceVector * D3DXVec2Dot(&v2, &distanceVector);
		D3DXVECTOR2 v1t = v1 - v1n; // tangent component 
		D3DXVECTOR2 v2t = v2 - v2n;
		D3DXVECTOR2 newV1n = (((spaceShip->getMass() - ball->getMass()) * v1n) + (2 * ball->getMass() * v2n)) / (spaceShip->getMass() + ball->getMass()); //after collision change the normal; find the new normal with mass; refer wiki 
		D3DXVECTOR2 newV2n = (((ball->getMass() - spaceShip->getMass()) * v2n) + (2 * spaceShip->getMass() * v1n)) / (spaceShip->getMass() + ball->getMass());
		D3DXVECTOR2 newV1 = newV1n + v1t;//form the new vactor 
		D3DXVECTOR2 newV2 = newV2n + v2t;
		spaceShip->setVector(newV1);
		ball->setVector(newV2);
	}
}


