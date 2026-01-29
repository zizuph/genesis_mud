inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 BB_DIR + "burrow4_2","west",0,1


void
create_room()
{

    areaname   = "Bucklebury";
    land       = "Buckland";
    roomtype   = 5;
    areatype   = "village";
    smialsize  = "tiny";

    extraline = "This is a very relaxing bedroom. It is decorated in "+
    "soft, soothing colours.  It looks like a great place to lie down and "+
    "have a nap.";

    add_exit(EXIT1);

    make_the_room();
}
