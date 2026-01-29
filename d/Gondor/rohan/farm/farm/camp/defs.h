#include "/d/Gondor/defs.h"

// Defines for the Dunelending Area by Rohan
#define CAMP_DIR		(FARM_DIR + "farm/camp/")
#define CAMP_LIB_DIR	(CAMP_DIR + "lib/")
#define CAMP_ROOM_DIR	(CAMP_DIR + "rooms/")
#define CAMP_ARM_DIR	(CAMP_DIR + "arm/")
#define CAMP_WEP_DIR	(CAMP_DIR + "wep/")
#define CAMP_NPC_DIR	(CAMP_DIR + "npc/")
#define CAMP_OBJ_DIR	(CAMP_DIR + "obj/")
#define CAMP_FOOD_DIR   (CAMP_OBJ_DIR + "food/")

//For the guards
#define GUARDMAKER		(CAMP_LIB_DIR + "base_dunlending")
#define SCOUT 	CAMP_NPC_DIR + "scout"
#define GUARD 	CAMP_NPC_DIR + "guard"
#define CAPTAIN	CAMP_NPC_DIR + "captain"
#define ARCHER 	CAMP_NPC_DIR + "archer"

//For animals
#define ANIMAL		"/d/Gondor/common/npc/"
#define CROW		ANIMAL + "crow"
#define FOX			ANIMAL + "fox"
#define GRASSHOPPER	ANIMAL + "grasshopper"
#define DEER		ANIMAL + "buck"
#define OWL			ANIMAL + "owl"
#define SNAKE		ANIMAL + "snake"
#define WOLF		ANIMAL + "wolf"
#define RABBIT		ANIMAL + "rabbit"
#define RANDOM_ANIMAL	({CROW, FOX, GRASSHOPPER, DEER, OWL, SNAKE, WOLF, RABBIT})

//For Questing
#define QUEST       "_i_did_edoras_jaine_sword_quest"
#define QUESTING    "_i_am_doing_edoras_jaine_sword_quest"
#define JSWORD      "edoras_jaine_quest_longsword"