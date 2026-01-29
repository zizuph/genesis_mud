#include "defs.h"
#include <macros.h>

inherit MIST_SHORE_BASE;

#define VAMPIRES_MASTER "/d/Faerun/guilds/vampires/master/vampires_master.c"

int
do_coven_teleport()
{
    if (VAMPIRES_MASTER->is_occ_vampires(this_player()->query_name()) == 1)
    {          
        if (VAMPIRES_MASTER->is_coven3_member(this_player()->query_name()) == 1)
        { 
            write("\nYou fade into the mist, and is quickly teleported "
            +"to your coven.\n\n");

            tell_room(environment(this_object()), QCTNAME(this_player())
            + " fades into the mist.\n", this_player());
            
            this_player()->move_living("M", "/d/Faerun/guilds/vampires/rooms/cv3_entryway", 1);
            
            tell_room("/d/Faerun/guilds/vampires/rooms/cv3_entryway", QCTNAME(this_player())
            + " suddenly materializes.\n", this_player());
            
            return 1;
        }
    }    
    
    return 0;
}


public void
create_mist_shore_room()
{
    add_mist_exit(RSHORE_EXIT, MIST_TOWER_DIR + "mist_isle02", "northwest");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle03", "north");
    add_mist_exit(LSHORE_EXIT, MIST_TOWER_DIR + "mist_isle04", "northeast"); 

    setuid();
    seteuid(getuid());
    clone_object(MIST_TOWER_DIR + "obj/obelisk")->move(this_object(), 1);
}


void
init()
{
    ::init();
    add_action(do_coven_teleport, "coventeleport");
}
