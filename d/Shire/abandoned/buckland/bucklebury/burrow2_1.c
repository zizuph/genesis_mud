inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"


#define EXIT1 BB_DIR + "burrow2_2","west",0,1
#define EXIT2 BB_DIR + "buroad13","north",0,1

void
create_room()
{

    areaname   = "Bucklebury";
    land       = "Buckland";
    roomtype   =1;
    areatype   = "village";
    smialsize  = "tiny";

    extraline = "This hall is rather small, with nothing much in particular "+
    "to look at. You would probably have a more interesting time if you "+
    "ventured further in.";

    add_exit(EXIT1);
    add_exit(EXIT2);

    make_the_room();
}

