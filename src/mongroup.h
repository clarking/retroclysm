#pragma once

#include "mtype.h"
#include <vector>

enum moncat_id {
	mcat_null = 0,
	mcat_forest,
	mcat_ant,
	mcat_bee,
	mcat_worm,
	mcat_zombie,
	mcat_plants,
	mcat_fungi,
	mcat_goo,
	mcat_chud,
	mcat_sewer,
	mcat_nether,
	num_moncats
};

struct mongroup {
	moncat_id type;
	int posx, posy;
	unsigned char radius;
	unsigned int population;
	mongroup(moncat_id ptype, int pposx, int pposy, unsigned char prad,
			 unsigned int ppop) {
		type = ptype;
		posx = pposx;
		posy = pposy;
		radius = prad;
		population = ppop;
	}
};

