/* a_pass10.c: Pass into moutains. */

inherit "/std/room";
#include "defs.h"

void create_room()
{
    BRIEF;
    set_long ("You are in a crevice. "+
        "The path leads along the bottom of this crevice, "+
              "the jutting edges of cliffs protecting you from the "+
              "sun above. Right here it is a rather tight squeeze "+
              "if you want to go to the north, but beyond the path "+
              "seems to become wider.\n");

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
    "tight fit if you are going northwards.\n");

    OUTSIDE
    add_exit(WILD_PASS+"pass11.c","north","@@northwards",2);
    add_exit(WILD_PASS+"pass09.c","southeast",0,2);
}

int northwards()
{
	write("With a little effort you manage to squeeze through.\n");
	return 0;
}
