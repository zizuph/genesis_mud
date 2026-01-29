
/* File name: archer_camp2.c
 * The Elven Archers training camp in the Qualinesti forest.
 * 
 * Blizzard, 06.11.2003
 */
    
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/qualinesti/local.h"
#include "../guild.h"

inherit  GUILD_CAMP_BASE;

void
reset_qualinesti_room()
{

}

void
create_camp()
{
    add_my_desc("There are several tents scattered about.\n");
    
    add_item( ({"tent", "tents" }),
        "These are simple earth-colored tents. You cannot say much about " +
        "about them, but they were obviously made by elves.\n");
    
    OUTSIDE;
    
    add_exit(GUILD_ROOM + "archer_camp1.c", "west", 0, 1);    
    add_exit(GUILD_ROOM + "entrance.c", "south", 0, 1);
    add_exit(GUILD_ROOM + "archer_camp3.c", "east", 0, 1);
    add_exit(GUILD_ROOM + "archer_camp5.c", "north", 0, 1);
    add_exit(GUILD_ROOM + "archer_camp6.c", "northeast", 0, 1);
        
    reset_qualinesti_room();
    
}

    