// file name:        /d/Avenir/common/bazaar/admin/a5.c
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
    set_short("Just north of the trefoil fountain");
    set_long("A fountain shimmers and murmurs south of here, and "+
        "beyond it glows a red-gold building. A slightly menacing "+
        "building lies to the west, and opposite it, across the "+
        "square, arches a large gate made of a dark, almost black "+
        "wood.\n");

    add_outside();

    add_exit(BAZ_ADMIN +"a1", "north",  0);
    add_exit(BAZ_ADMIN +"a6", "east", 0);
    add_exit(BAZ_ADMIN +"fount", "south", 0);
    add_exit(BAZ_ADMIN +"a4", "west", 0);
   
    /* There, but not obvious */
    add_exit(BAZ_ADMIN +"a3", "northeast",  0, 1, 1);    
    add_exit(BAZ_ADMIN +"a8", "southeast",  0, 1, 1);       
    add_exit(BAZ_ADMIN +"a2", "northwest",  0, 1, 1);    
    add_exit(BAZ_ADMIN +"a7", "southwest",  0, 1, 1);       

    reset_admin_room();
}
