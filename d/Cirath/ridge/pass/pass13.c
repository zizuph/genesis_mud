/* a_pass13.c: Pass into moutains. */

inherit "/d/Cirath/std/room";
#include "defs.h"

void create_room()
{
    BRIEF;
    set_long ("You are in a crevice. "+
              "The path makes an intricate little turn upwards towards "+
              "the north here, while slanting down towards the southwest. "+
              "Also to the north the rocks and air are getting hotter for each "+
              "step you take, while it is cooler to the southwest.\n");

    add_item(({"rock","rocks","wall","walls"}),"The walls look "+
            "like it is natural rock, and it is jagged, as if "+
            "some great force had ripped the ground apart to make "+
            "this crevice.\n");

    add_item("sun","You are happy to find this sanctuary against "+
            "the punishing sun of Athas.\n");

    add_item("air","All along the crevice the air is pleasantly cool.\n");

    
    TRAIL;
    OUTSIDE
    add_exit(WILD_PASS+"pass14.c","north",0,2);
    add_exit(WILD_PASS+"pass12.c","southwest",0,2);
}
