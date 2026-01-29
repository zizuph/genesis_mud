/* a_pass08.c: Pass into moutains. */

inherit "/std/room";
#include "defs.h"

void create_room()
{
    BRIEF;
    set_long ("You are in a crevice. "+
              "The path seems to level out to the northwest, "+
              "while it slants slightly upwards to the southeast. "+
              "A wind from northwest brings a welcome breeze to your "+
              "face, and you briefly lean towards the jagged rock walls "+
              "to savour the feeling.\n");
    
    add_item(({"rock","rocks","wall","walls"}),"The walls "+
            "look like it is natural rock, and it is jagged, "+
            "as if some great force had ripped the ground apart "+
            "to make this crevice.\n");

    add_item("sun","You are happy to find this sanctuary against "+
            "the punishing sun of Athas.\n");
    
    add_item("air","All along the crevice the air is pleasantly cool.\n");

    TRAIL;
    OUTSIDE

    add_exit(WILD_PASS+"pass09.c","northwest",0,1);
    add_exit(WILD_PASS+"pass07.c","southeast",0,1);
}
