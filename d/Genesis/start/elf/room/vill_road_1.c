#include "../stddefs.h"
#include "/sys/stdproperties.h"
#include "vill_road.h"

#pragma save_binary

inherit ELFROOM;

#define WEST         ROOMDIR + "vill_road_2"
#define NORTH        ROOMDIR + "vill_scholar_1"
#define SOUTH        ROOMDIR + "vill_road_8"
#define SOUTHWEST    ROOMDIR + "vill_park_2"
#define NORTHEAST    ROOMDIR + "trade_road_6"

#define NAT_LONG \
  "The road continues to the west and south, while " + \
  "to the southwest a small path leads into the park, winding its way " + \
  "beneath the oaks. In the northeast the Trade Road disappears into the " + \
  "fir forest, and straight to the north a path leads to the house of " + \
  "the widow Wormwood.\n"
#define FOR_LONG \
  "The road continues to the west and south, while " + \
  "to the southwest a small path leads into the park, winding its way " + \
  "beneath the oaks. In the northeast a road disappears into the forest, " +\
  "and to the north a small path leads into a garden.\n"

create_room()
{
  set_short(N_KNOW(VILL_ROAD_NAT_SHORT, VILL_ROAD_FOR_SHORT));
  set_long( N_KNOW(WRAP(VILL_ROAD_NAT_LONG + NAT_LONG),
		   WRAP(VILL_ROAD_FOR_LONG + FOR_LONG)));

  VILL_ROAD_STD_ITEMS;

  add_exit(WEST,      "west", 0);
  add_exit(NORTH,     "north", 0);
  add_exit(SOUTH,     "south", 0);
  add_exit(SOUTHWEST, "southwest", 0);
  add_exit(NORTHEAST, "northeast", 0);
}
