#include "/d/Gondor/defs.h"
inherit (THORN_DIR + "out_door_master.c");

#include "locals.h"
#include <language.h>

void
create_area_room()
{
    set_areatype(3);
    set_areadesc("fine");
    set_whereis("in");
    set_cityname("Thornlin");
    set_crop("weed");
    set_areaname("Lossarnach");
    set_land("Gondor");
    set_extraline("There are fields to your east. North the road is "+
      "running into the village. West of here you see "+
      "the village.");

    add_item("road","It seems the road cuts its self trough the fields.\n");

    add_exit(THORN_DIR + "r3","north",0,2);
    add_exit(THORN_DIR + "f4","east",0,2);
}

