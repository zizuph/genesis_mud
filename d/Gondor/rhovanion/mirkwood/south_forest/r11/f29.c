#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(11);
    add_mirkwood_exits(([
        "southeast" : "r12/f30",
        "southwest" : "r12/f28",
        "south" : "r12/f29",
        "northwest" : "r10/f28",
        "east" : "r11/f30",
        "north" : "r10/f29",
        "northeast" : "r10/f30",
        "west" : "r11/f28",
    ]));
    
}
