#pragma once

class game;

class monster;

class mdeath {
public:
	void normal(game *g, monster *z); // Empty function
	void acid(game *g, monster *z); // Drops acid around the body
	void boomer(game *g, monster *z); // Explodes in vomit :3
	void fungus(game *g, monster *z); // Explodes in spores D:
	void fungusawake(game *g, monster *z); // Turn into live fungaloid
	void shriek(game *g, monster *z); // Screams loudly
	void worm(game *g, monster *z); // Spawns 2 half-worms
	void disappear(game *g, monster *z); // Hallucination disappears
	void guilt(game *g, monster *z); // Morale penalty
	void blobsplit(game *g, monster *z); // Creates more blobs
	void melt(game *g, monster *z); // Normal death, but melts
	void explode(game *g, monster *z); // Damaging explosion
};

