
/* File name: shooting_ground.c
 * The Elven Archers training camp in the Qualinesti forest.
 * Shooting ground.
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
    set_short_desc("on the shooting ground");

    set_long_desc("This is the place, where the elven archers practice " +
        "their archery skill.");

    add_my_desc("\n");
    
    OUTSIDE;
    
    add_exit(GUILD_ROOM + "archer_camp4.c", "southeast", 0, 1);    
    add_exit(GUILD_ROOM + "training_room.c", "east", 0, 1);
 
    reset_qualinesti_room();
    
}

    