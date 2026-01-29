// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/ut5.c
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
    set_long("Running level to the east in an eerie darkness, "+
        "the tunnel rises steeply to the southwest. The air feels "+
        "warm and oppressive, and a gentle draft seems to come from "+
        "the east.\n");

    add_exit(UNION + "room/entry","east");
    add_exit("ut4","southwest");

    /*
     * Put additional add_items below. 
     */

    add_w_tunnel();

    add_item(({"floor","ground"}),"The floor here is perfectly level "+
        "and smooth. Whoever carved it from the stone took extra care "+
        "to ensure its perfection. "+
        "Shadows flicker along the ground from some unseen source.\n");
    add_tell("Shadows seem to writhe and twist in the "
        +"corner of your eye.\n");

    reset_tunnel_room();
}


