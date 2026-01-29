inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 BB_DIR + "burrow2_3","west",0,1


void
create_room()
{

    areaname   = "Bucklebury";
    land       = "Buckland";
    roomtype   = 5;
    areatype   = "village";
    smialsize  = "tiny";

    extraline = "This room, although one of the larger ones in the burrow, "+
    "is not really what one would call spacious.";

    add_exit(EXIT1);

    make_the_room();
}
