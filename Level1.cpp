#include "Level1.h"
#include "bg.h"
//
//#define LEVEL1_WIDTH 10
//#define LEVEL1_HEIGHT 3

//#define LEVEL1_WIDTH 140 //4200/30=140
//#define LEVEL1_HEIGHT 200 //6000/30=200


#define LEVEL1_WIDTH 84 //4200/50=84
#define LEVEL1_HEIGHT 120 //6000/50=120




void Level1::initializePlayer() {
	//state.player.dieSound = Mix_LoadWAV("die.wav"); //must be 16 bit wav
	state.player.entityType = PLAYER;
	state.player.isStatic = false;
	state.player.width = 2.4f;
	state.player.height = 2.8f;
	state.player.lives = 3;
	state.player.position = glm::vec3(19, -54, 0);
	state.player.acceleration = glm::vec3(0, 0, 0);
	//collisions
	state.player.collider = new Entity();
	state.player.collider->entityType = COLLIDER;
	state.player.collider->isStatic = false;
	state.player.collider->height = 0.75f;
	state.player.collider->width = 0.5f;
	state.player.collider->textureID = Util::LoadTexture("images/dummy.png");
	state.player.collider->textureIDIdle = state.player.collider->textureID;
	state.player.collider->textureIDWalk = state.player.collider->textureID;
	state.player.collider->spriteWidthFB = 0.5f;
	state.player.collider->spriteHeightFB = 0.5f;
	//state.player.collider->position = glm::vec3(-2.0, -24.375, 0);
	state.player.collider->position = glm::vec3(0.0, 1.0, 0);
	//state.player.collider->spritePosition = glm::vec3(-2.0, -24.375, 0);
	state.player.collider->spritePosition = glm::vec3(1.0, -1.0, 0);
	state.player.collider->acceleration = glm::vec3(0, 0, 0);
	//player animation
	//state.player.textureID = Util::LoadTexture("images/chicken_front_back_skate.png");
	state.player.textureIDIdle = state.player.textureID;
	//state.player.textureIDWalk = Util::LoadTexture("images/chicken_side_skate_sheet3.png");
	state.player.spriteWidthFB = 2.4f;
	state.player.spriteHeightFB = 2.8f;
	state.player.spriteWidthW = 2.8f;
	state.player.spriteHeightW = 2.8f;
	state.player.cols = 3; //texture cols
	state.player.rows = 3; //texture rows
	state.player.colsWalk = 4; //texture cols
	state.player.rowsWalk = 4; //texture rows
	state.player.walkDown = new int[14]{ 0,0,0,0,0,3,2,1,1,1,1,1,4,2 };
	state.player.walkUp = new int[14] {6,6,6,6,6,6,5,7,7,7,7,7,7,5};
	state.player.idleUp = new int[14]{ 7,7,7,7,7,7,7,7,7,7,7,7,7,7 };
	state.player.idleDown = new int[14]{ 4,4,4,4,4,4,4,4,4,4,4,4,4,4 };
	state.player.walkRight = new int[27]{ 8,8,8,8,8,13,13,9,9,9,9,9,13,13,0,0,0,1,1,12,9,9,9,9,9,13,13 };
	state.player.walkLeft = new int[27]{ 11,11,11,11,11,14,14,10,10,10,10,10,14,14,3,3,3,2,2,15,10,10,10,10,10,14,14 };
	state.player.idleLeft = new int[27]{ 14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14 };
	state.player.idleRight = new int[27]{ 13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13 };
	state.player.currentAnim = state.player.idleDown;
	state.player.animFrames = 14;
	state.player.animFramesWalk = 27;
	state.player.animationState = UP_DOWN;
}

