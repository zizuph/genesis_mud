// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/r10b.c
// creator(s):       Casca, 11/28/99
// revisions:        
// purpose:          
// note:             
// bug(s):           
// to-do:            


inherit "/d/Avenir/common/dark/darkl2_base.c";

#include "/d/Avenir/common/dark/dark.h"

void
create_tunnel_room()
{
    set_short("Cave");
    set_long("This is a small dark cave. All the surfaces are "+
        "blackened with aged soot. In the center of the room is "+
        "a charred skeleton.\nThere is a very unnatural sensation "+
        "hanging about this room.\n");

    add_exit("r10","south");


    /*
     * Put additional add_items below. 
     */

    add_cavern();

    add_item(({"skeleton","bones"}),"This is a skeleton of a winged wolf, "+
        "the bones are blackened and brittle as if they had been subjected "+
        "to extreme heat.\n");
    add_item(({"wall","walls"}),"The walls are smooth and blackened, the "+
        "result of being subjected to extreme heat.\n");
    add_item(({"floor","ground"}),"The floor is smooth in the center and "+
        "nearly glasslike in substance. Some event of great heat has taken "+
        "place in this cave.\n");
    add_item(({"ceiling","roof","above"}),"The ceiling has been blackened "+
        "with soot from a great fire.\n");
    add_tell("A low ghostly howl whispers through the cavern.\n");
    add_tell("You hear a low thump like that of flapping wings "+
        "and feel a soft blast of wind.\n");

    reset_tunnel_room();

}
