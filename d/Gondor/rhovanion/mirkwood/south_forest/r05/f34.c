#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(14);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r06/f35",
        "southwest" : "r06/f33",
        "south" : "r06/f34",
        "northwest" : "r04/f33",
        "east" : "r05/f35",
        "north" : "r04/f34",
        "northeast" : "r04/f35",
        "west" : "r05/f33",
    ]));
    
}
