// file name:   /d/Avenir/common/outpost/fort6.c
// creator(s):  Kazz    March 1995
// last update: April 1995
//		Denis, Jul'96: Removed the traces of the tomato and carts quests
// purpose:     outpost storage room
// note:	pier worker (Jarod) deposits crates here.
// bug(s):
// to-do:       retain pointer to tomatoes? (need?)

# pragma strict_types
# include "/d/Avenir/common/common.h"
inherit "/d/Avenir/inherit/room";

void create_domain_room()
{
    set_short("Storage room");
    set_long("This room is quite empty, and even clean, but it does appear "+
	     "to be a storage room. The south wall bends sharply "+
	     "northeast, making for a less than square room. It is made "+
	     "entirely of the natural cavern wall.\n");

    add_exit("fort5", "north", 0);

    add_item(({"wall", "ceiling"}),
             "The north wall and ceiling are naturally smooth, "+
	     "together they curve overhead to the north.\n" );
    add_item(({"cavern"}),
             "The cavern has been used to provide some walls and "+
	     "ceiling for the fort.\n" );

    LIGHT
    IN

   reset_domain_room();
}

void
reset_domain_room()
{
}
