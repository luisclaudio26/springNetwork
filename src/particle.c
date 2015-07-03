#include "../include/particle.h"

void interact(Particle* p1, Particle* p2)
{
	return;
}

void initializeParticle(Particle* p, double mass, double radius)
{
	p->mass = mass;
	p->radius = radius;

	p->force = p->vel = p->pos = p->momentum = (Vec2D){0.0 , 0.0};
	p->energy = 0.0;

	return;
}

void updateParticle(Particle* p, double timeStep)
{
	p->pos.x += 0.5;
	p->pos.y += 0.5;
	return;
}