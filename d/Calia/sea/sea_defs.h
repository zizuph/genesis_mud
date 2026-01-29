
#include "/d/Calia/domain.h"

#define WATER "/d/Calia/sea/"
#define WATER_STD (WATER+"std/")
#define WATEROB (WATER + "objects/")
#define CAVE (WATER + "pyros/")
#define SEA_WEAPONS (WATER + "weapons/")
#define SEA_ARMOURS (WATER + "armours/")
#define SEA_SPECIALS (WATER + "specials/")
#define SEA_CREATURES (WATER + "creatures/")
#define SEA_OBJECTS (WATER + "objects/")
#define SEA_LEFTOVERS (WATER + "creatures/leftovers/")
#define BEACH (WATER + "beach/")
#define SEA_NET_ID "_sea_net_id"
#define THAL (WATER+"thalassia/")
#define THALL (THAL+"lesser/")
#define THALM (THAL+"major/")
#define THALC (THAL+"citadel/")
#define MERMQ_SHADOW (WATEROB + "mermaid_ring_shadow")

/* following defs added 14/9/2002 */

#define CLIFF_ROOM (BEACH + "cliff/")
#define CAVE_ROOM (BEACH + "caves/")
#define CAVE_LEV1 (CAVE_ROOM + "lev1/")
#define CAVE_LEV2 (CAVE_ROOM + "lev2/")
#define AERIE (CLIFF_ROOM + "aerie/")
#define NEST (AERIE + "nest")
#define FISH_I_FROM_THALASSIAN_SEA "_fish_i_from_thalassian_sea"
#define OBJ_I_VILLAGER_ORIGIN "_obj_i_villager_origin" 
#define BASE_CLIFF (CLIFF_ROOM + "base_cliff_room")
#define BASE_CAVE (CAVE_ROOM + "base_cave_room")
#define ROOM_TELL "/d/Calia/std/room_tell_room"

/* end of addition */

#define X_LIMIT 16
#define Y_LIMIT 16
#define Z_LIMIT 5

#define NUM_SECTORS_X 2
#define NUM_SECTORS_Y 2
#define NUM_SECTORS_Z 5

#define ROOM_I_SEAWEED_FOREST "_room_i_is_seaweed_forest"
#define X_SECTOR(x) ((x * NUM_SECTORS_X) / X_LIMIT)
#define Y_SECTOR(y) ((y * NUM_SECTORS_Y) / Y_LIMIT)
#define Z_SECTOR(z) ((z * NUM_SECTORS_Z) / Z_LIMIT)

#define SECTOR_PATH_TEXT(x, y, z) ("SECTOR_PATH("+x+","+y+","+z+")")

#define SECTOR_PATH(x, y, z) (WATER + "sector_" + X_SECTOR(x) + "_" +\
                              Y_SECTOR(y) + "_" + Z_SECTOR(z) + "/")

#define SECTOR_ROOM_STD(x, y, z) (WATER_STD + "sector_" + X_SECTOR(x) + "_" +\
                              Y_SECTOR(y) + "_" + Z_SECTOR(z) + "_room")

#define E(x) environment(x)

#define KR_HERBSEARCH "/d/Krynn/common/herbsearch.h" 

/* SPECIAL OBJECTS */

#define FRUIT "/d/Calia/std/fruit.c"
#define HAUNT "/d/Calia/gelan/specials/haunt_code.h"

#define SEA_QUESTS "/d/Calia/sea/sea_quests.h"
