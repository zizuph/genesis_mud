// file name:        /d/Avenir/common/village/pale/temple/02.c
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
    set_short("West Vault");
    set_long("You are standing at the west entrance of a huge "+
        "vault which extends upwards several floors. The "+
        "ceiling is made of several arches that form an open "+
        "dome, allowing the blessed light of the Source to "+
        "penetrate. In the center of the room to the east is "+
        "a grand spiral staircase.  The vault continues "+
        "southeast and northwest of here.  A broad gallery "+
        "extends west of here, at the far end of which rises "+
        "a massive granite wall.\n");

    add_exit("03", "west", 0);
    add_exit("01", "east", 0);
    add_exit("07", "northeast", 0);
    add_exit("16", "southeast", 0);

    add_vault();


    /* Screens, scents, source, floors and walls added from the
     * base room, put additional add_items below. 
     */

    reset_domain_room();
    add_item("staircase",
        "East of here is the grand spiral staircase, you "
        + "should go east if you wish to look at it more "
        + "closely.\n");
}
