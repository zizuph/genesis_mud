#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(33);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r09/f23",
        "southwest" : "r09/f21",
        "south" : "r09/f22",
        "northwest" : "r11/f21",
        "east" : "r10/f23",
        "north" : "r11/f22",
        "northeast" : "r11/f23",
        "west" : "r10/f21",
    ]));
    
}
