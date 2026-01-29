/*
 * Sector M -  Miath Rae, sea around SW speir 
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
    "You are sailing along the blue-green waters of Miath Rae, " +
    "which surrounds the southwestern speir of the Khalakhor mainland.\n";

  mixed *ddp;
  
  if (TP->query_skill(SS_LOC_SENSE) > 30) {
    ddp = get_distance_direction(Xx, Yy, "Sa Morgan");
    descr += "You guess the village of Sa Morgan is somewhere to your " + ddp[1] +
      ".\n";
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
                           "the waters of Miath Rae turn out to be "+
                           "too tough.\n");
  set_sailing_difficulty_message("You navigate skillfully " +
                                 "through Miath Rae.\n");

  set_short("Through Miath Rae " + Xx + "," + Yy + "," + Zz);
  set_long(long_descr);

  add_item(({"sea", "ocean", "water"}),
           "The waters of Miath Rae shine in the bright turquoise. "+
           "White sheep-like clusters of foam merrily ride the smooth "+
           "waves, making the ship rock gently sideways, without making "+
           "you feel threatened.\n");
  add_item(({"continents","landmasses"}),
           "You can see the coasts of the southwestern speir of "+
           "Khalakhor at some distance. " +
           "You will need to get closer to them to find a good spot for "+
           "a landfall.\n");

}
