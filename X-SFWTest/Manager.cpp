#include "Manager.h"
#include <iostream>
bool doCollision(bubble & bubble, const Wall & wall)
{

	auto hit = collides(bubble.transform, bubble.collider,
		wall.transform, wall.collider);

	if (hit.penetrationDepth > 0)
	{
		static_resolution(bubble.transform.position, bubble.rigidbody.velocity, hit, 1);
		return true;
	}
	return false;
}

bool doCollision(bubble & bubble, const Goal & goal)
{

	auto hit = collides(bubble.transform, bubble.collider,
		goal.transform, goal.collider);

	if (hit.penetrationDepth > 0)
	{
		//static_resolution(bubble.transform.position, bubble.rigidbody.velocity, hit, 1);
		return true;
	}
	return false;
}

void doCollision(bubble * bubble, const Wall & wall)
{
	

	auto hit = collides(bubble->transform, bubble->collider,
		wall.transform, wall.collider);

	if (hit.penetrationDepth > 0)
	{

		static_resolution(bubble->transform.position, bubble->rigidbody.velocity, hit);
		//return true;
	}
	//return false;
}

bool doCollision(Ball &ball, const Wall &wall)
{

	auto hit = collides(ball.transform, ball.collider,
		wall.transform, wall.collider);

	if (hit.penetrationDepth > 0)
	{
		static_resolution(ball.transform.position, ball.rigidbody.velocity, hit);
		return true;
	}
	return false;
}

bool doCollision(bubble & bubble, Ball & ball)
{
	Collision hit = collides(bubble.transform, bubble.collider,
		ball.transform, ball.collider);

	if (hit.penetrationDepth > 0)
	{
		dynamic_resolution(bubble.transform.position,
			bubble.rigidbody.velocity,
			bubble.rigidbody.mass,
			ball.transform.position,
			ball.rigidbody.velocity,
			ball.rigidbody.mass,
			hit);
		return true;
	}
	return false;
}

void doCollision(bubble * bub, bubble * bub2)
{
	Collision hit = collides(bub->transform, bub->collider,
		bub2->transform, bub2->collider);

	if (hit.penetrationDepth > 0)
	{
		dynamic_resolution(bub->transform.position,
			bub->rigidbody.velocity,
			bub->rigidbody.mass,
			bub2->transform.position,
			bub2->rigidbody.velocity,
			bub2->rigidbody.mass,
			hit);
	}
}

	void Manager::MakeABaby(vec2 spawn, vec2 target)
	{
		//float xJump = rand() % 50 + 25;
		//float yJump = rand() % 550 + 200;
		int c = 0;
		for (; findCirclePntr[c] != nullptr && c < bubblemax -1; ++c);
		if (c == bubblemax -1) return;
		{
			findCirclePntr[c] = new bubble(spawn, target);

			findCirclePntr[c]->sprite = sfw::loadTextureMap("../resources/Army_guy.png");
			findCirclePntr[c]->rigidbody.drag = 0.001;
			findCirclePntr[c]->transform.position = spawn;
			findCirclePntr[c]->rigidbody.mass = rand() % 3 + 2;
			findCirclePntr[c]->sprite.dim = { 1.5,1.5 };
			findCirclePntr[c]->transform.dimension = vec2{ 12,15 };
			findCirclePntr[c]->collider.box.extents = { .5, .5 };
			findCirclePntr[c]->collider.box.position = { 0,0 };
			//findCirclePntr[c]->rigidbody.force = {xJump,yJump };
		}
		
	}

	void Manager::updateAll()
	{
		for (int i = 0; i < bubblemax; ++i)
			if (findCirclePntr[i] != nullptr)
			{
				
				findCirclePntr[i]->update();
				//findCirclePntr[i]->collider.box.position = findCirclePntr[i]->transform.position;
				for (int j = 0; j < 25; j++)
				{

						doCollision(findCirclePntr[i], wall[j]);
				}
				for (int k = 1; k < bubblemax; ++k)
				{
					if (findCirclePntr[k] != nullptr)
					{
						if (i != k)
						{
							doCollision(findCirclePntr[i], findCirclePntr[k]);
						}
					}
				}
				if (findCirclePntr[i] != nullptr)
				{

					if (doCollision(*findCirclePntr[i], goal) == true)
					{
						std::cout << "YAAAYYYYY SHEAAAAAA" << std::endl;
					}
				}
				
				
			}

	}
	void Manager::updateGatherAll()
	{
		for (int i = 0; i < bubblemax; ++i)
			if (findCirclePntr[i] != nullptr)
			{
				findCirclePntr[i]->gatherUpdate();
				for (int j = 0; j < 25; j++)
				{
					doCollision(findCirclePntr[i], wall[j]);
				}
				for (int k = 1; k < bubblemax; ++k)
				{
					if (findCirclePntr[k] != nullptr)
					{
						if (i != k)
						{
							doCollision(findCirclePntr[i], findCirclePntr[k]);
						}
					}
				}
			}
	}

	void Manager::updateExplodeAll()
	{
		for (int i = 0; i < bubblemax; ++i)
			if (findCirclePntr[i] != nullptr)
				findCirclePntr[i]->explodeUpdate();
	}

	void Manager::drawAll()
	{
		for (int i = 0; i < bubblemax; ++i)
			if (findCirclePntr[i] != nullptr)
			{

				drawbox(findCirclePntr[i]->collider.box, CYAN);
				findCirclePntr[i]->draw();
			}

		//drawbox(g)
	}
	
	