/* a_pass12.c: Pass into moutains. */

inherit "/std/room";
#include "defs.h"

void create_room()
{
    BRIEF;
    set_long ("You are in a crevice. "+
              "The path bends upwards and northeast here, and the "+
              "air is getting a little warmer towards the latter "+
              "direction. The rock walls are still cool, and you "+
	      "savour the feeling of their cool rugged feeling "+
              "against your hot skin. The path goes upwards to "+
              "the northeast, or south, where it seems a bit "+
              "cooler.\n");

    add_item(({"rock","rocks","wall","walls"}),"The walls look "+
            "like it is natural rock, and it is jagged, as if "+
            "some great force had ripped the ground apart to make "+
            "this crevice.\n");

    add_item("sun","You are happy to find this sanctuary against "+
            "the punishing sun of Athas.\n");

    add_item("air","All along the crevice the air is pleasantly cool.\n");

    TRAIL;
    OUTSIDE
    add_exit(PASS_DIR+"a_pass13.c", "northeast", 0, 5);
    add_exit(PASS_DIR+"a_pass11.c","south",0,5);
}
