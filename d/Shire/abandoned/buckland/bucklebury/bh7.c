inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"


#define EXIT1 BB_DIR + "bh6","west",0,1
#define EXIT2 BB_DIR + "bh8","east",0,1
#define EXIT3 BB_DIR + "bh10","north",0,1
#define EXIT4 BB_DIR + "bh11","down",0,1

void
create_room()
{

    areaname  = "Bucklebury";
    land      = "Buckland";
    roomtype  = 8;
    areatype  = "village";
    smialsize = "large";

    extraline = "This corridor leads to the inner parts of the burrow.  "+
    "To your east is one of the most visited rooms of Brandy Hall..the "+
    "dining room.  The parlour is to the north, and downstairs is the cellar.";



    add_exit(EXIT1);
    add_exit(EXIT2);
    add_exit(EXIT3);
    add_exit(EXIT4);

    make_the_room();
}
