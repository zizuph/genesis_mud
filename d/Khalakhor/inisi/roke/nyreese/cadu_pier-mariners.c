#pragma strict_types

#include <stdproperties.h>

#include "/d/Khalakhor/ocean/defs.h"

inherit "/std/room";
inherit "/d/Khalakhor/ocean/lib";



/* This next function is essential when it comes to removing the drown 
   object. Imagine if one leaves a standard water room into an area with
   non-standard underwater rooms.. the drown object will stay, but it will
   not get removed if they then go to an ordinary room. */
int
query_standard_water_room ()
{
  return 0; 
}

void
create_room ()
{
  set_short("On the new pier");

  set_long("You are standing on the new extension to the Cadu pier, "+
           "built to accommodate the ships of the Mariners of Genesis. "+
           "The main part of the pier is to your north, extending then "+
           "all the way to the west, where it enters the town of Cadu.\n");
  add_prop("_live_s_can_fish", "saltwater");

	add_item(({"sea" }),
           "The gentle waves are lapping at the pier.\n");

  add_exit("cadu_pier_5","north");
  add_row_exit(CADU_ENTRY, "east", no_go, 1);

  add_prop(ROOM_I_INSIDE, 0);
  add_prop(ROOM_I_TYPE, ROOM_NORMAL);

  // Set the sailing skill required to sail to this room.
  set_sailing_difficulty(NORMAL_DIFFICULTY);

  // Set the optional message when sailing into this room.
  set_sailing_fail_message("You feel uncomfortable departing the welcome "+
                           "piers of Cadu.\n");
  set_sailing_difficulty_message("You navigate across the calm " +
                                 " waters surrounding Cadu!\n");
}

