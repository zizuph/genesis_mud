#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(38);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r06/f44",
        "southwest" : "r06/f42",
        "south" : "r06/f43",
        "northwest" : "r08/f42",
        "east" : "r07/f44",
        "north" : "r08/f43",
        "northeast" : "r08/f44",
        "west" : "r07/f42",
    ]));
    
}
