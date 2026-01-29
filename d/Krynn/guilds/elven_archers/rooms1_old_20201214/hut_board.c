/**
 * Room in the Archer Guild
 *
 * Navarre November 23th 2007.
 */
    
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "../guild.h"
inherit "/d/Krynn/std/room";

void
reset_krynn_room()
{
}

void
create_krynn_room()
{

    set_long("You are in a large open area. The tree branches making up the ceiling open to " +
             "allow a clear view of the sky while at the same time providing some protection " +
             "from bad weather. This room faces the broad side of a tree trunk that is being " +
             "used as a place to post messages for the other archers. The trunk is littered " +
             "with small pieces of parchment attatched to the trunk in various ways.\n");

    set_short("You are standing in the board room");    
    add_item(({"tree", "tree trunk", "side", "broad side", "big tree", "oak", "big oak"}),
             "The large tree trunk this room faces are used to hold messages to be shared among the archers.\n");
    add_item(({"area", "large area", "large open area", "open area"}), long());

    add_item(({"branches", "tree branches", "ceiling"}), "The tree branches make up the ceiling, " +
               "which is partly open with a clear view of the sky.\n");
    add_item(({"sky", "clear view", "view"}), "You have a clear view of the sky through the opening in the ceiling.\n");

    add_item("weather", "The weather doesn't look too bad today.\n");

    add_item(({"hut", "camouflaged hut"}), "You are standing in it.\n");

    OUTSIDE;
    add_exit(ROOMS + "hut_entrance", "west", 0);
    add_exit(ROOMS + "hut_postoffice", "east", 0);

    // Clone the guild board
    room_add_object(GUILD_OBJ + "archer_board", 1, 0);
    
    reset_room();
}
