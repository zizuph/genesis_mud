/*
 * Sector g - around Galaith
 * Tapakah, 11/2021
 */

#pragma strict_types

#include "defs.h"

inherit ROOM_BASE;
inherit SEA_SECTOR;

string
long_descr ()
{
  mixed *distance_direction_point = get_distance_direction(Xx, Yy);
  string descr =
    "You are traversing the shallow waters adjacent to the shores of "+
    "the island of Galaith, somewhere to the west from the Khalakhor "+
    "mainland. The island has rocky shores is covered with vegetation "+
    "and has a beautiful tall tower protruding from its center. You are "+
    "currently " + direction[1] + " of the tower.";

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
                           "even the calm waters surrounding the "+
                           "Galaith Isle seem too dangerous.\n");
  set_sailing_difficulty_message("You navigate skillfully " +
                                 "along the coasts of Galaith Isle.\n");

  set_short("Around Galaith Isle");
  set_long(long_descr);

  add_item(({"sea", "ocean", "water"}),
           "The waters lap at the shores of Galaith. They don't "+
           "look particularly threatening or tumultous. Moving away will "+
           "enter you into Cuan Siorruidh, the ocean "+
           "washing the lands of the mainland of Khalakhor and the rest "+
           "of the islands. The mainland of Khalakhor is somewhere far "+
           "to the east.\n");
  add_item(({"continents","landmasses"}),
           "You can see the coasts of the Galaith Isle really near. " +
           "You just need to find a good landing spot. The island is "+
           "dominated by the magestic tower in its center, surrounded "+
           "by a forest. You see some exotic animals peeking out from "+
           "between the trees.\n");
  add_item(({"coast", "land"}),
           "You see the rocky coast of Galaith Isle, but you can't find a "+
           "comfortable spot for landing just yet.\n");

}
