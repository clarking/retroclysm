#pragma once

#include <ncurses.h>
//#include <stdlib.h>
#include <vector>
#include <string>

#include "mapdata.h"
#include "mapitems.h"
#include "overmap.h"
#include "item.h"
#include "monster.h"
#include "npc.h"

class player;

class item;

struct itype;

class map {
public:
// Constructors & Initialization
	map();

	map(std::vector<itype *> *itptr, std::vector<itype_id> (*miptr)[num_itloc],
		std::vector<trap *> *trptr);

	~map();

	void init(game *g, int x, int y);

	void generate(game *g, overmap *om, int x, int y, int turn);

// Visual Output
	void draw(game *g, WINDOW *w);

	void debug();

	void drawsq(WINDOW *w, player &u, int x, int y, bool invert, bool show_items);

// File I/O
	void save(overmap *om, unsigned int turn, int x, int y);

	void load(game *g, int wx, int wy);

	void shift(game *g, int wx, int wy, int x, int y);

	void spawn_monsters(game *g);

// Movement and LOS
	int move_cost(int x, int y); // Cost to move through; 0 = impassible
	bool trans(int x, int y); // Transparent?
	// (Fx, Fy) sees (Tx, Ty), within a range of (range)?
	// tc indicates the Bresenham line used to connect the two points, and may
	//  subsequently be used to form a path between them
	bool sees(int Fx, int Fy, int Tx, int Ty, int range, int &tc);
	//std::vector<Point> route(int Fx, int Fy, int Tx, int Ty); // Best route

// Terrain
	ter_id &ter(int x, int y); // Terrain at coord (x, y); {x|y}=(0, SEE{X|Y}*3]
	std::string tername(int x, int y); // Name of terrain at (x, y)
	std::string features(int x, int y); // Words relevant to terrain (sharp, etc)
	bool has_flag(t_flag flag, int x, int y);

	bool is_destructable(int x, int y);

	bool close_door(int x, int y);

	bool open_door(int x, int y, bool inside);

	bool bash(int x, int y, int str, std::string &sound);

	void destroy(game *g, int x, int y, bool makesound);

	void shoot(game *g, int x, int y, int &dam, bool hit_items);

// Radiation
	int &radiation(int x, int y);    // Amount of radiation at (x, y);

// Items
	std::vector <item> &i_at(int x, int y);

	item water_from(int x, int y);

	void i_clear(int x, int y);

	void i_rem(int x, int y, int index);

	Point find_item(item *it);

	void add_item(int x, int y, itype *type, int birthday);

	void add_item(int x, int y, item new_item);

	void process_active_items(game *g);

// Traps
	trap_id &tr_at(int x, int y);

	void add_trap(int x, int y, trap_id t);

	void disarm_trap(game *g, int x, int y);

// Fields
	field &field_at(int x, int y);

	bool add_field(game *g, int x, int y, field_id t, unsigned char density);

	bool process_fields(game *g);

	void step_in_field(int x, int y, game *g);

	void mon_in_field(int x, int y, game *g, monster *z);

// mapgen.h functions
	void place_items(items_location loc, int chance, int x1, int y1,
					 int x2, int y2, bool ongrass, int turn);

	void make_all_items_owned();

	void add_spawn(mon_id type, int count, int x, int y);

private:
	void saven(overmap *om, unsigned int turn, int x, int y, int gridx, int gridy);

	bool loadn(game *g, int x, int y, int gridx, int gridy);

	void draw_map(overmap_terrain_id terrain_type, overmap_terrain_id t_north, overmap_terrain_id t_east,
				  overmap_terrain_id t_south, overmap_terrain_id t_west, overmap_terrain_id t_above, int turn);

	void rotate(int turns);// Rotates the current map 90*turns degress clockwise
	// Useful for houses, shops, etc

	submap grid[9];
	std::vector <item> nulitems; // Returned when &i_at() is asked for an OOB value
	ter_id nulter;    // Returned when &ter() is asked for an OOB value
	trap_id nultrap; // Returned when &tr_at() is asked for an OOB value
	field nulfield; // Returned when &field_at() is asked for an OOB value
	int nulrad;    // OOB &radiation()

	std::vector<itype *> *itypes;
	std::vector<trap *> *traps;
	std::vector<itype_id> (*mapitems)[num_itloc];
};

