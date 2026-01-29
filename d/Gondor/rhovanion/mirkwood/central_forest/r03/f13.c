#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(11);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r02/f14",
        "southwest" : "r02/f12",
        "south" : "r02/f13",
        "northwest" : "r04/f12",
        "east" : "r03/f14",
        "north" : "r04/f13",
        "northeast" : "r04/f14",
        "west" : "r03/f12",
    ]));
    
}
