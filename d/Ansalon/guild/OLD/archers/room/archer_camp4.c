
/* File name: archer_camp4.c
 * The Elven Archers training camp in the Qualinesti forest.
 * Outside the armoury.
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
    add_my_desc("An old tent, made of strong canvas, has been set here.\n");
    
    add_item(({ "tent", "old tent", "armoury tent" }),
        "This tent, used for storing armours and weapons, has been made " +
        "of hard and strong canvas to make sure that items inside are " +
        "secured as much as possible against the corrosion and " +
        "changes of the weather in general.\n");
    
    OUTSIDE;
    
    add_exit(GUILD_ROOM + "archer_camp5.c", "east", 0, 1);    
    add_exit(GUILD_ROOM + "shooting_ground.c", "northwest", 0, 1);
    add_exit(GUILD_ROOM + "armoury_tent.c", "tent", 0, 1);
        
    reset_qualinesti_room();
    
}

    