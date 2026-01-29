// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/s10.c
// creator(s):       unknown
// revisions:        Casca, 11/13/99
// purpose:          
// note:             Possible room for a dust element
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
    set_short("Dusty tunnel");
    set_long("The tunnel here is quite dusty, it hangs in the air "+
        "and covers all of the horizontal surfaces. The passage "+
        "curves around to the west and northeast.\n");

    add_exit("s9","west",0,DUST);
    add_exit("s11","southeast",0,DUST);
    add_exit("e17","northeast");    
	/*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    add_item(({"dust"}),"There is a great deal of dust here. It hangs "+
        "so thickly in the air that it nearly chokes you.\n");
    add_item(({"floor","ground"}),
        "The stone of the ground is uneven and rough a "
        + "thick coating of dust covers much of it.\n");
    add_tell("A puff of wind stirs up the dust and briefly obsures your "+
        "vision.\n");
   add_cmd_item("air", "smell", "Against your better judgement you "+
        "sample the air and get a big breath of dust. You cough and choke "+
        "untill your able to draw a fresh breath of air.\n");


    reset_tunnel_room();
}
