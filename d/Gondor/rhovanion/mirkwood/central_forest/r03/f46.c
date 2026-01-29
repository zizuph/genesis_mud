#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(15);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r02/f47",
        "southwest" : "r02/f45",
        "south" : "r02/f46",
        "northwest" : "r04/f45",
        "east" : "r03/f47",
        "north" : "r04/f46",
        "northeast" : "r04/f47",
        "west" : "r03/f45",
    ]));
    
}
