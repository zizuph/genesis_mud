#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(64);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r06/f42",
        "southwest" : "r06/m40",
        "south" : "r06/m41",
        "northwest" : "r08/f40",
        "east" : "r07/f42",
        "north" : "r08/f41",
        "northeast" : "r08/f42",
        "west" : "r07/f40",
    ]));
    
}
