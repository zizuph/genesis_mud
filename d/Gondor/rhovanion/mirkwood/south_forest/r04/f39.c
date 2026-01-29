#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(15);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r05/f40",
        "southwest" : "r05/f38",
        "south" : "r05/f39",
        "northwest" : "r03/f38",
        "east" : "r04/f40",
        "north" : "r03/f39",
        "northeast" : "r03/f40",
        "west" : "r04/f38",
    ]));
    
}
