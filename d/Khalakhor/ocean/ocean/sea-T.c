/*
 * sector T - Lucky Sea
 * Tapakah, 11/2021
 */

#pragma strict_types

#include "defs.h"

inherit SEA_SECTOR;

string
long_descr ()
{
  string descr =
    "You are sailing along the greenish waters of Farraige T'adh, " +
    "the Lucky Sea that surrounds the Oilean Adh, the Lucky Island. "+
    "You are trying to understand the reason for the hue of the "+
    "water, because it doesn't seem to be full of algae.\n";

  return descr;
}

string
get_continents ()
{
  return
    "You can see the the shores of the Lucky Island at some distance. " +
    "You will need to get closer to them to find a good spot for "+
    "a landfall.\n";
}

void
create_sea_room ()
{
  ::create_sea_sector("Farraige T'adh", NORMAL_DIFFICULTY);

  add_item(({"sea", "ocean", "water"}),
           "The waters of Farraige T'adh are of a greenish colour, "+
           "calm, but playful and deep, and your eyes fail to penetrate them "+
           "to any significant depths. You do feel a bit relaxed.\n");
}
