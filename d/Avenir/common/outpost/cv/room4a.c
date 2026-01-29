/* cv/room4a.c
 * Lilith Oct 2021
 * Coven Location #2 for the Faerun Vampires.
 * Any changes to these rooms should be discussed
 * by the GM of the Vamps and the Liege of Avenir.
 */
inherit "/d/Faerun/guilds/vampires/rooms/std/vampires_std_room";
#include "/d/Faerun/defs.h"
#include "/d/Faerun/guilds/vampires/guild.h";
#include <composite.h>
#include <filter_funs.h>
#include <stdproperties.h>



#define BELOW ({"/d/Avenir/common/outpost/cv/room4", \
                "/d/Avenir/common/outpost/cv/room5", \
                "/d/Avenir/common/outpost/cv/room6", \
				"/d/Avenir/common/outpost/cv/lounge"})

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
see_below(void)
{
    object *live = get_view(BELOW);

    if (!sizeof(live))
        return "";

    return " In the cavern below, you can see "+
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
		
	set_short("atop candelabra");
	set_long("From here you can see that the candelabra is suspended "
        +"above the cavern floor using four thick chains mounted into " 
        +"the walls. It is made of iron wrought by a skilled smith. "
        +"Hundreds of candles burn in tiers below you, just far enough "
		+"away that they pose you no danger. All around you, stalactites "
        +"and massive crystals thrust down from the cavern ceiling. "
        +"In the light of the candles you can see their incredible beauty "
        +"and colorfulness up close.@@see_below@@\n");
    
	add_item(({"ceiling","stalactites"}),
        "The ceiling of this cavern is draped in darkness that is pierced "
        +"by stalactites formed over the eons. The stalactites glitter "
        +"and gleam in the light of the candelabra.\n");
    add_item(({"dark", "darkness"}), "The darkness is so deep that even "
        +"from here your eyes cannot penetrate it.\n");
	add_item(({"candelabra", "chandelier", "candles"}),
       "The massive candelabra is suspended from the cavern ceiling by a "
        +"thick chain. Hundreds of candles cast a muted, mellow light on "
	    +"the cavern beneath it.\n");
    add_item(({"tier", "tiers"}), "Looking down through the grate you "
        +"you are resting on, you can see that the candles are arranged "
        +"in tiers that provide a cascade of soft, mellow light.\n");
    add_item(({"grate"}), "The grate is the top of the candelabra. The "
        +"tiers and the candles hang from it. It makes a convenient "
		+"spot from which to enjoy the beauty of the cavern.\n");
    add_item(({"chain", "thick chain"}),
        "A chain with links the size of your hand is fastened to the wall. "
        +"It connects to a massive candelabra suspended from the ceiling.\n");
		 		
    add_exit("room4",  "down");

    reset_faerun_room();

}

