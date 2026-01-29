#include "../stddefs.h"
#include "/sys/stdproperties.h"
#include "trade_road.h"

#pragma save_binary

inherit ELFROOM;

#define EAST       ROOMDIR + "trade_road_5"
#define SOUTHWEST  ROOMDIR + "vill_road_1"

#define NAT_LONG \
  "Southwest of here you can see the village of Greenoaks, beyond which " + \
  "the towers of the Royal Castle rises. In the east the Trade road " + \
  "disappears into the forest.\n"
#define FOR_LONG \
  "Southwest of here you can see a small village, beyond which " + \
  "the towers of a magnificent castle rises. In the east, the road " + \
  "disappears into the forest.\n"
 
#define CASTLE_ITEM ({"castle", "palace", "tower", "towers"})
#define CASTLE_NDESC \
  "The towers of King Oberon's and Queen Titania's castle " + \
  "shimmers from the sunlight reflected and refracted by the thousands of " +\
  "jewels that has been set into the castle walls.\n" 
#define CASTLE_FDESC \
  "The towers of a castle shimmers in the sunlight, as if " +\
  "jewels had been set into its walls.\n"


create_room()
{
  set_short(N_KNOW(TRADE_ROAD_NAT_SHORT, TRADE_ROAD_FOR_SHORT));
  set_long( N_KNOW(WRAP(TRADE_ROAD_NAT_LONG + NAT_LONG),
		   WRAP(TRADE_ROAD_FOR_LONG + FOR_LONG)));

  TRADE_ROAD_STD_ITEMS;
  add_item(CASTLE_ITEM, N_KNOW(WRAP(CASTLE_NDESC), WRAP(CASTLE_FDESC))); 

  add_exit(EAST,      "east",      0);
  add_exit(SOUTHWEST, "southwest", 0);
  tie_to_map(CENTER_SQUARE, 186, 3, 554, 1);

  stock();
}


void stock()
{
  restock_object(OBJDIR+"weather_sign", 1, "billboard");
}

reset_room()
{
  stock();
}
