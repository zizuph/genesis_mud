
/* File name :  herbalist.c
 *
 * Inside the herbalist's tent.
 *
 * Blizzard, 05.11.2003
 */
 
#include "/d/Krynn/common/defs.h"
#include "../guild.h"

inherit R_FILE


public void
create_krynn_room()
{
    set_short("inside the herbalist's tent");
    set_long("You are standing inside the herbalist's tent.\n");
    
    INSIDE;
    NO_TIME;
    
    add_exit(GUILD_ROOM + "archer_camp6.c", "out", 0, 1);
    
}
