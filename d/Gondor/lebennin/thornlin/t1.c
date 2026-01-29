#include "/d/Gondor/defs.h"
inherit (THORN_DIR + "out_door_master.c");

#include "locals.h"
#include <language.h>

void
create_area_room()
{
    areatype = 2;
    areadesc = "forest";
    whereis ="in";
    cityname = "Thornlin";
    treetype = "beech";
    grass = "sappy";
    areaname = "Lossarnach";
    land = "Gondor";
    set_extraline("Trails are running into the forest from "
      + "the south and southwest. A single trail continues northward "
      + "while in the other directions the forest is impenetrable.");

    add_item("trail","The trail is just visible.\n");

    set_noshow_obvious(1); 
    add_exit(THORN_DIR + "t2","north",0,2);
    add_exit(THORN_DIR + "r3","south",0,2);
    add_exit(THORN_DIR + "r2b","southwest",0,2);
}