void Level1::initializeEnemies() {
	//GLuint enemyTextureID = Util::LoadTexture("images/man_sheet.png");
	state.enemies = enems;
	for (int i = 0; i <ENEMY_COUNT; i++) {
		state.enemies[i].isActive = true;
		state.enemies[i].entityType = ENEMY;
		state.enemies[i].aiType = MAN;
		state.enemies[i].aiState = MOVING;
		state.enemies[i].isStatic = false;
	    state.enemies[i].textureID = enemyTextureID;
		state.enemies[i].textureIDIdle = enemyTextureID;
		state.enemies[i].textureIDWalk = enemyTextureID;
		/*state.enemies[i].height = 1.5f;
		state.enemies[i].width = 1.8f;*/
		state.enemies[i].height = 0.5f;
		state.enemies[i].width = 0.5f;
		state.enemies[i].spriteWidthFB = 2.0f;
		state.enemies[i].spriteHeightFB = 2.4f;
		state.enemies[i].spriteWidthW = 2.0f;
		state.enemies[i].spriteHeightW = 2.4f;
		/*state.enemies[i].spriteWidthFB = state.enemies[i].width;
		state.enemies[i].spriteHeightFB = state.enemies[i].height;
		state.enemies[i].spriteWidthW = state.enemies[i].width;
		state.enemies[i].spriteHeightW = state.enemies[i].height;*/
		if (i % 2 == 0) {
			state.enemies[i].velocity = glm::vec3(6, 6, 0);
		}
		else {
			state.enemies[i].velocity = glm::vec3(8, 8, 0);
		}
		state.enemies[i].position = glm::vec3(8.0 + (6*i), -20.375, 0);
		
		state.enemies[i].spritePosition = state.enemies[i].position;
		state.enemies[i].spritePosition.y -= 0.9;
		state.enemies[i].speed = 0.1; //animation speed 
		state.enemies[i].cols = 2; //texture cols
		state.enemies[i].rows = 2; //texture rows
		state.enemies[i].colsWalk = 2;
		state.enemies[i].rowsWalk = 2;
		state.enemies[i].walkUp = new int[1]{ 1 };
		state.enemies[i].walkDown = new int[1]{ 0 };
		state.enemies[i].idleDown = new int[1]{ 0 };
		state.enemies[i].idleUp = new int[1]{ 1 };
		state.enemies[i].idleLeft = new int[1]{2 }; 
		state.enemies[i].walkRight = new int[1]{ 3 }; 
		state.enemies[i].idleRight = new int[1]{ 3 }; 
		state.enemies[i].walkLeft = new int[1]{ 2 };
		state.enemies[i].currentAnim = state.enemies[i].walkDown;
		state.enemies[i].animFrames = 1;
		state.enemies[i].aiType = MAN;
		state.enemies[i].aiState = MOVING;
		state.enemies[i].timer = 0;
	}


	state.enemies[2].position = glm::vec3(14.0f, -45.0f, 0); 
	state.enemies[3].position = glm::vec3(20.0f, -45.0f, 0);
	state.enemies[4].position = glm::vec3(6.0f, -45.0f, 0);
	state.enemies[5].position = glm::vec3(38.0f, -45.0f, 0);

	state.enemies[6].position = glm::vec3(24.0f, -25.0f, 0);
	state.enemies[7].position = glm::vec3(28.0f, -25.0f, 0);
	state.enemies[8].position = glm::vec3(30.0f, -35.0f, 0);
	state.enemies[9].position = glm::vec3(6.0f, -50.0f, 0);
	state.enemies[10].position = glm::vec3(12.0f, -25.0f, 0);
	state.enemies[11].position = glm::vec3(6.0f, -50.0f, 0);
	state.enemies[12].position = glm::vec3(30.0f, -50.0f, 0);
	state.enemies[13].position = glm::vec3(8.0f, -15.0f, 0);
	state.enemies[14].position = glm::vec3(7.0f, -45.0f, 0);

	state.enemies[15].position = glm::vec3(38.0f, -20.0f, 0);
	state.enemies[16].position = glm::vec3(28.0f, -10.0f, 0);
	state.enemies[17].position = glm::vec3(20.0f, -15.0f, 0);
	state.enemies[18].position = glm::vec3(8.0f, -5.0f, 0);
	state.enemies[19].position = glm::vec3(21.0f, -2.0f, 0);
	state.enemies[20].position = glm::vec3(38.0f, -30.0f, 0);
	state.enemies[21].position = glm::vec3(30.0f, -25.0f, 0);
	state.enemies[22].position = glm::vec3(6.0f, -4.0f, 0);
	state.enemies[23].position = glm::vec3(35.0f, -4.0f, 0);
	state.enemies[24].position = glm::vec3(20.0f, -12.0f, 0);
	

	
}

