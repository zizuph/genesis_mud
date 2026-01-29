// file name:   crypt114
// creator:     Lilith July 2021
// last update:   Lilith & Zizuph, May-July 2021: finishing area for launch
// purpose:     Room in the underground crypts
// note:        Most of the code for these rooms is in
//              dead.c - see that file for info on these rooms.
// bug(s):
// to_do:

inherit "/d/Avenir/common/dead/dead";
#include "../dead.h"

void
create_room()
{
    add_exit(CRYPT+"pit_of_despair","down", 0, 10, 1);
	add_exit(CRYPT+"crypt113","up", 0, 20, 1);

    set_short("wall of the pit of despair");
    set_long("You are clinging to the wall near the bottom "
	    +"of a deep pit somewhere in the catacombs of Sybarus. "
		+"The stench wafting up from below smells like a mass  "
		+"grave was converted into the latrine for an army. "
		+"Up ahead the the darkness is not as deep as the "
        +"miasma of despair emanating below. You feel an "
        +"urgent need to climb up out of here."		
		+"\n");
		  
	add_prop(ROOM_S_DARK_MSG, "The darkness around you is much too "
        +"thick to");
    add_prop(ROOM_S_DARK_LONG, "The darkness here is thick "
        +"and oppressive. The stench is so bad you can feel "
		+"it clinging to your skin. The darkness seems "
		+"less deep above you.\n");
 
 
    add_item(({"wall", "walls"}), "The wall is rough, "
		+"with jagged projections that you could use as "
		+"hand-holds to climb up out of here.");
    add_cmd_item(({"wall", "walls"}), "feel" ,"Disgusting! The wall "
        +"feels slick with slime or perhaps blood.\n");	
    add_item(({"dark","darkness","black","blackness","gloom"}),
        "Darkness is, by its nature, invisible.\n");
    add_item(({"floor","ground"}), "Floor? What floor? "
	    +"You are clinging for your life to a slimy disgusting wall!.\n");
 	add_tell("Death. Despair. Fear. Overwhelming fear.");
    add_tell("Something moves underfoot. You find yourself hoping "
	    +"it is just a rat.");
    add_tell("Are you stuck here? Is this a death trap? Are you going to die here?!?");
    add_tell("Something vile splatters you from above.");
    add_tell("The stench is so bad you just might pass out.");	
 
    add_prop(ROOM_I_LIGHT, -6);
    reset_room();
 }

void
reset_room()
{
  set_searched(0);   crypt_reset();
}
