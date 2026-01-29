// file name:      /d/Genesis/hannah/galanos/guilds/angel/tower/01.c
// creator(s):       Hannah, 10/99
// revisions:
// purpose:
// note:           
// bug(s):
// to-do:

/* Inherit the room that is the base for the area. */
inherit "/std/room.c";

/* Include the local area defines, etc */
#include "/d/Genesis/hannah/galanos/guilds/angel/tower/defs.h"  

/* Now create the room.  */
void
create_room()
{
    set_short("Ephemeridae Tower");
    set_long("This tower is dedicated to "+
        "the best friend I ever had.\n"); 
        
    add_exit(FI_DIR + "23", "west", 0);
    add_exit(FI_DIR + "32", "northeast", 0);
    add_exit(FI_DIR + "25", "southeast", 0);

    /* Air, cobbles, source, and hedges added from the base room, 
     * put additional add_items below. 
     */

    reset_room();
}
