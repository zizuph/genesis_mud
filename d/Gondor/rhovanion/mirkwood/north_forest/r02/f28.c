#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest_edge";

void create_mirkwood_north_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southwest" : MIRKWOOD_ELFPATH_DIR + "p27",
        "south"     : MIRKWOOD_ELFPATH_DIR + "p28",
        "southeast" : MIRKWOOD_ELFPATH_DIR + "p29",

        "northwest" : "r03/f27",
        "east" : "r02/f29",
        "north" : "r03/f28",
        "northeast" : "r03/f29",
        "west" : "r02/f27",
    ]));
    
}
