/**
* Rack room for Knight Rank or Above.
* Navarre 2006
*/

#pragma strict_types

#include "../local.h"
#include <macros.h>

inherit GUILD_IR;

void
reset_guild_room()
{
    
}

void
create_guild_room()
{
    setuid();
    seteuid(getuid());
    set_short("Storage room of the Templar Knights that have "+
              "proved themselves in the eyes of the Dark Queen");
    
    set_long("This space is used by the Templar Knights "+
        "to store any gear or equipment they wish to "+
        "leave for other Knights.  "+
        "The general racks can be found to the south.\n");    
    
    clone_object(OBJ+"rack_knight")->move(TO);
    
    add_exit(ROOM+"storage","south");
    reset_guild_room();
}
