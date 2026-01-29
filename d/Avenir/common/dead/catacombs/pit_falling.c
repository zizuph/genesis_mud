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
    set_short("falling through the ground");

    set_long("You can see nothing in the blackness all around, "
      +"oppressive and deeply distressing. The "
      +"scent of moist earth fills your nose, and you experience "
      +"a prolonged sensation of falling"
      +".\n");
    add_prop(ROOM_S_DARK_MSG, "The darkness around you is much too "
      +"thick to");
    add_prop(ROOM_S_DARK_LONG, "Darkness presses upon you "
      +"from all directions. The scent of moist earth fills "
      +"fills your nose and you feel like you are falling.\n");

    add_item(({"ground", "dirt", "soil"}),
      "It is damp, and rich with the scent of decay.\n");	
    // Swallowed by earth, the darkness is deep.
    add_prop(ROOM_I_LIGHT, -10);

    // In the event mortal doesn't get moved out of here
    // Lets give them some exits with high fatigue cost
	// because its exhausting trying to move through dirt.
    add_exit(CRYPT+"pit_of_despair","down", 0, 50, 0);	
    add_exit(CRYPT+"pit_fell","out", 0, 20, 1);	
}

/*
*   Drop the player into the crypt.
*   This is gonna hurt...
*   but at least it won't kill them.
*/
void
move_along(object tp)
{
	if (!present(tp))	return;
	
    tp->catch_msg("You finally land with a painful "
      +"thud on a lumpy, slimy, sticky floor. OUCH!\n "
      +"An oppressive feeling of terror floods your being."
      +"\n");
    tp->add_panic(50);
    tp->move_living("M", CRYPT+"pit_of_despair", 0 , 1);
    
}	

// If player is here for too long, move them along.
void 
enter_inv(object ob, object from)
{

    ::enter_inv(ob, from);

    if(!interactive(ob)) return;
	
    set_alarm(10.0, 0.0, &move_along(ob));

}

