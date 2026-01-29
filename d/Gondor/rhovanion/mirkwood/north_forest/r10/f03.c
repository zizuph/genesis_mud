#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(26);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r09/f04",
        "southwest" : "r09/f02",
        "south" : "r09/f03",
        "northwest" : "r11/f02",
        "east" : "r10/f04",
        "north" : "r11/f03",
        "northeast" : "r11/f04",
        "west" : "r10/f02",
    ]));
    
}
