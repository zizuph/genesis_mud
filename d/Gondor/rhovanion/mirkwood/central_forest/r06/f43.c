#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(68);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r05/f44",
        "southwest" : "r05/f42",
        "south" : "r05/f43",
        "northwest" : "r07/f42",
        "east" : "r06/f44",
        "north" : "r07/f43",
        "northeast" : "r07/f44",
        "west" : "r06/f42",
    ]));
    
}
