/*
 * Sector c - around Nyreese
 * Tapakah, 10/2021
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
    "the island of Nyreese, southeast of the Khalakhor mainland. ";

  if (Yy >= 25)
    descr +=
      "Cadu, the capital city of Nyreese, dominates the view. You can see "+
      "the famous Cadu castle looming over the center of the town. You also "+
      "catch a glimpse over the famous Cadu casino.";
  else if (Xx >= 5)
    descr +=
      "This part of the shore is characterized by a thick forest, giving "+
      "way in the north to the mountains climbing higher and higher as "+
      "they form the northeastern point of Nyreese. You notice ruins "+
      "of an old monastery in those mountains.";
  else {
    descr +=
      "The western and the northwestern shores of Nyreese are characterised "+
      "by jagged rocks obstructing any access to the coast and a thick forest "+
      "of pines, oaks, and birches. It seems to you like there is a strange "+
      "shimmering in the middle of the forest.";
  }
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
                           "Nyreese seem to dangerous.\n");
  set_sailing_difficulty_message("You navigate skillfully " +
                                 "along the coasts of Nyreese.\n");

  set_short("Around Nyreese");
  set_long(long_descr);

  add_item(({"sea", "ocean", "water"}),
           "The waters lap at the shores of Nyreese. They don't "+
           "look particularly threatening or tumultous. Moving away will "+
           "enter you into Okiyan, the smaller ocean surrounding Nyreese "+
           "and Carisca. Far beyond it lays Cuan Siorruidh, the ocean "+
           "washing the lands of the mainland of Khalakhor and the rest "+
           "of the islands.\n");
  add_item(({"continents","landmasses"}),
           "You can see the coasts of Nyreese really near. " +
           "You just need to find a good landing spot.\n");
  add_item(({"coast", "land"}),
           "You see the coast of Nyreese, but you can't find a "+
           "comfortable spot for landing just yet.\n");

}
