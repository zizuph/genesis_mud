#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(12);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r04/f28",
        "southwest" : "r04/f26",
        "south" : "r04/f27",
        "northwest" : "r02/f26",
        "east" : "r03/f28",
        "north" : "r02/f27",
        "northeast" : "r02/f28",
        "west" : "r03/f26",
    ]));
    
}
