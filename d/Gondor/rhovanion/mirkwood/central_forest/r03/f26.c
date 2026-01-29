#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(78);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r02/f27",
        "southwest" : "r02/f25",
        "south" : "r02/f26",
        "northwest" : "r04/f25",
        "east" : "r03/f27",
        "north" : "r04/f26",
        "northeast" : "r04/f27",
        "west" : "r03/f25",
    ]));
    
}
