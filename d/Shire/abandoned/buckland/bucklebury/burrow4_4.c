inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"


#define EXIT1 BB_DIR + "burrow4_3","west",0,1

void
create_room()
{

    areaname  = "Bucklebury";
    land      = "Buckland";
    roomtype  = 10;
    areatype  = "village";
    smialsize = "small";

    extraline = "This pantry is quite well stocked, but in an odd sort of "+
    "way. Nothing in here needs to be cooked. Perhaps that is why there is "+
    "no kitchen in this burrow. These hobbits must go to the inn when they "+
    "want a hot meal.";

    add_exit(EXIT1);

    make_the_room();
}
