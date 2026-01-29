/* cv/post.c
 * Lilith Nov 2021
 * Coven Location #2 for the Faerun Vampires.
 * Any changes to these rooms should be discussed
 * by the GM of the Vamps and the Liege of Avenir.
 *
 * removed sitting down to read mail msg. - Lilith June 2022
 */

inherit "/d/Faerun/guilds/vampires/rooms/std/vampires_std_room";
inherit "/d/Genesis/lib/post";
#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "/d/Faerun/guilds/vampires/guild.h";



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
	set_short("postal room");
	set_long("This is a quiet little nook to sit down to read your "
        +"mail and perhaps even write a letter. It feels like a " 
        +"geode in here, with all the crystals jutting out of the "
        +"walls and ceiling. There are a couple of armchairs here, "
        +"and a small table with pens and paper. The floor is smooth "
		+"and dark.\n");
		
    add_exit("room9",  "north");
    add_exit("room6",  "east");	


	add_item(({"ceiling","stalactites"}),
        "The ceiling of this room is draped in darkness that is pierced "
        +"by stalactites formed over the eons.\n");
    add_item(({"dark", "darkness"}), "The darkness is so deep that even "
        +"your eyes cannot penetrate it.\n");
    add_item(({"crystal", "crystals", "wall", "walls"}),
        "Crystals of every size have grown from the walls and ceiling. "
        +"They are mostly transparent with blue and green tints to them.\n"); 		
    add_item(({"floor", "ground", "basalt"}),
        "The basalt floor is chiseled level and polished to a high gloss that "
        +"accentuates the sparkle of the microcrystals within it.\n");
    add_item(({"air"}), "The air is still and cool.\n");
    add_cmd_item(({"air"}), ({"smell", "sniff"}), 
        "The air smells faintly of the sea of Sybarus.\n");
	add_item(({"table", "small", "letter table" }), "It is a small letter "
        +"table for reading and writing letters upon.\n");
    add_item(({"armchair", "armchairs", "chair", "chairs"}),
        "High-backed and draped with furs, the armchairs are decadently "
        +"comfortable.\n");		

}


public void
autosit(object who)
{
 //   write("You collect your mail and sit in one of the armchairs.\n");
 //   say(({ who->query_met_name() + " sits in an armchair.\n",
 //	    who->query_nonmet_name() + " sits in an armchair.\n", ""}));
}


void
init()
{
    ::init();
    post_init();
}


public void
enter_inv(object to, object from)
{
    ::enter_inv(to, from);

    if (query_interactive(to))
	set_alarm(1.5, 0.0, &autosit(to));
}

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob,to);
    post_leave_inv(ob,to);
    if (query_interactive(to))
	to->catch_tell("You rise from your chair as you leave the room.\n");
}
