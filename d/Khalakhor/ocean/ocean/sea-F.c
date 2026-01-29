/*
 * Sector F -  Farraige Tradalah, from the Nexus to the west 
 * Tapakah, 10-11/2021
 */

#pragma strict_types

#include <ss_types.h>
#include "defs.h"

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

string
get_continents ()
{
  return
    "You can see the western coasts of Khalakhor at some distance. " +
    "You will need to get closer to them to find a good spot for "+
    "a landfall.\n";
}

void
create_sea_room ()
{
  ::create_sea_sector("Farraige Tradalah", TRICKY_DIFFICULTY);
  
  add_item(({"sea", "ocean", "water"}),
           "The waters of Farraige Tradalah are of a deep lapis lazuli "+
           "colour, and quite deep, and your eyes fail to penetrate them "+
           "to any significant depths. However you notice small local "+
           "currents and eddies that keep you quite awake.\n");
}
