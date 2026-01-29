// file name:        /d/Avenir/common/bazaar/admin/a17.c
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
    set_short("on a gilded bridge between the First and Second Gates");
    set_long("There is a definite sway here in the center of the "+
        "bridge between the First and Second Gates. You struggle "+
        "to maintain your balance on the kesoit planks, some "+
        "instinct warning you not to brush against the golden "+
        "wires which form the sides of the bridge. "+
        "The air is filled with a glorious humming caused by thousands "+
        "of wires vibrating in the wind. Just west is the portcullis "+
        "known as the Second Gate, while to the southeast the chalcedony "+
        "walls of the Forbidden City can be seen.\n");   

    add_bridge();

    add_exit(BAZ_ADMIN +"a18", "southeast", 0);

    /* Place the second Gate */
    gate = clone_object(BAZAAR + "Obj/door/second_gate2.c");
    gate->move(TO);  
    set_dircmd("west");  

    reset_admin_room();
}

