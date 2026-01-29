#include "../stddefs.h"
#include "/sys/stdproperties.h"
#include "trade_road.h"

#pragma save_binary

inherit ELFROOM;

#define NORTHEAST   ROOMDIR + "trade_road_4"
#define WEST        ROOMDIR + "trade_road_6"
#define SOUTH       ROOMDIR + "begin"
#define NORTH       ROOMDIR + "orchard_1"

#define NAT_LONG \
  "From the south, shreds of fog from the Glade of Beginnings sweeps in, "+\
  "obscuring the road at irregular intervals, as it continues towards " + \
  "the northeast and west.\n" +\
  "In the north the dark wall of the fir forest is broken " + \
  "by the bright colours of a small orchard.\n"
  
#define FOR_LONG \
  "South is a mist-filled opening in the forest, from which now and then "+\
  "shreds of fog sweeps in over the road. The road continues towards " + \
  "the northeast and west.\n" +\
  "In the north the dark wall of the fir forest is broken " + \
  "by the bright colours of a small orchard.\n"


create_room()
{
  set_short(N_KNOW(TRADE_ROAD_NAT_SHORT, TRADE_ROAD_FOR_SHORT));
  set_long( N_KNOW(WRAP(TRADE_ROAD_NAT_LONG + NAT_LONG),
		   WRAP(TRADE_ROAD_FOR_LONG + FOR_LONG)));

  TRADE_ROAD_STD_ITEMS;

  add_exit(NORTHEAST, "northeast", 0);
  add_exit(WEST,      "west",      0);
  add_exit(NORTH,     "north",     0);
  add_exit(SOUTH,     "south",     0);
  tie_to_map(CENTER_SQUARE, CENTER_X, 4, CENTER_Y, 1);
}
