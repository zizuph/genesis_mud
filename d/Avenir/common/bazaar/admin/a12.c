// file name:        /d/Avenir/common/bazaar/admin/a12.c
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
    set_short("southwest corner of Tribunal Square");
    set_long("You stand in the southwest corner of the courtyard, "+
        "with the green marble Kestares building northwest, and "+
        "the Tribunal rising in the southeast. The trefoil fountain "+
        "splashes and glitters in the center of the square. There is "+
        "a small iron grille here.\n");

    add_outside();
    add_item(({"grille", "iron grille", "small iron grill"}),
        "It leads southwest into the gloomy darkness between "+
        "buildings. It is closed. It is locked.\n");
    add_item(({"lock" }), "You can't see the locking mechanism.\n");

    add_exit(BAZ_ADMIN +"a9", "north",  0);
    add_exit(BAZ_ADMIN +"a13", "east",  0);    
    
    /* There, but not obvious */
    add_exit(BAZ_ADMIN +"a10", "northeast",  0, 1, 1);    
   
    reset_admin_room();
}
