// file name:  /d/Genesis/hannah/galanos/guilds/angel/tower/basement/10.c
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
    set_short("Catacombs");
    set_long("An eye for his eyes."+
        "These dark caverns hold the secrets of the dead.\n"); 
        
    add_exit(BA_DIR + "04", "northeast", 0);
    add_exit(BA_DIR + "06", "northwest", 0);
    add_exit(BA_DIR + "02", "southeast", 0);
    add_exit(BA_DIR + "08", "southwest", 0);

    /* Air, cobbles, source, and hedges added from the base room, 
     * put additional add_items below. 
     */

    reset_room();
}
