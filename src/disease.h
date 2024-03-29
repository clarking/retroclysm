#pragma once

#include "rng.h"
#include "game.h"
#include "bodypart.h"
#include <sstream>

struct game;

void dis_msg(game *g, dis_type type) {
	switch (type) {
		case DI_HEATSTROKE:
			g->add_msg("You have heatstroke!");
			break;
		case DI_FBFACE:
			g->add_msg("Your face is frostbitten.");
			break;
		case DI_FBHANDS:
			g->add_msg("Your hands are frostbitten.");
			break;
		case DI_FBFEET:
			g->add_msg("Your feet are frostbitten.");
			break;
		case DI_ONFIRE:
			g->add_msg("You're on fire!");
			break;
		case DI_SMOKE:
			g->add_msg("You inhale a lungful of thick smoke.");
			break;
		case DI_TEARGAS:
			g->add_msg("You inhale a lungful of tear gas.");
			break;
		case DI_BOOMERED:
			g->add_msg("You're covered in bile!");
			break;
		case DI_SPORES:
			g->add_msg("You're covered in tiny spores!");
			break;
		case DI_SLIMED:
			g->add_msg("You're covered in thick goo!");
			break;
		case DI_LYING_DOWN:
			g->add_msg("You lie down to go to sleep...");
			break;
		case DI_DRUNK:
		case DI_HIGH:
			g->add_msg("You feel lightheaded.");
			break;
		case DI_ADRENALINE:
			g->add_msg("You feel a surge of adrenaline!");
			g->u.moves += 800;
			break;
		case DI_ASTHMA:
			g->add_msg("You can't breathe... asthma attack!");
			break;
		case DI_BLIND:
			g->add_msg("You're blinded!");
			break;
	}
}

