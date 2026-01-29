// file name:        /d/Avenir/common/bazaar/admin/b10.c
// creator(s):       Lilith, Sept 97
// revisions:        Lilith, Oct 2021
// purpose:
// note:
// bug(s):
// to-do:

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/bazaar/admin/admin_base";
inherit "/d/Avenir/inherit/sair_wall";

/* Include the local area defines, etc */
#include "/d/Avenir/common/bazaar/admin/admin.h"

/* Now create the room.  */
void
create_admin_room()
{
    set_short("gap in the foundation");
    set_long("This is a room in the foundation of the Questioning "+
        "place. It is more of a gap, really, a sheltered spot to "+
        "place tools or supplies. It appears to be forgotten though, "+
        "as it is empty except for grime.\n");    

    add_item(({"grime"}),
        "The stones of the foundation are covered in many years "+
        "worth of grime.\n");
    add_item(({ "wall", "walls", "foundation" }),
		"The walls of the foundation are made of flawed pieces "+
	    "of semi-precious stones like carnelian, agate, and marble.\n");
	
	add_sair_wall();
	set_sair_dest(({DEAD+"hill/cairn", OUTPOST +"fort4", 
        BAZAAR +"extr/centr"}));

    add_prop(ROOM_I_LIGHT, -3);
    add_exit(BAZ_ADMIN +"a19", "southeast", 0);
    add_exit(BAZ_ADMIN +"a19", "out",  0, 1, 1);
	
    reset_admin_room();
}

public void
init()
{
    ::init();
    sair_init();  
}