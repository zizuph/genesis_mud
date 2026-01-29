#include "../stddefs.h"
#include "/sys/stdproperties.h"
#include "trade_road.h"

#pragma save_binary

inherit ELFROOM;

#define NORTHWEST    ROOMDIR + "trade_road_2"
#define SOUTH        ROOMDIR + "trade_road_4"

#define LONG \
  "The road continues among the firs to the northwest and to the south.\n"

create_room()
{
  set_short(N_KNOW(TRADE_ROAD_NAT_SHORT, TRADE_ROAD_FOR_SHORT));
  set_long( N_KNOW(WRAP(TRADE_ROAD_NAT_LONG + LONG),
		   WRAP(TRADE_ROAD_FOR_LONG + LONG)));

  TRADE_ROAD_STD_ITEMS;

  add_exit(NORTHWEST, "northwest", 0);
  add_exit(SOUTH    , "south", 0);

  tie_to_map(CENTER_SQUARE, 186, 5, 554, 3);
}
