/* a_pass07.c: Pass into moutains. */

inherit "/std/room";
#include "defs.h"

void create_room()
{
    BRIEF;
    set_long ("You are in a crevice. The path continues down to "+
              "the northwest, and south it slants slightly upwards."+
              " The air is pleasantly cool here. The rock walls are "+
              "also cool, and you relax your pace to enjoy this "+
              "rare luxury. \n");

    add_item(({"rock","rocks","wall","walls"}),"The walls "+
            "look like it is natural rock, and it is jagged, "+
            "as if some great force had ripped the ground apart "+
            "to make this crevice.\n");

    add_item("sun","You are happy to find this sanctuary against "+
            "the punishing sun of Athas.\n");

    add_item("air","The air is pleasantly cool down in this "+
            "crevice\n");
    TRAIL;
    OUTSIDE
    add_exit(WILD_PASS+"pass08.c","northwest",0,1);
    add_exit(WILD_PASS+"pass06.c","south",0,1);
}
