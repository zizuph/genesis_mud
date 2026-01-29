#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(13);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r07/f48",
        "southwest" : "r07/f46",
        "south" : "r07/f47",
        "northwest" : "r05/f46",
        "east" : "r06/f48",
        "north" : "r05/f47",
        "northeast" : "r05/f48",
        "west" : "r06/f46",
    ]));
    
}
