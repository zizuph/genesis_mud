#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southwest" : "r24/f30",
        "south" : "r24/f31",
        "northwest" : "r22/f30",
        "north" : "r22/f31",
        "northeast" : "r22/f32",
        "west" : "r23/f30",
    ]));
    
}
