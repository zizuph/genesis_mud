#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(22);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r02/f14",
        "southwest" : "r02/f12",
        "south" : "r02/f13",
        "northwest" : "r04/f12",
        "east" : "r03/f14",
        "north" : "r04/f13",
        "northeast" : "r04/f14",
        "west" : "r03/f12",
    ]));
    
}
