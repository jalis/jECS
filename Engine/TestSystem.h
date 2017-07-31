#pragma once

#include "Engine.h"

#include <map>

namespace jECS
{
	struct TestSystem : jECS::system
	{
	private:
		struct pos {
			float x;
			float y;
		};
		std::array<entity*, maxEntities> shortlist;
		std::map<int, pos> positions;
		std::size_t size;
		int testIteration;
	public:
		TestSystem();
		void update() override;
		void refresh(std::array<std::unique_ptr<jECS::entity>, jECS::maxEntities>*, std::size_t) override;
	};
}