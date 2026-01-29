#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r06/f14",
        "southwest" : "r06/f12",
        "south" : "r06/f13",
        "northwest" : "r04/f12",
        "east" : "r05/f14",
        "north" : "r04/f13",
        "northeast" : "r04/f14",
        "west" : "r05/f12",
    ]));
    
}