void dis_effect(game *g, player &p, disease &dis) {
	int bonus;
	int junk;
	switch (dis.type) {
		case DI_HEATSTROKE:
			p.moves -= 15;
			p.str_cur -= 2;
			p.per_cur -= 1;
			p.int_cur -= 2;
			break;
		case DI_FBFACE:
			p.per_cur -= 2;
			break;
		case DI_FBHANDS:
			p.dex_cur -= 4;
			break;
		case DI_FBFEET:
			p.moves -= 40;
			p.str_cur -= 1;
			break;
		case DI_SMOKE:
			p.str_cur--;
			p.dex_cur--;
			if (one_in(5)) {
				if (!p.is_npc()) {
					g->add_msg("You cough heavily.");
					g->sound(p.posx, p.posy, 12, "");
				}
				else
					g->sound(p.posx, p.posy, 12, "a hacking cough.");
				p.moves -= 80;
				p.hurt(g, bp_torso, 0, 1 - (rng(0, 1) * rng(0, 1)));
			}
			break;
		case DI_TEARGAS:
			p.str_cur -= 2;
			p.dex_cur -= 2;
			p.int_cur -= 1;
			p.per_cur -= 4;
			if (one_in(3)) {
				if (!p.is_npc()) {
					g->add_msg("You cough heavily.");
					g->sound(p.posx, p.posy, 12, "");
				}
				else
					g->sound(p.posx, p.posy, 12, "a hacking cough");
				p.moves -= 100;
				p.hurt(g, bp_torso, 0, rng(0, 3) * rng(0, 1));
			}
			break;
		case DI_ONFIRE:
			p.hurtall(3);
			for (int i = 0; i < p.worn.size(); i++) {
				if (p.worn[i].made_of(VEGGY) || p.worn[i].made_of(PAPER) ||
					p.worn[i].made_of(PAPER)) {
					p.worn.erase(p.worn.begin() + i);
					i--;
				}
				else if ((p.worn[i].made_of(COTTON) || p.worn[i].made_of(WOOL)) &&
						 one_in(10)) {
					p.worn.erase(p.worn.begin() + i);
					i--;
				}
				else if (p.worn[i].made_of(PLASTIC) && one_in(50)) {
					p.worn.erase(p.worn.begin() + i);
					i--;
				}
			}
			break;
		case DI_BOOMERED:
			p.per_cur -= 5;
			break;
		case DI_SPORES:
			p.moves -= 40;
			if (one_in(30))
				p.add_disease(DI_FUNGUS, -1, g);
			break;
		case DI_FUNGUS:
			bonus = 0;
			if (p.has_trait(PF_POISRESIST))
				bonus = 100;
			p.moves -= 10;
			p.str_cur -= 1;
			p.dex_cur -= 1;
			if (dis.duration > -600) {    // First hour symptoms
				if (one_in(160 + bonus)) {
					if (!p.is_npc()) {
						g->add_msg("You cough heavily.");
						g->sound(p.posx, p.posy, 12, "");
					}
					else
						g->sound(p.posx, p.posy, 12, "a hacking cough");
					p.pain++;
				}
				if (one_in(100 + bonus)) {
					if (!p.is_npc())
						g->add_msg("You feel nauseous.");
				}
				if (one_in(100 + bonus)) {
					if (!p.is_npc())
						g->add_msg("You smell and taste mushrooms.");
				}
			}
			else if (dis.duration > -3600) {    // One to six hours
				if (one_in(600 + bonus * 3)) {
					if (!p.is_npc())
						g->add_msg("You spasm suddenly!");
					p.moves = 0;
					p.hurt(g, bp_torso, 0, 5);
				}
				if ((p.has_trait(PF_WEAKSTOMACH) && one_in(1600 + bonus * 8)) ||
					one_in(2000 + bonus * 10)) {
					if (!p.is_npc())
						g->add_msg("You vomit a thick, gray goop.");
					else if (g->u_see(p.posx, p.posy, junk))
						g->add_msg("%s vomits a thick, gray goop.", p.name.c_str());
					p.moves = -200;
					p.hunger += 50;
					p.thirst += 68;
				}
			}
			else {    // Full symptoms
				if (one_in(1000 + bonus * 8)) {
					if (!p.is_npc())
						g->add_msg("You double over, spewing live spores from your mouth!");
					else if (g->u_see(p.posx, p.posy, junk))
						g->add_msg("%s coughs up a stream of live spores!", p.name.c_str());
					p.moves = -500;
					int sporex, sporey;
					monster spore(g->mtypes[mon_spore]);
					for (int i = -1; i <= 1; i++) {
						for (int j = -1; j <= 1; j++) {
							sporex = p.posx + i;
							sporey = p.posy + j;
							if (g->m.move_cost(sporex, sporey) > 0 && one_in(5)) {
								if (g->mon_at(sporex, sporey) >= 0) {    // Spores hit a monster
									if (g->u_see(sporex, sporey, junk))
										g->add_msg("The %s is covered in tiny spores!",
												   g->z[g->mon_at(sporex, sporey)].name().c_str());
									if (!g->z[g->mon_at(sporex, sporey)].make_fungus(g))
										g->kill_mon(g->mon_at(sporex, sporey));
								}
								else {
									spore.spawn(sporex, sporey);
									g->z.push_back(spore);
								}
							}
						}
					}
				}
				else if (one_in(6000 + bonus * 20)) {
					if (!p.is_npc())
						g->add_msg("Fungus stalks burst through your hands!");
					else if (g->u_see(p.posx, p.posy, junk))
						g->add_msg("Fungus stalks burst through %s's hands!", p.name.c_str());
					p.hurt(g, bp_arms, 0, 60);
					p.hurt(g, bp_arms, 1, 60);
				}
			}
			break;
		case DI_SLIMED:
			p.moves -= 30;
			if (p.moves < 1)
				p.moves = 1;
			p.dex_cur -= 2;
			break;
		case DI_LYING_DOWN:
			p.moves = 0;
			if (p.can_sleep(g)) {
				dis.duration = 1;
				if (!p.is_npc())
					g->add_msg("You fall asleep.");
				p.add_disease(DI_SLEEP, 6000, g);
			}
			if (dis.duration == 1 && !p.has_disease(DI_SLEEP))
				if (!p.is_npc())
					g->add_msg("You try to sleep, but can't...");
			break;
		case DI_SLEEP:
			p.moves = 0;
			if (g->turn % 25 == 0) {
				if (p.fatigue > 0)
					p.fatigue -= rng(1, 2);
				if (p.has_trait(PF_FASTHEALER) && one_in(2))
					p.healall(rng(0, 1));    // Sum chance of 1/4, PLUS normal rate
				else
					p.healall(rng(0, 1) * rng(0, 1) * rng(0, 1));
				if (p.fatigue <= 0 && p.fatigue > -20) {
					p.fatigue = -25;
					g->add_msg("Fully rested.");
					dis.duration = dice(3, 100);
				}
			}
			if (g->turn % 100 == 0) {
				// Hunger and thirst advance more slowly while we sleep.
				p.hunger--;
				p.thirst--;
			}
			if (rng(2, 80) + rng(0, 100) + rng(0, 120) + rng(0, p.fatigue) <
				g->light_level() && (one_in(p.fatigue / 10) || p.fatigue < 10)) {
				g->add_msg("The light wakes you up.");
				dis.duration = 1;
			}
			break;
		case DI_PKILL1:
			if (dis.duration <= 70 && dis.duration % 7 == 0 && p.pkill < 35)
				p.pkill++;
			break;
		case DI_PKILL2:
			if (dis.duration % 7 == 0 &&
				(one_in(p.addiction_level(ADD_PKILLER)) || one_in(p.addiction_level(ADD_PKILLER))))
				p.pkill += 2;
			break;
		case DI_PKILL3:
			if (dis.duration % 2 == 0 &&
				(one_in(p.addiction_level(ADD_PKILLER)) || one_in(p.addiction_level(ADD_PKILLER))))
				p.pkill++;
			break;
		case DI_PKILL_L:
			if (dis.duration % 20 == 0 && p.pkill < 49 &&
				(one_in(p.addiction_level(ADD_PKILLER)) || one_in(p.addiction_level(ADD_PKILLER))))
				p.pkill++;
			break;
		case DI_TOOK_XANAX:
			if (dis.duration % 25 == 0 && (p.stim > 0 || one_in(2)))
				p.stim--;
			break;
		case DI_DRUNK:

			// We get 600 turns, or one hour, of DI_DRUNK for each drink we have (on avg)
			// So, the duration of DI_DRUNK is a good indicator of how much alcohol is in
			//  our system.

			p.per_cur -= int(dis.duration / 800);
			p.dex_cur -= int(dis.duration / 800);
			p.int_cur -= int(dis.duration / 800);
			p.str_cur -= int(dis.duration / 1000);

			if (dis.duration <= 600)
				p.str_cur += 1;

			if (dis.duration > 2000 + 100 * dice(2, 100) &&
				(p.has_trait(PF_WEAKSTOMACH) || one_in(20)))
				p.vomit(g);

			if (!p.has_disease(DI_SLEEP) && dis.duration >= 4500 &&
				one_in(500 - int(dis.duration / 80))) {
				if (!p.is_npc())
					g->add_msg("You pass out.");
				p.add_disease(DI_SLEEP, dis.duration / 2, g);
			}
			break;
		case DI_CIG:
			if (dis.duration >= 200) {    // Smoked too much
				p.str_cur -= 1;
				p.dex_cur -= 1;
				if (dis.duration >= 500 && (one_in(50) || one_in(20) && p.has_trait(PF_WEAKSTOMACH)))
					p.vomit(g);
			}
			else {
				p.dex_cur++;
				p.int_cur++;
				p.per_cur++;
			}
			break;
		case DI_HIGH:
			p.dex_cur--;
			p.int_cur--;
			p.per_cur--;
			break;
		case DI_POISON:
			if ((!p.has_trait(PF_POISRESIST) && one_in(150)) || (p.has_trait(PF_POISRESIST) && one_in(900))) {
				if (!p.is_npc())
					g->add_msg("You're suddenly wracked with pain!");

				p.pain += 2;
				p.hurt(g, bp_torso, 0, rng(0, 2) * rng(0, 1));
			}

			p.per_cur--;
			p.dex_cur--;

			if (!p.has_trait(PF_POISRESIST))
				p.str_cur -= 2;
			break;
		case DI_FOODPOISON:
			bonus = 0;

			if (p.has_trait(PF_POISRESIST))
				bonus = 600;

			if (one_in(300 + bonus)) {
				if (!p.is_npc())
					g->add_msg("You're suddenly wracked with pain and nausea!");
				p.pain += 2;
				p.hurt(g, bp_torso, 0, 2);
			}

			if ((p.has_trait(PF_WEAKSTOMACH) && one_in(350 + bonus)) || one_in(900 + bonus))
				p.vomit(g);

			p.moves -= 35;
			p.str_cur -= 3;
			p.dex_cur--;
			p.per_cur--;

			if (p.has_trait(PF_POISRESIST)) {
				p.moves += 15;
				p.str_cur += 2;
			}
			break;

		case DI_SHAKES:
			p.dex_cur -= 4;
			p.str_cur--;
			break;
		case DI_HALLU:
			// This assumes that we were given DI_HALLU with a 3600 (6-hour) lifespan
			if (dis.duration > 3000) {    // First hour symptoms
				if (one_in(300)) {
					if (!p.is_npc())
						g->add_msg("You feel a little strange.");
				}
			}
			else if (dis.duration > 2400) {    // Coming up
				if (one_in(100) || (p.has_trait(PF_WEAKSTOMACH) && one_in(100))) {
					if (!p.is_npc())
						g->add_msg("You feel nauseous.");
					p.hunger -= 5;
				}
				if (!p.is_npc()) {
					if (one_in(200))
						g->add_msg("Huh?  What was that?");
					else if (one_in(200))
						g->add_msg("Oh god, what's happening?");
					else if (one_in(200))
						g->add_msg("Of course... it's all fractals!");
				}
			}
			else if (dis.duration == 2400)    // Visuals start
				p.add_disease(DI_VISUALS, 2400, g);

			else {    // Full symptoms
				p.per_cur -= 2;
				p.int_cur -= 1;
				p.dex_cur -= 2;
				p.str_cur -= 1;
				if (one_in(50)) {    // Generate phantasm
					monster phantasm(g->mtypes[mon_hallu_zom + rng(0, 3)]);
					phantasm.spawn(p.posx + rng(-10, 10), p.posy + rng(-10, 10));
					g->z.push_back(phantasm);
				}
			}

			break;
		case DI_ADRENALINE:
			if (dis.duration > 400) {    // 20 minutes positive effects
				p.moves += rng(40, 100);
				p.str_cur += 5;
				p.dex_cur += 3;
				p.int_cur -= 8;
				p.per_cur += 1;
			}
			else if (dis.duration == 400) {    // 40 minutes come-down
				if (!p.is_npc())
					g->add_msg("Your adrenaline rush wears off.  You feel AWFUL!");
				p.moves -= 300;
			}
			else {
				p.str_cur -= 2;
				p.dex_cur -= 1;
				p.int_cur -= 1;
				p.per_cur -= 1;
			}

			break;
		case DI_ASTHMA:
			if (dis.duration > 1200) {
				if (!p.is_npc())
					g->add_msg("Your asthma overcomes you.  You stop breathing and die...");
				p.hurtall(500);
			}

			p.moves -= dis.duration / 5;
			p.str_cur -= 2;
			p.dex_cur -= 3;
			break;
		case DI_METH:
			if (dis.duration > 600) {
				p.str_cur += 2;
				p.dex_cur += 2;
				p.int_cur += 2;
				p.per_cur += 2;
				p.moves += 50;
			}
			else {
				p.str_cur -= 3;
				p.dex_cur -= 2;
				p.int_cur -= 1;
				p.moves -= 40;
			}
			break;
		case DI_TELEGLOW:

			// Default we get around 300 duration points per teleport (possibly more
			// depending on the source).
			// TODO: Include a chance to teleport to the nether realm.

			if (dis.duration > 6000) {    // 20 teles (no decay; in practice at least 21)
				if (one_in(1000 - ((dis.duration - 6000) / 10))) {
					if (!p.is_npc())
						g->add_msg("Glowing lights surround you, and you teleport.");

					g->teleport();
					if (one_in(4))
						p.rem_disease(DI_TELEGLOW);
				}

				if (one_in(1200 - ((dis.duration - 6000) / 5)) && one_in(20)) {
					if (!p.is_npc())
						g->add_msg("You pass out.");

					p.add_disease(DI_SLEEP, 1200, g);
					if (one_in(6))
						p.rem_disease(DI_TELEGLOW);
				}
			}

			if (dis.duration > 3600) { // 12 teles
				if (one_in(4000 - int(.25 * (dis.duration - 3600)))) {
					int range = g->moncats[mcat_nether].size();
					mon_id type = (g->moncats[mcat_nether])[rng(0, range - 1)];
					monster beast(g->mtypes[type]);
					int x, y, tries = 0;
					do {
						x = p.posx + rng(-4, 4);
						y = p.posy + rng(-4, 4);
					}
					while ((x == p.posx && y == p.posy) || g->mon_at(x, y) != -1);

					if (g->m.move_cost(x, y) == 0)
						g->m.ter(x, y) = t_rubble;

					beast.spawn(x, y);
					g->z.push_back(beast);
					if (g->u_see(x, y, junk))
						g->add_msg("A portal opens nearby, and a monster crawls through!");

					if (one_in(2))
						p.rem_disease(DI_TELEGLOW);
				}

				if (one_in(3500 - int(.25 * (dis.duration - 3600)))) {
					if (!p.is_npc())
						g->add_msg("You shudder suddenly.");

					p.mutate(g);
					if (one_in(4))
						p.rem_disease(DI_TELEGLOW);
				}
			}

			if (dis.duration > 2400) {    // 8 teleports
				if (one_in(10000 - dis.duration))
					p.add_disease(DI_SHAKES, rng(40, 80), g);

				if (one_in(12000 - dis.duration)) {
					if (!p.is_npc())
						g->add_msg("Your vision is filled with bright lights...");

					p.add_disease(DI_BLIND, rng(10, 20), g);
					if (one_in(8))
						p.rem_disease(DI_TELEGLOW);
				}

				if (one_in(5000) && !p.has_disease(DI_HALLU)) {
					p.add_disease(DI_HALLU, 3600, g);
					if (one_in(5))
						p.rem_disease(DI_TELEGLOW);
				}
			}
			if (one_in(4000)) {
				if (!p.is_npc())
					g->add_msg("You're suddenly covered in ectoplasm.");

				p.add_disease(DI_BOOMERED, 100, g);
				if (one_in(4))
					p.rem_disease(DI_TELEGLOW);
			}

			if (one_in(10000)) {
				p.add_disease(DI_FUNGUS, -1, g);
				p.rem_disease(DI_TELEGLOW);
			}

			break;
	}
}

