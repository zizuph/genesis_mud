#include "../stddefs.h"
#include <stdproperties.h>
#include <composite.h>
#include <filter_funs.h>
#include "../desc_include/trade_road.h"
#include "../desc_include/cove.h"

#pragma save_binary

inherit ELFROOM;

#define SOUTHEAST ENTRANCE_LOCATION
#define DOWNHILL  ROOMDIR + "cove_2"
#define WEST      SHOREDIR + "path_1"
#define COVEROOMS \
  ({  \
      ROOMDIR + "cove_2", \
      ROOMDIR + "cove_3", \
      ROOMDIR + "cove_4", \
      ROOMDIR + "cove_5", \
  })

#define SHORT  "At a small, sheltered cove"

#define LONG \
  "You are standing above a small, sheltered cove, cut into the soft limestone "+\
  "of the coast by the sea, wind and rain through millenia. Inside the cove "+\
  "are some small piers, protruding into the deep, green, tranquil water.\n"+\
  "An unpaved road goes down to the pier from the dark forest in the south, and "+\
  "a small path leads downhill.\n@@cove_desc@@"
  
create_room()
{
  set_short(SHORT);
  set_long(WRAP(LONG));

  COVE_STD_ITEMS;
  TRADE_ROAD_STD_ITEMS;
  add_exit(SOUTHEAST, "southeast", 0);
//  add_exit(DOWNHILL,  "downhill",  0);
//  add_exit(WEST, "west", 0);

  stock();
}

stock()
{
}

reset_room()
{
  stock();
}


string cove_desc() 
{
  string *roomfiles;
  object *inv, *live, *dead, room;
  int i;

  roomfiles = COVEROOMS;
  inv = ({});
  for (i = 0; i < sizeof(roomfiles); i++) {
    if ((room = find_object(roomfiles[i])) != 0)
      inv += all_inventory(room);
  }

  if (inv && sizeof(inv) > 0) {
    live = FILTER_LIVE(inv);
    dead = FILTER_DEAD(inv);
    if (sizeof(live) > 0 && sizeof(dead) > 0)
      return WRAP("Down in the cove you see " + 
		  COMPOSITE_LIVE(live) + ", as well as " +
		  COMPOSITE_DEAD(dead) + ".\n");
    else if (sizeof(live) > 0)
      return WRAP("Down in the cove you see " + 
		  COMPOSITE_LIVE(live) + ".\n");
    else if (sizeof(dead) > 0)
      return WRAP("Down in the cove you see " + 
		  COMPOSITE_DEAD(dead) + ".\n");
  }
  return WRAP("The cove seems empty at the moment.\n");
}
