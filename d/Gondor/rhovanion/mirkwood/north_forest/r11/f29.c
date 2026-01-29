#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(11);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r10/f30",
        "southwest" : "r10/f28",
        "south" : "r10/f29",
        "northwest" : "r12/f28",
        "east" : "r11/f30",
        "north" : "r12/f29",
        "northeast" : "r12/f30",
        "west" : "r11/f28",
    ]));
    
}
