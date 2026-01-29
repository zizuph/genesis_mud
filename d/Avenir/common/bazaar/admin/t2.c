// file name:        /d/Avenir/common/bazaar/admin/t2.c
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
    set_short("First (southwest) tribunal room");
    set_long("This is First Tribunal Room. Here, those who have failed "+
        "to prove their innocence to the inquisitors face the adju"+
        "dicators for pronouncing of sentence. A throne-like chair "+
        "dominates the room, the only furnishing besides a post "+
        "to which prisoners are chained.\n");
   
    add_inside_tribunal();

    add_exit(BAZ_ADMIN +"t1", "northeast", 0);
    reset_admin_room();
}
