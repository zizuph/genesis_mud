/*
 * Sector n - around the North Speir
 * Tapakah, 11/2021
 */

#pragma strict_types

#include "defs.h"

inherit SEA_SECTOR;

string
long_descr ()
{
  string descr =
    "You are sailing along the dark patch of water along the shore of the "+
    "northern speir of Khalakhor. Moving away will take you back to the "+
    "Farraigh Scanthe, the Cracked Sea, and then to the Cuan Siorruidh, "+
    "the ocean surrounding the lands of Khalakhor.";
  string extra = "";
  if (Yy <= 5)
    extra = "You see the tall reddish spires of the volcanoes "+
      "interrupting the grayish spans of the northern wastelands. Some are "+
      "spewing smoke. The jagged rocks prevent any possibility of landing.\n";
  else if (Xx <= 20)
    extra = "You see low hills covered with sparse vegetation and a few "+
      "villages and camps spread out on them. There are some eddies going "+
      "next to the shore, preventing you from making a landfall.\n";
  else
    extra = "You see a flat shoreline, covered with shrubs and struggling "+
      "grasses, such as a typical tundra landscape. The sea seems too shallow "+
      "to allow a landfall.\n";
  descr = descr + extra + "\n";
  return descr;
}

string
get_continents ()
{
  return
    "You can see the the shores of the northern speir of Khalakhor "+
    "next to you. Most of the shore is not really approachable "+
    "but you should keep looking for a landing spot.\n";
}

int
get_difficulty ()
{
  if (Yy > 5) 
    return TRICKY_DIFFICULTY;
  return Yy == 1 ? HIGH_SEAS_DIFFICULTY : ROUGH_SEAS_DIFFICULTY;
}

void
create_sea_room ()
{
  ::create_sea_sector("northern shores of Khalakhor", -1);
  add_item(({"sea", "ocean", "water"}),
           "This strip of water is very dark, almost midnight-black, "+
           "you cannot see through it almost at all, but you have to "+
           "watch out for the eddies and the eruptions around you.\n");
  if (Yy <= 5) {
    set_short("At northern Khalakhor shore near the wastelands");
    add_item(({"volcanoes", "wastelands", "spires", "smoke"}),
             "The land seems to be cursed. Cracks in the snowed land filled"+
             "with lava, and huge rocks are everywhere. You seem to hear "+
             "explosions from the volcanoes followed by avalanches.\n");
  }
  else if (Xx <= 20) {
    set_short("At the western shore of the northern speir of Khalakhor");
    add_item(({"hills", "vegetations", "villages", "camps"}),
             "The hills are covered in low trees and brown grasses. Small "+
             "houses clumped together form random villages with twisty "+
             "roads between them. From the villages towards the Nexus of "+
             "Khalakhor a chain of military camps has been set.\n");
  }
  else {
    set_short("At the eastern shore of the northern speir of Khalakhor");
    add_item(({"tundra", "shrubs", "grasses"}),
             "Snow covered plains are set with various shrubs, small moors "+
             "and struggling grasses. You see some furry shapes darting "+
             "between the shrubs.\n");
  }
}
