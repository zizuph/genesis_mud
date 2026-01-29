// file name:        /d/Avenir/common/bazaar/admin/a14.c
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
    set_short("southeast corner of Tribunal Square");
    set_long("This is the southeast corner of the courtyard. The "+
       "arching Third Gate rises to the north, a small gatehouse "+
       "beside it. Trefoil fountain shimmers northwest of here, "+
       "and beyond it lies the Kestares Building.\n");

    add_outside();
    add_sgate();

    add_exit(BAZ_ADMIN +"a11", "north",  0);
    add_exit(BAZ_ADMIN +"a13", "west", 0);
   
    /* There, but not obvious */
    add_exit(BAZ_ADMIN +"a10",  "northwest",  0, 1, 1);    

    reset_admin_room();
}

