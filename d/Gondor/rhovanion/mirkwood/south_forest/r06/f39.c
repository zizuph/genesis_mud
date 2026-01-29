#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(67);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r07/f40",
        "southwest" : "r07/f38",
        "south" : "r07/f39",
        "northwest" : "r05/f38",
        "east" : "r06/f40",
        "north" : "r05/f39",
        "northeast" : "r05/f40",
        "west" : "r06/f38",
    ]));
    
}
