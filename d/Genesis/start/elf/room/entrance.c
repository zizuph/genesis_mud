
#include "../stddefs.h"
#include "/sys/stdproperties.h"
#include "trade_road.h"

#pragma save_binary

inherit "/std/room";
inherit STRINGLIB;
inherit MISCLIB;

#define NORTH    ENTRANCE_LOCATION
#define SOUTH    ROOMDIR + "trade_road_1"

#define SHORT  "The entrance to Faerie"

#define LEAVE_LONG \
  "You are now leaving Faerie for the outer world, where nature no "+\
  "longer follows the whim of the elf lords, but obeys the laws of "+\
  "mechanics and magics. Behind you can see the road disappear beneath "+\
  "the majestic, dark firs.\n"

#define ENTER_LONG \
  "Before you a simple road, no more than a wagon track, disappears "+\
  "into the dark forest, beneath majestic, dark firs. Here starts the "+\
  "realm of Faerie, where nature, and even Time itself, obeys the whims " +\
  "of the "+\
  "elf lords, and Winter and Summer may be no further than a few steps "+\
  "from each other.\n"

#define LONG \
  "To the south a simple road, no more than a wagon track, disappears "+\
  "into the dark forest, beneath majestic, dark firs. Here is the "+\
  "border to the realm of Faerie, where nature, and even Time itself, obeys "+\
  "the whims of the elf lords, and Winter and Summer may be no further "+\
  "than a few steps from each other.\n"

#define WIZINFO \
  "This is the main entrance to the elf start area from the outer world. "+\
  "Please note that much of the behaviour of the rooms depend on which "+\
  "race_name the player has. If you want to see the area as an elf sees "+\
  "it, call set_race_name(\"elf\") in yourself.\n" +\
  "This particular room is different, and varies its description depending "+\
  "on whether you are entering or leaving the elf area.\n" 


create_room()
{
  set_short(SHORT);
  set_long(LONG);

  TRADE_ROAD_STD_ITEMS;
/*
  add_dir_phrase("long", NORTH, WRAP(ENTER_LONG));
  add_dir_phrase("long", SOUTH, WRAP(LEAVE_LONG));
  add_dir_phrase("long",     0, WRAP(      LONG));
*/
  STD_WIZINFO;

  add_exit(SOUTH, "south", 0);
  add_exit(NORTH, "north", 0);
}


wizinfo()
{
  return WRAP(WIZINFO);
}

enter_inv(object obj, object origin)
{
    /*
     * if (obj && interactive(obj))
     *   if (origin && file_name(origin) == NORTH)
     *     notify(MAINTAINER,
     *     capitalize(obj->query_real_name()) + " enters the elf area.");
     *
     *   else if (!origin || file_name(origin) != SOUTH)
     *     notify(MAINTAINER,
     *     capitalize(obj->query_real_name()) + " enters from " + 
     *     (origin ? file_name(origin) : "nowhere") + 
     *     ".");
     */ 
  return ::enter_inv(obj, origin);
}


leave_inv(object obj, object destination)
{
    /*
     * if (obj && interactive(obj))
     *   if (destination && file_name(destination) == NORTH)
     *     notify(MAINTAINER,
     *	     capitalize(obj->query_real_name()) + " leaves the elf area.");
     */
  return ::leave_inv(obj, destination);
}
