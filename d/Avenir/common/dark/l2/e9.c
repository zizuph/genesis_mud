// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/e9.c
// creator(s):       unknown
// revisions:        Casca, 11/25/99
// purpose:          Connects to l2/add/t50.c         
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
    set_short("Chamber of dwarven statues");
    set_long("This appears to be a rather ancient chamber. "+
        "Although originally a natural cavern someone has worked "+
        "the walls and floor to smoother more level surfaces. "+
        "Spaced along the walls are ancient worn statues carved "+
        "directly from the walls of the chamber. In the center "+
        "of the floor is a shallow depression.\n");

    add_exit(L1 + "stair3", "up");
    add_exit("e7","southwest");
    add_exit("add/t50","east"); 

    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    add_item(({"figure","figures","statues","statue","stone figures",
        "stone figure","stone statue","stone statues"}),"The stone figures "+
        "are carved directly into the rock of the wall itself, a piece of "+
        "fine craftsmanship.  They appear to be dwarves, though you cannot "+
        "recognize any of the figures.\n");

    add_item(({"stair", "stairway", "stairwell", "steps"}),
        "The steps look almost natural as they lead upward into "+
        "darkness. If your eyes weren't so well-accustomed to "+
        "the dimness, you might have missed them.\n");

    add_item(({"depression", "hole"}),
        "This is a shallow concave depression in the center of the room. "+
        "Its about an arms length across and a hands width deep at its deepest. "+
        "Around the perimeter of the bowl is eight slots. "+
        "The floor near the depression has been smoothed, either intentionally "+
        "or by time and use.\n");

    add_item(({"slot","slots","holes"}),"Eight slots ring the perimeter of the "+
        "depression. They are each three finger widths square and a hands width "+
        "deep. Several of them have pieces of rusted metal filling them.\n");

    reset_tunnel_room();
}

