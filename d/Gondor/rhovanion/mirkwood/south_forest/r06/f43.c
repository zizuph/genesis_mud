#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r07/f44",
        "southwest" : "r07/f42",
        "south" : "r07/f43",
        "northwest" : "r05/f42",
        "east" : "r06/f44",
        "north" : "r05/f43",
        "northeast" : "r05/f44",
        "west" : "r06/f42",
    ]));
    
}
