// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/n6.c
// creator(s):       unknown
// revisions:        Casca, 11/13/99
//              Lilith May 2022: typo fixes
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
    set_short("Dead-end");
    set_long("It looks like some workers started exchavating a new tunnel "+
        "here but abandoned their efforts. "+
        "Baskets and tools lie amid piles of recently extracted stone. "+
        "There are scorch-marks along the walls.\n");

    add_exit("n3","south");

    /*
     * Put additional add_items below. 
     */

    add_r_tunnel();
    add_new_tunnel();

    reset_tunnel_room();
    add_item(({"basket","baskets"}),
        "Several baskets are scattered about the area. They "
        + "are filled to various degrees with stones and "
        + "debris from the construction.\n");
    add_item("north wall",
        "The north wall is heavily scarred with pickaxe "
        + "and chisel marks. It's apparent that construction "
        + "is still underway on this wall.\n");
    add_item("tools",
        "You notice some chisels laying amidst the debris "
        + "as well as a couple sledgehammers leaning against "
        + "the wall.\n");
	add_item(({"scorches", "scorch marks", "scorch-marks", "marks",
        "walls", "smudges"}), "Black scorch-marks have been left on "
        +"walls here.\n");	
}
