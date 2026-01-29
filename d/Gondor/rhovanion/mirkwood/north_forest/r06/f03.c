#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(24);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r05/f04",
        "southwest" : "r05/f02",
        "south" : "r05/f03",
        "northwest" : "r07/f02",
        "east" : "r06/f04",
        "north" : "r07/f03",
        "northeast" : "r07/f04",
        "west" : "r06/f02",
    ]));
    
}
