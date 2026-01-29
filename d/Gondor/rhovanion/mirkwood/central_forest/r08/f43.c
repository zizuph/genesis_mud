#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(15);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r07/f44",
        "southwest" : "r07/f42",
        "south" : "r07/f43",
        "northwest" : "r09/f42",
        "east" : "r08/f44",
        "north" : "r09/f43",
        "northeast" : "r09/f44",
        "west" : "r08/f42",
    ]));
    
}
