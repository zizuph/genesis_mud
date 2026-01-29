#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(71);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r02/f25",
        "southwest" : "r02/f23",
        "south" : "r02/f24",
        "northwest" : "r04/f23",
        "east" : "r03/f25",
        "north" : "r04/f24",
        "northeast" : "r04/f25",
        "west" : "r03/f23",
    ]));
    
}
