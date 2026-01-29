// file name:        /d/Avenir/common/bazaar/admin/b1.c
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
    set_short("North entrance of Kestares");
    set_long("The walls of this room are bare green-marble blocks. "+
        "The floor is smooth and dark, as is the table in the center "+
        "of the room. Two chairs face each other across the gleaming "+
        "surface.\n");

    add_inside_inquis();

    add_exit(BAZ_ADMIN +"b2", "south", 0);
    add_exit(BAZ_ADMIN +"a2", "east",  0);    

    reset_admin_room();
}
