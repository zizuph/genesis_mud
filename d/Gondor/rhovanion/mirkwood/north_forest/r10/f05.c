#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(4);
    set_spider_nest_chance(49);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r09/f06",
        "southwest" : "r09/f04",
        "south" : "r09/f05",
        "northwest" : "r11/f04",
        "east" : "r10/f06",
        "north" : "r11/f05",
        "northeast" : "r11/f06",
        "west" : "r10/f04",
    ]));
    
}
