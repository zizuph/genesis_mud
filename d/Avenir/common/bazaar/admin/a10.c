// file name:        /d/Avenir/common/bazaar/admin/a10.c
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
    set_short("south of the fountain at center of courtyard");
    set_long("You stand near the center of this large courtyard, "+
        "just south of the large, musical fountain opposite "+
        "the arched gate. East is a small gatehouse, and due "+
        "south lies the entrance to a glowing red-gold building.\n");

    add_outside();
    add_sgate();

    add_exit(BAZ_ADMIN +"fount", "north",  0);
    add_exit(BAZ_ADMIN +"a11", "east", 0);
    add_exit(BAZ_ADMIN +"a13", "south", 0);
    add_exit(BAZ_ADMIN +"a9", "west", 0);
   
    /* There, but not obvious */
    add_exit(BAZ_ADMIN +"a8", "northeast",  0, 1, 1);    
    add_exit(BAZ_ADMIN +"a14", "southeast",  0, 1, 1);       
    add_exit(BAZ_ADMIN +"a7", "northwest",  0, 1, 1);    
    add_exit(BAZ_ADMIN +"a12", "southwest",  0, 1, 1);       

    reset_admin_room();
}
