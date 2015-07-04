#include "../include/particle.h"
#include "../include/parameters.h"
#include <math.h>

#define PRINTPAIR_R(label,pair) printf("%s = (%f,%f)\n", label, pair.x, pair.y);
#define PRINTPAIR_P(label,pair) printf("%s = (%f,%f)\n", label, pair.mod, pair.ang);

//-----------------------------------------------------
//------------ INTERNAL - VECTORIAL STUFF -------------
//-----------------------------------------------------
typedef struct {
	double mod, ang;
} Polar2D;

static Polar2D difference(Particle* p1, Particle* p2)
{
	Polar2D out;
	Vec2D diff;

	diff.x = p2->pos.x - p1->pos.x;
	diff.y = p2->pos.y - p1->pos.y;

	out.mod = Vec2D_modulus(diff);
	out.ang = Vec2D_angle(diff);

	return out;
}

static void polar2Rect(Polar2D src, Vec2D* dst)
{
	dst->x = src.mod * cos(src.ang);
	dst->y = src.mod * sin(src.ang);
}

static double Vec2D_QuadMod(Vec2D v)
{
	return v.x * v.x + v.y * v.y;
}

double Vec2D_modulus(Vec2D v)
{
	return sqrt( Vec2D_QuadMod(v) );
}

double Vec2D_angle(Vec2D v)
{
	return atan2(v.y, v.x);
}

//-------------------------------------------
//------------ INTERNAL - OTHER -------------
//-------------------------------------------
static double loseEnergy(Particle* p, double LoE)
{
	p->energy = (1.0-LoE) * p->energy;

	//Calculate how much velocity will decrease due to
	//loss of energy
	Polar2D newVel;
	newVel.mod = sqrt(2 * p->energy / p->mass);
	newVel.ang = Vec2D_angle(p->vel);

	//Convert to rectangular coordinates
	polar2Rect(newVel, &p->vel);

	//Update momentum here?
}

static void spring(Particle* p1, Particle* p2, 
			double springLength, double springCoeff, double LoE)
{
	//Calculate deformation
	Polar2D diff = difference(p1, p2);
	double deformation = springLength - diff.mod;

	//Calculate elastic force
	Polar2D elasticForce_p;
	elasticForce_p.mod = - springCoeff * deformation;
	elasticForce_p.ang = diff.ang;

	//Convert to rectangular coordinates
	Vec2D elasticForce_r; 
	polar2Rect(elasticForce_p, &elasticForce_r);

	//Apply forces : particle 2 receives the force
	//in opposite direction (as our distance vector
	//points from p1 to p2)
	p1->force.x += elasticForce_r.x;
	p1->force.y += elasticForce_r.y;

	p2->force.x += -elasticForce_r.x;
	p2->force.y += -elasticForce_r.y;

	//Simulate loss of energy due to spring imperfection
	loseEnergy(p1, LoE);
	loseEnergy(p2, LoE);
}

//-------------------------------------------
//------------ FROM PARTICLE.H --------------
//-------------------------------------------
void interact(Particle* p1, Particle* p2)
{
	//Test values - change this for some constant after
	spring(p1, p2, SPRING_LENGTH, SPRING_COEFFICIENT, LOSS_OF_ENERGY);
}

void initializeParticle(Particle* p, double mass, double radius)
{
	p->mass = mass;
	p->radius = radius;

	p->force = p->vel = p->pos = p->momentum = (Vec2D){0.0 , 0.0};
	p->energy = 0.0;

	p->e = GLOBAL_E;

	return;
}

void updateParticle(Particle* p, double timeStep)
{
	Vec2D accel; //Acceleration
	accel.x = p->force.x / p->mass;
	accel.y = p->force.y / p->mass;
	accel.y += GRAVITY;

	p->vel.x += accel.x * timeStep;
	p->vel.y += accel.y * timeStep;

	p->pos.x += p->vel.x * timeStep;
	p->pos.y += p->vel.y * timeStep;

	p->energy = p->mass * Vec2D_QuadMod(p->vel) / 2;
	
	p->momentum.x = p->vel.x * p->mass; 
	p->momentum.y = p->vel.y * p->mass;

	//After calculations, "clean" force
	p->force = (Vec2D){0.0, 0.0};

	return;
}