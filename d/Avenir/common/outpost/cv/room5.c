/* cv/room5.c
 * Lilith Oct 2021
 * Coven Location #2 for the Faerun Vampires.
 * Any changes to these rooms should be discussed
 * by the GM of the Vamps and the Liege of Avenir.
 *
 * Talk to Nerull about adding a check allowing
 * coven members only west of here, where the 
 * tomb, rack, etc are.
 *
 */

inherit "/d/Faerun/guilds/vampires/rooms/std/vampires_std_room";
#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "/d/Faerun/guilds/vampires/guild.h";
#include <composite.h>
#include <filter_funs.h>



#define LOUNGE ({"/d/Avenir/common/outpost/cv/lounge"})

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
see_lounge(void)
{
    object *live = get_view(LOUNGE);

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

	set_short("northwest crystal chamber");
	set_long("Nothing man could ever create would match the numinous beauty of "
        +"this crystal cavern. Stalacmites and massive crystals jut from the "
        +"ceiling and walls, their colors heightened by the soft light of the "
        +"candelabra high above. The agate walls are interrupted here and "
        +"there with embedded geodes of olivine and chrysoberyl crystals. " 		
		+"Most of the coven amenities are west of here up a long set of stairs. "
        +"The lounging area is southeast@@see_lounge@@\n");

    add_exit("room4",  "east");
	add_exit("room6",  "south");
    add_exit("room9",  "west");
    // non-obvious exits:
    add_exit("room9",  "up", 0, 0, 1);	
    add_exit("lounge", "southeast", 0, 0, 1);
    
    add_item(({"wall", "walls", "agate", "bands", "swirls"}),
        "The walls of this chamber look like they were made by the hand "
        +"of a god who turned the seas to stone. Blues and greens and "
        +"creamy whites in bands and swirls of gorgeous agate have been "
		+"polished by the flow of water over the eons.\n");
    add_item(({"geode", "geodes", "olivine", "chrysoberyl"}),
        "The agate walls are interrupted with large geodes containing "
        +"green olivine and blue-green chrysoberyl cystals, some as "
		+"large as your thumb.\n"); 	
	add_item(({"floor", "ground", "basalt"}),
        "The basalt floor is chiseled level and polished to a high gloss that "
        +"accentuates the sparkle of the microcrystals within it.\n");
	add_item(({"ceiling","stalactites"}),
        "The ceiling of this chamber is draped in darkness that is pierced "
        +"by stalactites formed over the eons. The stalactites glitter "
        +"and gleam in the light of the candelabra.\n");
    add_item(({"dark", "darkness"}), "The darkness is so deep that even "
        +"your eyes cannot penetrate it.\n");	
	add_item(({"candelabra", "chandelier", "candles","candlelight"}),
       "A massive candelabra is suspended from the cavern ceiling by a "
        +"thick chain. Hundreds of candles cast a muted, mellow light on "
	    +"the cavern beneath it.\n");
    add_item(({"crystal", "crystals", "microcrystals", "facets"}),
        "Crystals of every size, from microcrystals sprinkled in the basalt "
		+"to giant selenite crystals as thick as your thigh, make this cavern"
        +"ous space into a geode the size of which you have never seen before."
        +"The facets reflect the soft candlelight back at you.\n"); 		
    add_item(({"air"}), "The air is still and cool.\n");
    add_cmd_item(({"air"}), ({"smell", "sniff"}), 
        "The air smells faintly of the sea of Sybarus.\n");
    reset_faerun_room();

}
