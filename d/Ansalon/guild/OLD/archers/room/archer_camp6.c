
/* File name: archer_camp6.c
 * The Elven Archers training camp in the Qualinesti forest.
 * Before the Herbalist tent.
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
    add_my_desc("The mixed scent of herbs is coming from the small tent.\n");
    
    add_item(({"tent", "herb tent", "herbalist tent", "small tent" }),
        "This small tent is being used for storing herbs, that very " +
        "often come in handy for the elves.\n");
    
    OUTSIDE;
    
    add_exit(GUILD_ROOM + "archer_camp5.c", "west", 0, 1);    
    add_exit(GUILD_ROOM + "archer_camp2.c", "southwest", 0, 1);
    add_exit(GUILD_ROOM + "herbalist.c", "tent", 0, 1);
    
    reset_qualinesti_room();
    
}

    