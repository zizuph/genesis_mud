#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(13);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r11/f03",
        "southwest" : "r11/f01",
        "south" : "r11/f02",
        "northwest" : "r13/f01",
        "east" : "r12/f03",
        "north" : "r13/f02",
        "northeast" : "r13/f03",
        "west" : "r12/f01",
    ]));
    
}
