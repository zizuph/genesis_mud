// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/r9.c
// creator(s):       Grace Jun 1996
// revisions:        Casca, 11/13/99 moved away from population
// purpose:          Something for players to find in the Utterdark,
//                   after defeating the winged-wolf.
// note:             The found objects are: 3 torches, bones, a bracelet,
//                   a gem & a feather-knife.
// bug(s):           
// to-do:          


inherit "/d/Avenir/common/dark/darkl2_base.c";

#include <stdproperties.h>
#include "/d/Avenir/common/dark/dark.h"
#include "/d/Avenir/common/herbs/herbsearch.h"
#define GET_ONE(x)   ((x) [random(sizeof(x))])

string *herbs = HERB_MASTER->query_herbs( ({"cave"}) );


void 
reset_tunnel_room()
{
    set_searched(0);
}

void
create_tunnel_room()
{
    set_short("cavern");
    set_long("This is the lair of the winged wolf. There is a strong "+
        "animal scent in here. A small amount of water seeps from "+
        "a crack in the wall, forming a puddle in one corner of "+
        "the room. Lichen and fungi grow on the stone walls and "+ 
        "around the puddle. To the west is the mouth of the cave, "+
        "where it becomes a ledge, and then just darkness beyond.\n");

    add_exit("r9","west");

    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();
	add_prop("_av_mine_special", 2);

    add_item(({"lichen", "fungi"}), "They grow sparsely along the walls"+
        "and floor, following the trickle of water.\n");
    add_item("wall", "It is natural stone, dark, and slightly damp in "+
        "places. Water trickles from a small crack.\n");
    add_item("crack", "It is just a pressure-crack in the otherwise solid "+
        "stone.\n");
    add_item(({"water", "trickle"}), "The water is heavy with "+
        "dissolved minerals. It forms a shallow puddle on the floor.\n");
    add_item("puddle", "The puddle has formed in a hollow in the stone "+
        "floor. Minerals crust the bottom of the puddle, giving the water "+
        "a teal tint.\n");


    set_up_herbs(({ GET_ONE(herbs), GET_ONE(herbs), GET_ONE(herbs) }), 
        ({ "walls","puddle","lichen", "fungi" }), 5);
}
