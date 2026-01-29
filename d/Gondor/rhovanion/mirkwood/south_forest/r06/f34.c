#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(21);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r07/f35",
        "southwest" : "r07/f33",
        "south" : "r07/f34",
        "northwest" : "r05/f33",
        "east" : "r06/f35",
        "north" : "r05/f34",
        "northeast" : "r05/f35",
        "west" : "r06/f33",
    ]));
    
}
