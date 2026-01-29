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
  set_short("In a forest clearing on a shore");

  set_long("You are on a small clearing on a sandy shore of the volcanic, "+
           "island of Carisca. Warm, damp forest starts immediately to "+
           "your east, climbing up the slopes of the famous Carisca "+
           "volcano. On the other sides you are surrounded by the calm "+
           "waters of the sea.\n");
  add_prop("_live_s_can_fish", "saltwater");

	add_item(({"sea" }),
           "The gentle waves are lapping at the pier.\n");

  add_exit("f6","east");
  add_row_exit(CARISCA_ENTRY, "west", no_go, 1);

  add_prop(ROOM_I_INSIDE, 0);
  add_prop(ROOM_I_TYPE, ROOM_NORMAL);

  // Set the sailing skill required to sail to this room.
  set_sailing_difficulty(NORMAL_DIFFICULTY);

  // Set the optional message when sailing into this room.
  set_sailing_fail_message("You feel uncomfortable departing the welcome "+
                           "shores of Carisca.\n");
  set_sailing_difficulty_message("You navigate across the calm " +
                                 " waters surrounding Carisca!\n");
}

