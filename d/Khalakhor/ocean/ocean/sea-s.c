#pragma strict_types

#include "defs.h"

inherit SEA_SECTOR;

string
long_descr ()
{
  string descr =
    "You are sailing along the midnight-black waters of Farraige Scanthe, " +
    "the Cracked Sea that wash the desolate shores of Khalakhor's northern "+
    "speir. It's called cracked for a reason - there are water eruptions "+
    "and eddies all around you, as if the sea-bed is cracking under "+
    "a pressure.";
  string extra = "";
  if (Yy <= 5)
    extra = "You see the tall reddish spires of the volcanoes "+
      "interrupting the grayish spans of the northern wastelands. Some are "+
      "spewing smoke.\n";
  else if (Xx <= 20)
    extra = "You see low hills covered with sparse vegetation and a few "+
      "villages and camps spread out on them.\n";
  else
    extra = "You see a flat shoreline, covered with shrubs and struggling "+
      "grasses, such as a typical tundra landscape.\n";
  descr = descr + extra + "\n";
  return descr;
}

string
get_continents ()
{
  return
    "You can see the the shores of the northern Khalakhor in the "+
    "distance, but you'll need to get closer to find a landing "+
    "spot.\n";
}

int
get_difficulty ()
{
  return Yy == 0
    ? HIGH_SEAS_DIFFICULTY
    : ROUGH_SEAS_DIFFICULTY;
}

void
create_sea_room ()
{
  ::create_sea_sector("Farraige Scanthe", -1);
  
  add_item(({"sea", "ocean", "water"}),
           "The waters of Farraige Scanthe are of a midnight-black colour, "+
           "unstable, swirling and letting out strange eruptions, they "+
           "seem to justify its name of Cracked Sea. You are as vigilant "+
           "as you ever could be.\n");
  if (Yy <= 5) {
    set_short("Through Farraige Scanthe near the wastelands");
    add_item(({"volcanoes", "wastelands", "spires", "smoke"}),
             "From such a distance that place looks rather desolate.\n");
  }
  else if (Xx <= 20) {
    set_short("Through Farraige Scanthe near the western shore of "+
              "the northern speir");
    add_item(({"hills", "vegetations", "villages", "camps"}),
             "You are too far away to notice any particular details.\n");
  }
  else {
    set_short("Through Farraige Scanthe near the eastern shore of "+
               "the northern speir");
    add_item(({"tundra", "shrubs", "grasses"}),
             "You are too far away to notice any particular details.\n");
  }
}
