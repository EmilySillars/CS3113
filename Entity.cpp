#include "Entity.h"

Entity::Entity()
{
	collider = NULL;
    entityType = PLATFORM;
    isStatic = true;
    isActive = true;
    position = glm::vec3(0);
    speed = 0;
    width = 1;
    height = 1;
	spriteWidthFB = 1;
	spriteHeightFB = 1;
	spritePosition = position;
	//AI
	aiDirection = glm::vec3(0, -1, 0);
	//animation
	animationState = UP_DOWN;
	timer = 0;
	animTime = 0;
	animIndex = 0;
	aiType = MAN;
	aiState = MOVING;
	lives = -1;
	//sounds
	dieSound = Mix_LoadWAV("sounds/die.wav"); //must be 16 bit wav
}
//236, 162, 242
//glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
//glClearColor((236/255)f, (162/255)f, (242/255)f, 1.0f);
//glClearColor((159 / 255), (237 / 255), (233 / 255), 1.0f);

bool Entity::CheckCollision(Entity other)
{
    if (isStatic == true) return false;
    if (isActive == false || other.isActive == false) return false;
    
    float xdist = fabs(position.x - other.position.x) - ((width + other.width) / 2.0f);
    float ydist = fabs(position.y - other.position.y) - ((height + other.height) / 2.0f);

    if (xdist < 0 && ydist < 0)
    {
        if (entityType == PLAYER && other.entityType == BONE)
        {
            other.isActive = false;
        }
        
        return true;
    }
    
    return false;
}

bool Entity::pointBoxCollision(glm::vec3 point, Entity box) {
	float leftEdge = box.position.x- (box.width / 2);
	float rightEdge = box.position.x + (box.width/2);
	float topEdge = box.position.y + (box.height / 2);
	float bottomEdge = box.position.y - (box.height / 2);
	return ((point.x < rightEdge && point.x > leftEdge) && (point.y < topEdge && point.y > bottomEdge));
}

bool Entity::verticalSegmentBoxOverlap(glm::vec3 start, glm::vec3 end, Entity box) {
	float topEdge = box.position.y + (box.height / 2);
	float bottomEdge = box.position.y - (box.height / 2);
	float leftEdge = box.position.x - (box.width / 2);
	float rightEdge = box.position.x + (box.width / 2);
	//three cases for vertical overlap:
	bool y = (start.y > bottomEdge && start.y < topEdge) // case 1: start point overlaps box vertically.
		|| (end.y > bottomEdge && end.y < topEdge)       // case 2: endpoint overlaps box vertically.
		|| (start.y < bottomEdge && end.y >topEdge);     // case 3: box is in between start and end points.
	bool x = ((start.x > leftEdge) && (start.x < rightEdge)); //start and end points have same x-coord.
	return (x && y);
}

bool Entity::horizontalSegmentBoxOverlap(glm::vec3 start, glm::vec3 end, Entity box) {
	float leftEdge = box.position.x - (box.width / 2);
	float rightEdge = box.position.x + (box.width / 2);
	float topEdge = box.position.y + (box.height / 2);
	float bottomEdge = box.position.y - (box.height / 2);
	//three cases for horizontal overlap:
	bool y = (start.x > leftEdge && start.x < rightEdge) // case 1: start point overlaps box horizontally.
		|| (end.x > leftEdge && end.x < rightEdge)       // case 2: endpoint overlaps box horizontally.
		|| (start.x < leftEdge && end.x >rightEdge);     // case 3: box is in between start and end points.
	bool x = ((start.y > bottomEdge) && (start.y < topEdge)); //start and end points have same y-coord.
	return (x && y);
}

