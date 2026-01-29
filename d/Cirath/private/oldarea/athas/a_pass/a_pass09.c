/* a_pass09.c: Pass into moutains. */

inherit "/std/room";
#include "defs.h"

void create_room()
{
    BRIEF;
    set_long ("You are in a crevice. "+
              "The path seems to be perfectly level here, "+
              "and you enjoy the cool air of the crevice as you "+
              "journey onward. The air does not seem to be quite "+
              "so dry and arid here.\n");

    add_item(({"rock","rocks","wall","walls"}),"@@descrocks");

    add_item("sun","You are happy to find this sanctuary against "+
            "the punishing sun of Athas.\n");
    
    add_item("air","All along the crevice the air is pleasantly cool.\n");

    TRAIL;
    OUTSIDE
    add_exit(PASS_DIR+"a_pass10.c", "northwest", 0, 5);
    add_exit(PASS_DIR+"a_pass08.c","southeast",0,5);

}




string descrocks()
{
	write("The walls look "+
            "like it is natural rock, and it is jagged, as if "+
            "some great force had ripped the ground apart to make "+
            "this crevice.\n");
return "";
}
    
