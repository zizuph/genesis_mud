/*
 * Sector g - around Galaith
 * Tapakah, 11/2021
 */

#pragma strict_types

#include "defs.h"

inherit SEA_SECTOR;

string
long_descr ()
{
  mixed *direction = get_distance_direction(Xx, Yy);
  string descr =
    "You are traversing the shallow waters adjacent to the shores of "+
    "the island of Galaith, somewhere to the west from the Khalakhor "+
    "mainland. The island has rocky shores is covered with vegetation "+
    "and has a beautiful tall tower protruding from its center. The tower "+
    "is currently to your " + direction[1] + ".";

  descr += "\n";
  return descr;
}

string
get_continents ()
{
  return
    "You can see the coasts of the Galaith Isle really near. " +
    "You just need to find a good landing spot. The island is "+
    "dominated by the magestic tower in its center, surrounded "+
    "by a forest. You see some exotic animals peeking out from "+
    "between the trees.\n";
}

void
create_sea_room ()
{
  ::create_sea_sector("Galaith Isle shores", NORMAL_DIFFICULTY);
  
  add_item(({"sea", "ocean", "water"}),
           "The waters lap at the shores of Galaith. They don't "+
           "look particularly threatening or tumultous. Moving away will "+
           "enter you into Cuan Siorruidh, the ocean "+
           "washing the lands of the mainland of Khalakhor and the rest "+
           "of the islands. The mainland of Khalakhor is somewhere far "+
           "to the east.\n");
  add_item(({"coast", "land"}),
           "You see the rocky coast of Galaith Isle, but you can't find a "+
           "comfortable spot for landing just yet.\n");

}
