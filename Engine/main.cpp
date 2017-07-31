#include "Engine.h"

#include <iostream>
#include <stdlib.h>

int main()
{
	jECS::Manager myManager;

	std::bitset<jECS::numOfComponents> testableFlags;
	testableFlags.flip(jECS::testable);
	std::bitset<jECS::numOfComponents> notTestableFlags;

	for (int i = 0; i < jECS::maxEntities; i++) {
		myManager.newEntity(testableFlags);
	}

	myManager.refresh();

	do
	{
		for (int i = rand() % 1000; i > 0; --i)
		{
			myManager.update();
		}
		myManager.refresh();
		for (int i = rand() % 1000; i > 0; --i)
		{
			myManager.newEntity(testableFlags);
		}
	} while (myManager.refresh() > 0);
}