#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "northwest" : MIRKWOOD_OLDROAD_DIR + "r04",
        "north" : MIRKWOOD_OLDROAD_DIR + "r05",
        "northeast" : MIRKWOOD_OLDROAD_DIR + "r06",

        "southeast" : "r01/f11",
        "southwest" : "r01/p09-r01",
        "south" : "r01/f10",
        "east" : "r00/f11",
        "west" : "r00/p09-r00",
    ]));
    
}
