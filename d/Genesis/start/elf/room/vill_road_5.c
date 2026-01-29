#include "../stddefs.h"
#include "/sys/stdproperties.h"
#include "vill_road.h"

#pragma save_binary

inherit ELFROOM;

#define EAST         ROOMDIR + "vill_road_6"
#define NORTH        ROOMDIR + "vill_road_4"
#define NORTHEAST    ROOMDIR + "vill_park_5"
#define SOUTH        ROOMDIR + "vill_inn_2"

#define NAT_LONG \
  "The road continues to the east and north, while " + \
  "to the northeast a small path leads into the park, winding its way " + \
  "beneath the oaks.\n" + \
  "South and west of the road lies the village inn, the Frolicking Fawn. " +\
  "Its main entrance is straight south, while the entrance to its wine " +\
  "cellar is further up the road to the north.\n"
#define FOR_LONG \
  "The road continues to the east and north, while " + \
  "to the northeast a small path leads into the park, winding its way " + \
  "beneath the oaks. South and west of the road is a large building, with " +\
  "a large door straight south of here. The building continues along the " +\
  "road to the north, and you can see another door there.\n"

#define INN_ITEM ({"inn", "entrance", "house", "the frolicking fawn", "fawn", \
		    "house", "the fawn", "large house", "building",  \
		    "main entrance"})
#define INN_NDESC \
  "Beside the main door to the inn is the sign it has taken its name from." +\
  "On the sign is a young deer skipping and jumping on a summer meadow.\n"
#define INN_FDESC \
  "Beside the door into the building, there is a painted sign, " +  \
  "showing a deer above some grass.\n"

create_room()
{
  set_short(N_KNOW(VILL_ROAD_NAT_SHORT, VILL_ROAD_FOR_SHORT));
  set_long( N_KNOW(WRAP(VILL_ROAD_NAT_LONG + NAT_LONG),
		   WRAP(VILL_ROAD_FOR_LONG + FOR_LONG)));

  VILL_ROAD_STD_ITEMS;
  add_item(INN_ITEM, N_KNOW(WRAP(INN_NDESC), WRAP(INN_FDESC)));

  add_exit(EAST,      "east",      0);
  add_exit(NORTH,     "north",     0);
  add_exit(NORTHEAST, "northeast", 0);
  add_exit(SOUTH,     "south",     NYI);
}
