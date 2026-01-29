inherit "/d/Shire/eastroad/villagemaker";
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/macros.h"

#define EXIT1 BB_DIR + "buroad9","north",0,1
#define EXIT2 BB_DIR + "buroad11","south",0,1
#define EXIT3 BB_DIR + "shop","east",0,1
#define EXIT4 BB_DIR + "buroad12","west",0,1

void
create_room()
{
    areaname  = "Bucklebury";
    land      = "Buckland";
    areatype  = 2;
    areadesc  = "dirt road";

    extraline = "This is the middle of Bucklebury. To the east is a busy "+
    "looking shop, and a road continues to the west. The main road "+
    "continues to the north and south.";

    add_item(({"road","dirt road"}),"This is the main road in Bucklebury.\n");

    add_exit(EXIT1);
    add_exit(EXIT2);
    add_exit(EXIT3);
    add_exit(EXIT4);

    make_the_room();
}


