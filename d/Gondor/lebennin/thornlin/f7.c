#include "/d/Gondor/defs.h"
inherit (THORN_DIR + "out_door_master.c");

#include "locals.h"

void
create_area_room()
{
    set_areatype(3);
    set_areadesc("poor");
    set_whereis("near");
    set_cityname("Thornlin");
    set_crop("rye");
    set_areaname("Lossarnach");
    set_land("Gondor");
    set_extraline("You see fields all around you. Not far to the north "+
      "are the foothills of the White Mountains. South of here "+
      "a road cuts through the fields going east-west.");

    add_item("road","It seems the road cuts its course through the fields "+
      "like a river trough a land.\n");

    add_mountains();
    add_exit(THORN_DIR + "r6","south",0,2);

}