void Level1::Initialize() {
	sign.position = glm::vec3(18.0, 5.5, 0.0);
	sign.spritePosition = sign.position;
	sign.height = 2.0f;
	sign.width = 2.0f;
	sign.spriteWidthFB = 5.0f;
	sign.spriteHeightFB = 5.0f;
	bg.position = glm::vec3(20.85, -29.85, 0);
	bg.spritePosition = bg.position;
	bg.height = 3.2f;
	bg.width = 0.5f;
	bg.spriteWidthFB = 42.00f;
	bg.spriteHeightFB = 60.00f;

	music = Mix_LoadMUS("sounds/music.mp3");
	Mix_PlayMusic(music, -1); //play music and loop forever
	Mix_VolumeMusic(3*(MIX_MAX_VOLUME /4)); //set volume from 0 10 128
	//Mix_HaltMusic(); //stop the music
	//state.player.die = Mix_LoadWAV("die.wav"); //must be 16 bit wav
	//Mix_PlayChannel(-1, bounce, 0); play chunk once and do not loop
	Mix_Volume(-1, MIX_MAX_VOLUME / 2); //set all channels to half volume
	/*cameraXMax = 10.5f; ///24.0f;
	cameraXMin = -15.5f;
	cameraYMax = 27.25f; ///24.0f;
	cameraYMin = -24.375f;*/
	cameraXMax = 50.0; ///24.0f;
	cameraXMin = -5.0f;
	cameraYMax = 1.0f; ///24.0f;
	cameraYMin = -60.0f;

	glClearColor(255.0f, 255.0f, 255.0f, 1.0f);
	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//fontTextureID = Util::LoadTexture("images/pixel_font.png");
	//GLuint mapTextureID = Util::LoadTexture("images/tileMap_4200_6060.jpg");
	//GLuint mapTextureID = Util::LoadTexture("images/dummy5.jpg");
	state.map = new Map(LEVEL1_WIDTH, LEVEL1_HEIGHT, level1_data, mapTextureID, 0.5f, 1, 1);
	//state.map = new Map(LEVEL1_WIDTH, LEVEL1_HEIGHT, level1_data, mapTextureID, 1.0f, 1, 1);
	//state.fg_2 = new Map(LEVEL1_WIDTH, LEVEL1_HEIGHT, level1_fg2, mapTextureID, 1.0f, 4, 11);
	initializePlayer();
	textPosition = glm::vec3(25, -49.5, 0);
	//the player position - # comes from the start position!!
	textDistanceFromPlayer = glm::vec3 (textPosition.x - state.player.position.x -2, 
		textPosition.y-state.player.position.y,1.0f);
	initializeEnemies();
	state.nextLevel = -1;
	
}
void Level1::Update(float deltaTime) {
	state.player.Update(deltaTime, state.player, state.enemies, ENEMY_COUNT, state.map);
	updateText();
	for (int i = 0; i < ENEMY_COUNT; i++) {
		state.enemies[i].Update(deltaTime, state.player, state.enemies, ENEMY_COUNT, state.map);
	}


	if (state.player.lives == 0) {
		state.nextLevel = 2;
	}

	if (state.player.position.y > 2.0) {
		Mix_HaltMusic(); //stop the music
	}

	if (state.player.position.y > cameraYMax + 3) {
		state.nextLevel = 3;
	}
	

}

void Level1::updateText() {
	if (state.player.position.x > cameraXMin&&
		state.player.position.x < cameraXMax) {
		textPosition = glm::vec3(state.player.position.x + textDistanceFromPlayer.x, textPosition.y, 1.0f);
	}
	else if (state.player.position.x > cameraXMax) {
		textPosition = glm::vec3(cameraXMax + textDistanceFromPlayer.x,	textPosition.y, 1.0f);
	}
	else if (state.player.position.x < cameraXMin) {
		textPosition = glm::vec3(cameraXMin + textDistanceFromPlayer.x, textPosition.y, 1.0f);
	}

	if (state.player.position.y < cameraYMax &&
		state.player.position.y > cameraYMin) {
		textPosition = glm::vec3(textPosition.x, state.player.position.y + textDistanceFromPlayer.y, 1.0f);
	}
	else if (state.player.position.y < cameraYMin) {
		textPosition = glm::vec3(textPosition.x, cameraYMin + textDistanceFromPlayer.y, 1.0f);
	}
	else if (state.player.position.y > cameraYMax) {
		textPosition = glm::vec3(textPosition.x, cameraYMax + textDistanceFromPlayer.y, 1.0f);
	}
}

void Level1::Render(ShaderProgram* program) {
	bg.simpleRender(program);
	sign.simpleRender(program);
	//state.map->Render(program);
	for (int i = 0; i < ENEMY_COUNT; i++) {
		state.enemies[i].Render(program);
	}
	state.player.Render(program);
	//collider.simpleRender(program);
	//state.player.collider->simpleRender(program);
	drawInfo(program);	
}

void Level1 :: drawInfo(ShaderProgram* program) {
	std::ostringstream lives;
	lives << "Lives: " << state.player.lives;
	std::string str = lives.str();
		Util::DrawText(program, fontTextureID, str, 0.5f, -0.05f, textPosition);	
}

/*
if (state.player.position.x > cameraXMin) {
		if (state.player.position.x > cameraXMax) {
			Util::DrawText(program, fontTextureID, str, 0.4f, -0.05f, glm::vec3(cameraXMax + textDistanceFromPlayer.x,
				textPosition.y, 1.0f));
		}
		else {
			Util::DrawText(program, fontTextureID, str, 0.4f, -0.05f, glm::vec3(state.player.position.x + textDistanceFromPlayer.x,
				textPosition.y, 1.0f));
		}
	}
	else {
		Util::DrawText(program, fontTextureID, str, 0.4f, -0.05f, textPosition);
	}

*/