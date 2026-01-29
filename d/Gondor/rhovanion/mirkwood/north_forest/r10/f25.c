#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(22);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r09/f26",
        "southwest" : "r09/f24",
        "south" : "r09/f25",
        "northwest" : "r11/f24",
        "east" : "r10/f26",
        "north" : "r11/f25",
        "northeast" : "r11/f26",
        "west" : "r10/f24",
    ]));
    
}
