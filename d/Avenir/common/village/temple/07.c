// file name:        /d/Avenir/common/village/pale/temple/07.c
// creator(s):       Avenir Wizards, 03/01,04/02
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
    set_short("North Vault");
    set_long("You are standing at the north entrance of a huge "+
        "vault which extends upwards several floors. The "+
        "ceiling is made of several arches that form an open "+
        "dome, allowing the blessed light of the Source to "+
        "penetrate. In the center of the room to the south is "+
        "a grand spiral staircase.  The vault continues "+
        "northwest and northeast of here.  A broad gallery "+
        "extends north of here, at the far end of which rises "+
        "a massive granite wall.\n");


    add_exit("08", "north", 0);
    add_exit("01", "south", 0);
    add_exit("12", "southeast", 0);
    add_exit("02", "southwest", 0);

    add_vault();


    /* Air, cobbles, source, and hedges added from the base room, 
     * put additional add_items below. 
     */

    reset_domain_room();
    add_item(({"staircase","stairs"}),
        "South of here is the grand spiral staircase, you "
        + "should go south if you wish to look at it more "
        + "closely.\n");
}
