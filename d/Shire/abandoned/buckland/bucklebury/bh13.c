inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"


#define EXIT1 BB_DIR + "bh12","north",0,1

void
create_room()
{

    areaname  = "Bucklebury";
    land      = "Buckland";
    roomtype  = 10;
    areatype  = "village";
    smialsize = "large";

    extraline = "This pantry is so well stocked, you imagine it has enough "+
    "food in it to feed all of Buckland, not just Brandy Hall or Bucklebury.";

    add_item(({"shelves","shelf"}),"The shelves in this room have more "+
       "food and cooking ingredients in them than you've probably ever "+
       "seen.  There is flour, apples, extra spices and herbs that aren't "+
       "kept in the kitchen, and the list goes on and on and on.\n");


    add_exit(EXIT1);

    make_the_room();
}
