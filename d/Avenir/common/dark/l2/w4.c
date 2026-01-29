// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/w4.c
// creator(s):       unknown
// revisions:        Casca, 11/13/99
// purpose:          
// note:             
// bug(s):           
// to-do:            

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/dark/darkl2_base.c";

/* Include the local area defines, etc */
#include "/d/Avenir/common/dark/dark.h"  
#include "/d/Avenir/common/herbs/herbsearch.h"
#define GET_ONE(x)   ((x) [random(sizeof(x))])

string *herbs = HERB_MASTER->query_herbs( ({"cave"}) );
/* Now create the room.  */
void
create_tunnel_room()
{
    set_short("Damp tunnel");
    set_long("The tunnel here is very damp. "+
        "Stagnant puddles fill the depressions in the floor. "+
        "Lichen grows on much of the rock surfaces and fungi "+
        "grow in the damp soil. "+
        "The path leads to the east and northwest.\n");

    add_exit("w3","south","@@splash@@");
    add_exit("w5","north","@@splash@@");

    set_up_herbs(({ GET_ONE(herbs), GET_ONE(herbs), GET_ONE(herbs) }), 
        ({ "walls","puddle","rock","lichen", "fungi" }), 5);

    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    add_cmd_item(({"from pool","pool","water","the water","puddle","puddles"}),
        ({"drink","taste"}),
        "It is foul and brackish.\nYou feel slightly ill.\n");
    add_item(({"pool","pools","water","puddle","puddles"}),
        "Shallow pools of dirty, brackish water.\n");
    add_item(({"lichen", "fungi"}), "They grow sparsely along the walls"+
        " and floor.\n");

    reset_tunnel_room();
}

mixed
splash()
{
    write("You splash through puddles as you leave the area.\n");
    say(QCTNAME(TP) + " splashes through the puddles.\n");
    return 0;
}

reset_tunnel_room()
{
    set_searched(-2);
}
