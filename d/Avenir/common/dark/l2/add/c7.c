// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/c7.c
// creator(s):       Casca, 11/13/99
// revisions:
// purpose:
// note:           
// bug(s):
// to-do:

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/dark/albus_base.c";

/* Include the local area defines, etc */
#include "/d/Avenir/common/dark/dark.h"  


/* Now create the room.  */
void
create_albus_room()
{
    set_short("Northwestern corner");
    set_long("You are near the northwestern corner of a large, dimly "+
        "lit cavern. The cavern has several campfires scattered "+
        "about it. "+
        "This section, like most of the others, has a "+
        "carelessly maintained campfire surrounded by a motley "+
        "assortment of ragged tents and even more disreputable-"+
        "looking bedrolls. "+
        "There are two small entrances carved into the wall northeast "+
        "and northwest of here.\n");

    add_exit("c8", "south");
    add_exit("r3", "northwest");
    add_exit("r2", "northeast");
    add_exit("c6", "east");
    add_exit("c5", "southeast");


    /*
     * Put additional add_items below. 
     */


    add_cavern_room();


    reset_albus_room();
}

