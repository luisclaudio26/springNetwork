#include "../include/springNetwork.h"
#include "../include/parameters.h"

#define GRID_WIDTH 10
#define GRID_HEIGHT 10

static Particle P[GRID_WIDTH][GRID_HEIGHT];

//-------------------------------------------------
//------------- FROM SPRINGNETWORK.H --------------
//-------------------------------------------------
void drawNetwork()
{
	Particle* aux = &P;
	for(int i = 0; i < GRID_WIDTH * GRID_HEIGHT; i++, aux++)
		drawPoint(aux->pos.x, aux->pos.y, aux->radius, YELLOW);
}

void updateNetwork(double timeStep)
{
	//printf("Updating\n");

	/*
	interact(&P1, &P2);

	updateParticle(&P1, timeStep);
	updateParticle(&P2, timeStep);
	*/
}

void initializeNetwork()
{
	printf("Initializing network...\n");

	for(int i = 0; i < GRID_WIDTH; i++)
		for(int j = 0; j < GRID_HEIGHT; j++)
		{
			initializeParticle(&P[i][j], 10.0, 4.0);
			P[i][j].pos.x = i * 20 + 50;
			P[i][j].pos.y = j * 20 + 50;
		}
}

void destroyNetwork()
{
	printf("Destroying network...\n");
}