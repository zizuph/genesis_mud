#include "../stddefs.h"
#include "/sys/stdproperties.h"
#include "vill_park.h"

#pragma save_binary

inherit ELFROOM;

#define NORTHEAST    ROOMDIR + "vill_park_2"
#define NORTHWEST    ROOMDIR + "vill_park_1"
#define SOUTHEAST    ROOMDIR + "vill_park_4"
#define SOUTHWEST    ROOMDIR + "vill_park_5"
#define INTO         ROOMDIR + "vill_medit"

#define NAT_LONG \
  "You are standing in the center of the oak park, right at the white " + \
  "marble House of Meditation. From here, four paths leave in different " + \
  "directions, all leading out of the park.\n" 
#define FOR_LONG \
  "You are standing somewhere inside the park, right at a marble " + \
  "building that looks like a temple. In four different directions " + \
  "small paths disappear among the oaks and bushes.\n"

create_room()
{
  set_short(N_KNOW(VILL_PARK_NAT_SHORT, VILL_PARK_FOR_SHORT));
  set_long( N_KNOW(WRAP(NAT_LONG),
		   WRAP(FOR_LONG)));

  VILL_PARK_STD_ITEMS;

  add_exit(NORTHWEST, "northwest", 0);
  add_exit(NORTHEAST, "northeast", 0);
  add_exit(SOUTHWEST, "southwest", 0);
  add_exit(SOUTHEAST, "southeast", 0);
}


init()
{
  ::init();
  
  add_action("do_enter", "enter");
  add_action("do_enter", "go into");
}


do_enter(arg)
{
  if (arg && member_array(arg, HOUSE_ITEM) >= 0) {
    this_player()->move_living("into the house", INTO);
    return 1;
  }

  notify_fail(query_verb() + " what?\n");
}
