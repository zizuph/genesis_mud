// file name:        /d/Avenir/common/bazaar/admin/a15.c
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
    set_short("Near the Third Gate");
    set_long("A bridge begins here, a bridge like no other you have seen. "+
        "It is a long gilded tunnel broad enough for six men to stand "+
        "abreast. The bars are thick as your wrist, interwoven with "+
        "smaller golden wires to form a grid whose largest opening "+
        "would admit nothing larger than a clenched fist. Planks of "+
        "kesoit wood gleam in the light of the Source, their fragrance "+
        "carried to you by the brisk wind that has set the bridge "+
        "to swaying gently. West, the Third Gate stands, while east "+
        "the bridge leads toward the distant walls of the Forbidden "+
        "City.\n");

    add_exit(BAZ_ADMIN +"a16", "east", 0);

    add_bridge();
   
    /* Place the third Gate */
    gate = clone_object(BAZAAR + "Obj/door/third_gate2.c");
    gate->move(TO);  
    set_dircmd("west");  

    reset_admin_room();
}

