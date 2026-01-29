#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(11);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r11/f49",
        "southwest" : "r11/f47",
        "south" : "r11/f48",
        "northwest" : "r09/f47",
        "east" : "r10/f49",
        "north" : "r09/f48",
        "northeast" : "r09/f49",
        "west" : "r10/f47",
    ]));
    
}
