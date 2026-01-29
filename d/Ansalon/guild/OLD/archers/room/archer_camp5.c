
/* File name: archer_camp5.c
 * The Elven Archers training camp in the Qualinesti forest.
 * Outside the start room.
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
    add_my_desc("The large sleeping tent is set in the middle of the camp.\n");
    
    add_item(({"tent", "large tent", "large sleeping tent", "sleeping tent" }),
        "This tent seems to be large enough to accommodate big number of " +
        "people. It is probably the place where the elven warriors rest " +
        "after a long day of hunting or when it is just too cold outside.\n");
    
    OUTSIDE;
    
    add_exit(GUILD_ROOM + "archer_camp1.c", "southwest", 0, 1);
    add_exit(GUILD_ROOM + "archer_camp2.c", "south", 0, 1);
    add_exit(GUILD_ROOM + "archer_camp4.c", "west", 0, 1);    
    add_exit(GUILD_ROOM + "archer_camp6.c", "east", 0, 1);
    add_exit(GUILD_ROOM + "training_room.c", "northwest", 0, 1);
    add_exit(GUILD_ROOM + "archer_camp7.c", "north", 0, 1);
    add_exit(GUILD_ROOM + "post_office.c", "northeast", 0, 1);
    add_exit(GUILD_ROOM + "start_tent.c", "tent", 0, 1);
    
    reset_qualinesti_room();
    
}

    