int Entity::CheckCollisionsY(Entity *objects, int objectCount)
{
	// Probes for objects
	glm::vec3 top = glm::vec3(position.x, position.y + (height / 2), position.z);
	glm::vec3 top_left = glm::vec3(position.x - (width / 2), position.y + (height / 2), position.z);
	glm::vec3 top_right = glm::vec3(position.x + (width / 2), position.y + (height / 2), position.z);

	glm::vec3 bottom = glm::vec3(position.x, position.y - (height / 2), position.z);
	glm::vec3 bottom_left = glm::vec3(position.x - (width / 2), position.y - (height / 2), position.z);
	glm::vec3 bottom_right = glm::vec3(position.x + (width / 2), position.y - (height / 2), position.z);

    for (int i = 0; i < objectCount; i++)
    {
        Entity object = objects[i];
        
        if (CheckCollision(object))
        {
            float ydist = fabs(position.y - object.position.y);
            float penetrationY = fabs(ydist - (height / 2) - (object.height / 2));
			//pointBoxCollision(top_left, object) || pointBoxCollision(top_right, object) || pointBoxCollision(top, object)
            if (horizontalSegmentBoxOverlap(top_left,top_right, object)) {
                position.y -= penetrationY;
                velocity.y = 0;
                collidedTop = true;
				if (object.entityType == ENEMY) {
					//glClearColor((159.0f / 255.0f), (237.0f / 255.0f), (233.0f / 255.0f), 1.0f);
					//lives--;
					//position.y -= 0.4f;
					//Mix_PlayChannel(-1, dieSound, 0); //play chunk once and do not loop
					return ENEMY;
				}
				//glClearColor((103.0f / 255.0f), (140.0f / 255.0f), (214.0f / 255.0f), 1.0f);
				//glClearColor((207.0f / 255.0f), (114.0f / 255.0f), (103.0f / 255.0f), 1.0f);
            }
            else if (horizontalSegmentBoxOverlap(bottom_left, bottom_right, object)) {
                position.y += penetrationY;
                velocity.y = 0;
                collidedBottom = true;
				if (object.entityType == ENEMY) {
					//glClearColor((159.0f / 255.0f), (237.0f / 255.0f), (233.0f / 255.0f), 1.0f);
					//lives--;
					//position.y += 0.4f;
					//Mix_PlayChannel(-1, dieSound, 0); //play chunk once and do not loop
					return ENEMY;
				}
				//glClearColor((151.0f / 255.0f), (232.0f / 255.0f), (210.0f / 255.0f), 1.0f);
				/*if (object.entityType == ENEMY && object.aiState == FLAT) {
					glClearColor((50.0f / 255.0f), (50.0f / 255.0f), (210.0f / 255.0f), 1.0f);
				}*/
            }
        }
    }
	return -1;//did not collide with an enemy
}

//void Entity::CheckCollisionsX(Entity *objects, int objectCount)
//{
//	// Probes for objects
//	glm::vec3 top = glm::vec3(position.x, position.y + (height / 2), position.z);
//	glm::vec3 top_left = glm::vec3(position.x - (width / 2), position.y + (height / 2), position.z);
//	glm::vec3 top_right = glm::vec3(position.x + (width / 2), position.y + (height / 2), position.z);
//
//	glm::vec3 bottom = glm::vec3(position.x, position.y - (height / 2), position.z);
//	glm::vec3 bottom_left = glm::vec3(position.x - (width / 2), position.y - (height / 2), position.z);
//	glm::vec3 bottom_right = glm::vec3(position.x + (width / 2), position.y - (height / 2), position.z);
//
//	for (int i = 0; i < objectCount; i++)
//	{
//		Entity object = objects[i];
//
//		if (CheckCollision(object))
//		{
//			float xdist = fabs(position.x - object.position.x);
//			float penetrationX = fabs(xdist - (width / 2) - (object.width / 2));
//			if (verticalSegmentBoxOverlap(top_left, bottom_left, object)) {
//				position.x += penetrationX;
//				velocity.x = 0;
//				collidedLeft = true;
//				glClearColor((103.0f / 255.0f), (140.0f / 255.0f), (214.0f / 255.0f), 1.0f);
//			}
//			else if (verticalSegmentBoxOverlap(top_right, bottom_right, object)) {
//				position.x -= penetrationX;
//				velocity.x = 0;
//				collidedRight = true;
//				glClearColor((103.0f / 255.0f), (140.0f / 255.0f), (214.0f / 255.0f), 1.0f);
//			}
//		}
//	}
//}

