// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/r9.c
// creator(s):       Grace Jun 1996
// revisions:        Casca, 11/13/99 moved away from population
// purpose:          
// note:  
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
    set_short("crevice");
    set_long("A crevice in the stone, jagged and wet. The walls "+
	    "are covered in slime, which made it possible for you to "+
		"slip into this small space. There is no where to go but "+
		"back the way you came. Water is pooling at your feet.\n");

    add_exit("r9b","out");

    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    add_item(({"lichen", "fungi", "slime" }), "They grow sparsely along the "+
        "walls and floor, following the trickle of water.\n");
    add_item("wall", "It is natural stone, dark, and slightly damp in "+
        "places. Water trickles down the walls of the crack.\n");
    add_item(({"crack", "crevice" }), "It is a pressure-crack in the solid "+
        "stone.\n");
    add_item(({"water", "trickle"}), "The water is heavy with "+
       "dissolved minerals. It forms a shallow puddle on the floor "+
       "and trickles out of the crack into the cave beyond.\n");
    add_item("puddle", "The puddle has formed in a hollow in the stone "+
        "floor. Minerals crust the bottom of the puddle, giving the water "+
        "a teal tint.\n");


    set_up_herbs(({ GET_ONE(herbs), GET_ONE(herbs), GET_ONE(herbs) }), 
        ({ "walls","puddle","pool", "slime" }), 5);
}
