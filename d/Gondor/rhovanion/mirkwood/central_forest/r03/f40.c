#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(55);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r02/f41",
        "southwest" : "r02/f39",
        "south" : "r02/f40",
        "northwest" : "r04/f39",
        "east" : "r03/f41",
        "north" : "r04/f40",
        "northeast" : "r04/f41",
        "west" : "r03/f39",
    ]));
    
}
