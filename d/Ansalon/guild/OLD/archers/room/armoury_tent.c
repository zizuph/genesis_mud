
/* File name :  armoury_tent.c
 *
 * Inside the armoury tent.
 *
 * Blizzard, 05.11.2003
 */
 
#include "/d/Krynn/common/defs.h"
#include "../guild.h"

inherit R_FILE


public void
create_krynn_room()
{
    set_short("inside the armoury tent");
    set_long("You are standing inside the armoury tent. It was made of " +
        "strong canvas so the things stored in here are well protected " +
        "against changes of the weather. There are three big racks, " +
        "where the elves place their weapons and armours, as well " +
        "as other miscellaneous items.\n");
    
    INSIDE;
    NO_TIME;
    
    add_exit(GUILD_ROOM + "archer_camp4.c", "out", 0, 1);
    
}
