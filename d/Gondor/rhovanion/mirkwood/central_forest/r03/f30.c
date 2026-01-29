#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(89);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r02/f31",
        "southwest" : "r02/f29",
        "south" : "r02/f30",
        "northwest" : "r04/f29",
        "east" : "r03/f31",
        "north" : "r04/f30",
        "northeast" : "r04/f31",
        "west" : "r03/f29",
    ]));
    
}
