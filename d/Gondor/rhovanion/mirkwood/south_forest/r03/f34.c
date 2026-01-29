#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r04/f35",
        "southwest" : "r04/f33",
        "south" : "r04/f34",
        "northwest" : "r02/f33",
        "east" : "r03/f35",
        "north" : "r02/f34",
        "northeast" : "r02/f35",
        "west" : "r03/f33",
    ]));
    
}
