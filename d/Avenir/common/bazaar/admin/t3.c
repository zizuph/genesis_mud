// file name:        /d/Avenir/common/bazaar/admin/t3.c
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
    set_short("Second (south) tribunal room");
    set_long("This is the Second Tribunal Room. It is dominated by "+
        "a large, throne-like chair. Directly across from it is "+
        "a post to which prisoners are chained while waiting for "+
        "the adjudicator to pronounce sentence.\n");

    add_inside_tribunal();

    add_exit(BAZ_ADMIN +"t1", "north", 0);
    reset_admin_room();
}
