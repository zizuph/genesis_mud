#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r13/f11",
        "southwest" : "r13/f09",
        "south" : "r13/f10",
        "east" : "r12/f11",
        "north" : "r11/f10",
        "northwest" : "/d/Gondor/rhovanion/mirkwood/woodsmen/gairent1",
        "northeast" : "r11/f11",
        "west" : "r12/f09",
    ]));
    
}
