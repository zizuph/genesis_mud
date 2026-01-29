#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(34);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r06/f40",
        "southwest" : "r06/f38",
        "south" : "r06/f39",
        "northwest" : "r04/f38",
        "east" : "r05/f40",
        "north" : "r04/f39",
        "northeast" : "r04/f40",
        "west" : "r05/f38",
    ]));
    
}
