// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/ut2.c
// creator(s):       Cirion, July 1996
// revisions:        Casca, 11/24/99
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
    set_short("smooth tunnel");
    set_long("The tunnel turns from the north to the "+
        "southeast here. Shadows seem to play along the "+
        "smooth walls, and your footfalls pad on the "+
        "ground with utter silence.\n");

    add_exit("ut3","north");
    add_exit("ut1","southeast");

    /*
     * Put additional add_items below. 
     */

    add_w_tunnel();

    add_item(({"floor","ground"}),"The floor here is perfectly level "+
        "and smooth. Whoever carved it from the stone took extra care "+
        "to ensure its perfection. "+
        "Shadows flicker along the ground from some unseen source.\n");
    add_tell("Shadows seem to writhe and twist in the corner of your eye.");

    reset_tunnel_room();
}
