inherit "/d/Gondor/rohan/horn/helmsdeep.c";

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

void create_helmsdeep_room()
{
    set_short_desc("A bend in the road");
    set_extra_long("A bend in the road before the Hornburg. A path leads "+
    "south to Helm's Wall. The road bends west to the Hornburg and north "+
    "to Helm's Dike. ");

    ROAD;
    STREAM;
    GULLY;
    CLIFFS;
    GORGE;
    H_WALL;
    DIKE;
    PATH;
    MOUNTAINS;
    add_item(({ "keep", "hornburg", "rock", "spur" }), BSN(
    "There is a heel of rock thrusting outward from the northern cliff. "+
    "There upon its spur stands a keep with high walls, and within "+
    "them is a lofty tower."));
    add_item("walls", BSN(
    "The walls look like they spring from the very rock "+
    "upon which they stand."));
    add_item("tower", "Above the walls the tower stands secure.\n");

    add_exit(ROH_DIR + "horn/gorge/road1"   , "north", 0);
    add_exit(ROH_DIR + "horn/gorge/causeway", "west" , 0);
    add_exit(ROH_DIR + "horn/gorge/ofield1" , "south", 0, 2);
}
