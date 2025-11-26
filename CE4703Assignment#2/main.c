#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "gameSimulation.h"

int main()
{
	int numPacks;

	printf("Enter number of card packs to use: ");
	scanf("%d", &numPacks);

	if (numPacks <= 0) {
		printf("Invalid number of packs. Using 1 pack by default.\n");
		numPacks = 1;
	}

	simulateGame(numPacks);

	return 0;
}