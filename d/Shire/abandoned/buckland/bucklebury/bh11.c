inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 BB_DIR + "bh7","up",0,1

void
create_room()
{

    areaname  = "Bucklebury";
    land      = "Buckland";
    roomtype  = 9;
    areatype  = "village";
    smialsize = "large";

    extraline = "This cellar looks like it is visited quite often.  The "+
    "racks are full of numerous different kinds of wines.";
    "though.";

    add_item(({"rack","wine rack","racks","wine racks"}),"These wine racks "+
      "are full of wine, despite the fact that they seem to be visited "+
      "very often.\n");

    add_exit(EXIT1);

    make_the_room();

    remove_item("spiderwebs");
}

