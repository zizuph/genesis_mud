#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(20);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r02/f11",
        "southwest" : "r02/f09",
        "south" : "r02/f10",
        "northwest" : "r04/f09",
        "east" : "r03/f11",
        "north" : "r04/f10",
        "northeast" : "r04/f11",
        "west" : "r03/f09",
    ]));
    
}
