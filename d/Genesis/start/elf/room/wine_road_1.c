#include "../stddefs.h"
#include "/sys/stdproperties.h"
#include "wine_road.h"

#pragma save_binary

inherit ELFROOM;

#define SOUTH    ROOMDIR + "vill_road_2"
#define WEST     ROOMDIR + "vill_jail_1"
#define NORTH    ROOMDIR + "wine_road_2"

#define NAT_LONG \
  "The Wine Road goes from the village centrum in the south, out to the "+\
  "Wine Mountain in the north. Right here it is winding its way between two "+\
  "huge hedgerows. There is a dark opening in the west hedgerow.\n"
#define FOR_LONG \
  "The small road continues to the south and north, between two hedgerows. "+\
  "There is a dark opening in the west hedgerow\n"

#define OPENING_ITEM ({"opening", "dark opening"})
#define OPENING_DESC \
  "It is hard to see what is on the other side, but it seems like people " +\
  "walk this way quite often.\n"
  
create_room()
{
  set_short(N_KNOW(WINE_ROAD_NAT_SHORT, WINE_ROAD_FOR_SHORT));
  set_long( N_KNOW(WRAP(NAT_LONG), WRAP(FOR_LONG)));

  WINE_ROAD_STD_ITEMS;
  add_item(OPENING_ITEM, WRAP(OPENING_DESC));

  add_exit(SOUTH,     "south", 0);
  add_exit(WEST,      "west",  0);
  add_exit(NORTH,     "north", NYI);
}
