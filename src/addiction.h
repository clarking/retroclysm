#pragma once

#include "rng.h"
#include "game.h"
#include <sstream>

void addict_effect(game *g, addiction &add) {
	int in = add.intensity;

	switch (add.type) {
		case ADD_CIG:
			g->u.int_cur--;
			if (in > 20 || one_in((500 - 20 * in))) {
				g->add_msg("You %s a cigarette.", rng(0, 6) < in ? "need" : "could use");
				g->cancel_activity_query("You have a craving.");
				if (one_in(800 - 50 * in))
					g->u.fatigue++;
				if (one_in(400 - 20 * in))
					g->u.stim--;
				if (one_in((800 - 10 * in)))
					g->u.morale--;
			}
			break;
		case ADD_CAFFEINE:
			g->u.str_cur--;
			g->u.moves -= 2;
			if (in > 20 || one_in((500 - 20 * in))) {
				g->add_msg("You want some caffeine.");
				g->cancel_activity_query("You have a craving.");
				if (rng(0, 10) < in)
					g->u.stim--;

				if (in > 19 || one_in((1000 - 50 * in)))
					g->u.morale--;

				if (rng(8, 400) < in) {
					g->add_msg("Your hands start shaking... you need it bad!");
					g->u.add_disease(DI_SHAKES, 20, g);
				}
			}
			break;
		case ADD_ALCOHOL:
			g->u.per_cur--;
			g->u.int_cur--;
			if (rng(40, 1200) <= in * 10)
				g->u.health--;

			if (one_in(20) && rng(0, 20) < in) {
				g->add_msg("You could use a drink.");
				g->cancel_activity_query("You have a craving.");
				g->u.morale -= rng(1, 4);
			}
			else if (rng(8, 300) < in) {
				g->add_msg("Your hands start shaking... you need a drink bad!");
				g->cancel_activity_query("You have a craving.");
				g->u.add_disease(DI_SHAKES, 50, g);
			}
			else if (!g->u.has_disease(DI_HALLU) && rng(10, 1600) < in)
				g->u.add_disease(DI_HALLU, 3600, g);
			break;
		case ADD_SLEEP:
			// No effects here--just in player::can_sleep()
			// EXCEPT!  Prolong this addiction longer than usual.
			if (one_in(2) && add.sated < 0)
				add.sated++;
			break;
		case ADD_PKILLER:
			g->u.str_cur -= 1 + int(in / 7);
			g->u.per_cur--;
			g->u.dex_cur--;

			if (g->u.pain < in * 3)
				g->u.pain++;

			if (g->u.morale > 0 - in)
				g->u.morale--;

			if ((in >= 25 || g->turn % (100 - in * 4) == 0) && g->u.pkill > 0)
				g->u.pkill--;    // Tolerance increases!

			if (in >= 40 || one_in((1200 - 30 * in)))
				g->u.health--;

			if (one_in(20) && dice(2, 20) < in) {
				g->add_msg("Your hands start shaking... you need some painkillers.");
				g->cancel_activity_query("You have a craving.");
				g->u.add_disease(DI_SHAKES, 20 + in * 5, g);
			}
			else if (one_in(20) && dice(2, 30) < in) {
				g->add_msg("You feel anxious.  You need your painkillers!");
				g->cancel_activity_query("You have a craving.");
				g->u.morale -= 5;
			}
			else if (one_in(50) && dice(3, 50) < in) {
				g->add_msg("You throw up heavily!");
				g->cancel_activity_query("Throwing up.");
				g->u.vomit(g);
			}
			break;
		case ADD_SPEED:
			g->u.moves -= in;

			if (g->u.morale > 0 - in)
				g->u.morale--;

			g->u.int_cur--;
			g->u.str_cur--;

			if (in >= 20 || g->turn % (100 - in * 5) == 0)
				g->u.stim--;

			if (rng(0, 150) <= in)
				g->u.health--;

			if (dice(2, 100) < in) {
				g->add_msg("You feel depressed.  Speed would help.");
				g->cancel_activity_query("You have a craving.");
				g->u.morale -= rng(1, 1 + int(in / 3));
			}
			else if (one_in(10) && dice(2, 80) < in) {
				g->add_msg("Your hands start shaking... you need a pick-me-up.");
				g->cancel_activity_query("You have a craving.");
				g->u.add_disease(DI_SHAKES, in * 20, g);
			}
			else if (one_in(50) && dice(2, 100) < in) {
				g->add_msg("You stop suddenly, feeling bewildered.");
				g->cancel_activity();
				g->u.moves -= 300;
			}
			else if (!g->u.has_disease(DI_HALLU) && one_in(20) && 8 + dice(2, 80) < in) {
				g->u.add_disease(DI_HALLU, 3600, g);
			}
			break;
		case ADD_COKE:
			g->u.int_cur--;
			g->u.per_cur--;

			if (g->u.morale > -20 && (in >= 30 || one_in((900 - 30 * in)))) {
				g->add_msg("You feel like you need a bump.");
				g->cancel_activity_query("You have a craving.");
				g->u.morale -= 2;
			}

			if (dice(2, 80) <= in) {
				g->add_msg("You feel like you need a bump.");
				g->cancel_activity_query("You have a craving.");
				g->u.stim--;
			}
			break;
	}
}

std::string addiction_name(addiction cur) {
	switch (cur.type) {
		case ADD_CIG:
			return "Nicotine Withdrawal";
		case ADD_CAFFEINE:
			return "Caffeine Withdrawal";
		case ADD_ALCOHOL:
			return "Alcohol Withdrawal";
		case ADD_SLEEP:
			return "Sleeping Pill Dependance";
		case ADD_PKILLER:
			return "Opiate Withdrawal";
		case ADD_SPEED:
			return "Amphetamine Withdrawal";
		case ADD_COKE:
			return "Cocaine Withdrawal";
		default:
			return "Erroneous addiction";
	}
}

std::string addiction_text(addiction cur) {
	std::stringstream dump;
	int strpen = 1 + int(cur.intensity / 7);
	switch (cur.type) {
		case ADD_CIG:
			return "Intelligence - 1;   Occasional cravings";
		case ADD_CAFFEINE:
			return "Strength - 1;   Slight sluggishness;   Occasional cravings";
		case ADD_ALCOHOL:
			return "Perception - 1;   Intelligence - 1;   Occasional Cravings;\nRisk of delirium tremens";
		case ADD_SLEEP:
			return "You may find it difficult to sleep without medication.";
		case ADD_PKILLER:
			dump << "Strength -" << strpen << ";   Perception - 1;   Dexterity - 1;" <<	 std::endl << "Depression and physical pain to some degree.  Frequent cravings.  Vomiting.";
			return dump.str();
		case ADD_SPEED:
			return "Strength - 1;   Intelligence - 1;\nMovement rate reduction.  Depression.  Weak immune system.  Frequent cravings.";
		case ADD_COKE:
			return "Perception - 1;   Intelligence - 1;  Frequent cravings.";
	}

	return {};
}

