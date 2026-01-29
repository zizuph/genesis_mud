// file name:        /d/Avenir/common/bazaar/admin/a19.c
// creator(s):       Lilith, Nov 2021
// revisions:
// purpose:
// note:
// bug(s):
// to-do:

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/bazaar/admin/admin_base";

/* Include the local area defines, etc */
#include "/d/Avenir/common/bazaar/admin/admin.h"

/* Now create the room.  */
void
create_admin_room()
{
    set_short("southwest of Tribunal Square");
    set_long("This is a narrow street southwest of Tribunal Square. "+  
        "It is a bit gloomy here, where the path leads into the "+
        "shadows between the Questioning place and the Tribunal building. "+
		"The sounds of water splashing in a fountain can be heard beyond "+
		"the small iron gate northeast.\n");

    add_outside();
    add_item(({"grille", "gate", "iron grille", "iron gate"}),
        "It leads northeast into the Tribunal Square. It is swung wide open.\n");
    add_item(({"lock" }), "You can't see the locking mechanism.\n");

//    add_tell("You can hear a moan coming from nearby.");
	
    add_exit(BAZ_ADMIN +"a12", "northeast",  0);
    add_exit(BAZ_ADMIN +"a20", "southwest",  0);    
    
    /* There, but not obvious */
    add_exit(BAZ_ADMIN +"b10", "northwest",  0, 1, 1);    
    add_exit(BAZ_ADMIN +"b10", "in",  0, 1, 1);    
   
    reset_admin_room();
}
