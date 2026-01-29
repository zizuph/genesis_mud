#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(56);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r09/f09",
        "southwest" : "r09/f07",
        "south" : "r09/f08",
        "northwest" : "r11/f07",
        "east" : "r10/f09",
        "north" : "r11/f08",
        "northeast" : "r11/f09",
        "west" : "r10/f07",
    ]));
    
}
