#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(15);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r04/f26",
        "southwest" : "r04/f24",
        "south" : "r04/f25",
        "northwest" : "r02/f24",
        "east" : "r03/f26",
        "north" : "r02/f25",
        "northeast" : "r02/f26",
        "west" : "r03/f24",
    ]));
    
}
