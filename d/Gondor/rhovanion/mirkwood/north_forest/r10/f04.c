#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(36);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r09/f05",
        "southwest" : "r09/f03",
        "south" : "r09/f04",
        "northwest" : "r11/f03",
        "east" : "r10/f05",
        "north" : "r11/f04",
        "northeast" : "r11/f05",
        "west" : "r10/f03",
    ]));
    
}
