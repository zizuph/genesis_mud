#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(25);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r10/f24",
        "southwest" : "r10/f22",
        "south" : "r10/f23",
        "northwest" : "r12/f22",
        "east" : "r11/f24",
        "north" : "r12/f23",
        "northeast" : "r12/f24",
        "west" : "r11/f22",
    ]));
    
}
