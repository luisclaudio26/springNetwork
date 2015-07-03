#ifndef _PARTICLE_H_
#define _PARTICLE_H_

typedef struct {
	double x, y;
} Vec2D;

typedef struct {
	Vec2D force; //Sum of all forces acting in this particle
	Vec2D pos;
	Vec2D vel;
	double mass;
	double radius;
	double energy;
	Vec2D momentum;
} Particle;

void interact(Particle* p1, Particle* p2);
void initializeParticle(Particle* p, double mass, double radius);
void updateParticle(Particle* p, double timeStep);

#endif