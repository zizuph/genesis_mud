#include "/d/Gondor/defs.h"
inherit (THORN_DIR + "out_door_master.c");

#include <language.h>
#include <macros.h>
#include "locals.h"

void
create_area_room()
{
    set_areatype(4);
    set_areadesc("fine");
    set_whereis("in");
    set_cityname("Thornlin");
    set_areaname("Lossarnach");
    set_land("Gondor");
    set_extraline("This is the eastern part of a square in the centre "+
      "of "+cityname+", to the east you see fields. South of here "+
      "is a cosy looking log house with small chimney on the "+ 
      "roof. The road comes from the west and continues north.");

    add_item("road","The road runs trough the sqaure from the west and "+
      "and continues north.\n");
    add_item("square","The square seems to be surrounded by different "+
      "buildings and fields. \n");
    add_item(({"buildings","house","log house"}),"You see a log house "+
      "south of here.\n");
    add_item("chimney","There is a dark chimney on top of the log house, "+
      "if it is its natural colour or due to the smoke "+
      "rising from the chimney you are unable to guess.\n");


    add_exit(THORN_DIR + "r2b","north",0);
    add_exit(THORN_DIR + "r2c","west",0);
    add_exit(THORN_DIR + "house2","south",0,1);

}
