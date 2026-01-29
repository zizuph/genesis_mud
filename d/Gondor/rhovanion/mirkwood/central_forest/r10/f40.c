#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(11);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r09/f41",
        "southwest" : "r09/f39",
        "south" : "r09/f40",
        "northwest" : "r11/f39",
        "east" : "r10/f41",
        "north" : "r11/f40",
        "northeast" : "r11/f41",
        "west" : "r10/f39",
    ]));
    
}
