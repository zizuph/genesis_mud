#include "../stddefs.h"
#include "/sys/stdproperties.h"
#include "swamp_path.h"

#pragma save_binary

inherit ELFROOM;

#define EAST  ROOMDIR + "swamp_1"
#define NORTH ROOMDIR + "swamp_path_2"

#define LONG \
  "The path goes roughly east and north from here. It is a bit hard to "+\
  "pinpoint the exact direction, as it is far from following a straight line.\n"

create_room()
{
  set_short(N_KNOW(SWAMP_PATH_NAT_SHORT, SWAMP_PATH_FOR_SHORT));
  set_long( N_KNOW(WRAP(SWAMP_PATH_NAT_LONG + LONG),
		   WRAP(SWAMP_PATH_FOR_LONG + LONG)));

  SWAMP_PATH_STD_ITEMS;

  add_exit(NORTH, "north", 0);
  add_exit(EAST,  "east",  0);
}
