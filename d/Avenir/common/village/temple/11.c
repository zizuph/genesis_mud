// file name:        /d/Avenir/common/village/pale/temple/
// creator(s):       Avenir Wizards, 03/01
// revisions:
// purpose:
// note:             Sair and Salilus's Altar's are here.
// bug(s):
// to-do:

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/village/temple_base.c";

/* Include the local area defines, etc */
#include "/d/Avenir/common/village/village.h"  

object altar;

void
reset_domain_room()
{
    if (!altar)
    {
        altar = clone_object("/d/Avenir/common/gods/altar/buc_altar");   
        altar->move(this_object());
    }
}


/* Now create the room.  */
void
create_temple_room()
{
    set_short("1st Hour");
    set_long("This is a cobbled walk bordered on both sides by "+
        "tall hedges. The air is laden with moisture that "+
        "glistens upon every surface, from the smallest of "+
        "leaves to the moss which thrives in the seams "+
        "between the cobbles. Through the easterly hedges the "+
        "scent of food from the merchantile pale drifts. "+
        "There is a large intersection southwest.\n");




    add_exit("08", "southwest", 0);
   

    /* Air, cobbles, source, and hedges added from the base room, 
     * put additional add_items below. 
     */

    reset_domain_room();
}
