#include "game.h"
#include "trap.h"
#include "rng.h"

void trapfunc::bubble(game *g, int x, int y) {
	g->add_msg("You step on some bubblewrap!");
	g->sound(x, y, 18, "Pop!");
	g->m.tr_at(x, y) = tr_null;
}

void trapfuncm::bubble(game *g, monster *z, int x, int y) {
	g->sound(x, y, 18, "Pop!");
	g->m.tr_at(x, y) = tr_null;
}

void trapfunc::beartrap(game *g, int x, int y) {
	g->add_msg("A bear trap closes on your foot!");
	g->sound(x, y, 8, "SNAP!");
	g->u.hit(g, bp_legs, rng(0, 1), 10, 16);
	g->u.add_disease(DI_BEARTRAP, -1, g);
	g->m.tr_at(x, y) = tr_null;
	g->m.add_item(x, y, g->itypes[itm_beartrap], g->turn);
}

void trapfuncm::beartrap(game *g, monster *z, int x, int y) {
	g->sound(x, y, 8, "SNAP!");
	if (z->hurt(35))
		g->kill_mon(g->mon_at(x, y));
	else
		z->moves = -800;
	g->m.tr_at(x, y) = tr_null;
	g->m.add_item(x, y, g->itypes[itm_beartrap], g->turn);
}

void trapfunc::board(game *g, int x, int y) {
	g->add_msg("You step on a spiked board!");
	g->u.hit(g, bp_feet, 0, 0, rng(6, 10));
	g->u.hit(g, bp_feet, 1, 0, rng(6, 10));
}

void trapfuncm::board(game *g, monster *z, int x, int y) {
	int t;
	if (g->u_see(z, t))
		g->add_msg("The %s steps on a spiked board!", z->name().c_str());
	if (z->hurt(rng(6, 10)))
		g->kill_mon(g->mon_at(x, y));
	else
		z->moves -= 80;
}

void trapfunc::tripwire(game *g, int x, int y) {
	g->add_msg("You trip over a tripwire!");
	std::vector <Point> valid;
	for (int j = x - 1; j <= x + 1; j++) {
		for (int k = y - 1; k <= y + 1; k++) {
			if (g->m.move_cost(j, k) != 0 && g->mon_at(j, k) == -1 &&
				g->npc_at(j, k) == -1)
				valid.push_back(Point(j, k));
		}
	}
	if (valid.size() > 0) {
		int index = rng(0, valid.size() - 1);
		g->u.posx = valid[index].x;
		g->u.posy = valid[index].y;
	}
	g->u.moves -= 150;
	if (rng(5, 20) > g->u.dex_cur)
		g->u.hurtall(rng(1, 4));
}

void trapfuncm::tripwire(game *g, monster *z, int x, int y) {
	int t;
	if (g->u_see(z, t))
		g->add_msg("The %s trips over a tripwire!", z->name().c_str());
	z->stumble(g, false);
	if (rng(0, 10) > z->type->sk_dodge && z->hurt(rng(1, 4)))
		g->kill_mon(g->mon_at(z->posx, z->posy));
}

void trapfunc::crossbow(game *g, int x, int y) {
	bool add_bolt = true;
	g->add_msg("You trigger a crossbow trap!");
	if (!one_in(4) && rng(8, 20) > g->u.dodge()) {
		body_part hit;
		switch (rng(1, 10)) {
			case 1:
				hit = bp_feet;
			case 2:
			case 3:
			case 4:
				hit = bp_legs;
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
				hit = bp_torso;
			case 10:
				hit = bp_head;
		}
		int side = rng(0, 1);
		g->add_msg("Your %s is hit!", body_part_name(hit, side).c_str());
		g->u.hit(g, hit, side, 0, rng(20, 30));
		add_bolt = !one_in(10);
	}
	else
		g->add_msg("You dodge the shot!");
	g->m.tr_at(x, y) = tr_null;
	g->m.add_item(x, y, g->itypes[itm_crossbow], 0);
	g->m.add_item(x, y, g->itypes[itm_string_6], 0);
	if (add_bolt)
		g->m.add_item(x, y, g->itypes[itm_bolt_steel], 0);
}

