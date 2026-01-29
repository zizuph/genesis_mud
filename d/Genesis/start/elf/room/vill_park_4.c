#include "../stddefs.h"
#include "/sys/stdproperties.h"
#include "vill_park.h"

#pragma save_binary

inherit ELFROOM;

#define NORTHWEST    ROOMDIR + "vill_park_3"
#define SOUTHEAST    ROOMDIR + "vill_road_7"

#define NAT_LONG \
  "Here a small path winds its way " + \
  "beneath the oaks. To the northwest it leads to the center of the " + \
  "park, while it leads out of the park to the southeast.\n"
#define FOR_LONG \
  "Here a small path winds its way " + \
  "beneath the oaks. To the northwest it leads further into the " + \
  "park, while it leads out of the park to the southeast.\n"

create_room()
{
  set_short(N_KNOW(VILL_PARK_NAT_SHORT, VILL_PARK_FOR_SHORT));
  set_long( N_KNOW(WRAP(VILL_PARK_NAT_LONG + NAT_LONG),
		   WRAP(VILL_PARK_FOR_LONG + FOR_LONG)));

  VILL_PARK_STD_ITEMS;
  HOUSE_FAR_STD_ITEM;

  add_exit(NORTHWEST, "northwest", 0);
  add_exit(SOUTHEAST, "southeast", 0);
}
