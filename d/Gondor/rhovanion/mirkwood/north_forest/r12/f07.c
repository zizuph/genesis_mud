#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(80);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r11/f08",
        "southwest" : "r11/f06",
        "south" : "r11/f07",
        "northwest" : "r13/f06",
        "east" : "r12/f08",
        "north" : "r13/f07",
        "northeast" : "r13/f08",
        "west" : "r12/f06",
    ]));
    
}
