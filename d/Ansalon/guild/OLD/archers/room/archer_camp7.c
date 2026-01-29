
/* File name: archer_camp7.c
 * The Elven Archers training camp in the Qualinesti forest.
 * Before the board room.
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
    add_my_desc("The small brown tent has been set here.\n");
    
    add_item(({"tent", "brown tent", "small brown tent", "small tent" }),
        "This is a small, ordinary tent. You are not sure what it is " +
        "being used for.\n");
    
    OUTSIDE;
    
    add_exit(GUILD_ROOM + "post_office.c", "east", 0, 1);    
    add_exit(GUILD_ROOM + "archer_camp5.c", "south", 0, 1);
    add_exit(GUILD_ROOM + "board_tent.c", "tent", 0, 1);
    
    reset_qualinesti_room();
    
}

    