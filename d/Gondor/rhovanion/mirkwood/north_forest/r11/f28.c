#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(15);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r10/f29",
        "southwest" : "r10/f27",
        "south" : "r10/f28",
        "northwest" : "r12/f27",
        "east" : "r11/f29",
        "north" : "r12/f28",
        "northeast" : "r12/f29",
        "west" : "r11/f27",
    ]));
    
}
