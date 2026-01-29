#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(4);
    set_spider_nest_chance(43);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r07/f42",
        "southwest" : "r07/f40",
        "south" : "r07/f41",
        "northwest" : "r09/f40",
        "east" : "r08/f42",
        "north" : "r09/f41",
        "northeast" : "r09/f42",
        "west" : "r08/f40",
    ]));
    
}
