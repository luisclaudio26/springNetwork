#include "../include/springNetwork.h"
#include "../include/parameters.h"

static Particle P1, P2;

//-------------------------------------------------
//------------- FROM SPRINGNETWORK.H --------------
//-------------------------------------------------
void drawNetwork()
{
	//printf("Drawing\n");

	drawPoint(P1.pos.x, P1.pos.y, P1.radius, YELLOW);
	drawPoint(P2.pos.x, P2.pos.y, P2.radius, RED);
}

void updateNetwork(double timeStep)
{
	//printf("Updating\n");

	interact(&P1, &P2);

	updateParticle(&P1, timeStep);
	updateParticle(&P2, timeStep);
}

void initializeNetwork()
{
	printf("Initializing network...\n");

	initializeParticle(&P1, 10.0, 1.0);
	initializeParticle(&P2, 15.0, 1.0);

	P1.pos.x = P1.pos.y = 100;
	P2.pos.x = P2.pos.y = 300;
}

void destroyNetwork()
{
	printf("Destroying network...\n");
}