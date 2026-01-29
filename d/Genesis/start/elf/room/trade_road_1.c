#include "../stddefs.h"
#include "/sys/stdproperties.h"
#include "trade_road.h"

#pragma save_binary

inherit ELFROOM;

#define NORTH        ROOMDIR + "entrance"
#define SOUTHWEST    ROOMDIR + "trade_road_2"
#define EAST         ROOMDIR + "magestone_place"

#define LONG \
  "The trade road continues to the north and southwest, " + \
  "while in the east there " + \
  "is a small clearing in the forest, from which "+\
  "blows a faint breeze of warm air.\n"

create_room()
{
  set_short(N_KNOW(TRADE_ROAD_NAT_SHORT, TRADE_ROAD_FOR_SHORT));
  set_long( N_KNOW(WRAP(TRADE_ROAD_NAT_LONG + LONG), 
		   WRAP(TRADE_ROAD_FOR_LONG + LONG)));	   

  TRADE_ROAD_STD_ITEMS;

  add_exit(NORTH,     "north", 0);
  add_exit(EAST,      "east", 0);
  add_exit(SOUTHWEST, "southwest", 0);

  tie_to_map(CENTER_SQUARE, 186, 5, 554, 5);
}