std::string dis_name(disease dis) {
	switch (dis.type) {
		case DI_NULL:
			return "";
		case DI_HEATSTROKE:
			return "Heatstroke";
		case DI_FBFACE:
			return "Frostbite - Face";
		case DI_FBHANDS:
			return "Frostbite - Hands";
		case DI_FBFEET:
			return "Frostbite - Feet";
		case DI_SMOKE:
			return "Smoke";
		case DI_TEARGAS:
			return "Tear gas";
		case DI_ONFIRE:
			return "On Fire";
		case DI_BOOMERED:
			return "Boomered";
		case DI_SPORES:
			return "Spores";
		case DI_SLIMED:
			return "Slimed";
		case DI_BLIND:
			return "Blind";
		case DI_POISON:
			return "Poisoned";
		case DI_FOODPOISON:
			return "Food Poisoning";
		case DI_SHAKES:
			return "Shakes";
		case DI_DRUNK:
			if (dis.duration > 2200)
				return "Wasted";
			if (dis.duration > 1400)
				return "Trashed";
			if (dis.duration > 800)
				return "Drunk";
			return "Tipsy";
		case DI_CIG:
			return "Cigarette";
		case DI_HIGH:
			return "High";
		case DI_VISUALS:
			return "Hallucinating";
		case DI_ADRENALINE:
			if (dis.duration > 400)
				return "Adrenaline Rush";
			return "Adrenaline Comedown";
		case DI_ASTHMA:
			if (dis.duration > 800)
				return "Heavy Asthma";
			return "Asthma";
		case DI_METH:
			if (dis.duration > 600)
				return "High on Meth";
			return "Meth Comedown";
		case DI_IN_PIT:
			return "Stuck in Pit";
		default:
			return "";
	}
}

