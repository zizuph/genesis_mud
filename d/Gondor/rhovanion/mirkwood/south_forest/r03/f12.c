#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r04/f13",
        "southwest" : "r04/f11",
        "south" : "r04/f12",
        "northwest" : "r02/f11",
        "east" : "r03/f13",
        "north" : "r02/f12",
        "northeast" : "r02/f13",
        "west" : "r03/f11",
    ]));
    
}
