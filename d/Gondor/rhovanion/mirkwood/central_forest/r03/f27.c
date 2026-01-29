#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(78);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r02/f28",
        "southwest" : "r02/f26",
        "south" : "r02/f27",
        "northwest" : "r04/f26",
        "east" : "r03/f28",
        "north" : "r04/f27",
        "northeast" : "r04/f28",
        "west" : "r03/f26",
    ]));
    
}
