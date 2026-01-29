/*
 * Sector l - around the Leprechaun Island
 * Tapakah, 11/2021
 */

#pragma strict_types

#include "defs.h"

inherit SEA_SECTOR;

string
long_descr ()
{
  mixed *ddp = get_distance_direction(Xx, Yy);
  string descr =
    "You are sailing the strangely green coastal waters of the Lucky Island. "+
    "If you pull away, you'll return to Farraige T'adh, the Lucky Sea, "+
    "and further away is Cuan Siorruidh, the ocean surrounding most of "+
    "Khalakhor. There is a large monument in the middle of the island "+
    "resembling something similar to a tree, but not quite. That monument "+
    "is currently to your " + ddp[1] + ".";

  if (Yy < 5)
    descr += " You notice three villages on the island, surrounding the "+
      "monument.";
  descr += "\n";
  return descr;
}

string
short_descr ()
{
  string descr = "Near the Lucky Island ";
  
  if (Yy >= 5)
    descr += "next to the pier road";
  else
    descr += "next to the three villages";

  return descr;
}

string
get_continents ()
{
  return
    "You can see the ludicrously green shores of the Lucky Island in front " +
    "of you. Everything is covered in grass and bushes as far as you can "+
    "see.\n";
}

string
get_villages ()
{
  if (Yy >= 5)
    return "You cannot see any villages from here.\n";
  return "You see three villages, one with some stocky buildings, "+
    "one with some sinuous peculiar structures, and one that seems to "+
    "consists of green hat-like huts.\n";
}

void
create_sea_room ()
{
  ::create_sea_sector("Lucky Island coasts", NORMAL_DIFFICULTY);
  
  set_short(short_descr);

  add_item(({"sea", "ocean", "water"}),
           "The sea gets its greenish hue from the immensely green shores "+
           "of the Lucky Island. The waters are calm, but safely deep enough. "+
           "Moving away from the shore will lead you into "+
           "Farraigh T'adh, and beyond it lies Cuan Siorruidh, the ocean "+
           "washing the lands of the mainland of Khalakhor and the rest "+
           "of the islands.\n");
  add_item(({"village", "villages" }), get_villages);
  add_item(({"coast", "land"}),
           "You see the coast overgrown with grasses and bushes, and not "+
           "really fit for a landing anywhere nearby.\n");
}
