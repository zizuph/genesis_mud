/* a_pass06.c: Pass into moutains. */

inherit "/std/room";
#include "defs.h"

void create_room()
{
    BRIEF;
    set_long ("You are at the south end of a crevice. "+
              "The path continues down into shadows you cannot "+
              "penetrate, as your eyes have become used to the "+
              "light outside. The air is pleasantly cool here, "+
              "and you think it might be even cooler further north, "+
	      "where the path continues into the crevice. " +
              "Northwards the path goes further down into the crevice, "+
              "and south the path continues.\n");

    add_item(({"rock","rocks","wall","walls"}),"The walls look like "+
            "it is natural rock, and it is jagged, as if some great "+
            "force had ripped the ground apart to make this crevice.\n");

    add_item("sun","You are happy to find this sanctuary against "+
    "the punishing sun of Athas, all along the crevice the air is "+
    "pleasantly cool.\n");

    TRAIL;
    OUTSIDE
   add_exit(WILD_PASS+"pass07.c","north",0,1);
   add_exit(WILD_PASS+"pass05.c","south",0,1);
}
