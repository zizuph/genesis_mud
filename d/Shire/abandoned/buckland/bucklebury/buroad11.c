inherit "/d/Shire/eastroad/villagemaker";
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/macros.h"

#define EXIT1 BB_DIR + "buroad10","north",0,1
#define EXIT2 BB_DIR + "inn","south",0,1
#define EXIT3 BB_DIR + "buroad13","west",0,1


void
create_room()
{
    areaname  = "Bucklebury";
    land      = "Buckland";
    areatype  = 2;
    areadesc  = "dirt road";

    extraline = "You are at the southern end of the main road in "+
    "Bucklebury.  The road goes to the north, or you can enter the inn "+
    "south of you that looks to be one of the more frequently visited "+
    "places here.  A smaller path goes to your west, towards a residential "+
    "part of Bucklebury.";

    add_item(({"road","dirt road"}),"The dirt road is the main one in "+
      "Bucklebury.\n");

    add_exit(EXIT1);
    add_exit(EXIT2);
    add_exit(EXIT3);


    make_the_room();
}


