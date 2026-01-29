/* a_pass11.c: Pass into moutains. */

inherit "/d/Cirath/std/room";
#include "defs.h"

void create_room()
{
    BRIEF;
    set_long ("You are in a crevice. "+
              "The path leads along the bottom of this crevice, "+
              "with, to your relief, no sunlight filtering down from "+
              "above. If you want to go to the south, you'd better be "+
              "prepared to get a bruise or two, as the walls narrow to "+
              "almost no space between them here.\n");

    add_item(({"rock","rocks","wall","walls"}),"The walls look "+
            "like it is natural rock, and it is jagged, as if "+
            "some great force had ripped the ground apart to make "+
            "this crevice.\nThe walls are very close here, making "+
            "the path rather narrow.\n");

    add_item("sun","You are happy to find this sanctuary against "+
             "the punishing sun of Athas.\n");

    add_item("air", "All along the crevice the air is pleasantly "+
             "cool.\n");

    add_item(({"trail","path"}),"The path narrows here, and its a "+
    "tight fit if you are going southwards.\n");

    OUTSIDE
    add_exit(WILD_PASS+"pass12.c","north",0,2);
    add_exit(WILD_PASS+"pass10.c","south","@@southwards",2);
}

int southwards()
{
	write("Not caring about the bruises you get, you push "+
              "on through.\n");
	return 0;
}
