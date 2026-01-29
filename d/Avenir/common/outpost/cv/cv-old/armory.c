/* cv/armory.c
 * Lilith Nov 2021
 * Coven Location #2 for the Faerun Vampires.
 * Any changes to these rooms should be discussed
 * by the GM of the Vamps and the Liege of Avenir.
 */


#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "/d/Faerun/guilds/vampires/guild.h";
#include <composite.h>
#include <filter_funs.h>

inherit VAMPIRES_STD_ROOM;

#define HALLWAY ({"/d/Avenir/common/outpost/cv/room13", \
                "/d/Avenir/common/outpost/cv/room10", \
                "/d/Avenir/common/outpost/cv/room9"})

public object *
get_view(string *arr)
{
    object *inv = ({});

    foreach(string path: arr)
    {
        object room = find_object(path);
        if (objectp(room))
            inv += all_inventory(room);
    }

    if (sizeof(inv))
        inv = FILTER_CAN_SEE(FILTER_LIVE(inv), this_player());

    return inv;
}


public string 
see_hallway(void)
{
    object *live = get_view(HALLWAY);

    if (!sizeof(live))
        return ".";

    return ", where you can see "+
        COMPOSITE_LIVE(live) + ".";
}



/*
 * Function name: create_vampires_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_vampires_room()
{
    seteuid(getuid());
    
    add_prop(ROOM_I_INSIDE, 1);
 	add_prop("_not_in_flux_zone", 1); //This prevents Source-related room tells.
    set_short("Armory");    
    set_long("This is a very functional room carved from the surrounding basalt. "
        +"The columns of stone which form the walls are smooth and unpolished, "
        +"unlike the floor, which has a beautiful lustre. The entire west wall "
        +"is a wooden rack that serves as the coven's armory. Back to the east "
        +"is the central hallway@@see_hallway@@"
		+"\n");
 
    room_add_object(VAMPIRES_GUILD_DIR + "obj/cv2_rack");
                      
    add_exit("room13", "east");
    
    add_item(({"floor", "ground", "basalt floor"}),
        "The basalt floor is chiseled smooth and polished to a high gloss "
        +"that accentuates the sparkle of the microcrystals within it.\n");   
	add_item(({"stone", "walls", "basalt", "baslt column", "columns"}),
        "The stone of the walls appears to be basalt that formed as magma cooled. It is "
        +"dark with a flight reddish tiny, and is peppered with crystals, too.\n");
	
	
	
    reset_faerun_room();
}

