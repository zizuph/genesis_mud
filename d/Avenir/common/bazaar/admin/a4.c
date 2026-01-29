// file name:        /d/Avenir/common/bazaar/admin/a4.c
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

/* Now create the room. */
void
create_admin_room()
{
    set_short("Outside the Questioning Place.");
    set_long("Alongside the low green marble building known as "+
        "the Questioning Place. There are entrances north and "+
        "south of here. Beyond the shimmering gold trefoil "+
        "fountain is a red-gold building. East arches a large "+
        "wood gate.\n");

    add_outside();

    add_exit(BAZ_ADMIN +"a2", "north",  0);
    add_exit(BAZ_ADMIN +"a5", "east", 0);
    add_exit(BAZ_ADMIN +"a7", "south", 0);
   
    /* There, but not obvious */
    add_exit(BAZ_ADMIN +"a1", "northeast",  0, 1, 1);    
    add_exit(BAZ_ADMIN +"fount", "southeast",  0, 1, 1);       
    reset_admin_room();
}
