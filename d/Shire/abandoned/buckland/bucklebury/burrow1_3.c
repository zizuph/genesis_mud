inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 BB_DIR + "burrow1_2","north",0,1


void
create_room()
{

    areaname   = "Bucklebury";
    land       = "Buckland";
    roomtype   = 5;
    areatype   = "village";
    smialsize  = "tiny";

    extraline = "The room is spotless.  The hobbit who uses this room "+
    "must spend a lot of his time cleaning.";



    add_exit(EXIT1);


    make_the_room();
}
