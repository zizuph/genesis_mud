#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(14);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r07/f50",
        "southwest" : "r07/f48",
        "south" : "r07/f49",
        "northwest" : "r05/f48",
        "east" : "r06/f50",
        "north" : "r05/f49",
        "northeast" : "r05/f50",
        "west" : "r06/f48",
    ]));
    
}
