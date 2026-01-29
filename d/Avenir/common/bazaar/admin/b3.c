// file name:        /d/Avenir/common/bazaar/admin/b3.c
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
    set_short("Questioning room");
    set_long("This questioning room is very dark, leaving you "+
        "uncertain of its dimensions. A chill rises from the "+
        "stone floor, and a low, barely audible sound seems "+
        "to float, disembodied, through the room, raising the hair "+
        "on the back of your neck. There is a table here, and "+
        "two chairs, one of which has various leather straps "+
        "attached.\n");

    add_inside_inquis();
    add_exit(BAZ_ADMIN +"b2", "east",  0);    
    reset_admin_room();
}
