#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(26);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r02/f39",
        "southwest" : "r02/f37",
        "south" : "r02/f38",
        "northwest" : "r00/f37",
        "east" : "r01/f39",
        "north" : "r00/f38",
        "northeast" : "r00/f39",
        "west" : "r01/f37",
    ]));
    
}
