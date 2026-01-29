#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(38);

    set_distance_to_edge(11);
    add_mirkwood_exits(([
        "southeast" : "r12/f35",
        "southwest" : "r12/f33",
        "south" : "r12/f34",
        "northwest" : "r10/f33",
        "east" : "r11/f35",
        "north" : "r10/f34",
        "northeast" : "r10/f35",
        "west" : "r11/f33",
    ]));
    
}
