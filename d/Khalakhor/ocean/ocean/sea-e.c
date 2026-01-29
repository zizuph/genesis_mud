/*
 * Sector e - around Port Macdunn/Tabor Sogh and SW speir
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
    "You are sailing the blue-green stretch between the shore of the "+
    "southeastern speir and the actual waters of Lear Min. The shore "+
    "is rocky, not particularly suitable for a landing, and the waves "+
    "are keeping you vigilant albeit not worried. ";
  if (ddp[0] <= 4.0 && ddp[2] == "Southeastern Speir of Khalakhor")
    descr += "You can see some contours of a village past the immediate "+
      "shore.";
  else if (ddp[0] <= 4.0 && ddp[2] == "Nexus of Khalakhor")
    descr += "You can see some tall mountains far in the east.";
  else if (Xx <= 24)
    descr += "Past the rocky shore you can see a dark conifer forest and "+
      "some mountains.";
  else
    descr += "Past the rocky shore you see steppe-like plains and occasional "+
      "groves.";
  descr += "\n";
  return descr;
}

string
short_descr ()
{
  string descr = "Near southeastern speir, ";
  
  if (Yy < 18 && Xx > 24)
    descr += "not far from the Khalakhor Nexus area";
  else if (Yy < 18 && Xx < 24)
    descr += "at the inner part of the shore";
  else if (Xx < 27)
    descr += "next to the village of Port Macdunn";
  else
    descr += "the speir's eastern coast";

  return descr;
}

string
get_continents ()
{
  string extra;
  
  if (Yy < 18 && Xx > 24)
    extra = "You see long stretches of plains with occasional groves of "+
      "trees as far as the eye can see. A couple of military camps seem "+
      "to have been set between the groves.\n";
  else if (Yy < 18 && Xx < 24)
    extra = "You see long stretches of plains with a dark-green forest "+
      "beyond it, and a mountain ridge coming from behind the forest "+
      "very close to the shore. There is a military camp locked between "+
      "the shore and the mountains.\n";
  else if (Xx < 27)
    extra = "You can see a large village surrounded by an earthen "+
      "embankment, and a large pier south of it.";
  else
    extra = "You can see a friendly-looking village near the coast.";
  return
    "You can see the coasts of the the southeastern speir really near. " +
    "You just need to find a good landing spot, although there are "+
    "plenty of jagged rocks along the shore, making the landing a "+
    "tougher task than it originally seemed. " + extra + "\n";
}

void
create_sea_room ()
{
  ::create_sea_sector("coasts of southeastern speir", TRICKY_DIFFICULTY);
  
  set_short(short_descr);
  add_item(({"sea", "ocean", "water"}),
           "The waters roll over the rocky shore of the southeastern speir. "+
           "They do not seem very threatening, but the ship keeps rocking from "+
           "left to right slightly all the time, making you stay vigilant "+
           "watching the sea. Moving away from the shore will lead you into "+
           "Lear Min, and beyond it lies Cuan Siorruidh, the ocean "+
           "washing the lands of the mainland of Khalakhor and the rest "+
           "of the islands.\n");
           
  add_item(({"coast", "land"}),
           "You see the rocky coast of the southeastern speir, and it doesn't "+
           "seem fit for a landing anywhere nearby.\n");
}
