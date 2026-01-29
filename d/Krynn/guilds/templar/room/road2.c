/**
* path in front of the guild.
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
    set_short("in front of the Templars of Takhisis headquarters");
    
    set_long("You are standing on a small dirt road outside the "+
        "headquarters of the Templars of Takhisis.  " +
        "Here is where those who are loyal to the Dark Queen, "+
        "and Her trusted minions, may enlist to serve Her desires "+
        "in a more direct way.  "+
        "The road leads north into the building, and west "+
        "to the main road between the Blue and Black Quarters.  "+
        "\n");
        
    add_item(({"building","headquarters","headquarter"}),
        "The small building to the north houses the Templars "+
        "of Takhisis.  It appears to have plenty of room to "+
        "expand over time.\n");
        
    add_item(({"road","path","dirt road","dirt path"}),
        "The dirt road looks relatively new, as if it has not "+
        "seen a lot of traffic.  "+
        "It leads north into the building, and west to the "+
        "main road.\n");
        
    add_exit(ROOM+"road1","west",0);
    add_exit(ROOM+"joinroom","north",0);
    reset_guild_room();

}
