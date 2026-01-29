#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "northwest" : MIRKWOOD_OLDROAD_DIR + "r02",
        "north" : MIRKWOOD_OLDROAD_DIR + "r03",
        "northeast" : MIRKWOOD_OLDROAD_DIR + "r04",

        "southeast" : "r01/p09-r01",
        "southwest" : "r01/f07",
        "south" : "r01/f08",
        "east" : "r00/p09-r00",
        "west" : "r00/f07",
    ]));
    
}
