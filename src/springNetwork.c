#include "../include/springNetwork.h"

static Particle P;

//-------------------------------------------------
//------------- FROM SPRINGNETWORK.H --------------
//-------------------------------------------------
void drawNetwork()
{
	//printf("Drawing\n");

	drawPoint(P.pos.x, P.pos.y, P.radius);
}

void updateNetwork(double timeStep)
{
	//printf("Updating\n");

	updateParticle(&P, timeStep);
}

void initializeNetwork()
{
	printf("Initializing network...\n");

	initializeParticle(&P, 10.0, 1.0);

	P.force.x = 1.0;
	P.force.y = 1.0;
}

void destroyNetwork()
{
	printf("Destroying network...\n");
}