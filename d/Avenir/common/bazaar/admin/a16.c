// file name:        /d/Avenir/common/bazaar/admin/a16.c
// creator(s):       Lilith, Oct 2002
// revisions:
// purpose:
// note:
// bug(s):
// to-do:

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/bazaar/admin/admin_base";

/* Include the local area defines, etc */
#include "/d/Avenir/common/bazaar/admin/admin.h"

//not using smis for this placement. 
static object gate;

/* Now create the room.  */
void
create_admin_room()
{
    set_short("on a gilded bridge between the Second and Third Gates");
    set_long("There is a definite sway here in the center of the "+
        "bridge between the Second and Third Gates. You struggle "+
        "to maintain your balance on the kesoit planks, some "+
        "instinct warning you not to brush against the golden "+
        "wires which form the sides of the bridge. "+
        "The air is filled with a glorious humming caused by thousands "+
        "of wires vibrating in the wind. Off to the west, the Third "+
        "Gate stands. ");   

    add_bridge();
    
    add_exit(BAZ_ADMIN +"a15", "west", 0);

    /* Place the second Gate */
    gate = clone_object(BAZAAR + "Obj/door/second_gate.c");
    gate->move(TO);  
    set_dircmd("east");  

    reset_admin_room();
}

