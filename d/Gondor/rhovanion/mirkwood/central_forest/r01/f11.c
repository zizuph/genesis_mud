#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(13);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r00/f12",
        "southwest" : "r00/f10",
        "south" : "r00/f11",
        "northwest" : "r02/f10",
        "east" : "r01/f12",
        "north" : "r02/f11",
        "northeast" : "r02/f12",
        "west" : "r01/f10",
    ]));
    
}
