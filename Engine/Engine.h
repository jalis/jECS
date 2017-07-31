#pragma once

#include <array>
#include <bitset>
#include <memory>

namespace jECS
{
	const int testable = 0;

	const std::size_t maxEntities = 10000;
	const std::size_t numOfComponents = 1;
	const std::size_t numOfSystems = 1;

	struct entity
	{
		int id;
		std::bitset<numOfComponents> components;
		bool alive;
	};

	struct system
	{
		virtual void update() {};
		virtual void refresh(std::array<std::unique_ptr<jECS::entity>, maxEntities>*, std::size_t) {};
	};

	class Manager
	{
	private:
		std::array<std::unique_ptr<jECS::entity>, maxEntities> entities;
		std::array<jECS::system*, numOfSystems> systems;
		std::size_t size;
		std::size_t nextSize;
		int nextID;
		bool refreshNeeded;
	public:
		Manager();
		~Manager();
		void update();
		std::size_t refresh();
		void newEntity(std::bitset<numOfComponents>);
	};

}
