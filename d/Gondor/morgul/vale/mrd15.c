#pragma strict_types

inherit "/d/Gondor/morgul/vale/morgul2.c";
#include "/d/Gondor/defs.h"

public void
create_morgul_room()
{
    set_extraline("A huge black iron-sign stands here.\n"); 
    add_item(({"sign",}), BSN(
        "The sign shows a picture of a Lidless Eye engulfed in devouring flames!"));
    add_item(({"slope", "valley", "ephel duath"}), BSN(
        "Only shadows and nothing but shadows envelops the entire place, except for a dusty cobbered " +
        "road and huge rocks from the walls of Ephel Duath."));
    add_item(({"road"}), BSN(
        "This is a dusty cobbered road leading to the eastern gates of Minas Morgul and to Cirith Ungol.")); 

    add_exit(MORGUL_DIR + "vale/mrd14","west",0,3);
    add_exit(MORGUL_DIR + "vale/inner3","east",0,3);
}





