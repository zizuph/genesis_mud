inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 BB_DIR + "burrow3_2","north",0,1
#define EXIT2 BB_DIR + "burrow3_4","east",0,1

void
create_room()
{

    areaname  = "Bucklebury";
    land      = "Buckland";
    roomtype  = 4;
    areatype  = "village";
    smialsize = "tiny";
    extraline = "In one corner of the kitchen is a table and some "+
    "chairs.  Perhaps that is why this burrow doesn't have a dining room. ";


    add_item("table","The table is clean and ready to be used.  The only "+
      "unusual thing about this table is that it is much smaller than "+
      "the tables most hobbits seem to use.\n");

    add_item(({"chair","chairs"}),"There are only a few chairs here, but "+
      "they all look very comfortable.\n");



    add_exit(EXIT1);
    add_exit(EXIT2);

    make_the_room();
}



