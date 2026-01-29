#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(15);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r06/f49",
        "southwest" : "r06/f47",
        "south" : "r06/f48",
        "northwest" : "r04/f47",
        "east" : "r05/f49",
        "north" : "r04/f48",
        "northeast" : "r04/f49",
        "west" : "r05/f47",
    ]));
    
}
