inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 BB_DIR + "burrow2_1","east",0,1
#define EXIT2 BB_DIR + "burrow2_3","south",0,1


void
create_room()
{

    areaname  = "Bucklebury";
    land      = "Buckland";
    roomtype  = 3;
    areatype  = "village";
    smialsize = "tiny";

    extraline = "The room is quite cramped, due to the size of the table. "+
    "Judging by the size of this room, not many hobbits live here, nor do "+
    "they get a lot of company.";

    add_item("table","The dishes are laid out on the table, but there is no "+
      "food on it yet.\n");


    add_exit(EXIT1);
    add_exit(EXIT2);



    make_the_room();
}



