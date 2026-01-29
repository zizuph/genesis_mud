// file name:        /d/Avenir/common/bazaar/admin/a6.c
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
    set_short("just west of a gatehouse");
    set_long("You stand near the arching Third Gate, outside a "+
        "small gatehouse. The trefoil fountain murmurs south"+
        "west of you, its water catching glow from the red-gold "+
        "building beyond. Directly across the square is the "+
        "low green marble building known as the Questioning "+
        "Place.\n");

    add_outside();
    add_ngate();

    add_exit(BAZ_ADMIN +"a3", "north",  0);
    add_exit(BAZ_ADMIN +"b8", "east", 0);
    add_exit(BAZ_ADMIN +"a8", "south", 0);
    add_exit(BAZ_ADMIN +"a5", "west", 0);
   
    /* There, but not obvious */
    add_exit(BAZ_ADMIN +"a1", "northwest",  0, 1, 1);    
    add_exit(BAZ_ADMIN +"fount", "southwest",  0, 1, 1);       

    reset_admin_room();
}
