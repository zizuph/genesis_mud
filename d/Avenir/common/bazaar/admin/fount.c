// file name:        /d/Avenir/common/bazaar/admin/fount.c
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
    set_short("fountain in the shape of a trefoil");
    set_long("You stand before the trefoil-shaped fountain at the "+
        "center of the "+
        "courtyard.\nSouth, the tribunal building rises, its red-"+
        "gold stone glowing in the light of the Source. The Third "+
        "Gate to the Forbidden City, closed and barred, lies east. "+
        "West is a long, low green-marble building.\n");

    add_outside();
    add_prop(ROOM_I_TYPE, ROOM_BEACH);

    add_exit(BAZ_ADMIN +"a6", "northeast",  0);    
    add_exit(BAZ_ADMIN +"a11", "southeast", 0);       
    add_exit(BAZ_ADMIN +"a4", "northwest",  0);    
    add_exit(BAZ_ADMIN +"a9", "southwest",  0);       

    /* There, but not obvious */
    add_exit(BAZ_ADMIN +"a5", "north",  0, 1, 1);
    add_exit(BAZ_ADMIN +"a8", "east", 0, 1, 1);
    add_exit(BAZ_ADMIN +"a10", "south", 0, 1, 1);
    add_exit(BAZ_ADMIN +"a7", "west", 0, 1, 1);

    reset_admin_room();
}