void trapfuncm::crossbow(game *g, monster *z, int x, int y) {
	int t;
	bool add_bolt = true;
	bool seen = g->u_see(z, t);
	if (!one_in(4)) {
		if (seen)
			g->add_msg("A bolt shoots out and hits the %d!", z->name().c_str());
		if (z->hurt(rng(20, 30)))
			g->kill_mon(g->mon_at(x, y));
		add_bolt = !one_in(10);
	}
	else if (seen)
		g->add_msg("A bolt shoots out, but misses the %d.", z->name().c_str());
	g->m.add_item(x, y, g->itypes[itm_crossbow], 0);
	g->m.add_item(x, y, g->itypes[itm_string_6], 0);
	if (add_bolt)
		g->m.add_item(x, y, g->itypes[itm_bolt_steel], 0);
}

void trapfunc::shotgun(game *g, int x, int y) {
	g->add_msg("You trigger a shotgun trap!");
	int shots = (one_in(8) || one_in(20 - g->u.str_max) ? 2 : 1);
	if (g->m.tr_at(x, y) == tr_shotgun_1)
		shots = 1;
	if (rng(5, 50) > g->u.dodge()) {
		body_part hit;
		switch (rng(1, 10)) {
			case 1:
				hit = bp_feet;
			case 2:
			case 3:
			case 4:
				hit = bp_legs;
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
				hit = bp_torso;
			case 10:
				hit = bp_head;
		}
		int side = rng(0, 1);
		g->add_msg("Your %s is hit!", body_part_name(hit, side).c_str());
		g->u.hit(g, hit, side, 0, rng(40 * shots, 60 * shots));
	}
	else
		g->add_msg("You dodge the shot!");
	if (shots == 2 || g->m.tr_at(x, y) == tr_shotgun_1) {
		g->m.add_item(x, y, g->itypes[itm_shotgun_sawn], 0);
		g->m.add_item(x, y, g->itypes[itm_string_6], 0);
		g->m.tr_at(x, y) = tr_null;
	}
	else
		g->m.tr_at(x, y) = tr_shotgun_1;
}

void trapfuncm::shotgun(game *g, monster *z, int x, int y) {
	int t;
	bool seen = g->u_see(z, t);
	int chance;
	switch (z->type->size) {
		case MS_TINY:
			chance = 100;
		case MS_SMALL:
			chance = 16;
		case MS_MEDIUM:
			chance = 12;
		case MS_LARGE:
			chance = 8;
		case MS_HUGE:
			chance = 2;
	}
	int shots = (one_in(8) || one_in(chance) ? 2 : 1);
	if (g->m.tr_at(x, y) == tr_shotgun_1)
		shots = 1;
	if (seen)
		g->add_msg("A bolt shoots out and hits the %d!", z->name().c_str());
	if (z->hurt(rng(40 * shots, 60 * shots)))
		g->kill_mon(g->mon_at(x, y));
	if (shots == 2 || g->m.tr_at(x, y) == tr_shotgun_1) {
		g->m.tr_at(x, y) = tr_null;
		g->m.add_item(x, y, g->itypes[itm_shotgun_sawn], 0);
		g->m.add_item(x, y, g->itypes[itm_string_6], 0);
	}
	else
		g->m.tr_at(x, y) == tr_shotgun_1;
}


void trapfunc::blade(game *g, int x, int y) {
	g->add_msg("A machete swings out and hacks your torso!");
	g->u.hit(g, bp_torso, 0, 12, 30);
}

void trapfuncm::blade(game *g, monster *z, int x, int y) {
	int t;
	if (g->u_see(z, t))
		g->add_msg("A machete swings out and hacks the %s!", z->name().c_str());
	int cutdam = 30 - z->type->armor;
	if (cutdam < 0)
		cutdam = 0;
	if (z->hurt(12 + cutdam))
		g->kill_mon(g->mon_at(x, y));
}

