
/* File name: training_room.c
 * The Elven Archers training camp in the Qualinesti forest.
 * Main training room.
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
    set_long_desc("This is the elven archers' main training place.");
    
    add_my_desc("\n");
    
    OUTSIDE;
    
    add_exit(GUILD_ROOM + "shooting_ground.c", "west", 0, 1);    
    add_exit(GUILD_ROOM + "archer_camp5.c", "southeast", 0, 1);

    reset_qualinesti_room();
    
}

    