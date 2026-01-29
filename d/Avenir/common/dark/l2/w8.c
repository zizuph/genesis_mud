// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/w8.c
// creator(s):       unknown
// revisions:        updated by Lilith 2 Nov 1996,
//                   for use with the dark_treas_pmodule.c
//                   Casca, 11/25/99 
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
    set_short("Large, spacious cavern");
    set_long("The tunnel meets here from two sides in "+
        "a large, spacious cavern.  This room looks like it may once "+
        "have been used to store vast amounts of some product or another. "+
        "To the northwest, a black tunnel opens up beneath a "+
        "beautiful black archway, barely discernable in the "+
        "gloom.\n");

    add_item(({"arch", "archway"}), "The archway to the northwest "
	     + "is made from a jet black onyx-like stone, beautifully "
	     + "formed with simple curves.\nIt leads into the shadows.\n");

    add_exit("n7", "east", 0);
    add_exit("w7", "southwest", 0);
    add_exit("ut1", "northwest", "@@arch@@");


    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    add_item(({"arch", "archway"}), "The archway to the northwest "
	     + "is made from a jet black onyx-like stone, beautifully "
	     + "formed with simple curves.\nIt leads into the shadows.\n");

    reset_tunnel_room();
}



mixed 
arch()
{
    write("You pass beneath the arch, and enter the finely-chiseled "
	  + "tunnel.\n");
    say(QCTNAME(TP) + " passes beneath the arch.\n");
    return 0;
}
