#include "/d/Gondor/defs.h"
inherit (THORN_DIR + "out_door_master.c");

#include "locals.h"
#include <language.h>

void
create_area_room()
{
    set_areatype(4);
    set_areadesc("well travelled");
    set_whereis("in");
    set_crop("barley");
    set_cityname("Thornlin");
    set_areaname("Lossarnach");
    set_land("Gondor");

    set_extraline("North of here you see fields covering the "+ 
      "lands like a"+
      " blanket, the main road continues southwest-east.");

    add_item(({"field","fields"}),"You see "+crop+" growing on the field "+ 
      "just north of here.\n");

    add_exit(THORN_DIR + "r4","southwest",0,1);
    add_exit(THORN_DIR + "r6","east",0,1);
    add_exit(THORN_DIR + "f6","north",0,2);

}
