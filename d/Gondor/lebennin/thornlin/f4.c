#include "/d/Gondor/defs.h"
inherit (THORN_DIR + "out_door_master.c");

#include "locals.h"
#include <language.h>


void
create_area_room()
{
    set_areatype(3);
    set_areadesc("dirty");
    set_whereis("near");
    set_cityname("Thornlin");
    set_crop("wheat");
    set_areaname("Lossarnach");
    set_land("Gondor");
    set_extraline("All around there are fields with different kinds of crops, "+
      "on this field there is growing "+crop+". To the north and "+
      "northwest lies a well travelled road.");

    add_exit(THORN_DIR + "f3","west",0,2);
    add_exit(THORN_DIR + "r3","northwest",0,2);
    add_exit(THORN_DIR + "r4","north",0,2);
    add_exit(THORN_DIR + "f1","northeast",0,2);
    add_exit(THORN_DIR + "f5","east",0,2);

}