void trapfunc::landmine(game *g, int x, int y) {
	g->add_msg("You trigger a landmine!");
	g->explosion(x, y, 20, 24, false);
	g->m.tr_at(x, y) = tr_null;
}

void trapfuncm::landmine(game *g, monster *z, int x, int y) {
	int t;
	if (g->u_see(x, y, t))
		g->add_msg("The %s steps on a landmine!", z->name().c_str());
	g->explosion(x, y, 20, 24, false);
	g->m.tr_at(x, y) = tr_null;
}

void trapfunc::telepad(game *g, int x, int y) {
	g->sound(x, y, 6, "vvrrrRRMM*POP!*");
	g->add_msg("The air shimmers around you...");
	g->teleport();
}

void trapfuncm::telepad(game *g, monster *z, int x, int y) {
	g->sound(x, y, 6, "vvrrrRRMM*POP!*");
	int j;
	if (g->u_see(z, j))
		g->add_msg("The air shimmers around the %s...", z->name().c_str());
	do {
		z->posx = rng(z->posx - SEEX, z->posx + SEEX);
		z->posy = rng(z->posy - SEEY, z->posy + SEEY);
	} while (g->m.move_cost(z->posx, z->posy) == 0);
}

void trapfunc::goo(game *g, int x, int y) {
	g->add_msg("You step in a puddle of thick goo.");
	g->u.infect(DI_SLIMED, bp_feet, 6, 20, g);
	if (one_in(3)) {
		g->add_msg("The acidic goo eats away at your feet.");
		g->u.hit(g, bp_feet, 0, 0, 5);
		g->u.hit(g, bp_feet, 1, 0, 5);
	}
	g->m.tr_at(x, y) = tr_null;
}

void trapfuncm::goo(game *g, monster *z, int x, int y) {
	if (z->type->id == mon_blob) {
		z->speed += 15;
		z->hp = z->speed;
	}
	else {
		z->poly(g->mtypes[mon_blob]);
		z->speed -= 15;
		z->hp = z->speed;
	}
	g->m.tr_at(x, y) = tr_null;
}

void trapfunc::dissector(game *g, int x, int y) {
	g->add_msg("Electrical beams emit from the floor and slice your flesh!");
	g->sound(x, y, 10, "BRZZZAP!");
	g->u.hit(g, bp_head, 0, 0, 15);
	g->u.hit(g, bp_torso, 0, 0, 20);
	g->u.hit(g, bp_arms, 0, 0, 12);
	g->u.hit(g, bp_arms, 1, 0, 12);
	g->u.hit(g, bp_hands, 0, 0, 10);
	g->u.hit(g, bp_hands, 1, 0, 10);
	g->u.hit(g, bp_legs, 0, 0, 12);
	g->u.hit(g, bp_legs, 1, 0, 12);
	g->u.hit(g, bp_feet, 0, 0, 10);
	g->u.hit(g, bp_feet, 1, 0, 10);
}

void trapfuncm::dissector(game *g, monster *z, int x, int y) {
	g->sound(x, y, 10, "BRZZZAP!");
	if (z->hurt(60))
		g->kill_mon(g->mon_at(x, y));
}

void trapfunc::pit(game *g, int x, int y) {
	g->add_msg("You fall in a pit!");
	int dodge = g->u.dodge();
	int damage = rng(10, 20) - rng(dodge, dodge * 5);
	if (damage > 0) {
		g->add_msg("You hurt yourself!");
		g->u.hurtall(rng(int(damage / 2), damage));
		g->u.hit(g, bp_legs, 0, damage, 0);
		g->u.hit(g, bp_legs, 1, damage, 0);
	}
	else
		g->add_msg("You land nimbly.");
	g->u.add_disease(DI_IN_PIT, -1, g);
}

void trapfuncm::pit(game *g, monster *z, int x, int y) {
	int junk;
	if (g->u_see(x, y, junk))
		g->add_msg("The %s falls in a pit!", z->name().c_str());
	if (z->hurt(rng(10, 20)))
		g->kill_mon(g->mon_at(x, y));
	else
		z->moves = -1000;
}

