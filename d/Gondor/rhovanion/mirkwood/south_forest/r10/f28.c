#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(10);
    add_mirkwood_exits(([
        "southeast" : "r11/f29",
        "southwest" : "r11/f27",
        "south" : "r11/f28",
        "northwest" : "r09/f27",
        "east" : "r10/f29",
        "north" : "r09/f28",
        "northeast" : "r09/f29",
        "west" : "r10/f27",
    ]));
    
}
