#include "../include/particle.h"
#include <math.h>

#define PRINTPAIR(label,pair) printf("%s = (%f,%f)\n", label, pair.x, pair.y);

//-----------------------------------
//------------ INTERNAL -------------
//-----------------------------------
typedef struct {
	double mod, ang;
} Polar2D;

static Polar2D distance(Particle* p1, Particle* p2)
{
	Polar2D out;
	Vec2D diff;

	diff.x = p1->pos.x - p2->pos.x;
	diff.y = p1->pos.y - p2->pos.y;

	out.mod = Vec2D_modulus(diff);
	out.ang = Vec2D_angle(diff);

	return out;
}

double Vec2D_modulus(Vec2D v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}

double Vec2D_angle(Vec2D v)
{
	return atan2(v.y, v.x);
}

//-------------------------------------------
//------------ FROM PARTICLE.H --------------
//-------------------------------------------
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
	Vec2D accel; //Acceleration
	accel.x = p->force.x / p->mass;
	accel.y = p->force.y / p->mass;

	p->vel.x += accel.x * timeStep;
	p->vel.y += accel.y * timeStep;

	p->pos.x += p->vel.x * timeStep;
	p->pos.y += p->vel.y * timeStep;

	p->energy = p->mass * Vec2D_modulus(p->vel) / 2;
	
	p->momentum.x = p->vel.x * p->mass; 
	p->momentum.y = p->vel.y * p->mass;

	#ifdef DEBUG
		PRINTPAIR("Pos", p->pos);
		PRINTPAIR("Force", p->force);
	#endif

	return;
}