#include "../village.h"
#define TRAILBASE     ROOM + "trailbase"
#define ROADBASE      ROOM + "road_base"
#define ROAD_MESSAGES ROOM + "road_messages"
#define HOMEBASE      ROOM + "home_base"
#define BK_GROVEBASE  ROOM + "bk_grove_base"
#define BK_TREEBASE   ROOM + "bk_tree_base"

#define VILLAGER      NPC + "villager"

#define INSIDE       add_prop(ROOM_I_INSIDE, 1)
#define DARK         add_prop(OBJ_I_LIGHT, -1)
#define LIGHT        add_prop(OBJ_I_LIGHT, 1)
#define BEES         add_prop(BEE_ROOM,1)
