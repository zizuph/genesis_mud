/*
 * File:          /d/Avenir/common/dark/submissions/a_long,_dark_tunnel.c
 * Creator:       Cirion
 * Date:          Wed Jun  3 14:44:50 1998
 * Note:          This room was auto-generated using
 *                the room creator module inherited by
 *                /d/Avenir/common/dark/mon/foreman#57576
 * Comments:      
 *                This is a test room for the Utterdark, to see
 *                if the room creation module is working here.
 */
#include "defs.h"
inherit "/std/room";

void
create_room ()
{
    set_short("a long, dark tunnel");
    set_long("This long tunnel descends steeply into the gloom, "
        + "its rocky floor slippery underfoot. The ceiling "
        + "of the tunnel is veiled in gloom, from where you "
        + "can hear tiny creatures moving about.\n");

    add_item(({"floor","ground"}),
        "The floor of the tunnel is made from very smooth "
        + "stone, and it descends down the the northeast.\n");
    add_item(({"wall","walls"}),
        "The walls are craggy, and contain many cracks.\n");
    add_item(({"crack","cracks"}),
        "The cracks are all a heair's breadth, and run all "
        + "along the walls in a chaotic pattern.\n");
    add_item(({"ceiling","up","above"}),
        "The ceiling is veiled in gloom.\n");
    add_item(({"dark","darkness","gloom"}),
        "You cannot make out anything within it.\n");
    add_item(({"down","northeast"}),
        "The tunnel slants down to the northeast.\n");
    add_item(({"stone"}),
        "The stone of the floor is very smooth, in stark "
        + "contrast to the craggy, uneven walls.\n");
    add_item(({"descent"}),
        "It makes you fear for your footing.\n");
    add_item(({"descent"}),
        "It makes you fear for your footing.\n");
    add_item(({"descent"}),
        "It makes you fear for your footing.\n");
    add_cmd_item(({"sound","sounds","creatures","to creatures"}),
        ({"listen","hear"}),
        "The noises are very faint. They sound alomst like "
        + "a myrias spiders moving about very quickly.\n");
    add_cmd_item(({"floor","ground"}),
        ({"touch","feel"}),
        "The floor is very smooth, almost slippery.\n");


}
