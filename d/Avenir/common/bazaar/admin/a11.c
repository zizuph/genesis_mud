// file name:        /d/Avenir/common/bazaar/admin/a11.c
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
    set_short("south-east corner, near south gatehouse");
    set_long("The trefoil fountain at the center of the square is "+
        "just northwest of you, and beyond it squats the green marble "+
        "Kestares building. Southwest is the Tribunal, pulsing red-"+
        "gold in the light of the Source. A gatehouse lies directly "+
        "east, on the south side of the Third Gate.\n");
    add_outside();
    add_sgate();
    add_exit(BAZ_ADMIN +"a8", "north",  0);
    add_exit(BAZ_ADMIN +"b9", "east", 0);
    add_exit(BAZ_ADMIN +"a14", "south", 0);
    add_exit(BAZ_ADMIN +"a10", "west", 0);
   
    /* There, but not obvious */
    add_exit(BAZ_ADMIN +"fount",  "northwest",  0, 1, 1);    
    add_exit(BAZ_ADMIN +"a13", "southwest",  0, 1, 1);       

    reset_admin_room();
}

