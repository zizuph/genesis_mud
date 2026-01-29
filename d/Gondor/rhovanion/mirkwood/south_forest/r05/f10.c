#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r06/f11",
        "northwest" : "/d/Gondor/rhovanion/mirkwood/woodsmen/weanting1",
        "southwest" : "r06/p09-r06",
        "south" : "r06/f10",
        "east" : "r05/f11",
        "north" : "r04/f10",
        "northeast" : "r04/f11",
        "west" : "r05/p09-r05",
    ]));
    
}
