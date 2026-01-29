#include "../stddefs.h"
#include "/sys/stdproperties.h"
#include "vill_road.h"

#pragma save_binary

inherit ELFROOM;

#define NORTH     ROOMDIR + "vill_road_1"
#define SOUTH     ROOMDIR + "vill_road_7"
#define EAST      ROOMDIR + "vill_board"

#define NAT_LONG \
  "The road continues to the north and south, and " + \
  "to the east is a public bulletin board, protected from rain by a small " + \
  "wooden roof.\n"
#define FOR_LONG \
  "The road continues to the north and south, while " + \
  "to the east is a small building with a wooden roof, but no walls.\n" 

#define SHELTER_ITEM ({"shelter", "building", "roof", "gazebo", })
#define SHELTER_DESC \
  "It is a small wooden building, with an octagonal roof on eight " + \
  "pillars. It has many gingerbread wood-carvings patterned after flowers " + \
  "and leaves, and it looks mostly like a gazebo, protecting more from " + \
  "rain and sun than from wind.\n"
  
create_room()
{
  set_short(N_KNOW(VILL_ROAD_NAT_SHORT, VILL_ROAD_FOR_SHORT));
  set_long( N_KNOW(WRAP(VILL_ROAD_NAT_LONG + NAT_LONG),
		   WRAP(VILL_ROAD_FOR_LONG + FOR_LONG)));

  VILL_ROAD_STD_ITEMS;
  add_item(SHELTER_ITEM, WRAP(SHELTER_DESC));

  add_exit(NORTH,      "north", 0);
  add_exit(SOUTH,      "south", 0);
  add_exit(EAST,       "east",  0);
}
