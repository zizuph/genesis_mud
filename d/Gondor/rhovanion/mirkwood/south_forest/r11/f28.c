#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(11);
    add_mirkwood_exits(([
        "southeast" : "r12/f29",
        "southwest" : "r12/f27",
        "south" : "r12/f28",
        "northwest" : "r10/f27",
        "east" : "r11/f29",
        "north" : "r10/f28",
        "northeast" : "r10/f29",
        "west" : "r11/f27",
    ]));
    
}
