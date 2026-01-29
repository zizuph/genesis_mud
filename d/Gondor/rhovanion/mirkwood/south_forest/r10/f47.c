#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r11/f48",
        "southwest" : "r11/f46",
        "south" : "r11/f47",
        "northwest" : "r09/f46",
        "east" : "r10/f48",
        "north" : "r09/f47",
        "northeast" : "r09/f48",
        "west" : "r10/f46",
    ]));
    
}
