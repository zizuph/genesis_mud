inherit "/d/Shire/eastroad/villagemaker";
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/macros.h"

#define EXIT1 BB_DIR + "buroad7","north",0,1
#define EXIT2 BB_DIR + "buroad9","southeast",0,1

void
create_room()
{
    areaname  = "Bucklebury";
    land      = "Buckland";
    areatype  = 2;
    areadesc  = "dirt road";

    extraline = "This road goes north out of Buckebury, and southeast "+
    "towards some more residences and some busy looking places.";

    add_item(({"road","dirt road"}),"This road leads around Brandy Hall "+
      "and also into the main part of Bucklebury.\n");

    add_exit(EXIT1);
    add_exit(EXIT2);

    make_the_room();
}

