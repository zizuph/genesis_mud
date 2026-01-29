/*
 * Sector F -  Farraige Tradalah, from the Nexus to the west 
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
    "You are sailing along the lapis lazuli waters of Farraige Tradalah, " +
    "the Trade Sea which stretches west from the Nexus part of Khalakhor.\n";

  mixed *ddp;
  
  if (TP->query_skill(SS_LOC_SENSE) > 30) {
    if (Yy >= 12)
      descr +=
        "You realize you should be somewhere between the southwestern spier "+
        "and the Isle of Galaith.\n";
    else
      descr +=
        "You are quite close to the Nexus.\n";
  }
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
                           "the waters of Farraige Tradalah turn out to be "+
                           "too tough.\n");
  set_sailing_difficulty_message("You navigate skillfully " +
                                 "through Farraige Tradalah.\n");

  set_short("Through Farraige Tradalah");
  set_long(long_descr);

  add_item(({"sea", "ocean", "water"}),
           "The waters of Farraige Tradalah are of a deep lapis lazuli "+
           "colour, and quite deep, and your eyes fail to penetrate them "+
           "to any significant depths. However you notice small local "+
           "currents and eddies that keep you quite awake.\n");
  add_item(({"continents","landmasses"}),
           "You can see the western coasts of halakhor at some distance. " +
           "You will need to get closer to them to find a good spot for "+
           "a landfall.\n");

}
