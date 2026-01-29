#include "/d/Gondor/defs.h"
inherit (THORN_DIR + "out_door_master");

#include "locals.h"
#include <language.h>

void
create_area_room()
{
    set_areatype(3);
    set_areadesc("fertile");
    set_whereis("near");
    set_cityname("Thornlin");
    set_crop("barley");
    set_areaname("Lossarnach");
    set_land("Gondor");
    set_extraline("All around there are fields with different kinds of "+
      "crops. On this field, "+crop+" is growing. To the north, there "+
      "is a road leading from the southwest to the east.");

    add_item("road", "The road is running through the fields "
      + "from the southwest to the east just north of this field.\n");

    add_exit(THORN_DIR + "f5","south",0,2);
    add_exit(THORN_DIR + "f4","southwest",0,2);
    add_exit(THORN_DIR + "f2","east",0,2);

}

