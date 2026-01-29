/* cv/room11.c
 * Lilith Oct 2021
 * Coven Location #2 for the Faerun Vampires.
 * Any changes to these rooms should be discussed
 * by the GM of the Vamps and the Liege of Avenir.
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "/d/Faerun/guilds/vampires/guild.h";

inherit VAMPIRES_STD_ROOM;

// Back exit.
#define PORT_LEDGE "/d/Avenir/common/ledge/ledge9"

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
	set_short("opening of lava tube");
	set_long("This is the north end of the lava tube, which opens up onto "
        +"a bird's eye view of the great Sybarus cavern itself. You can " 
        +"see the light of the Source illuminating the sea and the distant "
        +"islands. Directly beneath you, the cavern wall is very steep and "
        +"smooth, with a narrow ledge far below that climbs toward the "
        +"port. The roosting spot for the coven's bats is west.\n");

    add_exit("room12", "south");
	add_exit("roost", "west");
    
	add_item(({"sea", "source", "cavern", "islands"}), "This view of the "
        +"Sybarus cavern is spectacular. It is truly a beautiful setting, "
        +"one of nature's wonders.\n");
    add_item(({"ledge", "wall", "cliff", "cavern wall", "down"}),
        "Looking down, you can see that you are standing at the edge of "
        +"an opening in the cavern wall, and that there is a ledge far "
		+"below.\n");
    add_item(({"stone", "bands", "basalt"}),
        "The stone appears to be a basalt made when magma cooled. It is "
        +"patterned with bands of colourful agate, and some crystals, too.\n");
	add_item(({"agate", "colourful agate", "agates", "stripes"}),	
        "Formed eons ago when heated gases were trapped in these magma "
        +"tunnels and then slowly cooled. They are beautiful, forming "
        +"ribbons, bands, and lacy swirls in blues, greens, and white.\n");		
    add_item(({"crystal", "crystals"}),
        "Crystals poke out from random surfaces, all pointing "
        +"toward the center of the tunnel.\n"); 		
    add_item(({"floor", "ground", "basalt floor"}),
        "The basalt floor is chiseled level and polished to a high gloss "
        +"that accentuates the sparkle of the microcrystals within it.\n");
	add_item(({"ceiling","stalactites", "formations"}),
        "The ceiling of this corridor is draped in darkness that is pierced "
        +"by crystal-encrusted stalactites formed over the eons.\n");
    add_item(({"dark", "darkness"}), "The darkness above is so deep that "
        +"even your eyes cannot penetrate it.\n");			
 

    reset_faerun_room();

}

/*
 * Function name: do_jump
 * Description:   Do we jump down?
 * Returns:       0 - no; 1 - yes.
 */
private int
action_jump(string str)
{
    object tp = this_player();

    notify_fail("What do you want to do, jump down?\n");
    if (!strlen(str) || !parse_command(str, ({ }), 
        "'down' / 'over' [onto] [the] [ledge] / [edge]"))
	return 0;    

 
    write("You jump down onto the ledge, surviving a landing that would "
        +"have killed a mortal.\n");
    say(QCTNAME(tp) + "jumps over the edge!\n");
    tp->move_living("M", PORT_LEDGE, 1, 1);
    return 1;
}


void
init()
{
    ::init();

    add_action(action_jump, "jump");
	
}
