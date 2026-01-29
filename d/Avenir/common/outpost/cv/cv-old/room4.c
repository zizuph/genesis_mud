/* cv/room4.c
 * Lilith Oct 2021
 * Coven Location #2 for the Faerun Vampires.
 * Any changes to these rooms should be discussed
 * by the GM of the Vamps and the Liege of Avenir.
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <composite.h>
#include <filter_funs.h>
#include "/d/Faerun/guilds/vampires/guild.h";

inherit VAMPIRES_STD_ROOM;

#define CANDELABRA "/d/Avenir/common/outpost/cv/room4a"
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
	set_short("northeast crystalline cavern");
	set_long("The magnificence of the natural world is on display in this "
        +"place. Stalactites covered in crystals project from a ceiling " 
        +"cloaked in impenetrable darkness. A massive candelabra hangs from "
        +"a thick chain, casting wavering light that sets myriad facets "
        +"asparkle. The floor and walls seem to flow with colourful "
        +"bands of agate. South is a lounging area@@see_lounge@@"		
		+"\n");

		
    add_exit("room3",  "east");
    add_exit("room5",  "west");
    add_exit("lounge", "south");	
	// non-obvious
    add_exit("room6",  "southwest", 0, 0, 1);

    
	add_item(({"ceiling","stalactites"}),
        "The ceiling of this cavern is draped in darkness that is pierced "
        +"by stalactites formed over the eons. The stalactites glitter "
        +"and gleam in the light of the candelabra.\n");
    add_item(({"dark", "darkness"}), "The darkness is so deep that even "
        +"your eyes cannot penetrate it.\n");	
	add_item(({"candelabra", "chandelier", "candles","candlelight"}),
        "A massive candelabra is suspended from the cavern ceiling by a "
        +"thick chain. Hundreds of candles cast a muted, mellow light on "
	    +"the cavern beneath it.\n");
    add_item(({"chain", "thick chain"}),
        "A chain with links the size of your hand is fastened high on the "
        +"wall. It connects to the massive candelabra suspended from the "
        +"ceiling.\n");		
    add_item(({"crystal", "crystals", "microcrystals", "facets"}),
        "Crystals of every size, from microcrystals sprinkled in the basalt "
		+"to giant selenite crystals as thick as your thigh, make this cavern"
        +"ous space into a geode the size of which you have never seen before."
        +"The facets reflect the soft candlelight back at you.\n"); 		
    add_item(({"selenite", "selenite crystals"}),
        "These are massive, translucent crystals formed by super-heated, "
        +"mineral-rich water and vapor that cooled slowly enough for the "
		+"crystals to form and grow to monolithic proportions.\n"); 	
    add_item(({"wall", "walls", "agate", "bands", "swirls"}),
        "The walls of this chamber look like they were made by the hand "
        +"of a god who turned the seas to stone. Blues and greens and "
        +"creamy whites in bands and swirls of gorgeous agate have been "
		+"polished smooth by the flow of water over the eons.\n");
    add_item(({"floor", "ground", "basalt"}),
        "The basalt floor is chiseled level and polished to a high gloss that "
        +"accentuates the sparkle of the microcrystals within it.\n");
    add_item(({"air"}), "The air is still and cool.\n");
    add_cmd_item(({"air"}), ({"smell", "sniff"}), 
        "The air smells faintly of the sea of Sybarus.\n");

    reset_faerun_room();

}

/*
 * Function name: do_climb
 * Description:   Do we climb the chain here?
 * Returns:       0 - no; 1 - yes.
 */

private int 
action_climb(string str)
{
    object tp = this_player();
    object ospace;
	
    notify_fail(capitalize(query_verb()) + " what?\n");
    if(!strlen(str) || !parse_command(str, ({}), 
        "[up] [the] 'chain' / 'candelabra'"))
    return 0;

    notify_fail("You are too busy fighting right now.\n");
    if(tp->query_attack())
    return 0;

    notify_fail("You are too tired.\n");
    if(tp->query_fatigue() < 20)
    return 0;

    // Start climbing 
    write("You begin to "+ query_verb() +" up the chain.\n");
    say(tp->query_cap_name() +" "+ query_verb() +"s up the chain.\n");  

    ospace = find_object(CANDELABRA);
    int volume = 0;
    if (ospace)
    {
    	foreach (object obj : all_inventory(ospace))
    	{
    	    volume += obj->query_prop(OBJ_I_VOLUME);
    	}
    }
    // If there is more than this volume in it, then there
    // isn't room for a person in this space.
	// Sort of like the Stump on the Holm.
    if (volume > 35000)
    {   
	write("You look around, but there isn't room for you on the candelbra "
        +"itself so you climb back down.\n");
    say(tp->query_cap_name() +" "+ query_verb() +"s back down the chain.\n");  
	return 1;
    }
    write("You see there is a spot with enough room for you on the "+
	    "candelabra so you climb carefully on to it.\n");
    tp->move_living("X", CANDELABRA, 1, 0);
    return 1;

}



void
init()
{
    ::init();
    add_action(action_climb, "climb");
}

