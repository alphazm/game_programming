#include "Field1.h"

Field1::Field1()
{
	sprite = NULL;
	texture = NULL;
}

Field1::~Field1()
{
	sprite->Release();
	sprite = NULL;
	texture->Release();
	texture = NULL;
	gameObjects.clear();
	delete player1;
	delete player2;
	delete ball;
}

void Field1::init()
{
	
	input = Input::getInstance();
	player1 = new SpaceShip();
	player2 = new SpaceShip();
	ball = new Ball();
	goal1.left = goal1.top = 0;
	goal1.right = 50;
	goal1.bottom =180;
	goal2.left = goal2.top = 0;
	goal2.right = 50;
	goal2.bottom = 180;
	field.left = field.top = 0;
	field.right = 720;
	field.bottom = 480;
	fieldPosition = new D3DXVECTOR3(180, 120,0);
	gate1Position = new D3DXVECTOR3(155,270,0);
	gate2Position = new D3DXVECTOR3(875, 270, 0);
	device = Graphics::getInstance()->d3dDevice;
	D3DXCreateSprite(device, &sprite);
	D3DXCreateTextureFromFile(device, "assets/field.png",&texture);
	D3DXCreateTextureFromFile(device, "assets/door.png", &texture2);
	player1->Initialize(device, sprite, { 250,360 }, 0);
	player1->setRotation(4.71f);
	player1->setPlayerNumber(0);
	player1->setFriction(0.8);
	player2->Initialize(device,  sprite,{ 830,360 }, 1);
	player2->setRotation(1.57f);
	player2->setPlayerNumber(1);
	player2->setFriction(0.8);
	ball->Initialize(device, sprite,{ WIN_WIDTH / 2, WIN_HEIGHT / 2 }, 2);
	ball->setFriction(0.6);
	gameObjects.push_back(player1);
	gameObjects.push_back(player2);
	gameObjects.push_back(ball);
	D3DXMatrixTransformation2D(&mat, NULL, NULL, NULL, NULL, NULL, NULL);
}

void Field1::update()
{
	//p1
	if (input->aKey())
		player1->rotation -= player1->rotationSpeed;
	if (input->dKey())
		player1->rotation += player1->rotationSpeed;
	if (input->aKey())
		player1->force = { player1->enginePower * (float)cos(player1->rotation),  player1->enginePower * (float)sin(player1->rotation) };
	if (input->sKey())
		player1->force = { (player1->enginePower * (float)cos(player1->rotation))*-1,  (player1->enginePower * (float)sin(player1->rotation))*-1 };
	//p2
	if (input->leftKey())
		player2->rotation -= player2->rotationSpeed;
	if (input->RightKey())
		player2->rotation += player2->rotationSpeed;
	if (input->upKey())
		player2->force = { player2->enginePower * (float)cos(player2->rotation),  player2->enginePower * (float)sin(player2->rotation) };
	if (input->downKey())
		player2->force = { (player2->enginePower * (float)cos(player2->rotation)) * -1,  (player2->enginePower * (float)sin(player2->rotation)) * -1 };
	collider.Circle(player1, player2);
	collider.Circle(player1, ball);
	collider.Circle(player2, ball);
	collider.inside(ball, &field);
	collider.inside(player1, &field);
	collider.inside(player2, &field);
	if (collider.leftGoal(ball, &goal1, &field))
		//player1 win
		;
	if (collider.rightGoal(ball, &goal2, &field))
			//player2 win
		;
}

void Field1::draw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->SetTransform(&mat);
	sprite->Draw(texture, &field, NULL, fieldPosition, D3DCOLOR_XRGB(255, 255, 255));
	sprite->Draw(texture2, &goal1, NULL, gate1Position, D3DCOLOR_XRGB(255, 255, 255));
	sprite->Draw(texture2, &goal2, NULL, gate2Position, D3DCOLOR_XRGB(255, 255, 255));
	
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->Draw();
	}
	sprite->End();
}

void Field1::release()
{
}

