// file name:        /d/Avenir/common/village/pale/temple/
// creator(s):       Avenir Wizards, 03/01
// revisions:
// purpose:
// note:           
// bug(s):
// to-do:

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/village/temple_base.c";

/* Include the local area defines, etc */
#include "/d/Avenir/common/village/village.h"  

/* Now create the room.  */
void
create_temple_room()
{
    set_short("East Vault");
    set_long("You are standing at the east entrance of a huge "+
        "vault which extends upwards several floors. The "+
        "ceiling is made of several arches that form an open "+
        "dome, allowing the blessed light of the Source to "+
        "penetrate. In the center of the room to the west is "+
        "a grand spiral staircase.  The vault continues "+
        "southwest and northwest of here.  A broad gallery "+
        "extends east of here, at the far end of which rises "+
        "a massive granite wall.\n");


    add_exit("13", "east", 0);
    add_exit("01", "west", 0);
    add_exit("07", "northwest", 0);
    add_exit("16", "southwest", 0);

    add_vault();


     /* Screens, scents, source, floors and walls added from the
      * base room, put additional add_items below. 
      */

    reset_domain_room();
    add_item("staircase",
        "West of here is the grand spiral staircase, you "
        + "should go west if you wish to look at it more "
        + "closely.\n");
}
