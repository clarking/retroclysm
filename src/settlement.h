#pragma once

#include "npc.h"
#include "overmap.h"
#include "faction.h"

struct settlement {
	settlement();

	settlement(int mapx, int mapy);

	void pick_faction(game *g, int omx, int omy);

	void set_population();

	void populate(game *g) {};

	int num(overmap_terrain_id ter);

	void add_building(overmap_terrain_id ter);


	Faction fact;
	int posx;
	int posy;
	int pop;
	int size;
	int buildings[ot_wall - ot_set_house + 1];
};

