#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(12);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r11/f42",
        "southwest" : "r11/f40",
        "south" : "r11/f41",
        "northwest" : "r09/f40",
        "east" : "r10/f42",
        "north" : "r09/f41",
        "northeast" : "r09/f42",
        "west" : "r10/f40",
    ]));
    
}
