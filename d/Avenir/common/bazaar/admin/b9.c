// file name:        /d/Avenir/common/bazaar/admin/b9.c
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
    set_short("South gatehouse");
    set_long("The walls of this small gatehouse are made of the same "+
        "stone as the courtyard outside. It is small, with room for "+
        "just a few people to stand. There are regularly-spaced "+
        "slits in the walls.\n");    

    add_item(({"walls", "wall", "slit", "slits"}),
        "The slits look out onto various parts of the courtyard.\n");

    add_exit(BAZ_ADMIN +"a11", "west", 0);

    reset_admin_room();
}
