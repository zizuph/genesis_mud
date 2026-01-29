#include "defs.h"

inherit MIST_ISLE_BASE;

#define VAMPIRES_MAPPINGS ("/d/Faerun/guilds/vampires/master/vampires_mappings")
#define VAMPIRES_MASTER   ("/d/Faerun/guilds/vampires/master/vampires_master")

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
    
    write("There is no obvious exit down.\n");

    return 1;
}


public void
create_mist_isle_room()
{
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle23", "west");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle19", "southeast");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle18", "south");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle17", "southwest");
    
    add_exit("/d/Faerun/guilds/vampires/rooms/cv3_entryway", "down", block_check ,0, 1);
}


void
do_whispers()
{
    if (VAMPIRES_MASTER->is_occ_vampires(this_player()->query_name()) == 1)
	{          
        if (VAMPIRES_MASTER->no_coven3_master() == 1)
        {
            if (VAMPIRES_MAPPINGS->query_vampires_rank(this_player()->query_name()) >= 2)
            {
                this_player()->catch_tell(">>Your sense that the location of a vacant vampire "
                +"coven is located down from here<<\n");
                
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