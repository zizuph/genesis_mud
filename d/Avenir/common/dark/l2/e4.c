// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/e4.c
// creator(s):       unknown
// revisions:        Casca, 11/25/99
// purpose:          
// note:             
// bug(s):           
// to-do:            

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/dark/darkl2_base.c";

/* Include the local area defines, etc */
#include "/d/Avenir/common/dark/dark.h"  


/* Now create the room.  */
void
create_tunnel_room()
{
    set_short("Foremans quarters");
    set_long("These quarters are much better appointed than those to "+
        "to the northeast undoubtedly this is the domain of people "+
        "with more importance. "+
        "A bronze brazier provides enough light and warmth "+
        "to make this room comfortable. Three "+
        "bedrolls are laid out on the smoother sections of the "+
        "floor.\n");

    add_exit("e3","northeast");

    LIGHT

    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    add_item("brazier",
        "Three simple iron rods form a tripod that supports "+
        "a wrought iron pot full of hot coals.\n");
    add_item(({"bed","beds","bedroll","bedrolls"}),
        "Three bedrolls are arranged on the few smooth "+
        "sections of the floor. The are well padded and "+
        "look comfortable.\n");

    reset_tunnel_room();
}
