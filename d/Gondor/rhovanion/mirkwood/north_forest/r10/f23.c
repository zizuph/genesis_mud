#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(29);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r09/f24",
        "southwest" : "r09/f22",
        "south" : "r09/f23",
        "northwest" : "r11/f22",
        "east" : "r10/f24",
        "north" : "r11/f23",
        "northeast" : "r11/f24",
        "west" : "r10/f22",
    ]));
    
}
