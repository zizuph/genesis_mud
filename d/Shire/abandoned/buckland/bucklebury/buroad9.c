inherit "/d/Shire/eastroad/villagemaker";
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/macros.h"

#define EXIT1 BB_DIR + "buroad8","northwest",0,1
#define EXIT2 BB_DIR + "buroad10","south",0,1
#define EXIT3 BB_DIR + "bank","east",0,1
#define EXIT4 BB_DIR + "post","west",0,1

void
create_room()
{
    areaname  = "Bucklebury";
    land      = "Buckland";
    areatype  = 2;
    areadesc  = "dirt road";

    extraline = "This is part of the heart of Bucklebury.  To the west "+
    "is the post office and to the east is a bank.  The road leads to "+
    "the northwest, and even further in to the heart southwards.";


    add_item(({"road","dirt road"}),"This dirt road is the main road of "+
      "Bucklebury.\n");

    add_exit(EXIT1);
    add_exit(EXIT2);
    add_exit(EXIT3);
    add_exit(EXIT4);


    make_the_room();
}


