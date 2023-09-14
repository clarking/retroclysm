#pragma once

#include <vector>
#include "itype.h"
#include "mongroup.h"
#include "mapitems.h"
#include "crafting.h"

void setvector(std::vector <itype_id> &vec, ...);

void setvector(std::vector <component> &vec, ...);

void setvector(std::vector <mon_id> &vec, ...);

void setvector(std::vector <items_location_and_chance> &vec, ...);

