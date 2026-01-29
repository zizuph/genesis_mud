/*
 *
 *
 *
 */

#define STD_ROOM                   "/std/room"
#define DUNGEON_DIR                "/d/Faerun/mere/mausoleum/"
#define DUNGEON_DROPDIRECTORY1     "/d/Faerun/mere/mausoleum/loot_drops1/"

// Number of dungeon monsters per room that spawns them
#define TOMB_SPAWN_NUMBER          3 

// if 40 is equal or larger than 100, full compliment of 
// dungeon monsters will spawn in the room (add_npc).
#define RANDOM_MONSTER_SPAWNCHANCE 40

// Total size of dungeon = SIZE1 + random SIZE2. Minimum 11 room, and max 20.
#define TOMB_INSTANCE_SIZE1       10
#define TOMB_INSTANCE_SIZE2       10


// If LEGENDARY_DROPCHANCE > random(100), legendary item drops instead.
#define LEGENDARY_DROPCHANCE       5

// TOMB CHEST EPIC droptable
string *tomb_chest_drop_epic = ({ "no_drop",
	                         "no_drop",
	                         "no_drop" });
							 
							 
// TOMB CHEST LEGENDARY droptable
string *tomb_chest_drop_legendary = ({ "no_drop",
	                                   "no_drop",
	                                   "no_drop" });