
/* File name: archer_camp3.c
 * The Elven Archers training camp in the Qualinesti forest.
 * Before the general equipment store.
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
    add_my_desc("There is a big supply tent standing here.\n");
    
    add_item(({"tent", "big tent", "big supply tent", "supply tent" }),
        "This tent is being used for storing the general equipment and " +
        "if you need anything you probably should visit it.\n");
    
    OUTSIDE;
    
    add_exit(GUILD_ROOM + "archer_camp2.c", "west", 0, 1);    
    add_exit(GUILD_ROOM + "general_store.c", "tent", 0, 1);
    
    reset_qualinesti_room();
    
}

    