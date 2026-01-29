// file name: crypt112
// creator: Ilyian (September 1, 1995)
// last update:   Lilith & Zizuph, May-July 2021: finishing area for launch
// purpose: Room in the underground crypts
// note: Most of the code for these rooms is in
//         dead.c - see that file for info on these rooms.
// bug(s):
// to_do:

inherit "/d/Avenir/common/dead/crypt_base";
#include "../dead.h"

void
create_crypt_room()
{
	add_exit(CRYPT+"crypt113","down", 0, 10, 1);
	add_exit(CRYPT+"crypt111","up", 0, 20, 1);
    add_exit(CRYPT+"crypt111","climb", 0, 20, 1);
    set_short("wall of the pit of despair");
    set_long("You are clinging to the disgustingly slimy wall "
	    +"of a pit somewhere in the catacombs of Sybarus. "
		+"The stench is so unbelievably bad, you might as "
		+"well be climbing through an ogre's anus. "
		+"Up ahead the darkness is not as deep as the "
        +"miasma of despair emanating below."		
		+"\n");
		  
	add_prop(ROOM_S_DARK_MSG, "The darkness around you is much too "
        +"thick to");
    add_prop(ROOM_S_DARK_LONG, "The darkness here is thick "
        +"and oppressive. The stench is so bad you can feel "
		+"it clinging to your skin. The darkness seems "
		+"less deep above than below.\n");
		

    add_item(({"wall", "walls"}), "The wall is rough, "
		+"with jagged projections that you could use as "
		+"hand-holds to climb up out of here.");
    add_cmd_item(({"wall", "walls"}), "feel", "Disgusting! The wall "
        +"feels slick with slime or perhaps blood.\n");	
    add_item(({"dark","darkness","black","blackness","gloom"}),
        "Darkness is, by its nature, invisible.\n");
    add_item(({"floor","ground"}), "Floor? What floor? "
	    +"You are clinging for dear life to a slimy disgusting wall!.\n");
 	add_tell("Death. Despair. Fear. Overwhelming fear.");
    add_tell("Something moves underfoot. You find yourself hoping "
	    +"it is just a rat.");
    add_tell("Are you stuck here? Is this a death trap? Are you going to die here?!?");
    add_tell("Something vile splatters you from above.");
    add_tell("The stench is so bad you just might pass out.");	
 
 
    add_prop(ROOM_I_LIGHT, -5);
    reset_domain_room();
 }

void
reset_domain_room()
{
  set_searched(0);    ::reset_domain_room();
}
