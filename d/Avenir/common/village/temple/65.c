// file name:        /d/Avenir/common/village/pale/temple/
// creator(s):       Avenir Wizards, 03/01
// revisions:
// purpose:
// note:           
// bug(s):
// to-do:

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/village/temple_base.c";

/* Include the local area defines, etc */
#include "/d/Avenir/common/village/village.h"  

/* Now create the room.  */
void
create_temple_room()
{
    set_short("Death");
    set_long("This is a cobbled walk bordered on both sides by "+
        "tall hedges. The air is laden with moisture that "+
        "glistens upon every surface, from the smallest of "+
        "leaves to the moss which thrives in the seams "+
        "between the cobbles. Through the easterly hedges the "+
        "scent of food from the merchantile pale drifts. "+
        "There is a large intersection southwest.\n");




    add_exit("64", "north", 0);
   

    /* Air, cobbles, source, and hedges added from the base room, 
     * put additional add_items below. 
     */

    reset_domain_room();
}
