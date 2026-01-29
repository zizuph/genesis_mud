#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r04/f22",
        "southwest" : "r04/f20",
        "south" : "r04/f21",
        "northwest" : "r02/f20",
        "east" : "r03/f22",
        "north" : "r02/f21",
        "northeast" : "r02/f22",
        "west" : "r03/f20",
    ]));
    
}
