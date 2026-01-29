#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(87);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r10/f07",
        "southwest" : "r10/f05",
        "south" : "r10/f06",
        "northwest" : "r12/f05",
        "east" : "r11/f07",
        "north" : "r12/f06",
        "northeast" : "r12/f07",
        "west" : "r11/f05",
    ]));
    
}
