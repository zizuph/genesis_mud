#pragma strict_types

#include <ss_types.h>
#include "defs.h"

inherit ROOM_BASE;
inherit SEA_SECTOR;

string
long_descr ()
{
  string descr =
    "You are sailing along the greenish waters of Farraige T'adh, " +
    "the Lucky Sea that surrounds the Oilean Adh, the Lucky Island. "+
    "You are trying to understand the reason for the hue of the "+
    "water, because it doesn't seem to be full of algae.\n";

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
  set_sailing_fail_message("For an unskilled sailor as you are, even"+
                           "the waters of Farraige T'adh turn out to be "+
                           "too tough.\n");
  set_sailing_difficulty_message("You navigate skillfully " +
                                 "through Farraige T'adh.\n");

  set_short("Through Farraige T'adh");
  set_long(long_descr);

  add_item(({"sea", "ocean", "water"}),
           "The waters of Farraige T'adh are of a greenish colour, "+
           "calm, but playful and deep, and your eyes fail to penetrate them "+
           "to any significant depths. You do feel a bit relaxed.\n");
  add_item(({"continents","landmasses"}),
           "You can see the the shores of the Lucky Island at some distance. " +
           "You will need to get closer to them to find a good spot for "+
           "a landfall.\n");

}
