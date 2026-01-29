inherit "/std/room.c";
#include <stdproperties.h>
#include "../defs.h"

void
create_room()
{
    set_short("Common Room");
    set_long(break_string(
"This room serves as a common room for those too poor to buy a room at a " +
"inn, or too unskilled to pick a pocket.  There are bunks and hammocks here " +
"for sleeping.  Be very quiet, for there are a number of nasty-looking " +
"people here already asleep.  Blackhands can type 'start here' to begin " +
"their game from this location.\n", 78));

    add_exit(G_ROOMS + "ghall3", "west", 0);

    add_item(({"bunk", "bunks"}), break_string(
"What matress is left is flea-ridden, and many springs are missing from " +
"these 'beds.'  I guess youd have to be poor to want to sleep here.\n", 78));

    add_item(({"hammocks", "hammock"}), break_string(
"These hammocks are of the type sailors use on long voyages.  Why are " +
"they here?  They were probablly stolen from the shipyard.\n", 78));

    add_prop(ROOM_I_INSIDE, 1);

}
