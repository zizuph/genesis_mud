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
#define VAMPIRES_MASTER   ("/d/Faerun/guilds/vampires/master/vampires_master")

inherit BASE_TUNNEL;

string extraline = "";


public int
block_check()
{
    if (VAMPIRES_MASTER->is_occ_vampires(this_player()->query_name()) == 1)
	{          
        return 0;
    }      
    
    if (this_player()->query_average() >= 190)
    {
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
    set_extraline(tun_desc5(extraline));

    reset_room();

    add_exit("/d/Faerun/guilds/vampires/rooms/cv1_entryway", "north", block_check ,0, 1);
    add_exit(TUN_DIR + "tu05", "southwest");
    add_exit(TUN_DIR + "tu06", "southeast");
}


void
do_whispers()
{
    if (VAMPIRES_MASTER->is_occ_vampires(this_player()->query_name()) == 1)
	{          
        if (VAMPIRES_MASTER->no_coven1_master() == 1)
        {
            if (VAMPIRES_MAPPINGS->query_vampires_rank(this_player()->query_name()) >= 2)
            {
                this_player()->catch_tell(">>Your sense that the location of a vacant vampire "
                +"coven is located north of here. You think you can somehow pass the wall to the "
                +"north<<\n");
                
                return;
            }
        }
    }        
 
    return;
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (interactive(ob))
    {
        set_alarm(0.2, 0.0, &do_whispers());
    }
}


public void
init()
{
    ::init();

}

void
reset_room()
{
    set_searched(0);
}

