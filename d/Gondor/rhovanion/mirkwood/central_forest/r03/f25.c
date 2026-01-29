#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(76);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r02/f26",
        "southwest" : "r02/f24",
        "south" : "r02/f25",
        "northwest" : "r04/f24",
        "east" : "r03/f26",
        "north" : "r04/f25",
        "northeast" : "r04/f26",
        "west" : "r03/f24",
    ]));
    
}
