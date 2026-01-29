#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(22);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r04/f14",
        "southwest" : "r04/f12",
        "south" : "r04/f13",
        "northwest" : "r06/f12",
        "east" : "r05/f14",
        "north" : "r06/f13",
        "northeast" : "r06/f14",
        "west" : "r05/f12",
    ]));
    
}