int Entity::CheckCollisionsX(Entity *objects, int objectCount)
{
	// Probes for objects
	glm::vec3 left = glm::vec3(position.x - (width*0.6), position.y, position.z);
	glm::vec3 right = glm::vec3(position.x + (width*0.6), position.y, position.z);
    for (int i = 0; i < objectCount; i++)
    {
        Entity object = objects[i];
        
        if (CheckCollision(object))
        {
            float xdist = fabs(position.x - object.position.x);
            float penetrationX = fabs(xdist - (width / 2) - (object.width / 2));
            if (pointBoxCollision(right, object)) {
                position.x -= penetrationX;
                velocity.x = 0;
                collidedRight = true;
				if (object.entityType == ENEMY ) { 
					//glClearColor((159.0f / 255.0f), (237.0f / 255.0f), (233.0f / 255.0f), 1.0f);
					//lives--; 
					//position.x -= 0.4f;
					//Mix_PlayChannel(-1, dieSound, 0); //play chunk once and do not loop
					return ENEMY;
				}
				//glClearColor((159.0f / 255.0f), (237.0f / 255.0f), (233.0f / 255.0f), 1.0f);
				//glClearColor((103.0f / 255.0f), (140.0f / 255.0f), (214.0f / 255.0f), 1.0f);
            }
            else if (pointBoxCollision(left, object)) {
                position.x += penetrationX;
                velocity.x = 0;
                collidedLeft = true;
				if (object.entityType == ENEMY ) {
					//lives--;
					//position.x += 0.4f;
					//Mix_PlayChannel(-1, dieSound, 0); //play chunk once and do not loop
					return ENEMY;
				}
				//glClearColor((103.0f / 255.0f), (140.0f / 255.0f), (214.0f / 255.0f), 1.0f);
            }
        }
    }
	return -1;
}


void Entity::Jump()
{
    if (collidedBottom)
    {
        velocity.y = 5.0f;
    }
}

void Entity::CheckCollisionsY(Map* map)
{
	// Probes for tiles
	glm::vec3 top = glm::vec3(position.x, position.y + (height / 2), position.z);
	glm::vec3 top_left = glm::vec3(position.x - (width / 2), position.y + (height / 2), position.z);
	glm::vec3 top_right = glm::vec3(position.x + (width / 2), position.y + (height / 2), position.z);

	glm::vec3 bottom = glm::vec3(position.x, position.y - (height / 2), position.z);
	glm::vec3 bottom_left = glm::vec3(position.x - (width / 2), position.y - (height / 2), position.z);
	glm::vec3 bottom_right = glm::vec3(position.x + (width / 2), position.y - (height / 2), position.z);

	float penetration_x = 0;
	float penetration_y = 0;
	if (map->IsSolid(top, &penetration_x, &penetration_y) && velocity.y > 0) {
		position.y -= penetration_y;
		velocity.y = 0;
		collidedTop = true;
	}
	else if (map->IsSolid(top_left, &penetration_x, &penetration_y) && velocity.y > 0) {
		position.y -= penetration_y;
		velocity.y = 0;
		collidedTop = true;
	}
	else if (map->IsSolid(top_right, &penetration_x, &penetration_y) && velocity.y > 0) {
		position.y -= penetration_y;
		velocity.y = 0;
		collidedTop = true;
	}
	if (map->IsSolid(bottom, &penetration_x, &penetration_y) && velocity.y < 0) {
		position.y += penetration_y;
		velocity.y = 0;
		collidedBottom = true;
	}
	else if (map->IsSolid(bottom_left, &penetration_x, &penetration_y) && velocity.y < 0) {
		position.y += penetration_y;
		velocity.y = 0;
		collidedBottom = true;
	}
	else if (map->IsSolid(bottom_right, &penetration_x, &penetration_y) && velocity.y < 0) {
		position.y += penetration_y;
		velocity.y = 0;
		collidedBottom = true;
	}
	
	if (entityType == ENEMY && (collidedBottom || collidedTop)) {
		aiDirection.x = 0;
		aiDirection.y = 0;
	}
}

