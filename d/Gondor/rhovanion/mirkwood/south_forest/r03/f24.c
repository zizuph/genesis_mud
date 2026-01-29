#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r04/f25",
        "southwest" : "r04/f23",
        "south" : "r04/f24",
        "northwest" : "r02/f23",
        "east" : "r03/f25",
        "north" : "r02/f24",
        "northeast" : "r02/f25",
        "west" : "r03/f23",
    ]));
    
}
