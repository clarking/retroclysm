#pragma once

#include "faction.h"

class game;

enum event_type {
	EVENT_NULL,
	EVENT_HELP,
	NUM_EVENT_TYPES
};

struct event {
	event_type type;
	int turn;
	Faction *relevant_faction;

	event() {
		type = EVENT_NULL;
		turn = 0;
		relevant_faction = nullptr;
	}

	event(event_type e_t, int t, Faction *r_f) {
		type = e_t;
		turn = t;
		relevant_faction = r_f;
	}

	void actualize(game *g) const;
};

