inherit "/d/Gondor/rohan/horn/helmsdeep.c";

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

void create_helmsdeep_room()
{
    set_short_desc("A causeway across the Deeping-stream");
    set_extra_long("A causeway across the Deeping-stream. To the "+
    "west, a ramp leads up to the Hornburg; to the east, the road goes to "+
    "the Dike. Beyond the causeway to the northwest is an open field. ");

    add_item("stream","The Deeping-stream slopes gently down from the wall "+
    "to the dike.\n");
    add_item("causeway",
    "It looks safe to cross the stream on the causeway.\n");
    add_item(({ "ground", "track", "tracks", "footprints" }), 
    "You don't find any solid ground to look at.\n");
    add_item("ramp", "A steep ramp leads up to the keep.\n");
    FIELD;
    GRASS;
    KEEP;
    DIKE;
    ROAD;
    GORGE;
    CLIFFS;
    MOUNTAINS;

    add_exit(ROH_DIR + "horn/gorge/croad"  ,"east"     ,0);
    add_exit(ROH_DIR + "horn/gorge/ramp"   ,"west"     ,0);
    add_exit(ROH_DIR + "horn/gorge/ofield4","northwest",0);
}

