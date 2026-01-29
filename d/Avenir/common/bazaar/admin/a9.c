// file name:        /d/Avenir/common/bazaar/admin/a9.c
// creator(s):       Lilith, Sept 97
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
    set_short("Just outside the south entrance of Kestares");
    set_long("The south door to the Questioning Place, a low "+
        "green marble building. You can see the trefoil fountain "+
        "shimmering east of here, and beyond it, the dark Third "+
        "Gate arches. South, the red-gold Tribunal building domin"+
        "ates the courtyard.\n");
    add_outside();
    add_exit(BAZ_ADMIN +"a7", "north",  0);
    add_exit(BAZ_ADMIN +"b7", "west",  0);
    add_exit(BAZ_ADMIN +"a12", "south", 0);
    add_exit(BAZ_ADMIN +"a10", "east",  0);    

    /* There, but not obvious */
    add_exit(BAZ_ADMIN +"fount", "northeast",  0, 1, 1);    
    add_exit(BAZ_ADMIN +"a13", "southeast",  0, 1, 1);    
    reset_admin_room();
}
