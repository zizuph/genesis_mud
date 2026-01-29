#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(51);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r02/f23",
        "southwest" : "r02/f21",
        "south" : "r02/f22",
        "northwest" : "r04/f21",
        "east" : "r03/f23",
        "north" : "r04/f22",
        "northeast" : "r04/f23",
        "west" : "r03/f21",
    ]));
    
}