void Entity::CheckCollisionsX(Map* map)
{
	// Probes for tiles
	glm::vec3 left = glm::vec3(position.x - (width / 2), position.y, position.z);
	glm::vec3 top_left = glm::vec3(position.x - (width / 2), position.y + (height / 2), position.z);
	glm::vec3 bottom_left = glm::vec3(position.x - (width / 2), position.y - (height / 2), position.z);

	glm::vec3 right = glm::vec3(position.x + (width / 2), position.y, position.z);
	glm::vec3 top_right = glm::vec3(position.x + (width / 2), position.y + (height / 2), position.z);
	glm::vec3 bottom_right = glm::vec3(position.x + (width / 2), position.y - (height / 2), position.z);
	
	float penetration_x = 0;
	float penetration_y = 0;
	if (map->IsSolid(left, &penetration_x, &penetration_y) && velocity.x < 0) {
		position.x += penetration_x;
		velocity.x = 0;
		collidedLeft = true;
	}

	if (map->IsSolid(top_left, &penetration_x, &penetration_y) && velocity.x < 0) {
		position.x += penetration_x;
		velocity.x = 0;
		collidedLeft = true;
	}

	if (map->IsSolid(bottom_left, &penetration_x, &penetration_y) && velocity.x < 0) {
		position.x += penetration_x;
		velocity.x = 0;
		collidedLeft = true;
	}

	if (map->IsSolid(right, &penetration_x, &penetration_y) && velocity.x > 0) {
		position.x -= penetration_x;
		velocity.x = 0;
		collidedRight = true;
	}

	if (map->IsSolid(top_right, &penetration_x, &penetration_y) && velocity.x > 0) {
		position.x -= penetration_x;
		velocity.x = 0;
		collidedRight = true;
	}

	if (map->IsSolid(bottom_right, &penetration_x, &penetration_y) && velocity.x > 0) {
		position.x -= penetration_x;
		velocity.x = 0;
		collidedRight = true;
	}

	if (entityType == ENEMY && (collidedLeft || collidedRight)) {
		aiDirection.x = 0;
		aiDirection.y = 0;
	}
}

void Entity::UpdateAnimation(float deltaTime) {
	//update animation based on movement
	if (velocity.x > 0 || velocity.x <0 ) {
		if(velocity.x > 0)
		animationState = RIGHT;
		if (velocity.x < 0)
		animationState = LEFT;
	}
	else if (velocity.y > 0 || velocity.y < 0) {
		animationState = UP_DOWN;
	}
	else {
		if (animationState == RIGHT)
			animationState = RIGHT_IDLE;
		if (animationState == LEFT)
			animationState = LEFT_IDLE;
	}
	
	animTime += deltaTime;

	
	if (animTime >= 0.1f) //means 8 fps
	{
		animTime = 0;
		animIndex++;
		switch (animationState) {
		case UP_DOWN:
			if (animIndex >= animFrames)
			{
				animIndex = 0;
			}
			break;
		default:
			if (animIndex >= animFramesWalk)
			{
				animIndex = 0;
			}
			break;
		}
		
	}
	
}


