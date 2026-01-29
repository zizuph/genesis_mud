
inherit "/d/Rhovanion/lib/room";

#include "/d/Rhovanion/farlong.h"

reset_room()
{
    if(!present("_sw_quest_hag"))
	clone_object(RHUN+"npc/hag")->move(TO, 1);
}

create_room()
{
    reset_euid();
    
    set_short("In a corner");
    set_long("You find yourself in a small, damp corner in the "+
	"ruins.  Walls of dirty-white stone surround this area in "+
	"a circular fashion, almost partitioning it off from the "+
	"rest of these ruins.  It also appears as though someone "+
	"might have lived here for a time.  The only exit is back "+
	"toward the center of the ruins, to the northeast.\n");
    
    AE(RHUN+"ruins/to_hag", "northeast");

    add_item(({"wall", "walls", "stone"}), "The walls, though "+
	"quite old and crumbled, still stand well enough to shelter "+
	"this area, surrounding it in a circular fashion, as though "+
	"at the bottom of some narrow round tower which once stretched "+
	"upward to touch the sky.\n");
    
    reset_room();
}
