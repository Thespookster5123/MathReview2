#pragma once

#include "vec2.h"
#include "transform.h"

class Rigidbody
{
public:
	float mass;


	vec2 velocity,     // speed * direction
		acceleration,
		force,
		impulse;	   // continuous forces
	float drag;
	float gravity;

	float angularVelocity,
		angularAcceleration,
		torque;
	float angularDrag;

	Rigidbody() : velocity{ 0,0 },
		acceleration{ 0,0 },
		force{ 0,-10 },
		impulse{ 0,0 },
		mass(3),
		drag(.05f),
		angularVelocity(0),
		angularAcceleration(0),
		torque(0),
		angularDrag(.25f),
		gravity(1000.908)//9.908
	{

	}

	// verlet integration may be preferable
	void integrate(Transform &T, float dt)
	{
		// linear motion
		acceleration = force / mass;
		velocity += acceleration * dt + impulse / mass;
		T.position += velocity * dt;
		impulse = { 0,0 };
		force = -velocity * drag;
		// angular motion (sort of)
		angularAcceleration = torque / mass;
		angularVelocity += angularAcceleration * dt;
		T.angle += angularVelocity * dt;
		torque = -angularVelocity * angularDrag;
	}
};