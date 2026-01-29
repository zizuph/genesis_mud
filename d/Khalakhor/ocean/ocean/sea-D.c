/*
 * Sector D -  Lear Dorcha, from the Nexus to the east 
 * Tapakah, 10-11/2021
 */

#pragma strict_types

#include "defs.h"

inherit SEA_SECTOR;

string
long_descr ()
{
  string landscape = Yy > 15 ? "grassy plains" : Yy > 11 ? "steppe" : "tundra";
  
  string descr =
    "You are sailing along the cobalt-blue waters of Lear Dorcha, " +
    "the Darkened Sea, which stretches east from the Nexus part of Khalakhor. "+
    "To your far west you seecan make out some " + landscape + ", whereas if "+
    "you turn east you will eventually reach Cuan Siorruidh, the great ocean "+
    "surrounding Khalakhor.\n";
  
  return descr;
}

string
get_continents ()
{
  return
    "You can see the western coasts of Khalakhor at some distance. "+
    "You will need to get closer to them to find a good spot for "+
    "a landfall.\n";
}

void
create_sea_room ()
{
  ::create_sea_sector("Lear Dorcha", TRICKY_DIFFICULTY);
  
  add_item(({"sea", "ocean", "water"}),
           "The waters of Lear Dorcha are of a deep cobalt-blue "+
           "colour, and quite deep, and your eyes fail to penetrate them "+
           "to any significant depths. However you notice small local "+
           "currents and eddies that keep you quite awake.\n");
}
