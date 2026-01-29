// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/t51.c
// creator(s):       Casca, 11/13/99
// revisions:
// purpose:
// note:           
// bug(s):
// to-do:

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/dark/darkl2_base.c";

/* Include the local area defines, etc */
#include "/d/Avenir/common/dark/dark.h"    
void reset_tunnel_room(){ set_searched(0); ::reset_domain_room(); }

/* Now create the room.  */
void
create_tunnel_room()
{
    set_short("damp tunnel");
    set_long("This is a narrow damp tunnel. Its shows no sign of "+
        "recent use but since the ground is gravel it is hard to "+
        "check for footprints. A tunnel continues to the northeast "+
        "while a larger tunnel is to the south. There is a body of "+
		"water east of here, but you can't get to it from here.\n");

    add_exit("t21", "south",0,);
    add_exit("t52", "northeast",0);

    /*
     * Put additional add_items below. 
     */
	 
	add_item(({"water", "lake", "river"}), 
        "It's water. Its hard to tell more from here. You'll "+
        "have to figure out how to get closer if you want to "+
        "know more about it.");
    add_item(({"gravel", "shards"}), 
        "Shards of rock that crunch underfoot.\n");

    add_n_tunnel();

    ::reset_tunnel_room();
}

