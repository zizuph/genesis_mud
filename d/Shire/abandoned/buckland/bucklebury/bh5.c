inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"


#define EXIT1 BB_DIR + "bh15","west",0,1
#define EXIT2 BB_DIR + "bh14","north",0,1
#define EXIT3 BB_DIR + "bh16","east",0,1
#define EXIT4 BB_DIR + "bh4","south",0,1

void
create_room()
{

    areaname  = "Bucklebury";
    land      = "Buckland";
    roomtype  = 8;
    areatype  = "village";
    smialsize = "large";

    extraline = "This corridor is used to get to the bedrooms of Brandy "+
    "Hall.  It was decided some time ago, that due to all of the activity "+
    "that went on in the other part of the burrow, that those rooms "+
    "should be moved to a slightly separate part of it.";

    add_item(({"rooms","inner rooms"}), "You can see down the corridor that "+
      "the rooms look very lived in, and are very clean.\n");


    add_exit(EXIT1);
    add_exit(EXIT2);
    add_exit(EXIT3);
    add_exit(EXIT4);

    make_the_room();
}
