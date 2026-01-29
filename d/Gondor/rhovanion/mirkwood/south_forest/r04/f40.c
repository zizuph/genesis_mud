#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(16);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r05/f41",
        "southwest" : "r05/f39",
        "south" : "r05/f40",
        "northwest" : "r03/f39",
        "east" : "r04/f41",
        "north" : "r03/f40",
        "northeast" : "r03/f41",
        "west" : "r04/f39",
    ]));
    
}
