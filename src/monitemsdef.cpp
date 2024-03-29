#include "game.h"
#include "setvector.h"

void game::init_monitems() {
	setvector(monitems[mon_ant],
			  mi_ants, 1, NULL);
	monitems[mon_ant_soldier] = monitems[mon_ant];
	monitems[mon_ant_queen] = monitems[mon_ant];

	setvector(monitems[mon_zombie],
			  mi_livingroom, 10, mi_kitchen, 8, mi_bedroom, 20, mi_dresser, 30,
			  mi_softdrugs, 5, mi_harddrugs, 2, mi_tools, 6, mi_trash, 7,
			  mi_ammo, 18, mi_pistols, 3, mi_shotguns, 2, mi_smg, 1,
			  NULL);
	monitems[mon_zombie_shrieker] = monitems[mon_zombie];
	monitems[mon_zombie_spitter] = monitems[mon_zombie];
	monitems[mon_zombie_electric] = monitems[mon_zombie];
	monitems[mon_zombie_fast] = monitems[mon_zombie];
	monitems[mon_zombie_brute] = monitems[mon_zombie];
	monitems[mon_zombie_hulk] = monitems[mon_zombie];
	monitems[mon_zombie_fungus] = monitems[mon_zombie];
	monitems[mon_boomer] = monitems[mon_zombie];
	monitems[mon_boomer_fungus] = monitems[mon_zombie];
	monitems[mon_zombie_necro] = monitems[mon_zombie];

	setvector(monitems[mon_chud],
			  mi_subway, 40, mi_sewer, 20, mi_trash, 5, mi_bedroom, 1,
			  mi_dresser, 5, mi_ammo, 18, NULL);
	monitems[mon_one_eye] = monitems[mon_chud];

	setvector(monitems[mon_bee],
			  mi_bees, 1, NULL);

	setvector(monitems[mon_eyebot],
			  mi_robots, 4, mi_ammo, 1, NULL);
	monitems[mon_manhack] = monitems[mon_eyebot];
	monitems[mon_skitterbot] = monitems[mon_eyebot];
	monitems[mon_secubot] = monitems[mon_eyebot];
	monitems[mon_molebot] = monitems[mon_eyebot];
	monitems[mon_tripod] = monitems[mon_eyebot];
	monitems[mon_chickenbot] = monitems[mon_eyebot];
	monitems[mon_tankbot] = monitems[mon_eyebot];
	monitems[mon_turret] = monitems[mon_eyebot];
}
