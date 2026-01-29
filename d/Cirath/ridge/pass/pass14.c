/* a_pass14.c: Pass into moutains. */

inherit "/d/Cirath/std/room";
#include "defs.h"

void create_room()
{
    BRIEF;
    set_long ("You are at the north end of a crevice. "+
              "The path slants sharply upwards here, and looking up "+
              "you see through an opening how the sun of Athas pours "+
              "its venom down over the landscape. Going north you "+
	      "will exit this haven and submit to the mercy of the sun "+
              ", while walking south will shelter you further.\n");

    add_item(({"rock","rocks","wall","walls"}),"The walls look "+
            "like it is natural rock, and it is jagged, as if "+
            "some great force had ripped the ground apart to make "+
            "this crevice.\n");

    add_item("sun","You are happy to find this sanctuary against "+
            "the punishing sun of Athas.\n");

    add_item("air","All along the crevice the air is pleasantly cool.\n");

    TRAIL;
    OUTSIDE
    add_exit(WILD_PASS+"pass15.c","north",0,2);
    add_exit(WILD_PASS+"pass13.c","south",0,2);
}
