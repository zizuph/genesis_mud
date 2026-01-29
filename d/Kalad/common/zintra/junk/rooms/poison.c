inherit "/std/room.c";
#include <stdproperties.h>
#include "../defs.h"

void
create_room()
{
    set_short("Poison Shop");
    set_long(break_string(
"The local posion shop, containing all the hazardous substances you need to " +
"help further your career.  Before you drink anything in here, make sure " +
"you didn't take a wrong turn; the pub is to the south.  There is a sign on " +
"the wall you can read for further directions.\n", 78));

    add_exit(G_ROOMS + "ghall1", "west", 0);

    add_item(({"lanterns", "lantern"}), break_string(
"They are rusty, smoky, and in great need of more oil.  Unfortuantely for " +
"you, they are firmly attached to the wall.\n", 78));

    add_item(({"sign", "instructions"}), "Its looks a bit tattered.\n");

    add_prop(ROOM_I_INSIDE, 1);
}
