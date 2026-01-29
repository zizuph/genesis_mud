// file name:        /d/Avenir/common/bazaar/admin/a13.c
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
    set_short("Just outside the Tribunal");
    set_long("You stand just outside the Tribunal building. Up close, "+
        "it no longer seems to glow, and you can clearly see the "+
        "veins of gold snaking through this reddish stone. The tre"+
        "foil fountain is due north, Third Gate is east, and the low, "+
        "green marble building is west.\n");

    add_outside();

    add_exit(BAZ_ADMIN +"a10", "north",  0);
    add_exit(BAZ_ADMIN +"a14", "east", 0);
    add_exit(BAZ_ADMIN +"t1", "south", 0);
    add_exit(BAZ_ADMIN +"a12", "west", 0);
   
    /* There, but not obvious */
    add_exit(BAZ_ADMIN +"a11", "northeast",  0, 1, 1);    
    add_exit(BAZ_ADMIN +"a9", "northwest",  0, 1, 1);    

    reset_admin_room();
}
