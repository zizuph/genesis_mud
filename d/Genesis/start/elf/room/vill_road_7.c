#include "../stddefs.h"
#include "/sys/stdproperties.h"
#include "vill_road.h"

#pragma save_binary

inherit ELFROOM;

#define WEST         ROOMDIR + "vill_road_6"
#define NORTH        ROOMDIR + "vill_road_8"
#define NORTHWEST    ROOMDIR + "vill_park_4"
#define EAST         ROOMDIR + "vill_post"

#define NAT_LONG \
  "The road continues to the west and north, while " + \
  "to the northwest a small path leads into the park, winding its way " + \
  "beneath the oaks. In the house to the east lies a post office.\n"
#define FOR_LONG \
  "The road continues to the west and north, while " + \
  "to the northwest a small path leads into the park, winding its way " + \
  "beneath the oaks. East is a small house.\n"

#define HOUSE_ITEM ({"house", "small house", "post", "post office", "office" })
#define HOUSE_NDESC \
  "The post office is situated in a small, whitewashed house with " + \
  "thatched roof. A picture of a mounted courier is painted on its wall.\n"
#define HOUSE_FDESC \
  "It is a small house with thached roof and "+\
  "whitewashed walls. On a wall is a painted picture of a horseman " + \
  "on a galloping horse.\n"

create_room()
{
  set_short(N_KNOW(VILL_ROAD_NAT_SHORT, VILL_ROAD_FOR_SHORT));
  set_long( N_KNOW(WRAP(VILL_ROAD_NAT_LONG + NAT_LONG),
		   WRAP(VILL_ROAD_FOR_LONG + FOR_LONG)));

  VILL_ROAD_STD_ITEMS;
  add_item(HOUSE_ITEM, N_KNOW(WRAP(HOUSE_NDESC), WRAP(HOUSE_FDESC)));

  add_exit(WEST,      "west",      0);
  add_exit(NORTH,     "north",     0);
  add_exit(NORTHWEST, "northwest", 0);
  add_exit(EAST,      "east",      0);
}
