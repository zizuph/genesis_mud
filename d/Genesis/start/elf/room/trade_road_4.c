#include "../stddefs.h"
#include "/sys/stdproperties.h"
#include "trade_road.h"

#pragma save_binary

inherit ELFROOM;

#define NORTH            ROOMDIR + "trade_road_3"
#define SOUTHWEST        ROOMDIR + "trade_road_5"
#define EAST             ROOMDIR + "swamp_path_1"

#define LONG \
  "The road continues among the firs to the southwest and to the north, and "+\
  "a small, muddy path disappears into the forest in the east.\n"

#define PATH_ITEM ({"path", "swamp path", "muddy rut", "ruts", "rut"})
#define PATH_DESC \
  "The path is only a deep rut of wet mud, winding an ambling "+\
  "way through the forest.\n"

#define MUD_ITEM ({"mud", "wet mud"})
#define MUD_DESC \
  "It is brown, wet and slippery, just the way mud is supposed to be.\n"


create_room()
{
  set_short(N_KNOW(TRADE_ROAD_NAT_SHORT, TRADE_ROAD_FOR_SHORT));
  set_long( N_KNOW(WRAP(TRADE_ROAD_NAT_LONG + LONG),
		   WRAP(TRADE_ROAD_FOR_LONG + LONG)));

  TRADE_ROAD_STD_ITEMS;
  add_item(   MUD_ITEM, WRAP(   MUD_DESC));   
  add_item(  PATH_ITEM, WRAP(  PATH_DESC));

  add_exit(NORTH,     "north", 0);
  add_exit(EAST,      "east",  0);
  add_exit(SOUTHWEST, "southwest", 0);

  tie_to_map(CENTER_SQUARE, 186, 5, 554, 2);
}
