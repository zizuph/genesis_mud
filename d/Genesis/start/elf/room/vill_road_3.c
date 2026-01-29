#include "../stddefs.h"
#include "/sys/stdproperties.h"
#include "vill_road.h"

#pragma save_binary

inherit ELFROOM;

#define EAST         ROOMDIR + "vill_road_2"
#define SOUTH        ROOMDIR + "vill_road_4"
#define NORTH        ROOMDIR + "vill_trainer_1"
#define SOUTHEAST    ROOMDIR + "vill_park_1"
#define WEST         ROOMDIR + "vill_shop"

#define NAT_LONG \
  "The road continues to the east and south, while " + \
  "to the southeast a small path leads into the park, winding its way " + \
  "beneath the oaks. In the house to the west lives Melien Tamsin, the " + \
  "trader, who is often willing to sell and buy most things, and to the " + \
  "north a gravel path leads to the house of sergeant Bullwhip.\n"
#define FOR_LONG \
  "The road continues to the east and south, while " + \
  "to the southeast a small path leads into the park, winding its way " + \
  "beneath the oaks. In the west there is a small house, and to the north " + \
  "a gravel path leads into a neglected garden.\n"

#define HOUSE_ITEM ({"house", "small house", "trader house", "trader's house"})
#define HOUSE_NDESC \
  "Trader Melien Tamsin lives in is a small house with thached roof and "+\
  "stout wooden walls, carved with likenesses of the animals of " + \
  "wilderness and forest.\n"
#define HOUSE_FDESC \
  "It is a small house with thached roof and "+\
  "wooden walls. There is animal pictures carved into its walls.\n"

#define GARDEN_ITEM ({"garden"})
#define GARDEN_DESC \
  "The garden seem neglected and untended. The weeds are by far in majority "+\
  "and are waging a winning war on the few herbs and ornamental plants left.\n"

create_room()
{
  set_short(N_KNOW(VILL_ROAD_NAT_SHORT, VILL_ROAD_FOR_SHORT));
  set_long( N_KNOW(WRAP(VILL_ROAD_NAT_LONG + NAT_LONG),
		   WRAP(VILL_ROAD_FOR_LONG + FOR_LONG)));

  VILL_ROAD_STD_ITEMS;
  add_item( HOUSE_ITEM, N_KNOW(WRAP(HOUSE_NDESC), WRAP(HOUSE_FDESC)));
  add_item(GARDEN_ITEM, GARDEN_DESC);

  add_exit(EAST,      "east",      0);
  add_exit(NORTH,     "north",     0);
  add_exit(SOUTH,     "south",     0);
  add_exit(SOUTHEAST, "southeast", 0);
  add_exit(WEST,      "west",      0);
}
