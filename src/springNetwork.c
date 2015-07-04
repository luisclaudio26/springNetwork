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
	//Add springs
	for(int i = 0; i < GRID_WIDTH; i++)
		for(int j = 0; j < GRID_HEIGHT; j++)
		{
			if(i + 1 < GRID_WIDTH)
				interact(&P[i][j], &P[i+1][j]);

			if(j + 1 < GRID_HEIGHT)
				interact(&P[i][j], &P[i][j+1]);
		}

	//Update all particles
	Particle* aux = &P;
	for(int i = 0; i < GRID_WIDTH * GRID_HEIGHT; i++, aux++)
		updateParticle(aux, timeStep);
}

void initializeNetwork()
{
	printf("Initializing network...\n");

	for(int i = 0; i < GRID_WIDTH; i++)
		for(int j = 0; j < GRID_HEIGHT; j++)
		{
			initializeParticle(&P[i][j], 10.0, 4.0);
			P[i][j].pos.x = i * 20 + 200;
			P[i][j].pos.y = j * 20 + 200;
		}
}

void destroyNetwork()
{
	printf("Destroying network...\n");
}