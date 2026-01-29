#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(14);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "southwest" : MIRKWOOD_ELFPATH_DIR + "p26",
        "south"     : MIRKWOOD_ELFPATH_DIR + "p27",
        "southeast" : MIRKWOOD_ELFPATH_DIR + "p28",

        "northwest" : "r03/f26",
        "east" : "r02/f28",
        "north" : "r03/f27",
        "northeast" : "r03/f28",
        "west" : "r02/f26",
    ]));
    
}
