// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/e3.c
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
    set_short("Barracks");
    set_long("It would appear is if this is where the sybarite "+
        "miners stay while not hard at work expanding the tunnels. "+
        "The tunnel to the north is very narrow, probably a large "+
        "reason this chamber was chosen to house the workers. The "+
        "narrow opening would give the miners a good advantage should "+
        "anything seek to threaten them. This chamber appears to "+
        "house the troll miners, judging by the smell and the filthy "+
        "bedding arranged around the walls. A small fire provides "+
        "some comfort and light. More chambers are visable to the "+
        "southeast and southwest.\n");

    add_exit("e2","north");
    add_exit("e4","southwest");
    add_exit("e5","southeast");

    LIGHT

    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    add_item(({"fire","campfire"}),"A small campfire provides enough "+
        "light to navigate the room, and enough heat to make it "+
        "somewhat comfortable.\n");
    add_item(({"bedding","bed","beds"}),"Several padded blankets have "+
        "been spread out near the fire. Additional blankets lay around to "+
        "serve as covers.\n");
    add_item("opening","The opening to the north is quite narrow. "+
        "During an attack defenders in this room could easily hold "+
        "off a large number of attackers.\n");
    add_tell("The fire crackles and pops throwing forth a shower of "+
        "sparks.\n");

    reset_tunnel_room();
}
