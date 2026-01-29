inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 BB_DIR + "bh5","south",0,1


void
create_room()
{

    areaname   = "Bucklebury";
    land       = "Buckland";
    roomtype   = 5;
    areatype   = "village";
    smialsize  = "large";

    extraline = "The room is very clean, but not very tidy.  There are "+
    "articles of clothing lying all over the floor.";


    add_item(({"floor","clothing","clothes","articles of clothing"}), 
      "The floor is kept clean, but there are a lot of clothes lying "+
      "all over the floor, as if a very busy hobbit lives here and "+
      "doesn't have the time to always pick them up.\n");


    add_exit(EXIT1);


    make_the_room();
}
