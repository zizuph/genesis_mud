// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/t10.c
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
        "dark and gloomy. Shadows fill the nooks and crevices of the walls "+
        "and ceiling. The barest hint of a breeze wafts from the south"+
        "east, where the heart of the shadows seems blackest. A fairly "+
        "recent opening has been carved into the northwest wall, "+
        "judging by the lack of erosion of the tool marks. You can "+
        "see another tunnel through it.\n");

    add_exit("t9", "southwest", 0);
    add_exit("t11", "northeast", 0);
    add_exit("r8", "southeast",0,0,1);
	add_exit("t63", "northwest", 0);

    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    add_item(({"shadow","shadows","nooks","crevices"}),
        "Deep shadows seem to pool in all the nooks and "
        + "crevices of the tunnel. Even light seems to fight "
        + "futilely against it. One section of shadows on the "
        + "southeast wall seems different.\n");
    add_item(({"walls","wall"}),
        "The walls here are rough and unever creating many "
        + "nooks and crevices which are filled with dark "
        + "shadows.\n");
    add_item(({"ceiling","roof","above"}),
        "The ceiling varies in height, sometimes you have "
        + "to duck to get past while in others it soars above "
        + "you nearly reaching the limit of your vision. "
        + "Shadows fill the depressions of the ceilings like "
        + "those in the walls.\n");
    add_item(({"marks", "tool marks"}), "These marks are not "
        +"naturally occuring--they were made by tools, and "
        +"fairly recently, too.\n");
    add_item(({"opening", "northwest opening"}), "Someone, or "
        +"something recently broke through the tunnel wall here.\n");
    add_tell("You notice an faint animal smell in the air.");
    reset_tunnel_room();
}

