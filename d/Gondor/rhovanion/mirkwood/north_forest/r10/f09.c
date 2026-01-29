#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(53);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r09/f10",
        "southwest" : "r09/f08",
        "south" : "r09/f09",
        "northwest" : "r11/f08",
        "east" : "r10/f10",
        "north" : "r11/f09",
        "northeast" : "r11/f10",
        "west" : "r10/f08",
    ]));
    
}
