/*
 * Sector b - around Baile Ashlagh
 * Tapakah, 10/2021
 */

#pragma strict_types

#include "defs.h"

inherit SEA_SECTOR;

string
long_descr ()
{
  string descr =
    "You are traversing the shallow waters adjacent to the shores of "+
    "the island of Baile Ashlagh, south of the Khalakhor mainland. ";

  if (Xx >= 29)
    descr +=
      "This part of the island is a long snake ending in a zone that might "+
      "be good enough to make a landfall.";
  else if (Xx >= 27)
    descr +=
      "The island widens here somewhat, and you can see a village surrounded "+
      "by a stockade, without a place suitable for a landing anywhere.";
  else {
    descr +=
      "You are next to the western part of the island which is covered by "+
      "a thick forest. You catch yourself wondering if you just saw a "+
      "goblin peeking out from the trees.";
  }
  descr += "\n";
  return descr;
}

string
get_continents ()
{
  return
    "You can see the coasts of Baile Ashlagh really near. " +
    "You just need to find a good landing spot.\n";
}

void
create_sea_room ()
{
  ::create_sea_sector("Baile Ashlagh shores", NORMAL_DIFFICULTY);
  
  add_item(({"sea", "ocean", "water"}),
           "The waters lap at the shores of Baile Ashlagh. They don't "+
           "look particularly threatening or tumultous. Moving away will "+
           "enter you into Lear Eahdomhain, the Shallow Sea, that lies "+
           "between Baile Ashlagh and Cuan Siorruidh.\n");

  add_item(({"coast", "land"}),
           "You see the coast of Baile Ashlagh, but you can't find a "+
           "comfortable spot for landing just yet.\n");

}
