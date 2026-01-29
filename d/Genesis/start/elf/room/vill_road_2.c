#include "../stddefs.h"
#include "/sys/stdproperties.h"
#include "vill_road.h"

#pragma save_binary

inherit ELFROOM;

#define WEST     ROOMDIR + "vill_road_3"
#define EAST     ROOMDIR + "vill_road_1"
#define NORTH    ROOMDIR + "wine_road_1"

#define NAT_LONG \
"The road continues to the west and east, while " + \
  "to the north the small Wine Road disappears between two hedgerows.\n"
#define FOR_LONG \
  "The road continues to the west and east, while " + \
  "to the north a small road disappears between two hedgerows.\n"

#define HROW_ITEM ({"hedgerow", "hedge", "hedgerows", "hedges"})
#define HROW_DESC \
  "The hedgerows are bushy, brushy, thorny and quite impenetrable.\n"
  
create_room()
{
  set_short(N_KNOW(VILL_ROAD_NAT_SHORT, VILL_ROAD_FOR_SHORT));
  set_long( N_KNOW(WRAP(VILL_ROAD_NAT_LONG + NAT_LONG),
		   WRAP(VILL_ROAD_FOR_LONG + FOR_LONG)));

  VILL_ROAD_STD_ITEMS;
  add_item(HROW_ITEM, WRAP(HROW_DESC));

  add_exit(WEST,      "west", 0);
  add_exit(EAST,      "east", 0);
  add_exit(NORTH,     "north", 0);
}
