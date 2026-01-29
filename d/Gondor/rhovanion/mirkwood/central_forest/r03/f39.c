#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(89);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r02/f40",
        "southwest" : "r02/f38",
        "south" : "r02/f39",
        "northwest" : "r04/m38",
        "east" : "r03/f40",
        "north" : "r04/f39",
        "northeast" : "r04/f40",
        "west" : "r03/f38",
    ]));
    
}
