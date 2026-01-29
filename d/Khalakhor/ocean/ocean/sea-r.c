/*
 * Sector r - around Carisca
 * Tapakah, 11/2021
 */

#pragma strict_types

#include "defs.h"

inherit SEA_SECTOR;

string
long_descr ()
{
  string descr =
    "You are traversing the shallow waters adjacent to the shores of "+
    "the island of Carisca, in the extreme southwest of the lands of "+
    "Khalakhor. The shores are covered by a thick, warm, dump forest "+
    "climbing up the slopes of the volcano in the center of the island.";

  descr += "\n";
  return descr;
}

string
get_continents ()
{
  return "You can see the coasts of Carisca really near. " +
    "You just need to find a good landing spot. The island is "+
    "dominated by the volcano in the center, its lower slopes "+
    "covered with a warm, damp forest. You notice strange huge "+
    "centipedes crawling around the forest and the volcano.\n";
}

void
create_sea_room ()
{
  ::create_sea_sector("Carisca coast", NORMAL_DIFFICULTY);
  
  add_item(({"sea", "ocean", "water"}),
           "The waters lap at the shores of Carisca. They don't "+
           "look particularly threatening or tumultous. Moving away will "+
           "enter you into Okiyan, the smaller ocean surrounding Carisca "+
           "and Carisca. Far beyond it lays Cuan Siorruidh, the ocean "+
           "washing the lands of the mainland of Khalakhor and the rest "+
           "of the islands.\n");
  add_item(({"coast", "land"}),
           "You see the coast of Carisca, but you can't find a "+
           "comfortable spot for landing just yet.\n");
  add_item(({"volcano"}),
           "A medium-sized active volcano dominates the island. You see "+
           "strange centipede-like creatures hurrying up and down its "+
           "slopes, occaionally fighting the boars at the ground level. "+
           "They seem to disregard the hot lava.\n");

}
