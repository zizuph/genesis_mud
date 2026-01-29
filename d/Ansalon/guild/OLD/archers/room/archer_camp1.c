
/* File name: archer_camp1.c
 * The Elven Archers training base in the Qualinesti forest.
 * Before Porthios' tent.
 *
 * Blizzard, 06.11.2003
 */
    
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/qualinesti/local.h"
#include "../guild.h"

inherit  GUILD_CAMP_BASE;

object   guard;

void
reset_qualinesti_room()
{
     if ( !guard )
     {
         guard = clone_object(GUILD_STD + "guard_base");
         guard->move(TO, 1);
     }
}

void
create_camp()
{
    add_my_desc("There is a large green tent standing here.\n");
    
    add_item(({ "tent", "green tent", "large green tent", "large tent" }),
        "This is a big green tent. It is guarded by an elven warrior, " +
        "what may suggest that it belongs to some important person.\n");
    
    OUTSIDE;
    
    add_exit(GUILD_ROOM + "archer_camp2.c", "east", 0, 1);    
    add_exit(GUILD_ROOM + "archer_camp5.c", "northeast", 0, 1);
    
 /* Exit to the Elven Archers join room */
    add_exit(GUILD_ROOM + "joinroom.c", "tent", 0, 1);
    
    reset_qualinesti_room();
    
}

    