void Entity::Update(float deltaTime, Entity player, Entity* objects, int objectCount, Map* map)
{
	collidedTop = false;
	collidedBottom = false;
	collidedLeft = false;
	collidedRight = false;

	velocity += acceleration * deltaTime; //gravity

	if (entityType == PLAYER) {
		int other = -1;

		//move horizontally
		position.x += velocity.x * deltaTime; 
		updateCollider();
		other = collider->CheckCollisionsX(objects, objectCount); // Fix if needed
		if (collider->collidedLeft || collider->collidedRight) {
			position.x = (collider->position).x - (collider->colliderXOffset);
		}
		if (other == ENEMY) {
			lives--;
			position = glm::vec3(19, -54, 0);
			Mix_PlayChannel(-1, dieSound, 0); //play chunk once and do not loop
		}
		//do it again for map:
		updateCollider();
		collider->CheckCollisionsX(map); // Fix if needed
		if (collider->collidedLeft || collider->collidedRight) {
			position.x = (collider->position).x - (collider->colliderXOffset);
		}
		//move vertically
		position.y += velocity.y * deltaTime;
		updateCollider();		
		other = collider->CheckCollisionsY(objects, objectCount); // Fix if needed
		if (collider->collidedTop || collider->collidedBottom) {
			position.y = (collider->position).y - (collider->colliderYOffset);
			//position.y = (collider->position).y + 1.15;
		}
		if (other == ENEMY) {
			lives--;
			position = glm::vec3(19, -54, 0);
			Mix_PlayChannel(-1, dieSound, 0); //play chunk once and do not loop
		}
		//do it again for map:
		updateCollider();
		 collider->CheckCollisionsY(map); // Fix if needed
		if (collider->collidedTop || collider->collidedBottom) {
			position.y = (collider->position).y - (collider->colliderYOffset);
		}
	}
	else {
		position.y += velocity.y * deltaTime; // Move on Y
		CheckCollisionsY(map);
		CheckCollisionsY(objects, objectCount); // Fix if needed

		position.x += velocity.x * deltaTime; // Move on X
		CheckCollisionsX(map);
		CheckCollisionsX(objects, objectCount); // Fix if needed
	}

	if (entityType == ENEMY) {
		//call AI function!
		AIUpdate(player, deltaTime);
		//UpdateAnimation(deltaTime);
	}
	else { //player

		//position.x = 0;
		//position.y = 0;
		//std::cout << "position is (" << position.x << "," << position.y << ")\n";
		spritePosition = position;
		UpdateAnimation(deltaTime);
	}

	
}

void Entity::updateCollider() {
	collider->collidedTop = false;
	collider->collidedBottom = false;
	collider->collidedLeft = false;
	collider->collidedRight = false;
	float XOffset = 0;
	float YOffset = 0;
	switch (animationState) {
	case UP_DOWN:
		collider->spriteWidthFB = 0.35;
		collider->spriteHeightFB = 0.5;
		XOffset = 0;
		YOffset = -1.15;
		break;
	case RIGHT:
		XOffset = 0.4;
		YOffset = -1.15;
		collider->spriteWidthFB = 0.74;
		collider->spriteHeightFB = 0.35;
		break;
	case RIGHT_IDLE:
		XOffset = 0.1;
		YOffset = -1.15;
		collider->spriteWidthFB = 1.0;
		collider->spriteHeightFB = 0.35;
		break;
	case LEFT:
		XOffset = -0.4;
		YOffset = -1.15;
		collider->spriteWidthFB = 0.74;
		collider->spriteHeightFB = 0.35;
		break;	
	case LEFT_IDLE:
		XOffset = -0.1;
		YOffset = -1.15;
		collider->spriteWidthFB = 1.0;
		collider->spriteHeightFB = 0.35;
		break;
	}
	//update height and width
	collider->width = collider->spriteWidthFB;
	collider->height = collider->spriteHeightFB;
	//update position
	collider->position.x = position.x + XOffset;
	collider->position.y = position.y + YOffset;
	collider->spritePosition.x = position.x + XOffset;
	collider->spritePosition.y = position.y + YOffset;
	//update offsets
	collider->colliderXOffset = XOffset;
	collider->colliderYOffset = YOffset;
	//update velocity so collisions with maps work!
	collider->velocity = velocity;
}

void Entity::simpleRender(ShaderProgram* program) {
	if (!isActive) { return; }
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, spritePosition);
	program->SetModelMatrix(modelMatrix);
	float x = spriteWidthFB / 2;
	float y = spriteHeightFB / 2;
	float vertices[] = { -1 * x, -1 * y, x, -1 * y, x, y, -1 * x, -1 * y, x, y, -1 * x, y };
	//float vertices[] = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
	float texCoords[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };

	glBindTexture(GL_TEXTURE_2D, textureID);

	glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices);
	glEnableVertexAttribArray(program->positionAttribute);

	glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
	glEnableVertexAttribArray(program->texCoordAttribute);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(program->positionAttribute);
	glDisableVertexAttribArray(program->texCoordAttribute);
}

