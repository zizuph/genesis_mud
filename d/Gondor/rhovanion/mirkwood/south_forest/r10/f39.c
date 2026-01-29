#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(14);

    set_distance_to_edge(10);
    add_mirkwood_exits(([
        "southeast" : "r11/f40",
        "southwest" : "r11/f38",
        "south" : "r11/f39",
        "northwest" : "r09/f38",
        "east" : "r10/f40",
        "north" : "r09/f39",
        "northeast" : "r09/f40",
        "west" : "r10/f38",
    ]));
    
}
