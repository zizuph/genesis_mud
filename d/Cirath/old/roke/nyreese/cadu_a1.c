/*
 * cadu_a1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/*  Ged  */
/*  updated Amelia 6-6-98 to remove the connection to Gar */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

void
create_room() 
{
    set_short("Alley");
    set_long("You are in a small alley east of the town square.\n" +
      "North is the local shop and south is the famous bank.\n" +
      "To the east there is a sudden steep dropoff. You look down " +
      "over the edge of the cliff to the sea far below, crashing " +
      "against the rocks. Lying on the boulders is what looks like the " +
      "massive remains of a dragonship, broken and destroyed.\n");


    add_item((({"cliff", "dropoff"})),
	     "The land suddenly ends at the cliff to the east, " +
	     "as though it had been broken off and sunk into the sea.\n");
    add_item((({"boulders", "rocks"})),
	     "The sea far below crashes onto huge boulders.\n");
    add_item((({"dragonship", "remains", "massive remains"})),
	     "The remains of the once proud dragonship lie foundered and " +
	     "broken on the rocks at the foot of the cliff.\n");

    add_exit("cadu_q9" , "west");
    add_exit("cadu_bank" , "south");
    add_exit("cadu_shop" , "north");
}
