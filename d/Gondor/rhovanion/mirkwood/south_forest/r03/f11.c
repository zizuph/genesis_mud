#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r04/f12",
        "southwest" : "r04/f10",
        "south" : "r04/f11",
        "northwest" : "r02/f10",
        "east" : "r03/f12",
        "north" : "r02/f11",
        "northeast" : "r02/f12",
        "west" : "r03/f10",
    ]));
    
}
