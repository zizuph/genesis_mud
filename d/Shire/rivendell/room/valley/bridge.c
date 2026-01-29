/*
 * Path to Rivendell
 * By Finwe, November 1997
 */
 
#pragma strict_types
 
#include "local.h"
 
inherit VALLEY_BASE;
 
void
create_valley_room()
{
 
    set_extraline("You stand on an arched stone bridge that " +
        "spans a finger of the river Bruinen. The river runs " +
        "along the southern edge of the House, dividing the " +
        "valley in two.");
 
    add_item("stones",
        "The stones of the bridge are large blocks of grey " +
        "stone. They are smooth and fitted tightly " +
        "together, forming a strong structure that spans the " +
        "river.\n");
    add_item (({"bridge", "stone bridge"}),
        "The bridge gracefully arches over the river. It is " +
        "wide enough for ten elves to walk abreast and " +
        "constructed of smooth gray stones.\n");
    add_item(({"river", "river bruinen", "bruinen", "river Bruinen"}),
        "The river rushes under the bridge as it heads west out " +
        "of the mountains. To the west you see mist rising up " +
        "where the river plunges over a waterfall.\n");
    add_item(({"carvings", "bridge carvings", "various carvings"}),
        "The carvings in the bridge are of trees, stars, " +
        "battles, and noble elves\n");
    add_item(({"house", "last homely house", "house of elrond", 
            "last homely house of the east", 
            "last homely house east of the sea"}),        
        "The house stands in the distance in the center of the " +
        "valley. Details can't be made out from this distance " +
        "other than it looks large.\n");
    add_item(({"waterfall", "falls"}),
        "Gazing west, a little ways down the river, you see a " +
        "great waterfall. It plunges over a cleft of rock and " +
        "falls into the river below. Mists rise from the " +
        "boiling, churning water below the falls. The " +
        "thundering sound of the water echos throughout the area.\n");
 
    add_exit(VALLEY_DIR + "v_path01", "east");
    add_exit(VALLEY_DIR + "path03",  "west");
 
}
 
string short_desc()
{
    return "A bridge in the valley of Imladris";
}
