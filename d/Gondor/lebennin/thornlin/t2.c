#include "/d/Gondor/defs.h"
inherit (THORN_DIR + "out_door_master.c");

#include "locals.h"
#include <language.h>

void
create_area_room()
{
    set_areatype(2);
    set_areadesc("old forest");
    set_whereis("in");
    set_cityname("Thornlin");
    set_treetype("beech");
    set_grass("sappy");
    set_areaname("Lossarnach");
    set_land("Gondor");
    set_extraline("A trail makes a smooth curve to the east. West the "
      +"forest seems thick. To the east the forest seems to grow "
      +"thinner.");

    add_item("trail","The trail is just visible.\n");

    set_noshow_obvious(1); 
    add_exit(THORN_DIR + "open_field","east",0,2);
    add_exit(THORN_DIR + "t1","south",0,2);
}

