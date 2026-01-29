#pragma strict_types

inherit "/d/Gondor/morgul/vale/morgul2.c";
#include "/d/Gondor/defs.h"

public void
create_morgul_room()
{

    FIXEUID;
    set_extraline("Shadows and dark obstacles occur from outsprings of the sides of Ephel Duath."); 
    add_item(({"slope", "valley", "ephel duath"}), 
        "Only shadows and nothing but shadows envelops the entire place, except for a dusty cobbled " +
        "road and huge rocks from the walls of Ephel Duath.");
    add_item(({"road"}),
        "This is a dusty cobbled road leading to the eastern gates of Minas Morgul and to Cirith Ungol."); 
    
    add_exit(MORGUL_DIR + "vale/mrd6","west",0,3);
    add_exit(MORGUL_DIR + "vale/mrd8","east",0,3);
//    add_exit(MORGUL_DIR + "vale/cv1","northeast",0,3);
    
   
}





