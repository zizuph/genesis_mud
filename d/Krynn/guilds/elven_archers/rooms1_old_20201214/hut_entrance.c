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
    set_long("You are at the entrance of a small wooden hut seated high up in the trees. "+
             "Here you can rest safely using one of the small bunks in here.\n");

    set_short("You are standing in the resting area in a small hut");


    add_item(({"hut", "wooden hut", "small hut", "small wooden hut"}),
               "This hut is used by the elite archers as a safe refuge.\n");
    add_item("trees", "The trees hide and carry the hut which you are standing in.\n");
    add_item(({"bunks", "bunk", "small bunk", "small bunks"}), "They do not look like the " +
               "most comfortable bed you have seen, but they should make do. You can " + 
               "use one of them by choosing to <start here>.\n");
    add_cmd_item("here", "start", "@@do_start");
    
    INSIDE;
    
    add_exit(ROOMS+"hut_board", "east", 0);
    add_exit(ROOMS+"entrance", "west", 0);
    reset_room();
}

int
do_start()
{
    if (TP->query_guild_name_occ() == "Ansalon Elvish Archers" ||
        TP->query_guild_name_lay() == "Ansalon Elvish Archers")
    {	
        TP->set_default_start_location(START_ROOM);
        write("You will start from here now any time you wake up.\n");
	return 1;
    }
    write("Only archers can start here.\n");
    return 1;
}
