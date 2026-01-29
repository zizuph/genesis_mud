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
    set_cityname("Thornlin");
    set_areaname("Lossarnach");
    set_land("Gondor");

    set_extraline("The road comes running from the west and continues northeast."+
      " South of here you see fields.");

    add_item("fields", "The fields look nice and fertile.\n");

    add_exit(THORN_DIR + "r3","west",0,1);
    add_exit(THORN_DIR + "r5","northeast",0,1);
    add_exit(THORN_DIR + "f4","south",0,1);

}
