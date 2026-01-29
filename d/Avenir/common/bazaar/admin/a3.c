// file name:        /d/Avenir/common/bazaar/admin/a3.c
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
    set_short("northeast corner of the courtyard");
    set_long("There is a lovely fountain in the center of the "+
        "courtyard which shimmers and murmurs to the delight "+
        "of eyes and ears. A gate arches high in the east, and "+
        "alongside it is a small gatehouse. A building glows red-"+
        "gold in the southern end of the square.\n");
    add_outside();

    add_exit(BAZ_ADMIN +"a1", "west",  0);
    add_exit(BAZ_ADMIN +"a6", "south", 0);
    add_exit("/d/Avenir/registry/relate", "north", 0);

    /* There, but not obvious */
    add_exit(BAZ_ADMIN +"a5", "southwest",  0, 1, 1);    
   
    reset_admin_room();
}
