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
    set_short("platform in a pit");

    set_long("You can see nothing in the blackness surrounding "
      +"you, but by the feel of things it seems like you are on "
      +"small platform projecting up from somewhere. "
	  +"There is nothing but empty air in every "
	  +"direction. It smells really, really, really bad here."
      +".\n");
    add_prop(ROOM_S_DARK_MSG, "The darkness around you is much too "
      +"thick to");
    add_prop(ROOM_S_DARK_LONG, "Darkness presses upon you "
      +"from all directions. The stink makes you want to "
	  +"puke. Your only way out of here is down.");
    add_item(({"ground", "platform"}),
        "You can't see it, but by feel it seems to be made of stone "
		+"and roughly the size of a dinner table or door.\n");	
    // Swallowed by earth, the darkness is deep.
	add_prop(ROOM_I_LIGHT, -20);

    // In the event mortal doesn't get moved out of here
    // Lets give them some exits
    add_exit(CRYPT+"pit_of_despair","down", 0, 10, 1);	
	
}

void
move_along(object tp)
{
	// Check to make sure they're still here.
	if (!present(tp)) return;
	
	tp->catch_msg("You lose your balance and fall the "
	   +"rest of the way down into a pit. OUCH!\n");

    tp->add_panic(50);
    tp->move_living("M", CRYPT+"pit_of_despair", 0 , 1);
 
}	

// If player is here for too long, move them along.
void 
enter_inv(object ob, object from)
{
	
    ::enter_inv(ob, from);

    if(!interactive(ob)) return;

    set_alarm(20.0, 0.0, &move_along(ob));
	
}

