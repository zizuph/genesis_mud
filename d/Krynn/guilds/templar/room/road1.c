/**
* Small path to the guild.
* Louie  2004
*/

#pragma strict_types

#include "../local.h"
#include <macros.h>

inherit GUILD_OR;

/** prototypes **/


void
reset_guild_room()
{
    
}

void
create_guild_room()
{
    set_short("dirt road leading to a small building");
    
    set_long("This is a small dirt road leading to a building to "+
        "the east, between the Blue and the Black Quarters.  " +
        "The main road can be reached by heading west.  "+
        "\n");
        
    add_item(({"building","headquarters","headquarter"}),
        "The small building to the east looks quite new.  "+
        "It appears to have plenty of room to "+
        "expand over time.\n");
        
    add_item(({"road","path","dirt road","dirt path"}),
        "The dirt road looks relatively new, as if it has not "+
        "seen a lot of traffic.  "+
        "It leads east towards the building, and west to the "+
        "main road.\n");
        
    add_exit(ROOM+"road2","east",0);
    add_exit("/d/Ansalon/taman_busuk/neraka/outer/blue/b10","west",0);
    reset_guild_room();

}
