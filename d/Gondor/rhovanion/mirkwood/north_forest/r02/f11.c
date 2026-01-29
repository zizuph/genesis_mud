#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(13);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r01/f12",
        "southwest" : "r01/f10",
        "south" : "r01/f11",
        "northwest" : "r03/f10",
        "east" : "r02/f12",
        "north" : "r03/f11",
        "northeast" : "r03/f12",
        "west" : "r02/f10",
    ]));
    
}
