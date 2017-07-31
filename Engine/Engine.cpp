#include "Engine.h"
#include "TestSystem.h"

#include <iostream>

jECS::Manager::Manager()
{
	size = 0;
	nextSize = 0;
	nextID = 0;

	refreshNeeded = false;

	systems[0] = new TestSystem;
}

jECS::Manager::~Manager()
{

}

void jECS::Manager::update()
{
	for (int i = 0; i < jECS::numOfSystems; i++)
	{
		systems[i]->update();
	}
}

std::size_t jECS::Manager::refresh()
{
#ifdef _DEBUG
/*	std::cout << std::endl << std::endl << "Entering Manager refresh:" << std::endl;
	for (int i = 0; i < size; ++i) std::cout << (entities[i].get()->alive ? "A" : "D"); */
	int swaps = 0;
#endif

	while (true)
	{
		int i = 0;
		int ri = nextSize;
#ifdef _DEBUG
		std::cout << std::endl << "i=" << i << ", ri=" << ri;
		std::cin.ignore();
#endif
		while (true)
		{
			if (i == ri) {
#ifdef _DEBUG
				std::cout << std::endl << "Arrived at ri, breaking loop";
#endif
				break;
			}
			if (!entities[i].get()->alive) {
#ifdef _DEBUG
				std::cout << std::endl << "Dead found at " << i;
#endif
				break;
			}
			++i;
		}
		while (true)
		{
			if (ri == i) {
#ifdef _DEBUG
				std::cout << std::endl << "Arrived at i, breaking loop";
#endif
				break;
			}
			--ri;
			if (entities[ri].get()->alive) {
#ifdef _DEBUG
				std::cout << std::endl << "Alive found at " << ri;
#endif
				break;
			}
		}
		if (i == ri)
		{

#ifdef _DEBUG
/*			std::cout << std::endl << "Nothing to swap:" << std::endl;
			for (int i = 0; i < size; ++i) std::cout << (entities[i].get()->alive ? "A" : "D"); */
			std::cout << std::endl << "size=" << size << ", nextSize=" << nextSize << ", i=" << i << ", making sizes match i";
#endif

			nextSize = size = i;

#ifdef _DEBUG
/*			std::cout << std::endl << "Refresh finished, " << swaps << " swaps made. Array after refresh:" << std::endl;
			for (int i = 0; i < size; ++i) std::cout << (entities[i].get()->alive ? "A" : "D");*/
			std::cout << std::endl;
#endif

			break;
		}
#ifdef _DEBUG
		std::cout << std::endl << "Swapping #" << i << " with #" << ri;
		++swaps;
#endif
		std::swap(entities[i], entities[ri]);
	}

	if (refreshNeeded) for (auto i : systems) i->refresh(&entities, size); refreshNeeded = false;

	return size;
}

void jECS::Manager::newEntity(std::bitset<numOfComponents> comps)
{
	if (nextSize == maxEntities) {
#ifdef _DEBUG
		std::cout << std::endl << "Max entities reached!";
		std::cin.ignore();
#endif
		return;
	}
	std::unique_ptr<entity> newEnt(new entity);
	newEnt->alive = true;
	newEnt->components = comps;
	newEnt->id = nextID;
	entities[nextSize] = std::move(newEnt);

	++nextSize;
	refreshNeeded = true;
}