// file name:        /d/Avenir/common/bazaar/admin/b2.c
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
    set_short("A dark passageway");
    set_long("You stand inside Kestares, the Questioning Place. Here, "+
        "those unfortunate enough to come to the attention of the "+
        "Inquisitors undergo preliminary questioning. A chill rises "+
        "from the stone floor, and a low, barely audible sound seems "+
        "to float, disembodied, through the room, raising the hair "+
        "on the back of your neck.\n");

    add_inside_inquis();

    add_exit(BAZ_ADMIN +"b6", "south", 0);
    add_exit(BAZ_ADMIN +"b3", "west",  0);    
    add_exit(BAZ_ADMIN +"b1", "north",  0);    
    reset_admin_room();
}
