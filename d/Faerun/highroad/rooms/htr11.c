/*
 * Mountain trail in the Sword Mountains
 * -- Finwe, July 2006
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_ROAD;

#define FIREKNIVES_MASTER   "/d/Faerun/guilds/fire_knives/master/occ_fireknives_master"
#define FIREKNIVES_GUILD_DIR   "/d/Faerun/guilds/fire_knives/"


int
do_goeast(string str)
{
    if (FIREKNIVES_MASTER->is_occ_fireknife(this_player()->query_name()) == 0)
    {
        if (!this_player()->query_wiz_level())
        {
            write("There is no obvious exit east.\n");

            return 1;
        }
    }
        
    write("\n\nYou silently dive into the snow and vanish "
    +"eastwards.\n\n");

    this_player()->move_living("M", FIREKNIVES_GUILD_DIR + "rooms/mountain_ft_member", 1);
        
    tell_room(FIREKNIVES_GUILD_DIR + "rooms/mountain_ft_member", QCTNAME(this_player())
    + " arrives from the snow.\n", this_player());
        
    return 1;
}



void
create_road()
{
    add_prop(ROOM_S_MAP_FILE, "sword_mt_map.txt");

    set_short("a snowy trail");
    set_extraline("Snow drifts are everywhere. The freezing wind has blown them together during snowstorms. The trail is barely visible, winding northeast and south.");

    add_item(({"trail", "rocky trail", "path"}),
        "The trail is hidden from view by all the snow here but appears to wind northeast and south.\n");
    
    reset_faerun_room();

    add_sword_mts_cold();

    add_exit(HR_DIR + "htr12", "northeast");
    add_exit(HR_DIR + "htr10", "south");
}

void
init()
{
    ::init();

    add_action(do_goeast, "east");
}

void
reset_faerun_room()
{
}

int climb()
{
    TP->move_living("climbing down the face of cliff.", HR_DIR + "htr08");
    return 1;
   
}