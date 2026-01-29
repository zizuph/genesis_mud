#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r05/f35",
        "southwest" : "r05/f33",
        "south" : "r05/f34",
        "northwest" : "r07/f33",
        "east" : "r06/f35",
        "north" : "r07/f34",
        "northeast" : "r07/f35",
        "west" : "r06/f33",
    ]));
    
}
