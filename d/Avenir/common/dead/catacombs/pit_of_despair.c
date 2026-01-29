// file name: falling
// creator(s): Lilith July 2021
// last update:   Lilith & Zizuph, May-July 2021: finishing area for launch
// purpose: If a player lands in here its because they 
//          did something blasphemous in Sybarus
//          and the gods have tossed them down here.
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/common/dead/crypt_base";
#include "../dead.h"

void
create_crypt_room()
{

	add_exit(CRYPT+"crypt114","up", 0, 20);
    add_exit(CRYPT+"crypt114", "climb", 0, 20, 1);	
    set_short("bottom of the pit of despair");
    set_long("You are deep in a stinking pit somewhere far below "
	    +"the surface of the Isle of the Dead. You can just make "
        +"out a wall in a blackness so dense that it absorbs nearly "
        +"all light. Bones crunch under your feet, and by the smell "
        +"a decaying corpse or two as well. This is a place "
		+"where hope dies and despair thrives. You feel an "
		+"overwhelming need to climb up out of here, lest "
		+"you remain here forever.\n");
		  
	add_prop(ROOM_S_DARK_MSG, "The darkness around you is much too "
        +"thick to");
    add_prop(ROOM_S_DARK_LONG, "The darkness here is thick "
        +"and oppressive. The stench is so bad you can feel "
		+"it clinging to your skin. Some bones crunch under "
        +"your feet. Dread and despair weigh heavily upon "
		+"your spirit.\n");

    add_item(({"wall", "walls"}), "The wall is rough, "
		+"with jagged projections that you could use as "
		+"hand-holds to climb up out of here.");
    add_cmd_item(({"wall", "walls"}), "feel", "Disgusting! The wall "
        +"feels slick with slime or perhaps blood.\n");	
    add_item(({"dark","darkness","black","blackness","gloom"}),
        "Darkness is, by its nature, invisible.\n");
    add_item(({"floor","ground"}),"The floor is uneven, "
        +"dark, and damp, making footing treacherous.\n");
	
 	add_tell("Death. Despair. Fear. Overwhelming fear.");
    add_tell("Something moves underfoot. You find yourself hoping "
	    +"it is just a rat.");
    add_tell("Are you stuck here? Is this a death trap? Are you going to die here?!?");
    add_tell("Something vile splatters you from above.");
    add_tell("The stench is so bad you just might pass out.");	
    add_prop(ROOM_I_LIGHT, -10);	
	
    reset_domain_room();

}

void
reset_domain_room()
{
   ::reset_domain_room();
}

