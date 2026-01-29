// file name:    fell.c
// creator(s)    Ilyian (25 August, 1995)
// last update:   Lilith & Zizuph, May-July 2021: finishing area for launch  
// purpose: This is the place where a player is when he is falling
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/common/dead/crypt_base";
#include "../dead.h"

void
create_crypt_room()
{
    set_short("inside cairn");
    set_long("White granite megaliths surround you, forming an "
	    +"ancient tomb. Underfoot, the ground is hard-packed and "
		+"gives off the scent of moist soil.\n");
	add_prop(ROOM_S_DARK_MSG, "The darkness around you is much too "
        +"thick to");
    add_prop(ROOM_S_DARK_LONG, "Darkness presses upon you "
        +"from all directions. The air smells of moist earth.\n");

    add_item(({"granite", "megaliths", "megalith", "white granite"}),
        "Large and somewhat oblong, these slabs of white granite "
        +"are bigger on the bottom that at the top. A few flat "
        +"slabs of the stone are balanced across them, forming "
        +"a primitive roof.\n");
	add_item(({"roof", "slabs" }),
	    "White granite, rough and unfinished.\n");
	add_item(({"ground", "dirt", "soil"}),
        "It is damp, and rich with the scent of decay.\n");	
    // Swallowed by earth, the darkness is deep.
	add_prop(ROOM_I_LIGHT, -20);

    // In the event mortal doesn't get moved out of here
    // Lets give them some exits
    add_exit(CRYPT+"crypt"+(random(25)),"down", 0, 40, 0);	
    add_exit(CRYPT+"crypt"+(random(25)),"out", 0, 40, 1);
	
}

void
move_along(object tp)
{
	// Check to make sure they're still here.
	if (!present(tp)) return;
	
	tp->catch_msg("The earth spits you out into  "
        +"a tunnel somewhere "
	    +"deep in the catacombs of Sybarus. OUCH!\n");
	// just a little damage from the fall
    tp->heal_hp(-(tp->query_max_hp() / 10));
    tp->move_living("M", CRYPT+"crypt"+(random(25)));
	// rooms 94-103

}	

// If player is here for too long, move them along.
void 
enter_inv(object ob, object from)
{
	
    ::enter_inv(ob, from);

    if(!interactive(ob)) return;

    set_alarm(20.0, 0.0, &move_along(ob));
	
}

