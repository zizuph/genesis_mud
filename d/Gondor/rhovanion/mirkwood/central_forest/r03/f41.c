#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(57);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r02/f42",
        "southwest" : "r02/f40",
        "south" : "r02/f41",
        "northwest" : "r04/f40",
        "east" : "r03/f42",
        "north" : "r04/f41",
        "northeast" : "r04/f42",
        "west" : "r03/f40",
    ]));
    
}
