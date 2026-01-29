// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/t4.c
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
    set_short("small, crude chamber");
    set_long("This small chamber is carved from the wall of the "+
        "large cavern that is directly northeast. It appears to be "+
        "a sleeping chamber for someone or something. Some bedding "+
        "lies along the north wall and there is a crude iron "+
        "brazier in the middle of the room. There is also a small "+
        "crate against the south wall.\n");


    add_exit("c8", "northeast");


    /*
     * Put additional add_items below. 
     */

    add_carved_room();
    add_item("crate","A small, poorly-built crate that holds some "+
        "dirty clothes.\n");
    add_item("brazier","A crudely crafted wrought iron brazier sits "+
        "in the center of the room. It provides enough heat to make "+
        "this room fairly comfortable.\n");
    add_item(({"bedding","bed"}),"This is a large plush pile of furs "+
        "that has bundled together forming a rather comfortable bed.\n");
    add_item(({"wall","walls"}),"The walls are rough and still bear "+
        "scars from their excavation. Some crude pictures have been "+
        "painted on the wall.\n");
    add_item(({"painting","paintings","picture","pictures"}),
        "There are several primitive paintings on the walls here. "+
        "One looks like a winged wolf and another appears to be a "+
        "large humanoid eating a smaller one. The rest are "+
        "so crudely rendered as to be unintelligable.\n");



    reset_albus_room();
}
