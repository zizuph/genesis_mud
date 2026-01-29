#include "../stddefs.h"
#include "/sys/stdproperties.h"
#include "vill_road.h"

#pragma save_binary

inherit ELFROOM;

#define NORTH     ROOMDIR + "vill_road_3"
#define SOUTH     ROOMDIR + "vill_road_5"
#define WEST      ROOMDIR + "vill_inn_1"

#define NAT_LONG \
  "The road continues to the north and south, and " + \
  "to the west is the wine cellar entrance of the village inn, " + \
  "the Frolicking Fawn. " + \
  "The inn has its main entrance further south.\n"

#define FOR_LONG \
  "The road continues to the north and south, while " + \
  "to the west is a door into a large house that continues southwards, "+\
  "where you can see another door into the building further down the road.\n"

#define INN_ITEM ({"inn", "entrance", "house", "the frolicking fawn", "fawn", \
		   "the fawn", "large house", "building", "cellar entrance"})
#define INN_NDESC \
  "Beside the door to the wine cellar, there is a sign cut from greenish " + \
  "wood in the shape of a cluster of grapes.\n"
#define INN_FDESC \
  "Beside the door into the building, there is a green sign, " + \
  "cut in the shape of a cluster of grapes.\n"
  
create_room()
{
  set_short(N_KNOW(VILL_ROAD_NAT_SHORT, VILL_ROAD_FOR_SHORT));
  set_long( N_KNOW(WRAP(VILL_ROAD_NAT_LONG + NAT_LONG),
		   WRAP(VILL_ROAD_FOR_LONG + FOR_LONG)));

  VILL_ROAD_STD_ITEMS;
  add_item(INN_ITEM, N_KNOW(WRAP(INN_NDESC), 
			    WRAP(INN_FDESC)));

  add_exit(NORTH,      "north", 0);
  add_exit(SOUTH,      "south", 0);
  add_exit(WEST,       "west", NYI);
}
