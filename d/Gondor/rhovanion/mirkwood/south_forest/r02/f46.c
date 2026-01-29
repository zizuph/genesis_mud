#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(15);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r03/f47",
        "southwest" : "r03/f45",
        "south" : "r03/f46",
        "northwest" : "r01/f45",
        "east" : "r02/f47",
        "north" : "r01/f46",
        "northeast" : "r01/f47",
        "west" : "r02/f45",
    ]));
    
}