std::string dis_description(disease dis) {
	int strpen, allpen;
	std::stringstream stream;
	switch (dis.type) {
		case DI_NULL:
			return "None";
		case DI_HEATSTROKE:
			return "Speed -15%;     Strength - 2;    Intelligence - 2;     Perception - 1";
		case DI_FBFACE:
			return "Perception - 2";
		case DI_FBHANDS:
			return "Dexterity - 2";
		case DI_FBFEET:
			return "Speed -40%;     Strength - 1";
		case DI_SMOKE:
			return "Strength - 1;     Dexterity - 1;\nOccasionally you will cough, costing movement and creating noise.\nLoss of health - Torso";
		case DI_TEARGAS:
			return "Strength - 2;     Dexterity - 2;    Intelligence - 1;    Perception - 4\nOccasionally you will cough, costing movement and creating noise.\nLoss of health - Torso";
		case DI_ONFIRE:
			return "Loss of health - Entire Body\nYour clothing and other equipment may be consumed by the flames.";
		case DI_BOOMERED:
			return "Perception - 5\nRange of Sight: 1;     All sight is tinted magenta";
		case DI_SPORES:
			return "Speed -40%\nYou can feel the tiny spores sinking directly into your flesh.";
		case DI_SLIMED:
			return "Speed -40%;     Dexterity - 2";
		case DI_BLIND:
			return "Range of Sight: 0";
		case DI_POISON:
			return "Perception - 1;    Dexterity - 1;   Strength - 2 IF not resistant\nOccasional pain and/or damage.";
		case DI_FOODPOISON:
			return "Speed - 35%;     Strength - 3;     Dexterity - 1;     Perception - 1\nYour stomach is extremely upset, and you keep having pangs of pain and nausea.";
		case DI_SHAKES:
			return "Strength - 1;     Dexterity - 4;";
		case DI_DRUNK:
			strpen = int(dis.duration / 1000);
			allpen = int(dis.duration / 800);
			stream << "Strength - " << strpen << ";    Dexterity - " << allpen << ";    Intelligence - " << allpen << ";    Perception - " << allpen;
			return stream.str();
		case DI_CIG:
			if (dis.duration > 200)
				return "Strength - 1;     Dexterity - 1\nYou smoked too much.";
			return "Dexterity + 1;     Intelligence + 1;     Perception + 1";
		case DI_HIGH:
			return "Dexterity - 1;     Intelligence - 1;     Perception - 1";
		case DI_VISUALS:
			return "You can't trust everything that you see.";
		case DI_ADRENALINE:
			if (dis.duration > 400)
				return "Speed +80;   Strength + 5;   Dexterity + 3;   Intelligence - 8;   Perception + 1";
			return "Strength - 2;     Dexterity - 1;     Intelligence - 1;     Perception - 1";
		case DI_ASTHMA:
			stream << "Speed - " << int(dis.duration / 5) << "%;     Strength - 2;     " <<  "Dexterity - 3";
			return stream.str();
		case DI_METH:
			if (dis.duration > 600)
				return "Speed +50;   Strength + 2;   Dexterity + 2;   Intelligence + 2;   Perception + 2";
			return "Speed -30;   Strength - 3;   Dexterity - 2;   Intelligence - 2";
		case DI_IN_PIT:
			return "You're stuck in a pit.  Sight distance is limited and you have to climb out.";
		default:
			return "Who knows?";
	}
}

