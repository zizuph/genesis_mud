#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(31);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r07/f43",
        "southwest" : "r07/f41",
        "south" : "r07/f42",
        "northwest" : "r09/f41",
        "east" : "r08/f43",
        "north" : "r09/f42",
        "northeast" : "r09/f43",
        "west" : "r08/f41",
    ]));
    
}
