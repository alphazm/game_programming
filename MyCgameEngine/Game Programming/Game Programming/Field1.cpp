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
	timer = new FrameTimer();
	timer->Init(30);
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
	player1->Initialize(device, D3DXVECTOR2(250,WIN_HEIGHT / 2), 0);
	player1->setRotation(1.57f);
	player1->setPlayerNumber(0);
	player1->setFriction(0.8);
	player2->Initialize(device, D3DXVECTOR2(830,WIN_HEIGHT / 2 ), 1);
	player2->setRotation(4.71f);
	player2->setPlayerNumber(1);
	player2->setFriction(0.8);
	ball->Initialize(device, D3DXVECTOR2(WIN_WIDTH / 2, WIN_HEIGHT / 2 ), 2);
	gameObjects.push_back(player1);
	gameObjects.push_back(player2);
	gameObjects.push_back(ball);
	D3DXMatrixTransformation2D(&mat, NULL, NULL, NULL, NULL, NULL, NULL);

}

void Field1::update()
{
	for (int i = 0; i < timer->FramesToUpdate(); i++) {
		//p1
		if (input->aKey())
			player1->rotation -= player1->rotationSpeed;
		if (input->dKey())
			player1->rotation += player1->rotationSpeed;
		if (input->wKey())
			player1->acceleration = { player1->enginePower /player1->mass,  player1->enginePower / player1->mass};
		if (input->sKey())
			player1->acceleration = { -(player1->enginePower / player1->mass) ,  -(player1->enginePower / player1->mass) };
		//p2
		if (input->leftKey())
			player2->rotation -= player2->rotationSpeed;
		if (input->RightKey())
			player2->rotation += player2->rotationSpeed;
		if (input->upKey())
			player2->acceleration = { player2->enginePower / player2->mass,  player2->enginePower / player2->mass };
		if (input->downKey())
			player2->acceleration = { -(player2->enginePower / player2->mass) ,  -(player2->enginePower / player2->mass) };
		collider.Circle(player1, player2);
		collider.Circle(player1, ball);
		collider.Circle(player2, ball);
		collider.inside(ball, &field, fieldPosition);
		collider.inside(player1, &field, fieldPosition);
		collider.inside(player2, &field, fieldPosition);
		if (collider.leftGoal(ball, &goal1, gate1Position)) {
			player1->position = D3DXVECTOR2(250, WIN_HEIGHT / 2);
			player1->rotation = 1.57f;
			player1->acceleration = { 0,0 };
			player1->velocity = { 0,0 };
			player2->position = D3DXVECTOR2(830, WIN_HEIGHT / 2);
			player2->rotation = 4.71f;
			player2->acceleration = { 0,0 };
			player2->velocity = { 0,0 };
			ball->position = D3DXVECTOR2(WIN_WIDTH / 2, WIN_HEIGHT / 2);
			ball->rotation = 0;
			ball->velocity = { 0,0 };
			Scorep2 += 1;
		}
		if (collider.rightGoal(ball, &goal2, gate2Position)) {
			player1->position = D3DXVECTOR2(250, WIN_HEIGHT / 2);
			player1->rotation = 1.57f;
			player1->acceleration = { 0,0 };
			player1->velocity = { 0,0 };
			player2->position = D3DXVECTOR2(830, WIN_HEIGHT / 2);
			player2->rotation = 4.71f;
			player2->acceleration = { 0,0 };
			player2->velocity = { 0,0 };
			ball->position = D3DXVECTOR2(WIN_WIDTH / 2, WIN_HEIGHT / 2);
			ball->rotation = 0;
			ball->velocity = { 0,0 };
			Scorep2 += 1;
		}
		if (Scorep1 == 12) {
			StateManager::getInstance()->initGameOver(device);
			StateManager::getInstance()->setGameOverState(1);
			return;
		}
		if (Scorep2 == 12) {
			StateManager::getInstance()->initGameOver(device);
			StateManager::getInstance()->setGameOverState(2);
			return;
		}
		player1->direction = { (float)sin(player1->rotation),-(float)cos(player1->rotation) };
		player1->acceleration = { player1->acceleration.x * player1->direction.x,  player1->acceleration.y * player1->direction.y };
		player1->velocity += player1->acceleration;
		player1->velocity *= player1->friction;
		player1->position += player1->velocity;
		player2->direction = { (float)sin(player2->rotation),-(float)cos(player2->rotation) };
		player2->acceleration = { player2->acceleration.x * player2->direction.x,  player2->acceleration.y * player2->direction.y };
		player2->velocity += player2->acceleration;
		player2->velocity *= player2->friction;
		player2->position += player2->velocity;
		
		ball->position += ball->velocity;
		player1->Update();
		player2->Update();
		ball->Update();
	}
}

void Field1::draw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->SetTransform(&mat);
	sprite->Draw(texture, &field, NULL, fieldPosition, D3DCOLOR_XRGB(255, 255, 255));
	sprite->Draw(texture2, &goal1, NULL, gate1Position, D3DCOLOR_XRGB(255, 255, 255));
	sprite->Draw(texture2, &goal2, NULL, gate2Position, D3DCOLOR_XRGB(255, 255, 255));
	sprite->End();
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->Draw();
	}
	
}

void Field1::release()
{
}

