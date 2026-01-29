inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 BB_DIR + "burrow3_3","west",0,1


void
create_room()
{

    areaname   = "Bucklebury";
    land       = "Buckland";
    roomtype   = 5;
    areatype   = "village";
    smialsize  = "tiny";

    extraline = "The room is very neat and tidy...and also very bright! "+
    "Once again, this room is done in vivid and flamboyant colours. It "+
    "makes you wonder how anyone could sleep in here.";



    add_exit(EXIT1);


    make_the_room();
}
