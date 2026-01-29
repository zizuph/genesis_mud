/*
 * Standard pier of Khalakhor
 */

#pragma no_clone
#pragma strict_types

#include <stdproperties.h>

#include "defs.h"

inherit "/d/Khalakhor/ocean/lib";

int
query_standard_water_room ()
{
  return 0; 
}

void
create_pier (string location)
{
  set_short(sprintf("On the Mariners pier of %s", location));
	add_item(({ "sea" }),
           "The waves are lapping at the pier.\n");

  add_prop(ROOM_I_INSIDE, 0);
  add_prop(ROOM_I_TYPE, ROOM_NORMAL);
  add_prop("_live_s_can_fish", "saltwater");

  set_sailing_difficulty(NORMAL_DIFFICULTY);
  set_sailing_fail_message(sprintf("You feel uncomfortable departing the welcome "+
                                   "piers of %s.\n", location));
  set_sailing_difficulty_message(sprintf("You navigate across the " +
                                         "waters surrounding %s!\n", location));
}