void trapfunc::pit_spikes(game *g, int x, int y) {
	g->add_msg("You fall in a pit!");
	int dodge = g->u.dodge();
	int damage = rng(40, 70);
	if (rng(5, 30) < dodge)
		g->add_msg("You avoid the spikes within.");
	else {
		body_part hit;
		switch (rng(1, 10)) {
			case 1:
			case 2:
				hit = bp_legs;
			case 3:
			case 4:
				hit = bp_arms;
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
			case 10:
				hit = bp_torso;
		}
		int side = rng(0, 1);
		g->add_msg("The spikes impale your %s!", body_part_name(hit, side).c_str());
		g->u.hit(g, hit, side, 0, damage);
		g->u.hit(g, bp_legs, 1, damage, 0);
	}
	g->u.add_disease(DI_IN_PIT, -1, g);
}

void trapfuncm::pit_spikes(game *g, monster *z, int x, int y) {
	int junk;
	if (g->u_see(z, junk))
		g->add_msg("The %s falls in a spiked pit!", z->name().c_str());
	if (z->hurt(rng(40, 70)))
		g->kill_mon(g->mon_at(x, y));
	else
		z->moves = -1000;
}

void trapfunc::sinkhole(game *g, int x, int y) {
	g->add_msg("You step into a sinkhole, and start to sink down!");
	if (g->u.has_amount(itm_rope_30, 1) &&
		query_yn("Throw your rope to try to catch soemthing?")) {
		int throwroll = rng(g->u.sklevel[sk_throw],
							g->u.sklevel[sk_throw] + g->u.str_cur + g->u.dex_cur);
		if (throwroll >= 12) {
			g->add_msg("The rope catches something!");
			if (rng(g->u.sklevel[sk_unarmed], g->u.sklevel[sk_unarmed] + g->u.str_cur) > 6) {
// Determine safe places for the character to get pulled to
				std::vector <Point> safe;
				for (int i = g->u.posx - 1; i <= g->u.posx + 1; i++) {
					for (int j = g->u.posx - 1; j <= g->u.posx + 1; j++) {
						if (g->m.move_cost(i, j) > 0 && g->m.tr_at(i, j) != tr_pit)
							safe.push_back(Point(i, j));
					}
				}
				if (safe.size() == 0) {
					g->add_msg("There's nowhere to pull yourself to, and you sink!");
					g->u.use_up(itm_rope_30, 1);
					g->m.add_item(g->u.posx + rng(-1, 1), g->u.posy + rng(-1, 1),
								  g->itypes[itm_rope_30], g->turn);
					g->m.tr_at(g->u.posx, g->u.posy) = tr_pit;
					g->vertical_move(-1, true);
				}
				else {
					g->add_msg("You pull yourself to safety!  The sinkhole collapses.");
					int index = rng(0, safe.size() - 1);
					g->u.posx = safe[index].x;
					g->u.posy = safe[index].y;
					g->m.tr_at(g->u.posx, g->u.posy) = tr_pit;
				}
			}
			else {
				g->add_msg("You're not strong enough to pull yourself out...");
				g->u.moves -= 100;
				g->u.use_up(itm_rope_30, 1);
				g->m.add_item(g->u.posx + rng(-1, 1), g->u.posy + rng(-1, 1),
							  g->itypes[itm_rope_30], g->turn);
				g->vertical_move(-1, true);
			}
		}
		else {
			g->add_msg("Your throw misses completely, and you sink!");
			if (one_in((g->u.str_cur + g->u.dex_cur) / 3)) {
				g->u.use_up(itm_rope_30, 1);
				g->m.add_item(g->u.posx + rng(-1, 1), g->u.posy + rng(-1, 1),
							  g->itypes[itm_rope_30], g->turn);
			}
			g->m.tr_at(g->u.posx, g->u.posy) = tr_pit;
			g->vertical_move(-1, true);
		}
	}
	else {
		g->add_msg("You sink into the sinkhole!");
		g->vertical_move(-1, true);
	}
}

