/*
 * Sector D -  Lear Dorcha, from the Nexus to the east 
 * Tapakah, 10-11/2021
 */

#pragma strict_types

#include <ss_types.h>
#include "defs.h"

inherit ROOM_BASE;
inherit SEA_SECTOR;

string
long_descr ()
{
  string descr =
    "You are sailing along the cobalt-blue waters of Lear Dorcha, " +
    "the Darkened Sea which stretches east from the Nexus part of Khalakhor.\n";

  return descr;
}

void
create_sea_room ()
{
  ::create_sea_room();
  ::create_sea_sector();
  
  // Set the sailing skill required to sail to this room.
  set_sailing_difficulty(TRICKY_DIFFICULTY);

  // Set the optional message when sailing into this room.
  set_sailing_fail_message("For a lesser skilled sailor as you are, "+
                           "the waters of Lear Dorcha turn out to be "+
                           "too tough.\n");
  set_sailing_difficulty_message("You navigate skillfully " +
                                 "through Lear Dorcha.\n");

  set_short("Through Lear Dorcha");
  set_long(long_descr);

  add_item(({"sea", "ocean", "water"}),
           "The waters of Lear Dorcha are of a deep cobalt-blue "+
           "colour, and quite deep, and your eyes fail to penetrate them "+
           "to any significant depths. However you notice small local "+
           "currents and eddies that keep you quite awake.\n");
  add_item(({"continents","landmasses"}),
           "You can see the western coasts of halakhor at some distance. " +
           "You will need to get closer to them to find a good spot for "+
           "a landfall.\n");

}
