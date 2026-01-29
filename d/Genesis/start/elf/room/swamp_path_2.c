#include "../stddefs.h"
#include "/sys/stdproperties.h"
#include "swamp_path.h"

#pragma save_binary

inherit ELFROOM;

#define NORTHWEST ROOMDIR + "swamp_path_1"
#define SOUTH     ROOMDIR + "swamp_path_3"

#define LONG \
  "The path goes roughly northwest and south from here. It is a bit hard to "+\
  "pinpoint the exact direction, as it is far from following a straight line.\n"

create_room()
{
  set_short(N_KNOW(SWAMP_PATH_NAT_SHORT, SWAMP_PATH_FOR_SHORT));
  set_long( N_KNOW(WRAP(SWAMP_PATH_NAT_LONG + LONG),
		   WRAP(SWAMP_PATH_FOR_LONG + LONG)));

  SWAMP_PATH_STD_ITEMS;

  add_exit(SOUTH,     "south",     0);
  add_exit(NORTHWEST, "northwest", 0);
}
