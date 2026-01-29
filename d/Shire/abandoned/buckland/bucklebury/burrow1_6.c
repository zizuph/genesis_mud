inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"


#define EXIT1 BB_DIR + "burrow1_5","west",0,1

void
create_room()
{

    areaname  = "Bucklebury";
    land      = "Buckland";
    roomtype  = 10;
    areatype  = "village";
    smialsize = "tiny";

    extraline = "This pantry is quite well stocked with lots of extra "+
    "food in it, just in case some unexpected company comes by. ";

    add_item(({"shelves","shelf"}),"The shelves in this room are full "+
      "of food and cooking ingredients.\n");


    add_exit(EXIT1);

    make_the_room();
}
