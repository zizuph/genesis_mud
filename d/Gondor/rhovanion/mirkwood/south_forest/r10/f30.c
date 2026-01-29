#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(14);

    set_distance_to_edge(10);
    add_mirkwood_exits(([
        "southeast" : "r11/f31",
        "southwest" : "r11/f29",
        "south" : "r11/f30",
        "northwest" : "r09/f29",
        "east" : "r10/f31",
        "north" : "r09/f30",
        "northeast" : "r09/f31",
        "west" : "r10/f29",
    ]));
    
}
