// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/ut3.c
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
    set_short("dark tunnel");
    set_long("Stretching north and south into identical "+
        "pools of gloaming darkness, the tunnel rises high "+
        "like some menacing hand overhead.\n");

    add_exit("ut4","north");
    add_exit("ut2","south");

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
