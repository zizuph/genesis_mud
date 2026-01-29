#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(12);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r09/f42",
        "southwest" : "r09/f40",
        "south" : "r09/f41",
        "northwest" : "r11/f40",
        "east" : "r10/f42",
        "north" : "r11/f41",
        "northeast" : "r11/f42",
        "west" : "r10/f40",
    ]));
    
}
