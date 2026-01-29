// file name:        /d/Avenir/common/bazaar/admin/t1.c
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
    set_short("Inside the Tribunal");
    set_long("The walls and floor of this long hall are made of "+
        "the same stone as the exterior of the building. The gold "+
        "veins in the stone have a muted glitter which catches the "+
        "eye without glare. The north exit leads back out into the "+
        "courtyard, while the other exits open onto three different "+
        "tribunal rooms.\n");
    add_inside_tribunal();
    add_exit(BAZ_ADMIN +"a13", "north", 0);
    add_exit(BAZ_ADMIN +"t2", "southwest", 0);
    add_exit(BAZ_ADMIN +"t3", "south", 0);
    add_exit(BAZ_ADMIN +"t4", "southeast", 0);

    reset_admin_room();
}
