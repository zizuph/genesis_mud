#pragma strict_types

inherit "/d/Gondor/morgul/vale/morgul2.c";
#include "/d/Gondor/defs.h"

public void
create_morgul_room()
{
    set_extraline("Shadows and dark obstacles occur from outprings of the sides of Ephel Duath\n"); 
    add_item(({"slope", "valley", "ephel duath"}), BSN(
        "Only shadows and nothing but shadows envelops the entire place, except for a dusty cobbered " +
        "road and huge rocks from the walls of Ephel Duath."));
    add_item(({"road"}), BSN(
        "This is a dusty cobbered road leading to the eastern gates of Minas Morgul and to Cirith Ungol.")); 
    add_exit(MORGUL_DIR + "vale/mrd10","west",0,3);
    add_exit(MORGUL_DIR + "vale/mrd12","east",0,3);
    
   
}





