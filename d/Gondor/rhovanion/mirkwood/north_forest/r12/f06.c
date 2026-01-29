#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(57);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r11/f07",
        "southwest" : "r11/f05",
        "south" : "r11/f06",
        "northwest" : "r13/f05",
        "east" : "r12/f07",
        "north" : "r13/f06",
        "northeast" : "r13/f07",
        "west" : "r12/f05",
    ]));
    
}
