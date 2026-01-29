#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(23);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r02/f12",
        "southwest" : "r02/f10",
        "south" : "r02/f11",
        "northwest" : "r04/f10",
        "east" : "r03/f12",
        "north" : "r04/f11",
        "northeast" : "r04/f12",
        "west" : "r03/f10",
    ]));
    
}
