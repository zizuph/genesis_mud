// file name:        /d/Avenir/common/bazaar/admin/a2.c
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
    set_short("Northwest corner of courtyard, near door to Kestares");
    set_long("You stand outside the north entrance of the low green "+
        "marble building. The golden fountain in the center of the "+
        "courtyard murmers and shimmers, and beyond it, there rises "+
        "a large arching wood gate. The Tribunal building glows red-"+
        "gold in the south.\n");
    add_outside();
    add_exit(BAZ_ADMIN +"b1", "west",  0);
    add_exit(BAZ_ADMIN +"a4", "south", 0);
    add_exit(BAZ_ADMIN +"a1", "east",  0);    

    /* There, but not obvious */
    add_exit(BAZ_ADMIN +"a5", "southeast",  0, 1, 1);    
   
    reset_admin_room();
}
