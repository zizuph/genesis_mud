inherit "/d/Shire/eastroad/villagemaker";
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/macros.h"

#define EXIT1 BB_DIR + "buroad6","west",0,1
#define EXIT2 BB_DIR + "buroad8","south",0,1

void
create_room()
{
    areaname  = "Bucklebury";
    land      = "Buckland";
    areatype  = 2;
    areadesc  = "dirt road";

    extraline = "You are standing just to the east of Brandy Hall.  There "+
    "are so many windows in this place that you figure it must be a full "+
    "time job to look after them alone. The road continues to the west "+
    "and to the south over the rolling hills that are around you.";

    add_item(({"window","windows"}),"Whoever has been cleaning all of "+
      "windows has been doing a very good job.  All of them are shiny, "+
      "without any smudges or fingerprints on them.\n");
    add_item(({"road","dirt road"}),"This is the main road that leads into "+
      "the main part of Bucklebury in one direction, and out of Bucklebury "+
      "in the other.\n");

    add_exit(EXIT1);
    add_exit(EXIT2);

    make_the_room();
}


