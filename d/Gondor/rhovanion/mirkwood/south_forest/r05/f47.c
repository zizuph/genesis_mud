#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(38);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r06/f48",
        "southwest" : "r06/f46",
        "south" : "r06/f47",
        "northwest" : "r04/f46",
        "east" : "r05/f48",
        "north" : "r04/f47",
        "northeast" : "r04/f48",
        "west" : "r05/f46",
    ]));
    
}
