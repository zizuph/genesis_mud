#include "../stddefs.h"
#include "/sys/stdproperties.h"
#include "trade_road.h"

#pragma save_binary

inherit ELFROOM;

#define WEST         ROOMDIR + "cairn"
#define NORTHEAST    ROOMDIR + "trade_road_1"
#define SOUTHEAST    ROOMDIR + "trade_road_3"

#define LONG \
  "A small, humble path disappears into the deep, shadow-filled forest in "+ \
  "the west, while the road continues to the northeast and southeast.\n"

#define PATH_ITEM ({"path", "small path"})
#define PATH_DESC \
  "Well, it is small and humble.\n"


create_room()
{
  set_short(N_KNOW(TRADE_ROAD_NAT_SHORT, TRADE_ROAD_FOR_SHORT));
  set_long( N_KNOW(WRAP(TRADE_ROAD_NAT_LONG + LONG),
		   WRAP(TRADE_ROAD_FOR_LONG + LONG)));

  add_item(PATH_ITEM, WRAP(PATH_DESC));
  TRADE_ROAD_STD_ITEMS;
  
  add_exit(WEST,      "west",      0);
  add_exit(NORTHEAST, "northeast", 0);
  add_exit(SOUTHEAST, "southeast", 0);

  tie_to_map(CENTER_SQUARE, 186, 4, 554, 4);
}
