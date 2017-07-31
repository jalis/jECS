#include "Engine.h"
#include "TestSystem.h"

#include <stdlib.h>
#include <iostream>

jECS::TestSystem::TestSystem()
{
	size = 0;
}

void jECS::TestSystem::update()
{
	if (size > 0) {
#ifdef _DEBUG
		int killTarget = rand() % size;
		std::cout << std::endl << "killTarget=" << killTarget;
		shortlist[killTarget]->alive = false;
#else
		shortlist[rand() % size]->alive = false;
#endif
	}
#ifdef _DEBUG
	else std::cout << std::endl << "No targets flagged 'testable'!";
#endif
}

void jECS::TestSystem::refresh(std::array<std::unique_ptr<jECS::entity>, jECS::maxEntities>* entities, std::size_t entSize)
{
	std::size_t i = 0;
	size = 0;

	while (i < entSize)
	{
		auto tempEnt = entities->at(i).get();

		if (tempEnt->components.test(testable))
		{
			shortlist[size] = tempEnt;
			++size;
		}
		++i;
	}
}
