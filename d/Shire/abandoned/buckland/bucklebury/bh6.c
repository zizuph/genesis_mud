inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"


#define EXIT1 BB_DIR + "bh2","west",0,1
#define EXIT2 BB_DIR + "bh7","east",0,1

void
create_room()
{

    areaname  = "Bucklebury";
    land      = "Buckland";
    roomtype  = 8;
    areatype  = "village";
    smialsize = "large";

    extraline = "This corridor leads to the inner parts of the burrow.  "+
    "The corridor, like the entryway, has little furniture or adornments, "+
    "but you can catch a glimpse of the inner rooms that look very cozy. ";

    add_item(({"rooms","inner rooms"}), "You can see down the corridor that "+
      "the rooms look very lived in, and are very clean.\n");


    add_exit(EXIT1);
    add_exit(EXIT2);

    make_the_room();
}
