// file name:        /d/Avenir/common/bazaar/admin/a1.c
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
    set_short("north end of a courtyard");
    set_long("You stand at the north end of a broad courtyard which "+
        "extends south, beyond a golden fountain, to a collonaded "+
        "building that glows red-gold in the light of the Source. "+
        "West is a long, low building of green marble, and opposite "+
        "it is a high arch with heavy wood doors.\n");
    add_outside();

    add_exit(BAZAAR +"extr/str26", "north", 0);
    add_exit(BAZ_ADMIN +"a3", "east",  0);    
    add_exit(BAZ_ADMIN +"a5", "south", 0);
    add_exit(BAZ_ADMIN +"a2", "west",  0);    

    /* There, but not obvious */
    add_exit(BAZ_ADMIN +"a6", "southeast",  0, 1, 1);    
    add_exit(BAZ_ADMIN +"a4", "southwest",  0, 1, 1);    
   
    reset_admin_room();
}
