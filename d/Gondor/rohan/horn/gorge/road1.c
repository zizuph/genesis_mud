inherit "/d/Gondor/rohan/horn/helmsdeep.c";

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

void create_helmsdeep_room()
{
    set_short_desc("A road south of breach in Dike");
    set_extra_long("On a road close to the Deeping-stream. There is a heel "+
    "of rock thrusting outward by the northern cliff. Upon "+
    "its spur stands a keep with high walls, and within "+
    "them a lofty tower. Another wall goes from the keep to "+
    "the southern cliff, barring passage to the gorge behind. "+
    "The road slopes up to the south towards the keep. ");

    KEEP;
    H_WALL;
    ROAD;
    STREAM;
    GULLY;
    ROCK;
    CLIFFS;
    GORGE;
    MOUNTAINS;
    add_item(({ "keep", "hornburg", "rock", "spur" }), BSN(
    "There is a heel of rock thrusting outward from the northern cliff. "+
    "There upon its spur stands a keep with high walls, and within "+
    "them is a lofty tower."));
    add_item("walls", BSN(
    "The walls look like they spring from the very rock "+
    "upon which they stand."));
    add_item("tower", "Above the walls the tower stands secure.\n");

    add_exit(ROH_DIR+"horn/gorge/breach","northeast",0);
    add_exit(ROH_DIR+"horn/gorge/croad","south",0,2);
}
