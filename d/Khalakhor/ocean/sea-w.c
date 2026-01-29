/*
 * Sector w - around Sa Morgan and SW speir
 * Tapakah, 11/2021
 */

#pragma strict_types

#include "defs.h"

inherit ROOM_BASE;
inherit SEA_SECTOR;

string
long_descr ()
{
  mixed *ddp = get_distance_direction(Xx, Yy);
  string descr =
    "You are sailing the blue-green stretch between the shore of the "+
    "southwestern speir and the actual waters of Miath Rae. The shore "+
    "is rocky, not particularly suitable for a landing, and the waves "+
    "are keeping you vigilant albeit not worried. ";
  if (ddp[0] <= 4.0 && ddp[2] == "Southwestern Speir of Khalakhor")
    descr += "You can see some contours of a village past the immediate "+
      "shore.";
  else if (ddp[0] <= 4.0 && ddp[2] == "Nexus of Khalakhor")
    descr += "You can see some tall mountains far in the east.";
  else if (Xx <= 13)
    descr += "past the rocky shore you can see a broadleaf forest.";
  else
    descr += "past the rocky shore you see verdant plains and occasional "+
      "groves.";
  descr += "\n";
  //  descr += implode(({Xx, Yy, Zz}), ",") + "\n";
  return descr;
}

string
short_descr ()
{
  string descr = "Near southwestern speir, ";
  
  if (Yy >= 19)
    descr += "next to the village of Sa Morgan.";
  else if (Yy <= 14)
    descr += "not far from the Khalakhor Nexus area.";
  else if (Xx <= 13)
    descr += "at the continent's westmost stretch.";
  else
    descr += "the speir's eastern coast.";

  return descr;
}

string
get_continents ()
{
  string extra = Yy >= 19
    ? "You can see a friendly-looking village near the coast."
    : "";
  return
    "You can see the coasts of the the southwestern speir really near. " +
    "You just need to find a good landing spot, although there are "+
    "plenty of jagged rocks along the shore, making the landing a "+
    "tougher task than it originally seemed. " + extra + "\n";
}

void
create_sea_room ()
{
  ::create_sea_room();
  ::create_sea_sector();
  
  // Set the sailing skill required to sail to this room.
  set_sailing_difficulty(TRICKY_DIFFICULTY);

  // Set the optional message when sailing into this room.
  set_sailing_fail_message("For an unskilled sailor as you are, "+
                           "the playful waves lapping at the  "+
                           "southwestern speir seem too dangerous.\n");
  set_sailing_difficulty_message("You navigate skillfully " +
                                 "along the coasts of the southwestern speir.\n");

  set_short(short_descr);
  set_long(long_descr);

  add_item(({"sea", "ocean", "water"}),
           "The waters roll over the rocky shore of the southwestern speir. "+
           "They do not seem very threatening, but the ship keeps rocking from "+
           "left to right slightly all the time, making you stay vigilant "+
           "watching the sea. Moving away from the shore will lead you into "+
           "Miath Rae, and beyond it lies Cuan Siorruidh, the ocean "+
           "washing the lands of the mainland of Khalakhor and the rest "+
           "of the islands.\n");
  add_item(({"continents","landmasses"}), get_continents);
           
  add_item(({"coast", "land"}),
           "You see the rocky coast of the southwestern speir, and it doesn't "+
           "seem fit for a landing anywhere nearby.\n");
}
