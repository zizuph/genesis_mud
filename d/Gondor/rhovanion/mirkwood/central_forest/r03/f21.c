#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(50);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r02/f22",
        "southwest" : "r02/f20",
        "south" : "r02/f21",
        "northwest" : "r04/f20",
        "east" : "r03/f22",
        "north" : "r04/f21",
        "northeast" : "r04/f22",
        "west" : "r03/f20",
    ]));
    
}
