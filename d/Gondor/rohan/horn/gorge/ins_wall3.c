inherit "/d/Gondor/rohan/horn/helmsdeep.c";

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

void create_helmsdeep_room()
{
    set_short_desc("A field inside Helm's wall");
    set_extra_long("A field inside the wall. The wall runs from "+
    "southeast to northwest. A path follows the wall, and "+
    "a stairway goes up to the middle section of the wall. ");

    FIELD;
    GRASS;
    PATH;
    KEEP;
    STAIRS;
    GORGE;
    CLIFFS;
    MOUNTAINS;
    add_item("wall","Helm's wall was built long ago by the sea-kings "+
    "from Gondor.\n");

    add_exit(ROH_DIR+"horn/gorge/ins_wall2","northwest",0);
    add_exit(ROH_DIR+"horn/gorge/ins_wall4","southeast",0);
    add_exit(ROH_DIR+"horn/on_walls/h_wall3","up",0,2);
}

