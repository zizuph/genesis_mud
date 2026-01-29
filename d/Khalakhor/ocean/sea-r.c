/*
 * Sector r - around Carisca
 * Tapakah, 11/2021
 */

#pragma strict_types

#include "defs.h"

inherit ROOM_BASE;
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

void
create_sea_room ()
{
  ::create_sea_room();
  ::create_sea_sector();
  
  // Set the sailing skill required to sail to this room.
  set_sailing_difficulty(NORMAL_DIFFICULTY);

  // Set the optional message when sailing into this room.
  set_sailing_fail_message("For such an unskilled sailor as you are, "+
                           "even the calm, shallow waters surrounding "+
                           "Carisca seem too dangerous.\n");
  set_sailing_difficulty_message("You navigate skillfully " +
                                 "along the coasts of Carisca.\n");

  set_short("Around Carisca");
  set_long(long_descr);

  add_item(({"sea", "ocean", "water"}),
           "The waters lap at the shores of Carisca. They don't "+
           "look particularly threatening or tumultous. Moving away will "+
           "enter you into Okiyan, the smaller ocean surrounding Carisca "+
           "and Carisca. Far beyond it lays Cuan Siorruidh, the ocean "+
           "washing the lands of the mainland of Khalakhor and the rest "+
           "of the islands.\n");
  add_item(({"continents","landmasses"}),
           "You can see the coasts of Carisca really near. " +
           "You just need to find a good landing spot. The island is "+
           "dominated by the volcano in the center, its lower slopes "+
           "covered with a warm, damp forest. You notice strange huge "+
           "centipedes crawling around the forest and the volcano.\n");
  add_item(({"coast", "land"}),
           "You see the coast of Carisca, but you can't find a "+
           "comfortable spot for landing just yet.\n");

}
