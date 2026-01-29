// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/s9.c
// creator(s):       unknown
// revisions:        Casca, 11/18/99
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
    set_short("Slightly dusty tunnel");
    set_long("The tunnel here is a little dustier then most, it hangs lightly "+
        "in the air and powders all of the horizontal surfaces. The passage "+
        "curves around to the northwest and east.\n");

    add_exit("s8","northwest",0,DUST);
    add_exit("s10","east",0,DUST);

    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    add_item(({"dust"}),"There is a thin layer of dust hanging in the air "+
        "here.\n");
    add_item(({"floor","ground"}),
        "The stone of the ground is uneven and rough a "
        + "light coating of dust covers much of it.\n");
    add_tell("A puff of wind stirs up the dust and briefly obsures your "+
        "vision.\n");
    add_cmd_item("air", "smell", "Against your better judgement you "+
        "sample the air and get a big breath of dust. You cough and choke "+
        "untill your able to draw a fresh breath of air.\n");
    

    reset_tunnel_room();
}

