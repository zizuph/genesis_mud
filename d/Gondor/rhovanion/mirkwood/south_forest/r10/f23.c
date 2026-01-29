#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(13);

    set_distance_to_edge(10);
    add_mirkwood_exits(([
        "southeast" : "r11/f24",
        "southwest" : "r11/f22",
        "south" : "r11/f23",
        "northwest" : "r09/f22",
        "east" : "r10/f24",
        "north" : "r09/f23",
        "northeast" : "r09/f24",
        "west" : "r10/f22",
    ]));
    
}
