#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r04/f40",
        "southwest" : "r04/f38",
        "south" : "r04/f39",
        "northwest" : "r02/f38",
        "east" : "r03/f40",
        "north" : "r02/f39",
        "northeast" : "r02/f40",
        "west" : "r03/f38",
    ]));
    
}
