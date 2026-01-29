#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(78);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r05/f43",
        "southwest" : "r05/f41",
        "south" : "r05/f42",
        "northwest" : "r07/f41",
        "east" : "r06/f43",
        "north" : "r07/f42",
        "northeast" : "r07/f43",
        "west" : "r06/m41",
    ]));
    
}