void Entity::Render(ShaderProgram *program) {
	if (!isActive) { return; }
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, spritePosition);
	program->SetModelMatrix(modelMatrix);
	if (velocity.x < 0) {
		DrawSpriteFromTextureAtlas(program, walkLeft[animIndex], textureIDWalk,rowsWalk, colsWalk,spriteWidthW, spriteHeightW);
		currentAnim = idleLeft;
	}
	else if (velocity.x > 0) {
		DrawSpriteFromTextureAtlas(program, walkRight[animIndex], textureIDWalk, rowsWalk, colsWalk, spriteWidthW, spriteHeightW);
		currentAnim = idleRight;
	}
	else if (velocity.y > 0) {
		DrawSpriteFromTextureAtlas(program, walkUp[animIndex], textureID, rows, cols, spriteWidthFB, spriteHeightFB);
		currentAnim = idleUp;
	}
	else if (velocity.y < 0) {
		DrawSpriteFromTextureAtlas(program, walkDown[animIndex], textureID, rows, cols, spriteWidthFB, spriteHeightFB);
		currentAnim = idleDown;
	}
	else {
		if (animationState == UP_DOWN) {
			DrawSpriteFromTextureAtlas(program, currentAnim[animIndex], textureIDIdle, rows, cols, spriteWidthFB, spriteHeightFB);
		}
		else {
			DrawSpriteFromTextureAtlas(program, currentAnim[animIndex], textureIDWalk, rowsWalk, colsWalk, spriteWidthW, spriteHeightW);
		}
	}
}

void Entity::DrawSpriteFromTextureAtlas(ShaderProgram *program, int index, GLuint textureID, int rows, int cols, float spriteWidth, float  spriteHeight)
{
	float u = (float)(index % cols) / (float)cols;
	float v = (float)(index / cols) / (float)rows;

	float width = 1.0f / (float)cols;
	float height = 1.0f / (float)rows;

	float texCoords[] = { u, v + height, u + width, v + height, u + width, v,
		u, v + height, u + width, v, u, v };
	float x = spriteWidth / 2;
	float y = spriteHeight / 2;
	float vertices[] = { -1 * x, -1 * y, x, -1 * y, x, y, -1 * x, -1 * y, x, y, -1 * x, y };

	glBindTexture(GL_TEXTURE_2D, textureID);

	glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices);
	glEnableVertexAttribArray(program->positionAttribute);

	glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
	glEnableVertexAttribArray(program->texCoordAttribute);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(program->positionAttribute);
	glDisableVertexAttribArray(program->texCoordAttribute);
}

void Entity::AIUpdate(Entity player, float deltaTime) {
	switch (aiType) {
	case MAN:
		AIMan(player, deltaTime);
		break;
	}

}

void Entity::AIMan(Entity& player, float deltaTime) {
	switch (aiState) { //do something different depending on state!
	case MOVING:
		if (aiDirection.y != 0) {
		position.y += velocity.y * deltaTime; // Move on Y
		spritePosition.y = position.y;
		//CheckCollisionsY(objects, objectCount); // Fix if needed
		}
		if (aiDirection.x != 0) {
			position.x += velocity.x * deltaTime; // Move on X
			spritePosition.x = position.x;
		//CheckCollisionsX(map);
		//CheckCollisionsX(objects, objectCount); // Fix if needed
		}
		if (aiDirection.x == 0 && aiDirection.y == 0) {
			aiState = PICKING;
		}
		break;
	case PICKING:
		velocity = glm::vec3(std::abs(velocity.x), std::abs(velocity.y), 0);
		int randomNum = std::rand();
		if (randomNum % 2 == 0 ) {
			//horizontal
			randomNum = std::rand();
			randomNum % 2 == 0 ? aiDirection.x = 1 : aiDirection.x = -1;
			velocity = glm::vec3(1 * aiDirection.x, 0, 0);
		}
		else {
			//vertical
			randomNum = std::rand();
			randomNum % 2 == 0 ? aiDirection.y = 1 : aiDirection.y = -1;
			velocity = glm::vec3(0, 1 * aiDirection.y, 0);
		}
		aiState = MOVING;
		/*timer += deltaTime;
		if (timer > 10.0f) {
			aiState = SHRINKING;
			timer = 0.0f;
			height = accordionMin;
			currentAnim = walkLeft;
		}*/
		break;
	}
}