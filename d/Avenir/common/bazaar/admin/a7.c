// file name:        /d/Avenir/common/bazaar/admin/a7.c
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
    set_short("Outside the Questioning Place, north of the entrance");
    set_long("A gate made of black wood arches in the east, above "+
        "the trefoil fountain which murmurs delightfully in the "+
        "center of the courtyard. South is the red-gold Tribunal "+
        "building, and northeast is the path leading toward the "+
        "museum and the bazaar.\n");
 
    add_outside();

    add_exit(BAZ_ADMIN +"a4", "north",  0);
    add_exit(BAZ_ADMIN +"fount", "east", 0);
    add_exit(BAZ_ADMIN +"a9", "south", 0);
   
    /* There, but not obvious */
    add_exit(BAZ_ADMIN +"a5", "northeast",  0, 1, 1);    
    add_exit(BAZ_ADMIN +"a10", "southeast",  0, 1, 1);       
    reset_admin_room();
}
