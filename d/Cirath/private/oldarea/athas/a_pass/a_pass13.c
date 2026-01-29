/* a_pass13.c: Pass into moutains. */

inherit "/std/room";
#include "defs.h"

void create_room()
{
    BRIEF;
    set_long ("You are in a crevice. "+
              "The path makes an intricate little turn upwards towards "+
              "the north here, while slanting down towards southwest. "+
              "To the north the rocks and air is getting hotter for each "+
              "step you take, while it is cooler to your southwest.\n");

    add_item(({"rock","rocks","wall","walls"}),"The walls look "+
            "like it is natural rock, and it is jagged, as if "+
            "some great force had ripped the ground apart to make "+
            "this crevice.\n");

    add_item("sun","You are happy to find this sanctuary against "+
            "the punishing sun of Athas.\n");

    add_item("air","All along the crevice the air is pleasantly cool.\n");

    
    TRAIL;
    OUTSIDE
    add_exit(PASS_DIR+"a_pass14.c","north",0,3);
    add_exit(PASS_DIR+"a_pass12.c","southwest",0,3);
}
