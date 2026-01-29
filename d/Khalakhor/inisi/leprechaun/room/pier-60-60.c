#pragma strict_types

#include <stdproperties.h>

#include "/d/Khalakhor/ocean/defs.h"

inherit "/std/room";
inherit "/d/Khalakhor/ocean/lib";



/* This next function is essential when it comes to removing the drown 
   object. Imagine if one leaves a standard water room into an area with
   non-standard underwater rooms.. the drown object will stay, but it will
   not get removed if they then go to an ordinary room. */
int
query_standard_water_room ()
{
  return 0; 
}

int
block_gss ()
{
  TP->catch_msg("A yellow metallic boom saying 'Genesis ShipLines' blocks "+
                "your way.\n");
  return 1;
}

int
block_lucky ()
{
  TP->catch_msg("You step onto the path leading into the west, but then three "+
                "figures, one bearded, another one bespectacled, and the " +
                "third one in a ridiculous "+
                "green hat appear and say: 'We are not welcoming visitors "+
                "just yet!', and you are forced to turn back.\n");
  return 1;
}

void
create_room ()
{
  set_short("On a pier on the Lucky Island.");

  set_long("You stand on a small but sturdy pier, recently built on "+
           "the Lucky Island. A path goes off the pier to the west, "+
           "waving between the vibrant grasses and bushes towards the "+
           "deeper parts of the island. To the east the pier is being "+
           "extended to establish regular cabotage to other parts "+
           "of Khalakhor.\n");

	add_item(({"sea" }),
           "The greenish waters are swaying calmly against the bases of "+
           "the pier.\n");

  add_exit("pier-61-60", "east", block_gss);
  add_exit("path-59-60", "west", block_lucky);
  
  add_row_exit(LUCKY_ENTRY, "south", no_go, 1);

  add_prop(ROOM_I_INSIDE, 0);
  add_prop(ROOM_I_TYPE, ROOM_NORMAL);

  // Set the sailing skill required to sail to this room.
  set_sailing_difficulty(NORMAL_DIFFICULTY);

  // Set the optional message when sailing into this room.
  set_sailing_fail_message("You feel uncomfortable departing the welcome "+
                           "shores of the Lucky Island.\n");
  set_sailing_difficulty_message("You navigate across the calm " +
                                 " waters surrounding the Lucky Island!\n");
}

