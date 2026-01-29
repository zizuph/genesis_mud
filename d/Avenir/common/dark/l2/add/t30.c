// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/t30
// revisions:
// purpose:
// note:           
// bug(s):
// to-do:

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/dark/darkl2_base.c";

/* Include the local area defines, etc */
#include "/d/Avenir/common/dark/dark.h"

/* Herb stuff */
#include "/d/Avenir/common/herbs/herbsearch.h"
#define GET_ONE(x)   ((x) [random(sizeof(x))])
string *herbs = HERB_MASTER->query_herbs( ({"cave"}) );

/* Now create the room.  */
void
create_tunnel_room()
{
    set_short("Filthy tunnel");
    set_long("The filth and debris in this tunnel is not as bad as that "+
        "of the tunnel to the north. Bone and rotting cloth along with rubble "+
        "and other detritus and debris choke the tunnel. You can see "+
        "a path through all the trash, evidence of the tunnel's use "+
        "despite the unpleasantness of being here. There is a hole "+
		"in the ceiling that can be climbed up through.\n");

    add_exit("t29", "east", 0);
    add_exit(L2 +"e15", "west", 0);
    add_exit(L1 +"cave1", "up", 0);
	 
	 
	 
    set_up_herbs(({ GET_ONE(herbs), GET_ONE(herbs), GET_ONE(herbs) }), 
        ({ "rubble", "remains", "rock", "lichen", "fungi" }), 5);

    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    add_item(({"trash","detritus"}),"Much of the trash here seems to be "+
        "the remains of various animals. You also notice what appears to "+
        "be rotting bedding. "+
        "Fungi grows on and around the rotting remains.\n");
    add_item(({"debris","rubble"}),"This appears to be the leavings of "+
        "tunnel diggings, but there are no signs that this tunnel "+
        "has ever been worked by the hands of man. "+
        "There are lichens growing on much of the rubble.\n");
    add_item(({"hole", "ceiling", "hole in ceiling", "up"}), 
	    "There is a hole in the ceiling "+
	    "near the back wall. The darkness is too deep "+
        "to see where it goes, but you can climb up through it.\n");		
    add_tell("You hear something moving amidst the trash.\n");
    add_tell("The smell here nearly makes you gag.\n");


    reset_tunnel_room();
}

reset_tunnel_room()
{
    set_searched(-2);
}
