//updated by Lilith 2 Nov 1996, for use with the dark_treas_pmodule.c 
// file in the /dark/obj/* dir. It places crates here.

inherit "/d/Avenir/inherit/room";
#include "/d/Avenir/common/dark/dark.h"
create_domain_room()
{
    set_short("Large, spacious cavern.");
    set_long(break_string("The clean tunnel meets here from two sides in"
	    + " a large, spacious cavern.  This room looks like it may once"
       + " have been used to store vast amounts of some product or another."
		    + " To the northwest, a black tunnel opens up beneath a"
		     + " beautiful black archway, barely discernable in the"
			  + " gloom.\n", 75));

    add_item(({"arch", "archway"}), "The archway to the northwest "
	     + "is made from a jet black onyx-like stone, beautifully "
	     + "formed with simple curves.\nIt leads into the shadows.\n");

    add_exit("/d/Avenir/common/dark/l2/n7", "east", 0);
    add_exit("/d/Avenir/common/dark/l2/w7", "southwest", 0);
    add_exit("ut1", "northwest", "@@arch@@");

    BLACK
	IN

}

mixed 
arch()
{
    write("You pass beneath the arch, and enter the finely-chiseled "
	  + "tunnel.\n");
    say(QCTNAME(TP) + " passes beneath the arch.\n");
    return 0;
}
