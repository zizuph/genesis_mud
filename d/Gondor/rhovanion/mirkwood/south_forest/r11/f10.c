#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r12/f11",
        "southwest" : "r12/f09",
        "south" : "r12/f10",
        "northwest" : "r10/f09",
        "east" : "r11/f11",
        "north" : "r10/f10",
        "northeast" : "r10/f11",
        "west" : "/d/Gondor/rhovanion/mirkwood/woodsmen/gairent1",
    ]));
    
}
