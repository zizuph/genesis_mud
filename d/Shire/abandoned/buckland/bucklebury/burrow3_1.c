inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"


#define EXIT1 BB_DIR + "burrow3_2","south",0,1
#define EXIT2 BB_DIR + "buroad14","north",0,1

void
create_room()
{

    areaname   = "Bucklebury";
    land       = "Buckland";
    roomtype   =1;
    areatype   = "village";
    smialsize  = "tiny";

    extraline = "This front hall is small, but very nice to look at.  It is "+
    "decorated in many bright colours, and makes your mood lift "+
    "immediately upon entering.";

    add_exit(EXIT1);
    add_exit(EXIT2);

    make_the_room();
}

