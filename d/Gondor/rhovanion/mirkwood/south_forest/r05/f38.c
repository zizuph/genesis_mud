#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(66);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r06/f39",
        "southwest" : "r06/f37",
        "south" : "r06/f38",
        "northwest" : "r04/f37",
        "east" : "r05/f39",
        "north" : "r04/f38",
        "northeast" : "r04/f39",
        "west" : "r05/f37",
    ]));
    
}
