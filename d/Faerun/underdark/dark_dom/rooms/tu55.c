/*
 * Tunnel room in Underdark
 * -- Finwe, July 2006
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

#define VAMPIRES_MAPPINGS ("/d/Faerun/guilds/vampires/master/vampires_mappings")

inherit BASE_TUNNEL;

string extraline = "";

public int
block_check()
{
    if (this_player()->query_guild_name_lay() != 0)
    {
        write("There is no obvious exit north.\n");
        
        return 1;
    }
    
    if (this_player()->query_guild_name_race() != 0)
    {
        write("There is no obvious exit north.\n");
        
        return 1;
    }
    
    if (this_player()->query_race() != "human")
    {
        write("There is no obvious exit north.\n");
        
        return 1;
    }
    
    if (this_player()->query_average() < 160)
    {
        write("There is no obvious exit north.\n");
        
        return 1;
    }
    
    
    if (VAMPIRES_MAPPINGS->query_vampire_seeker(this_player()->query_name()) == 7)
	{      
        write("You glide through the north wall as if it didn't exist.\n");
        
        tell_room(environment(this_player()), QCTNAME(this_player())
        +" suddenly vanishes into the north wall!\n", this_player());
            
        return 0;
    }  

    write("There is no obvious exit north.\n");
	
    return 1;
}


void
create_tunnel()
{
    add_std_herbs("underdark");

    set_short("A dark tunnel");
    set_extraline(tun_desc3(extraline));

    reset_room();

    add_exit("/d/Faerun/guilds/vampires/rooms/crypt", "north", block_check ,0, 1);
    add_exit(TUN_DIR + "tu49", "northeast");
    add_exit(TUN_DIR + "tu54", "west");
}

public void
init()
{
    ::init();

}
void
reset_room()
{
    make_drow();
    set_searched(0);
}
