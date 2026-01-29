#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r05/f42",
        "southwest" : "r05/f40",
        "south" : "r05/f41",
        "northwest" : "r03/f40",
        "east" : "r04/f42",
        "north" : "r03/f41",
        "northeast" : "r03/f42",
        "west" : "r04/f40",
    ]));
    
}
