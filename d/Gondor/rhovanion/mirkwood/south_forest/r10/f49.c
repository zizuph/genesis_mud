#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r11/f50",
        "southwest" : "r11/f48",
        "south" : "r11/f49",
        "northwest" : "r09/f48",
        "east" : "r10/f50",
        "north" : "r09/f49",
        "northeast" : "r09/f50",
        "west" : "r10/f48",
    ]));
    
}
