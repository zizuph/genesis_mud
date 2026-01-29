// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/t3.c
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

/* Now create the room.  */
void
create_tunnel_room()
{
    set_short("Shadowy tunnel");
    set_long("This is a large natural tunnel that seems perpetually "+
        "dark and gloomy. Shadows fill the nooks and crevices of the "+
        "walls and ceiling. There is a very deep shadow to the "+
        "east. The tunnel makes a sharp turn here to the southeast.\n");

    add_exit("t2", "west");
    add_exit("t4", "southeast");
    add_exit("t72", "enter", 0, 0, 1); // non-obvious

    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();
    add_item(({"crevice", "east crevice", "east shadow"}), 
	    "It looks like the crevice is actually an opening into "
		+"another tunnel. It seems like someone broke through to "
		+"this tunnel and then regretted it. You might be able "
		+"to enter here.\n"); 		
    add_item(({"shadow","shadows","nooks","crevices"}),
        "Deep shadows seem to pool in all the nooks and "
        + "crevices of the tunnel. Even light seems to fight "
        + "futilely against it.\n");
    add_item(({"walls","wall"}),
        "The walls here are rough and uneven, creating many "
        + "nooks and crevices which are filled with dark "
        + "shadows.\n");
    add_item(({"ceiling","roof","above"}),
        "The ceiling varies in height, sometimes you have "
        + "to duck to get past while in others it soars above "
        + "you nearly reaching the limit of your vision. "
        + "Shadows fill the depressions of the ceilings like "
        + "those in the walls.\n");

    reset_tunnel_room();
}

