#include "../stddefs.h"
#include "/sys/stdproperties.h"
#include "vill_road.h"

#pragma save_binary

inherit ELFROOM;

#define WEST     ROOMDIR + "vill_road_5"
#define EAST     ROOMDIR + "vill_road_7"
#define SOUTH  CASTLEDIR + "castle_road_1"

#define NAT_LONG \
"The road continues to the west and east, while " + \
  "to the south a tree-lined avenue leads to the Royal Castle.\n"
#define FOR_LONG \
  "The road continues to the west and east, while " + \
  "to the south a tree-lined avenue leads to the castle.\n"

#define AVENUE_ITEM "avenue"
  
create_room()
{
  set_short(N_KNOW(VILL_ROAD_NAT_SHORT, VILL_ROAD_FOR_SHORT));
  set_long( N_KNOW(WRAP(VILL_ROAD_NAT_LONG + NAT_LONG),
		   WRAP(VILL_ROAD_FOR_LONG + FOR_LONG)));

  VILL_ROAD_STD_ITEMS;
  add_item(AVENUE_ITEM, N_KNOW(WRAP(ROAD_NDESC),
			       WRAP(ROAD_FDESC)));

  add_exit(WEST,      "west", 0);
  add_exit(EAST,      "east", 0);
  add_exit(SOUTH,     "south", 0);
}
