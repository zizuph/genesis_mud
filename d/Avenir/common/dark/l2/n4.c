// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/w4.c
// creator(s):       unknown
// revisions:        Lilith, 2 Nov 1996 made compatable to smis module
//                   Casca, 11/13/99 update code and face lift
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
    set_short("Cavern");
    set_long("The clean tunnel meets here with a large, naturally formed "+
        "cavern. The stones here glow with a slight, eerie luminescence.\n"+
        "The tunnel continues out to the east and west.\n");

    add_exit("n3", "east");
    add_exit("n7", "west");

    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    add_item(({"stones","rock","rocks","light","luminescence"}),
	   "The rock of this naturally formed cavern sheds its own strange "+
	   "light, so dim it can hardly be perceived.\n");

    reset_tunnel_room();
}
